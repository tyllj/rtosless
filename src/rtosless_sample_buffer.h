#ifndef RTOSLESS_SAMPLE_BUFFER_H
#define RTOSLESS_SAMPLE_BUFFER_H

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "rtosless_hal.h"

#ifdef __cplusplus
extern "C" {
#endif

// ADC sample buffer optimized for uint16_t (12-bit ADC values)
typedef struct {
    uint16_t* buffer;
    volatile size_t head;
    volatile size_t tail;
    size_t capacity;
} rl_sample_buffer_t;

// Initialize sample buffer with external buffer array
static inline void rl_sample_buffer_init(rl_sample_buffer_t* buf, uint16_t* buffer_array, size_t capacity) {
    buf->buffer = buffer_array;
    buf->head = 0;
    buf->tail = 0;
    buf->capacity = capacity;
}

// Get buffer capacity
static inline size_t rl_sample_buffer_get_capacity(const rl_sample_buffer_t* buf) {
    return buf->capacity;
}

// Get current sample count
static inline size_t rl_sample_buffer_get_count(const rl_sample_buffer_t* buf) {
    bool ps = rl_enter_critical();
    size_t h = buf->head;
    size_t t = buf->tail;
    rl_exit_critical(ps);
    return (h >= t) ? (h - t) : (buf->capacity + h - t);
}

// Peek at sample n positions from tail (0 = oldest)
static inline uint16_t rl_sample_buffer_peek(const rl_sample_buffer_t* buf, size_t n) {
    bool ps = rl_enter_critical();
    
    size_t h = buf->head;
    size_t t = buf->tail;
    size_t count = (h >= t) ? (h - t) : (buf->capacity + h - t);
    
    if (n >= count) {
        rl_exit_critical(ps);
        return 0;
    }
    
    size_t index = (t + n) % buf->capacity;
    uint16_t sample = buf->buffer[index];
    
    rl_exit_critical(ps);
    return sample;
}

// Get average of last n samples (or all samples if n > count)
static inline uint16_t rl_sample_buffer_get_avg(const rl_sample_buffer_t* buf, size_t n) {
    size_t count = rl_sample_buffer_get_count(buf);
    if (count == 0) return 0;
    
    size_t samples = (n < count) ? n : count;
    if (samples > buf->capacity) samples = buf->capacity;
    
    uint32_t sum = 0;
    for (size_t i = 0; i < samples; ++i) {
        sum += rl_sample_buffer_peek(buf, i);
    }
    return sum / samples;
}

// Push new sample (overwrites oldest if buffer full)
static inline void rl_sample_buffer_push_back(rl_sample_buffer_t* buf, uint16_t sample) {
    bool ps = rl_enter_critical();
    
    buf->buffer[buf->head] = sample;
    size_t next_head = (buf->head + 1) % buf->capacity;
    
    if (next_head == buf->tail) {
        buf->tail = (buf->tail + 1) % buf->capacity;  // drop oldest
    }
    buf->head = next_head;
    
    rl_exit_critical(ps);
}

// Try to pop oldest sample
static inline bool rl_sample_buffer_try_pop(rl_sample_buffer_t* buf, uint16_t* out_sample) {
    bool ps = rl_enter_critical();
    if (buf->head == buf->tail) {
        rl_exit_critical(ps);
        return false;  // empty
    }
    *out_sample = buf->buffer[buf->tail];
    buf->tail = (buf->tail + 1) % buf->capacity;
    rl_exit_critical(ps);
    return true;
}

// Convenience macro for declaring buffer with static array
#define RL_SAMPLE_BUFFER_DECLARE(name, size) \
    static uint16_t name##_array[size]; \
    static rl_sample_buffer_t name = {name##_array, 0, 0, size}

#ifdef __cplusplus
}
#endif

#endif // RTOSLESS_SAMPLE_BUFFER_H
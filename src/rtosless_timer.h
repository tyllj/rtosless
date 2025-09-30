#ifndef RTOSLESS_TIMER_H
#define RTOSLESS_TIMER_H

#include <stdint.h>
#include "rtosless_events.h"

#define RL_TIMER_MAX_COUNT 16

// Bit masks for flags field
#define RL_TIMER_FLAG_TRIGGER_STATE_MASK 0x01  // bit 0
#define RL_TIMER_FLAG_RESOLUTION_MASK    0x02  // bit 1
#define RL_TIMER_FLAG_PRIORITY_MASK      0x0C  // bits 2-3
#define RL_TIMER_FLAG_MEMBER_CALLBACK    0x10  // bit 4

#define RL_TIMER_STATE_PAUSED 0
#define RL_TIMER_STATE_RUNNING 1
#define RL_TIMER_RESOLUTION_MILLIS 0
#define RL_TIMER_RESOLUTION_MICROS 1
#define RL_TIMER_TYPE_INTERVAL 0
#define RL_TIMER_TYPE_ONE_SHOT 1
#define RL_SCHED_PRIO_LOW 0
#define RL_SCHED_PRIO_HIGH 1

#ifdef __cplusplus
extern "C" {
#endif

uint8_t rl_timer_create(void (*handler)(void*), void* instance, uint32_t interval, uint32_t phase,
                        uint8_t resolution, uint8_t priority);
uint8_t rl_timer_do_each_millis(uint32_t interval, void (*handler)(void*), void* instance);
uint8_t rl_timer_do_each_micros(uint32_t interval, void (*handler)(void*), void* instance);
uint8_t rl_timer_do_in_millis(uint32_t delay, void (*handler)(void*), void* instance);
void rl_timer_pause(uint8_t index);
void rl_timer_continue(uint8_t index);
void rl_timer_delete(uint8_t index);
void rl_timer_reconfigure(uint8_t index, void (*handler)(void*), void* instance, uint32_t interval,
                          uint32_t phase, uint8_t resolution, uint8_t priority);
void rl_timer_process_queue(void);
void rl_timer_bind_member(uint8_t index, void* instance, void (*stub)(void*));

/* Function for member callback handling */
void rl_call_member_callback(rl_event_args_t args);

// Flag getters
static inline uint8_t rl_timer_get_trigger_state(uint8_t flags) {
    return flags & RL_TIMER_FLAG_TRIGGER_STATE_MASK;
}
static inline uint8_t rl_timer_get_resolution(uint8_t flags) {
    return (flags & RL_TIMER_FLAG_RESOLUTION_MASK) >> 1;
}
static inline uint8_t rl_timer_get_priority(uint8_t flags) {
    return (flags & RL_TIMER_FLAG_PRIORITY_MASK) >> 2;
}
static inline uint8_t rl_timer_is_member_callback(uint8_t flags) {
    return (flags & RL_TIMER_FLAG_MEMBER_CALLBACK) >> 4;
}

// Flag setters
static inline void rl_timer_set_trigger_state(uint8_t* flags, uint8_t state) {
    *flags = (*flags & ~RL_TIMER_FLAG_TRIGGER_STATE_MASK) | (state & RL_TIMER_FLAG_TRIGGER_STATE_MASK);
}
static inline void rl_timer_set_resolution(uint8_t* flags, uint8_t resolution) {
    *flags = (*flags & ~RL_TIMER_FLAG_RESOLUTION_MASK) | ((resolution << 1) & RL_TIMER_FLAG_RESOLUTION_MASK);
}
static inline void rl_timer_set_priority(uint8_t* flags, uint8_t priority) {
    *flags = (*flags & ~RL_TIMER_FLAG_PRIORITY_MASK) | ((priority << 2) & RL_TIMER_FLAG_PRIORITY_MASK);
}
static inline void rl_timer_set_member_callback(uint8_t* flags, uint8_t is_member) {
    *flags = (*flags & ~RL_TIMER_FLAG_MEMBER_CALLBACK) | ((is_member ? 1 : 0) << 4);
}

#ifdef __cplusplus
} // extern "C"

// Export template functions only for C++
template<typename T, void (T::*Method)()>
static void rl_timer_call_member_callback(void* obj) {
    (static_cast<T*>(obj)->*Method)();
}

template<typename T, void (T::*Method)()>
uint8_t rl_timer_create_member(T* instance,
                               uint32_t interval,
                               uint32_t phase,
                               uint8_t resolution,
                               uint8_t priority)
{
    uint8_t index = rl_timer_create(nullptr, nullptr, interval, phase, resolution, priority);
    if (index != 0xFF) {
        rl_timer_bind_member(index,
                            static_cast<void*>(instance),
                            &rl_timer_call_member_callback<T, Method>);
    }
    return index;
}

template<typename T, void (T::*Method)()>
uint8_t rl_timer_create_member_millis(T* instance, uint32_t interval, uint32_t phase = 0,
                                     uint8_t priority = RL_SCHED_PRIO_LOW)
{
    return rl_timer_create_member<T, Method>(instance, interval, phase,
                                           RL_TIMER_RESOLUTION_MILLIS, priority);
}

template<typename T, void (T::*Method)()>
uint8_t rl_timer_create_member_micros(T* instance, uint32_t interval, uint32_t phase = 0,
                                     uint8_t priority = RL_SCHED_PRIO_HIGH)
{
    return rl_timer_create_member<T, Method>(instance, interval, phase,
                                           RL_TIMER_RESOLUTION_MICROS, priority);
}
#endif

#endif // RTOSLESS_TIMER_H

#ifndef RTOSLESS_TIMER_H
#define RTOSLESS_TIMER_H



#include <stdint.h>

#define TIMER_MAX_COUNT 16

// Bit masks for flags field
#define TIMER_FLAG_TRIGGER_STATE_MASK 0x01  // bit 0
#define TIMER_FLAG_RESOLUTION_MASK    0x02  // bit 1
#define TIMER_FLAG_PRIORITY_MASK      0x0C  // bits 2-3
#define TIMER_FLAG_MEMBER_CALLBACK    0x10  // bit 4

#define TIMER_STATE_PAUSED 0
#define TIMER_STATE_RUNNING 1
#define TIMER_RESOLUTION_MILLIS 0
#define TIMER_RESOLUTION_MICROS 1
#define TIMER_TYPE_INTERVAL 0
#define TIMER_TYPE_ONE_SHOT 1
#define SCHED_PRIO_LOW 0
#define SCHED_PRIO_HIGH 1
namespace rl {
    uint8_t timer_create(void (*handler)(void), uint32_t interval, uint32_t phase,
                         uint8_t resolution, uint8_t priority);
    uint8_t timer_do_each_millis(void (*handler)(void), uint32_t interval);
    uint8_t timer_do_each_micros(void (*handler)(void), uint32_t interval);
    uint8_t timer_do_in_millis(void (*handler)(void), uint32_t delay);
    void timer_pause(uint8_t index);
    void timer_continue(uint8_t index);
    void timer_delete(uint8_t index);
    void timer_reconfigure(uint8_t index, void (*handler)(void), uint32_t interval,
                           uint32_t phase, uint8_t resolution, uint8_t priority);
    void timer_process_queue(void);
    void timer_bind_member(uint8_t index, void* instance, void (*stub)(void*));

    // Flag getters
    static inline uint8_t timer_get_trigger_state(uint8_t flags) {
        return flags & TIMER_FLAG_TRIGGER_STATE_MASK;
    }
    static inline uint8_t timer_get_resolution(uint8_t flags) {
        return (flags & TIMER_FLAG_RESOLUTION_MASK) >> 1;
    }
    static inline uint8_t timer_get_priority(uint8_t flags) {
        return (flags & TIMER_FLAG_PRIORITY_MASK) >> 2;
    }
    static inline uint8_t timer_is_member_callback(uint8_t flags) {
        return (flags & TIMER_FLAG_MEMBER_CALLBACK) >> 4;
    }

    // Flag setters
    static inline void timer_set_trigger_state(uint8_t* flags, uint8_t state) {
        *flags = (*flags & ~TIMER_FLAG_TRIGGER_STATE_MASK) | (state & TIMER_FLAG_TRIGGER_STATE_MASK);
    }
    static inline void timer_set_resolution(uint8_t* flags, uint8_t resolution) {
        *flags = (*flags & ~TIMER_FLAG_RESOLUTION_MASK) | ((resolution << 1) & TIMER_FLAG_RESOLUTION_MASK);
    }
    static inline void timer_set_priority(uint8_t* flags, uint8_t priority) {
        *flags = (*flags & ~TIMER_FLAG_PRIORITY_MASK) | ((priority << 2) & TIMER_FLAG_PRIORITY_MASK);
    }
    static inline void timer_set_member_callback(uint8_t* flags, uint8_t is_member) {
        *flags = (*flags & ~TIMER_FLAG_MEMBER_CALLBACK) | ((is_member ? 1 : 0) << 4);
    }

    template<typename T, void (T::*Method)()>
    static void timer_call_member_callback(void* obj) {
        (static_cast<T*>(obj)->*Method)();
    }

    template<typename T, void (T::*Method)()>
    uint8_t timer_create_member(T* instance,
                                uint32_t interval,
                                uint32_t phase,
                                uint8_t resolution,
                                uint8_t priority)
    {
        uint32_t ps = rl_enter_critical();
        uint8_t index = timer_create(nullptr, interval, phase, resolution, priority);
        if (index != 0xFF) {
            timer_bind_member(index,
                            static_cast<void*>(instance),
                            &timer_call_member_callback<T, Method>);
        }
        rl_exit_critical(ps);
        return index;
    }

    template<typename T, void (T::*Method)()>
    uint8_t timer_create_member_millis(T* instance, uint32_t interval, uint32_t phase = 0,
                                    uint8_t priority = SCHED_PRIO_LOW)
    {
        return timer_create_member<T, Method>(instance, interval, phase,
                                            TIMER_RESOLUTION_MILLIS, priority);
    }

    template<typename T, void (T::*Method)()>
    uint8_t timer_create_member_micros(T* instance, uint32_t interval, uint32_t phase = 0,
                                    uint8_t priority = SCHED_PRIO_HIGH)
    {
        return timer_create_member<T, Method>(instance, interval, phase,
                                            TIMER_RESOLUTION_MICROS, priority);
    }
}



#endif // RTOSLESS_TIMER_H

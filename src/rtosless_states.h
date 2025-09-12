#ifndef RTOSLESS_HAL_H
#define RTOSLESS_HAL_H


namespace rl {

    typedef void* state_id_t;

    typedef state_id_t (*state_fn_t)(void);

    typedef struct {
        state_fn_t current;
    } state_machine_t;

    inline void state_machine_init(state_machine_t* sm, state_fn_t initial) {
        sm->current = initial;
    }

    inline void state_machine_run(state_machine_t* sm) {
        if (sm->current) {
            sm->current = sm->current();
        }
    }
}
#endif

#endif // RTOSLESS_HAL_H

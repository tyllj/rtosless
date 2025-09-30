#ifndef RTOSLESS_STATES_H
#define RTOSLESS_STATES_H

#ifdef __cplusplus
extern "C" {
#endif

    typedef void* rl_state_id_t;

    typedef rl_state_id_t (*rl_state_fn_t)(void);

    typedef struct {
        rl_state_fn_t current;
    } rl_state_machine_t;

    static inline void rl_state_machine_init(rl_state_machine_t* sm, rl_state_fn_t initial) {
        sm->current = initial;
    }

    static inline void rl_state_machine_run(rl_state_machine_t* sm) {
        if (sm->current) {
            sm->current = (rl_state_fn_t)sm->current();
        }
    }

#ifdef __cplusplus
}
#endif

#endif // RTOSLESS_STATES_H

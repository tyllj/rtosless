#ifndef RTOSLESS_HAL_H
#define RTOSLESS_HAL_H

#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
    #endif


    bool rl_enter_critical(void);
    void rl_exit_critical(bool prev);

    #ifdef __cplusplus
}
#endif

#endif // RTOSLESS_HAL_H

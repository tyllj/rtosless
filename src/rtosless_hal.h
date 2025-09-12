#ifndef RTOSLESS_HAL_H
#define RTOSLESS_HAL_H

#ifdef __cplusplus
extern "C" {
    #endif

    #include <stdint.h>

    uint32_t rtosless_enter_critical(void);
    void rtosless_exit_critical(uint32_t prev);

    #ifdef __cplusplus
}
#endif

#endif // RTOSLESS_HAL_H

#ifndef RTOSLESS_KERNEL_H
#define RTOSLESS_KERNEL_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

uint32_t rl_millis();
uint32_t rl_micros();
uint32_t rl_cycles();

void rl_kernel(uint32_t millis, uint32_t micros);
    
#ifdef __cplusplus
}
#endif

#endif // RTOSLESS_KERNEL_H
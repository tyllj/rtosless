#ifndef RTOSLESS_STM_BACKGROUND_ADC_H
#define RTOSLESS_STM_BACKGROUND_ADC_H

/**
 * @file rtosless_stm_background_adc.h
 * @brief STM32F3 background ADC acquisition - C11 implementation
 * 
 * This module provides continuous background ADC sampling for STM32F3 microcontrollers
 * using interrupt-driven multi-channel acquisition with no dynamic memory allocation.
 * 
 * ## Configuration
 * 
 * Enable ADC instances by defining these macros in your project:
 * - `RTOSLESS_USE_BG_ADC1` - Enable background ADC1 sampling
 * - `RTOSLESS_USE_BG_ADC2` - Enable background ADC2 sampling  
 * - `RTOSLESS_USE_BG_ADC3` - Enable background ADC3 sampling
 * - `RTOSLESS_USE_BG_ADC4` - Enable background ADC4 sampling
 * 
 * For each enabled ADC, also define:
 * - `RTOSLESS_ADCx_SAMPLING_HZ` - Target sampling frequency (e.g., 1000 for 1kHz)
 * - `RTOSLESS_ADCx_NUM_CHANNELS` - Number of channels to sample (1-8)
 * - `RTOSLESS_ADCx_CHANNEL_0` through `RTOSLESS_ADCx_CHANNEL_7` - HAL channel constants
 * 
 * ## Usage Example
 * 
 * ```c
 * // In your configuration header:
 * #define RTOSLESS_USE_BG_ADC1
 * #define RTOSLESS_ADC1_SAMPLING_HZ 1000
 * #define RTOSLESS_ADC1_NUM_CHANNELS 3
 * #define RTOSLESS_ADC1_CHANNEL_0 ADC_CHANNEL_1
 * #define RTOSLESS_ADC1_CHANNEL_1 ADC_CHANNEL_2  
 * #define RTOSLESS_ADC1_CHANNEL_2 ADC_CHANNEL_3
 * 
 * // In your code:
 * #include "rtosless_stm_background_adc.h"
 * 
 * void setup() {
 *     rl_stm_setup_background_adc();  // Initialize all enabled ADCs
 * }
 * 
 * void loop() {
 *     extern rl_stm_background_adc_t bg_adc1;
 *     uint16_t value = rl_stm_background_adc_get_channel_value(&bg_adc1, 0);
 *     float freq = rl_stm_background_adc_get_actual_frequency(&bg_adc1);
 * }
 * ```
 * 
 * ## Memory Allocation
 * 
 * All memory is statically allocated at compile time using the `RL_STM_BACKGROUND_ADC_DECLARE`
 * macro. No dynamic allocation is performed during runtime.
 */

#if defined(STM32F3) || defined(STM32F301x8) || defined(STM32F302x8) || \
defined(STM32F303xC) || defined(STM32F373xC) || defined(STM32F334x8) || \
defined(STM32F3XX)

#include "../rtosless_sample_buffer.h"
#include "stm32f3xx_hal.h"
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

#define RL_STM_MAX_ADC_CHANNELS 8

/**
 * @brief Background ADC configuration structure
 */
typedef struct {
    uint32_t sampling_hz;
    uint32_t active_channels[RL_STM_MAX_ADC_CHANNELS];
    size_t num_channels;
} rl_stm_adc_config_t;

/**
 * @brief Background ADC instance structure
 * 
 * Supports scan + continuous conversion mode with per-channel sample buffers.
 * Designed for STM32duino projects using STM32F3xx HAL.
 */
typedef struct {
    ADC_HandleTypeDef* hadc;
    rl_stm_adc_config_t config;
    rl_sample_buffer_t* channel_buffers[RL_STM_MAX_ADC_CHANNELS];
    uint16_t* buffer_arrays[RL_STM_MAX_ADC_CHANNELS];
    size_t n_samples;
    size_t current_channel_index;
} rl_stm_background_adc_t;

// Core functions
void rl_stm_background_adc_init(rl_stm_background_adc_t* adc, 
                               ADC_HandleTypeDef* hadc,
                               const rl_stm_adc_config_t* config,
                               size_t n_samples);

void rl_stm_background_adc_set_channel_buffer(rl_stm_background_adc_t* adc,
                                             size_t channel_index,
                                             rl_sample_buffer_t* buffer,
                                             uint16_t* buffer_array);

void rl_stm_background_adc_start(rl_stm_background_adc_t* adc);
void rl_stm_background_adc_stop(rl_stm_background_adc_t* adc);

void rl_stm_background_adc_on_conversion_complete(rl_stm_background_adc_t* adc);

rl_sample_buffer_t* rl_stm_background_adc_get_buffer(const rl_stm_background_adc_t* adc, size_t channel_index);
ADC_HandleTypeDef* rl_stm_background_adc_get_handle(const rl_stm_background_adc_t* adc);

uint32_t rl_stm_background_adc_get_actual_sampling_frequency(const rl_stm_background_adc_t* adc);

// Helper functions
uint32_t rl_stm_adc_calculate_sampling_time(uint32_t target_hz);
float rl_stm_adc_get_sampling_cycles(uint32_t sampling_enum);

// Convenience macro for declaring a complete ADC setup
#define RL_STM_BACKGROUND_ADC_DECLARE(name, n_samples, max_channels) \
    static uint16_t name##_arrays[max_channels][n_samples]; \
    static rl_sample_buffer_t name##_buffers[max_channels]; \
    static rl_stm_background_adc_t name = {0}

#ifdef __cplusplus
}
#endif

#endif // STM32F3 guard
#endif // RTOSLESS_STM_BACKGROUND_ADC_H

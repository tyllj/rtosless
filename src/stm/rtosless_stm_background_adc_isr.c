/**
 * @file rtosless_stm_background_adc_isr.c
 * @brief STM32F3 background ADC interrupt service routines - C11 implementation
 */

#include "rtosless_stm_background_adc.h"

#if defined(STM32F3) || defined(STM32F301x8) || defined(STM32F302x8) || \
defined(STM32F303xC) || defined(STM32F373xC) || defined(STM32F334x8) || \
defined(STM32F3XX)

// Global ADC instances with static memory allocation
#ifdef ADC1
#ifdef RTOSLESS_USE_BG_ADC1
ADC_HandleTypeDef hadc1;
RL_STM_BACKGROUND_ADC_DECLARE(bg_adc1, 8, RTOSLESS_ADC1_NUM_CHANNELS);

void ADC1_IRQHandler(void) {
    HAL_ADC_IRQHandler(&hadc1);
}
#endif
#endif

#ifdef ADC2
#ifdef RTOSLESS_USE_BG_ADC2
ADC_HandleTypeDef hadc2;
RL_STM_BACKGROUND_ADC_DECLARE(bg_adc2, 8, RTOSLESS_ADC2_NUM_CHANNELS);

void ADC2_IRQHandler(void) {
    HAL_ADC_IRQHandler(&hadc2);
}
#endif
#endif

#ifdef ADC3
#ifdef RTOSLESS_USE_BG_ADC3
ADC_HandleTypeDef hadc3;
RL_STM_BACKGROUND_ADC_DECLARE(bg_adc3, 8, RTOSLESS_ADC3_NUM_CHANNELS);

void ADC3_IRQHandler(void) {
    HAL_ADC_IRQHandler(&hadc3);
}
#endif
#endif

#ifdef ADC4
#ifdef RTOSLESS_USE_BG_ADC4
ADC_HandleTypeDef hadc4;
RL_STM_BACKGROUND_ADC_DECLARE(bg_adc4, 8, RTOSLESS_ADC4_NUM_CHANNELS);

void ADC4_IRQHandler(void) {
    HAL_ADC_IRQHandler(&hadc4);
}
#endif
#endif

// HAL callback routing
void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc) {
    #ifdef RTOSLESS_USE_BG_ADC1
    if (hadc == rl_stm_background_adc_get_handle(&bg_adc1)) {
        rl_stm_background_adc_on_conversion_complete(&bg_adc1);
    }
    #endif
    #ifdef RTOSLESS_USE_BG_ADC2
    if (hadc == rl_stm_background_adc_get_handle(&bg_adc2)) {
        rl_stm_background_adc_on_conversion_complete(&bg_adc2);
    }
    #endif
    #ifdef RTOSLESS_USE_BG_ADC3
    if (hadc == rl_stm_background_adc_get_handle(&bg_adc3)) {
        rl_stm_background_adc_on_conversion_complete(&bg_adc3);
    }
    #endif
    #ifdef RTOSLESS_USE_BG_ADC4
    if (hadc == rl_stm_background_adc_get_handle(&bg_adc4)) {
        rl_stm_background_adc_on_conversion_complete(&bg_adc4);
    }
    #endif
}

// Helper function to initialize configured ADC instances
void rl_stm_setup_background_adc(void) {
    #ifdef RTOSLESS_USE_BG_ADC1
    // Configure ADC1 channels
    const uint32_t adc1_channels[] = {
        #if RTOSLESS_ADC1_NUM_CHANNELS > 0
        RTOSLESS_ADC1_CHANNEL_0,
        #endif
        #if RTOSLESS_ADC1_NUM_CHANNELS > 1
        RTOSLESS_ADC1_CHANNEL_1,
        #endif
        #if RTOSLESS_ADC1_NUM_CHANNELS > 2
        RTOSLESS_ADC1_CHANNEL_2,
        #endif
        #if RTOSLESS_ADC1_NUM_CHANNELS > 3
        RTOSLESS_ADC1_CHANNEL_3,
        #endif
        #if RTOSLESS_ADC1_NUM_CHANNELS > 4
        RTOSLESS_ADC1_CHANNEL_4,
        #endif
        #if RTOSLESS_ADC1_NUM_CHANNELS > 5
        RTOSLESS_ADC1_CHANNEL_5,
        #endif
        #if RTOSLESS_ADC1_NUM_CHANNELS > 6
        RTOSLESS_ADC1_CHANNEL_6,
        #endif
        #if RTOSLESS_ADC1_NUM_CHANNELS > 7
        RTOSLESS_ADC1_CHANNEL_7,
        #endif
    };
    
    rl_stm_adc_config_t adc1_config = {
        .sampling_hz = RTOSLESS_ADC1_SAMPLING_HZ,
        .active_channels = {0}, // Will be copied from array above
        .num_channels = RTOSLESS_ADC1_NUM_CHANNELS
    };
    
    // Copy channel array to config
    for (size_t i = 0; i < RTOSLESS_ADC1_NUM_CHANNELS && i < RL_STM_MAX_ADC_CHANNELS; i++) {
        adc1_config.active_channels[i] = adc1_channels[i];
    }
    
    rl_stm_background_adc_init(&bg_adc1, &hadc1, &adc1_config, 8);
    
    // Set up channel buffers - buffers are declared by the macro
    for (size_t i = 0; i < RTOSLESS_ADC1_NUM_CHANNELS && i < RL_STM_MAX_ADC_CHANNELS; i++) {
        rl_stm_background_adc_set_channel_buffer(&bg_adc1, i, 
            &bg_adc1_buffers[i], bg_adc1_arrays[i]);
    }
    
    rl_stm_background_adc_start(&bg_adc1);
    #endif
    
    #ifdef RTOSLESS_USE_BG_ADC2
    const uint32_t adc2_channels[] = {
        #if RTOSLESS_ADC2_NUM_CHANNELS > 0
        RTOSLESS_ADC2_CHANNEL_0,
        #endif
        #if RTOSLESS_ADC2_NUM_CHANNELS > 1
        RTOSLESS_ADC2_CHANNEL_1,
        #endif
        #if RTOSLESS_ADC2_NUM_CHANNELS > 2
        RTOSLESS_ADC2_CHANNEL_2,
        #endif
        #if RTOSLESS_ADC2_NUM_CHANNELS > 3
        RTOSLESS_ADC2_CHANNEL_3,
        #endif
        #if RTOSLESS_ADC2_NUM_CHANNELS > 4
        RTOSLESS_ADC2_CHANNEL_4,
        #endif
        #if RTOSLESS_ADC2_NUM_CHANNELS > 5
        RTOSLESS_ADC2_CHANNEL_5,
        #endif
        #if RTOSLESS_ADC2_NUM_CHANNELS > 6
        RTOSLESS_ADC2_CHANNEL_6,
        #endif
        #if RTOSLESS_ADC2_NUM_CHANNELS > 7
        RTOSLESS_ADC2_CHANNEL_7,
        #endif
    };
    
    rl_stm_adc_config_t adc2_config = {
        .sampling_hz = RTOSLESS_ADC2_SAMPLING_HZ,
        .active_channels = {0},
        .num_channels = RTOSLESS_ADC2_NUM_CHANNELS
    };
    
    for (size_t i = 0; i < RTOSLESS_ADC2_NUM_CHANNELS && i < RL_STM_MAX_ADC_CHANNELS; i++) {
        adc2_config.active_channels[i] = adc2_channels[i];
    }
    
    rl_stm_background_adc_init(&bg_adc2, &hadc2, &adc2_config, 8);
    
    for (size_t i = 0; i < RTOSLESS_ADC2_NUM_CHANNELS && i < RL_STM_MAX_ADC_CHANNELS; i++) {
        rl_stm_background_adc_set_channel_buffer(&bg_adc2, i, 
            &bg_adc2_buffers[i], bg_adc2_arrays[i]);
    }
    
    rl_stm_background_adc_start(&bg_adc2);
    #endif
    
    #ifdef RTOSLESS_USE_BG_ADC3
    const uint32_t adc3_channels[] = {
        #if RTOSLESS_ADC3_NUM_CHANNELS > 0
        RTOSLESS_ADC3_CHANNEL_0,
        #endif
        #if RTOSLESS_ADC3_NUM_CHANNELS > 1
        RTOSLESS_ADC3_CHANNEL_1,
        #endif
        #if RTOSLESS_ADC3_NUM_CHANNELS > 2
        RTOSLESS_ADC3_CHANNEL_2,
        #endif
        #if RTOSLESS_ADC3_NUM_CHANNELS > 3
        RTOSLESS_ADC3_CHANNEL_3,
        #endif
        #if RTOSLESS_ADC3_NUM_CHANNELS > 4
        RTOSLESS_ADC3_CHANNEL_4,
        #endif
        #if RTOSLESS_ADC3_NUM_CHANNELS > 5
        RTOSLESS_ADC3_CHANNEL_5,
        #endif
        #if RTOSLESS_ADC3_NUM_CHANNELS > 6
        RTOSLESS_ADC3_CHANNEL_6,
        #endif
        #if RTOSLESS_ADC3_NUM_CHANNELS > 7
        RTOSLESS_ADC3_CHANNEL_7,
        #endif
    };
    
    rl_stm_adc_config_t adc3_config = {
        .sampling_hz = RTOSLESS_ADC3_SAMPLING_HZ,
        .active_channels = {0},
        .num_channels = RTOSLESS_ADC3_NUM_CHANNELS
    };
    
    for (size_t i = 0; i < RTOSLESS_ADC3_NUM_CHANNELS && i < RL_STM_MAX_ADC_CHANNELS; i++) {
        adc3_config.active_channels[i] = adc3_channels[i];
    }
    
    rl_stm_background_adc_init(&bg_adc3, &hadc3, &adc3_config, 8);
    
    for (size_t i = 0; i < RTOSLESS_ADC3_NUM_CHANNELS && i < RL_STM_MAX_ADC_CHANNELS; i++) {
        rl_stm_background_adc_set_channel_buffer(&bg_adc3, i, 
            &bg_adc3_buffers[i], bg_adc3_arrays[i]);
    }
    
    rl_stm_background_adc_start(&bg_adc3);
    #endif
    
    #ifdef RTOSLESS_USE_BG_ADC4
    const uint32_t adc4_channels[] = {
        #if RTOSLESS_ADC4_NUM_CHANNELS > 0
        RTOSLESS_ADC4_CHANNEL_0,
        #endif
        #if RTOSLESS_ADC4_NUM_CHANNELS > 1
        RTOSLESS_ADC4_CHANNEL_1,
        #endif
        #if RTOSLESS_ADC4_NUM_CHANNELS > 2
        RTOSLESS_ADC4_CHANNEL_2,
        #endif
        #if RTOSLESS_ADC4_NUM_CHANNELS > 3
        RTOSLESS_ADC4_CHANNEL_3,
        #endif
        #if RTOSLESS_ADC4_NUM_CHANNELS > 4
        RTOSLESS_ADC4_CHANNEL_4,
        #endif
        #if RTOSLESS_ADC4_NUM_CHANNELS > 5
        RTOSLESS_ADC4_CHANNEL_5,
        #endif
        #if RTOSLESS_ADC4_NUM_CHANNELS > 6
        RTOSLESS_ADC4_CHANNEL_6,
        #endif
        #if RTOSLESS_ADC4_NUM_CHANNELS > 7
        RTOSLESS_ADC4_CHANNEL_7,
        #endif
    };
    
    rl_stm_adc_config_t adc4_config = {
        .sampling_hz = RTOSLESS_ADC4_SAMPLING_HZ,
        .active_channels = {0},
        .num_channels = RTOSLESS_ADC4_NUM_CHANNELS
    };
    
    for (size_t i = 0; i < RTOSLESS_ADC4_NUM_CHANNELS && i < RL_STM_MAX_ADC_CHANNELS; i++) {
        adc4_config.active_channels[i] = adc4_channels[i];
    }
    
    rl_stm_background_adc_init(&bg_adc4, &hadc4, &adc4_config, 8);
    
    for (size_t i = 0; i < RTOSLESS_ADC4_NUM_CHANNELS && i < RL_STM_MAX_ADC_CHANNELS; i++) {
        rl_stm_background_adc_set_channel_buffer(&bg_adc4, i, 
            &bg_adc4_buffers[i], bg_adc4_arrays[i]);
    }
    
    rl_stm_background_adc_start(&bg_adc4);
    #endif
}

#endif // STM32F3 guard
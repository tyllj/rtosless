#include "rtosless_stm_background_adc.h"
#include "rtosless_stm_adc_config.h"

#if defined(STM32F3) || defined(STM32F301x8) || defined(STM32F302x8) || \
defined(STM32F303xC) || defined(STM32F373xC) || defined(STM32F334x8) || \
defined(STM32F3XX)

using namespace rl::stm;

#ifdef ADC1
#ifdef RTOSLESS_USE_BG_ADC1
ADC_HandleTypeDef hadc1;
background_adc<8, RTOSLESS_ADC1_NUM_CHANNELS> bg_adc1(&hadc1, {
    .sampling_hz = RTOSLESS_ADC1_SAMPLING_HZ,
    .active_channels = {
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
    },
    .num_channels = RTOSLESS_ADC1_NUM_CHANNELS
});
extern "C" void ADC1_IRQHandler(void) {
    HAL_ADC_IRQHandler(&hadc1);
}
#endif
#endif

// Repeat for ADC2–ADC4...

#ifdef ADC2
#ifdef RTOSLESS_USE_BG_ADC2
ADC_HandleTypeDef hadc2;
background_adc<8, RTOSLESS_ADC2_NUM_CHANNELS> bg_adc2(&hadc2, {
    .sampling_hz = RTOSLESS_ADC2_SAMPLING_HZ,
    .active_channels = {
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
    },
    .num_channels = RTOSLESS_ADC2_NUM_CHANNELS
});
extern "C" void ADC2_IRQHandler(void) {
    HAL_ADC_IRQHandler(&hadc2);
}
#endif
#endif

#ifdef ADC3
#ifdef RTOSLESS_USE_BG_ADC3
ADC_HandleTypeDef hadc3;
background_adc<8, RTOSLESS_ADC3_NUM_CHANNELS> bg_adc3(&hadc3, {
    .sampling_hz = RTOSLESS_ADC3_SAMPLING_HZ,
    .active_channels = {
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
    },
    .num_channels = RTOSLESS_ADC3_NUM_CHANNELS
});
extern "C" void ADC3_IRQHandler(void) {
    HAL_ADC_IRQHandler(&hadc3);
}
#endif
#endif

#ifdef ADC4
#ifdef RTOSLESS_USE_BG_ADC4
ADC_HandleTypeDef hadc4;
background_adc<8, RTOSLESS_ADC4_NUM_CHANNELS> bg_adc4(&hadc4, {
    .sampling_hz = RTOSLESS_ADC4_SAMPLING_HZ,
    .active_channels = {
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
    },
    .num_channels = RTOSLESS_ADC4_NUM_CHANNELS
});
extern "C" void ADC4_IRQHandler(void) {
    HAL_ADC_IRQHandler(&hadc4);
}
#endif
#endif

// 🔁 HAL callback routing
extern "C" void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc) {
    #ifdef RTOSLESS_USE_BG_ADC1
    if (hadc == bg_adc1.get_handle()) bg_adc1.on_conversion_complete();
    #endif
    #ifdef RTOSLESS_USE_BG_ADC2
    if (hadc == bg_adc2.get_handle()) bg_adc2.on_conversion_complete();
    #endif
    #ifdef RTOSLESS_USE_BG_ADC3
    if (hadc == bg_adc3.get_handle()) bg_adc3.on_conversion_complete();
    #endif
    #ifdef RTOSLESS_USE_BG_ADC4
    if (hadc == bg_adc4.get_handle()) bg_adc4.on_conversion_complete();
    #endif
}

// 🧰 Optional: call this in setup() to initialize all enabled ADCs
void setup_background_adc() {
    #ifdef RTOSLESS_USE_BG_ADC1
    bg_adc1.init();
    #endif
    #ifdef RTOSLESS_USE_BG_ADC2
    bg_adc2.init();
    #endif
    #ifdef RTOSLESS_USE_BG_ADC3
    bg_adc3.init();
    #endif
    #ifdef RTOSLESS_USE_BG_ADC4
    bg_adc4.init();
    #endif
}

#endif

#ifndef RTOSLESS_STM_BACKGROUND_ADC_H
#define RTOSLESS_STM_BACKGROUND_ADC_H

#if defined(STM32F3) || defined(STM32F301x8) || defined(STM32F302x8) || \
defined(STM32F303xC) || defined(STM32F373xC) || defined(STM32F334x8) || \
defined(STM32F3XX)

#include "rtosless_sample_buffer.h"
#include "stm32f3xx_hal.h"

namespace rl::stm {

    /**
     * @brief Background ADC acquisition class for STM32F3.
     *
     * Supports scan + continuous conversion mode with per-channel sample buffers.
     * Designed for STM32duino projects using STM32F3xx HAL.
     *
     * To configure ADCs in STM32duino:
     *
     * 1. Create a file named `build_opt.h` in your sketch folder.
     * 2. Add macros to enable ADCs and configure channels:
     *
     *    #define RTOSLESS_USE_BG_ADC1
     *    #define RTOSLESS_ADC1_SAMPLING_HZ 20000
     *    #define RTOSLESS_ADC1_NUM_CHANNELS 2
     *    #define RTOSLESS_ADC1_CHANNEL_0 ADC_CHANNEL_1
     *    #define RTOSLESS_ADC1_CHANNEL_1 ADC_CHANNEL_2
     *
     * 3. Repeat for ADC2–ADC4 as needed.
     * 4. In your `setup()` function, call:
     *
     *    setup_background_adc();  // Initializes all enabled ADCs
     *
     * 5. Use `bg_adc1.get_buffer(0)` to access samples.
     */

    template<size_t n_samples, size_t max_channels = 8>
    class background_adc {
    public:
        using sample_t = uint16_t;

        struct config_t {
            uint32_t sampling_hz;
            uint8_t active_channels[max_channels];
            size_t num_channels;
        };

        ADC_HandleTypeDef* hadc;
        config_t config;
        rl::sample_buffer_t<sample_t, n_samples> buffers[max_channels];
        size_t current_channel_index = 0;

        background_adc(ADC_HandleTypeDef* adc, const config_t& cfg)
        : hadc(adc), config(cfg) {}

        void init() {
            hadc->Init.ContinuousConvMode = ENABLE;
            hadc->Init.ScanConvMode = ENABLE;
            HAL_ADC_Init(hadc);

            for (size_t i = 0; i < config.num_channels; ++i) {
                ADC_ChannelConfTypeDef sConfig = {};
                sConfig.Channel = config.active_channels[i];
                sConfig.Rank = i + 1;
                sConfig.SamplingTime = calculate_sampling_time(config.sampling_hz * config.num_channels);
                HAL_ADC_ConfigChannel(hadc, &sConfig);
            }

            HAL_ADC_Start_IT(hadc);
        }

        void on_conversion_complete() {
            sample_t value = HAL_ADC_GetValue(hadc);
            buffers[current_channel_index].push_back(value);
            current_channel_index = (current_channel_index + 1) % config.num_channels;
        }

        const rl::sample_buffer_t<sample_t, n_samples>& get_buffer(size_t index) const {
            return buffers[index];
        }

        ADC_HandleTypeDef* get_handle() const { return hadc; }

        uint32_t get_actual_sampling_frequency() const {
            uint32_t adc_clk = HAL_RCC_GetPCLK2Freq();
            uint32_t sampling_enum = calculate_sampling_time(config.sampling_hz * config.num_channels);
            float total_cycles = get_sampling_cycles(sampling_enum) + 12.5f;
            return static_cast<uint32_t>(adc_clk / total_cycles / config.num_channels);
        }

    private:
        uint32_t calculate_sampling_time(uint32_t target_hz) const {
            uint32_t adc_clk = HAL_RCC_GetPCLK2Freq();
            uint32_t cycles_per_sample = adc_clk / target_hz;

            if (cycles_per_sample <= 2)   return ADC_SAMPLETIME_1CYCLE_5;
            if (cycles_per_sample <= 8)   return ADC_SAMPLETIME_7CYCLES_5;
            if (cycles_per_sample <= 14)  return ADC_SAMPLETIME_13CYCLES_5;
            if (cycles_per_sample <= 28)  return ADC_SAMPLETIME_28CYCLES_5;
            if (cycles_per_sample <= 41)  return ADC_SAMPLETIME_41CYCLES_5;
            if (cycles_per_sample <= 55)  return ADC_SAMPLETIME_55CYCLES_5;
            if (cycles_per_sample <= 71)  return ADC_SAMPLETIME_71CYCLES_5;
            return ADC_SAMPLETIME_239CYCLES_5;
        }

        float get_sampling_cycles(uint32_t sampling_enum) const {
            switch (sampling_enum) {
                case ADC_SAMPLETIME_1CYCLE_5:    return 1.5f;
                case ADC_SAMPLETIME_7CYCLES_5:   return 7.5f;
                case ADC_SAMPLETIME_13CYCLES_5:  return 13.5f;
                case ADC_SAMPLETIME_28CYCLES_5:  return 28.5f;
                case ADC_SAMPLETIME_41CYCLES_5:  return 41.5f;
                case ADC_SAMPLETIME_55CYCLES_5:  return 55.5f;
                case ADC_SAMPLETIME_71CYCLES_5:  return 71.5f;
                case ADC_SAMPLETIME_239CYCLES_5: return 239.5f;
                default: return 13.5f;
            }
        }
    };

} // namespace rl::stm

#endif // STM32F3 guard
#endif // RTOSLESS_STM_BACKGROUND_ADC_H

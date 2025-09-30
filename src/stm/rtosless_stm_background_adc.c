#include "rtosless_stm_background_adc.h"

#if defined(STM32F3) || defined(STM32F301x8) || defined(STM32F302x8) || \
defined(STM32F303xC) || defined(STM32F373xC) || defined(STM32F334x8) || \
defined(STM32F3XX)

// Initialize background ADC instance
void rl_stm_background_adc_init(rl_stm_background_adc_t* adc, 
                               ADC_HandleTypeDef* hadc,
                               const rl_stm_adc_config_t* config,
                               size_t n_samples) {
    adc->hadc = hadc;
    adc->config = *config;  // Copy configuration
    adc->n_samples = n_samples;
    adc->current_channel_index = 0;
    
    // Initialize all buffer pointers to NULL
    for (size_t i = 0; i < RL_STM_MAX_ADC_CHANNELS; i++) {
        adc->channel_buffers[i] = NULL;
        adc->buffer_arrays[i] = NULL;
    }
}

// Set buffer for a specific channel
void rl_stm_background_adc_set_channel_buffer(rl_stm_background_adc_t* adc,
                                             size_t channel_index,
                                             rl_sample_buffer_t* buffer,
                                             uint16_t* buffer_array) {
    if (channel_index >= RL_STM_MAX_ADC_CHANNELS) return;
    
    adc->channel_buffers[channel_index] = buffer;
    adc->buffer_arrays[channel_index] = buffer_array;
    
    // Initialize the sample buffer
    rl_sample_buffer_init(buffer, buffer_array, adc->n_samples);
}

// Start ADC acquisition
void rl_stm_background_adc_start(rl_stm_background_adc_t* adc) {
    // Configure ADC for continuous scan mode
    adc->hadc->Init.ContinuousConvMode = ENABLE;
    adc->hadc->Init.ScanConvMode = ENABLE;
    HAL_ADC_Init(adc->hadc);
    
    // Configure channels
    for (size_t i = 0; i < adc->config.num_channels; ++i) {
        ADC_ChannelConfTypeDef sConfig = {0};
        sConfig.Channel = adc->config.active_channels[i];
        sConfig.Rank = i + 1;
        sConfig.SamplingTime = rl_stm_adc_calculate_sampling_time(
            adc->config.sampling_hz * adc->config.num_channels);
        HAL_ADC_ConfigChannel(adc->hadc, &sConfig);
    }
    
    // Start ADC with interrupts
    HAL_ADC_Start_IT(adc->hadc);
}

// Stop ADC acquisition
void rl_stm_background_adc_stop(rl_stm_background_adc_t* adc) {
    HAL_ADC_Stop_IT(adc->hadc);
}

// Handle conversion complete callback
void rl_stm_background_adc_on_conversion_complete(rl_stm_background_adc_t* adc) {
    uint16_t value = HAL_ADC_GetValue(adc->hadc);
    
    if (adc->current_channel_index < adc->config.num_channels &&
        adc->channel_buffers[adc->current_channel_index] != NULL) {
        rl_sample_buffer_push_back(adc->channel_buffers[adc->current_channel_index], value);
    }
    
    adc->current_channel_index = (adc->current_channel_index + 1) % adc->config.num_channels;
}

// Get buffer for specific channel
rl_sample_buffer_t* rl_stm_background_adc_get_buffer(const rl_stm_background_adc_t* adc, size_t channel_index) {
    if (channel_index >= RL_STM_MAX_ADC_CHANNELS) return NULL;
    return adc->channel_buffers[channel_index];
}

// Get ADC handle
ADC_HandleTypeDef* rl_stm_background_adc_get_handle(const rl_stm_background_adc_t* adc) {
    return adc->hadc;
}

// Get actual sampling frequency
uint32_t rl_stm_background_adc_get_actual_sampling_frequency(const rl_stm_background_adc_t* adc) {
    uint32_t adc_clk = HAL_RCC_GetPCLK2Freq();
    uint32_t sampling_enum = rl_stm_adc_calculate_sampling_time(
        adc->config.sampling_hz * adc->config.num_channels);
    float total_cycles = rl_stm_adc_get_sampling_cycles(sampling_enum) + 12.5f;
    return (uint32_t)(adc_clk / total_cycles / adc->config.num_channels);
}

// Calculate appropriate sampling time register value
uint32_t rl_stm_adc_calculate_sampling_time(uint32_t target_hz) {
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

// Get actual cycles for a sampling time enum
float rl_stm_adc_get_sampling_cycles(uint32_t sampling_enum) {
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

#endif // STM32F3 guard
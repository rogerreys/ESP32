#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "hal/adc_types.h"
#include "esp_adc/adc_oneshot.h"


adc_oneshot_unit_handle_t adc1_handle;

adc_oneshot_unit_init_cfg_t init_config1 = {
    .unit_id = ADC_UNIT_2,
    .ulp_mode = ADC_ULP_MODE_DISABLE,
};

adc_oneshot_chan_cfg_t config = {
    .bitwidth = ADC_BITWIDTH_DEFAULT,
    .atten = ADC_ATTEN_DB_12,
};

void app_main(void)
{
    
    adc_oneshot_new_unit(&init_config1, &adc1_handle);
    
    adc_oneshot_config_channel(adc1_handle, ADC_CHANNEL_0, &config);
    
    int adc_raw;
    while(1){
        // adc_oneshot_read(adc1_handle, ADC_CHANNEL_0, &raw_value);
        adc_oneshot_read(adc1_handle, ADC_CHANNEL_0, &adc_raw);
        printf("ADC RAW: %d\n", adc_raw);
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}

#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "hal/adc_types.h"
#include "esp_adc/adc_oneshot.h"
#include "driver/ledc.h"

#define LEDC_TIMER LEDC_TIMER_0         // Timer que usaremos
#define LEDC_MODE LEDC_HIGH_SPEED_MODE  // Modo de velocidad
#define LEDC_OUTPUT 19                  // Pin de salida
#define LEDC_CHANNEL LEDC_CHANNEL_0     // Canal de control
#define LEDC_DUTY_RES LEDC_TIMER_12_BIT // Resolucion en bit
#define LEDC_FREQUENCY 5000             // Frecuencia de funcionamiento
#define LEDC_DUTY 0                     // Valor inicial
#define LEDC_HPOINT 0                 // Ajuste de face
adc_oneshot_unit_handle_t adc1_handle;

adc_oneshot_unit_init_cfg_t init_config1 = {
    .unit_id = ADC_UNIT_2,
    .ulp_mode = ADC_ULP_MODE_DISABLE,
};

adc_oneshot_chan_cfg_t config = {
    .bitwidth = ADC_BITWIDTH_DEFAULT,
    .atten = ADC_ATTEN_DB_12,
};

// PWM Config
ledc_timer_config_t ledc_timer = {
    .speed_mode = LEDC_MODE,
    .timer_num = LEDC_TIMER,
    .duty_resolution = LEDC_DUTY_RES,
    .freq_hz = LEDC_FREQUENCY,
    .clk_cfg = LEDC_AUTO_CLK
};
ledc_channel_config_t ledc_channel = {
    .gpio_num = LEDC_OUTPUT,
    .speed_mode = LEDC_MODE,
    .channel = LEDC_CHANNEL,
    .intr_type = LEDC_INTR_DISABLE,
    .timer_sel = LEDC_CHANNEL,
    .duty = LEDC_DUTY,
    .hpoint = LEDC_HPOINT        
};

void app_main(void)
{
    // PWM
    ledc_timer_config(&ledc_timer);
    
    ledc_channel_config(&ledc_channel);
    // ANALOG 
    adc_oneshot_new_unit(&init_config1, &adc1_handle);
    
    adc_oneshot_config_channel(adc1_handle, ADC_CHANNEL_0, &config);
    
    int adc_raw;
    while(1){
        // adc_oneshot_read(adc1_handle, ADC_CHANNEL_0, &raw_value);
        adc_oneshot_read(adc1_handle, ADC_CHANNEL_0, &adc_raw);
        printf("ADC RAW: %d\n", adc_raw);
        
        // salida de señal
        ledc_set_duty(LEDC_MODE, LEDC_CHANNEL, adc_raw);
        ledc_update_duty(LEDC_MODE, LEDC_CHANNEL);

        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}

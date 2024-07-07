#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "hal/adc_types.h"
// #include "esp_adc/adc_oneshot.h"
#include "driver/ledc.h"
#include "string.h"
#include "esp_wifi.h"
#include "nvs_flash.h"
#include "protocol_examples_common.h"
#include "esp_http_server.h"


#define LEDC_TIMER      LEDC_TIMER_0            // Timer que usaremos
#define LEDC_MODE       LEDC_HIGH_SPEED_MODE    // Modo de velocidad
#define LEDC_OUTPUT_R   4                       // Pin de salida
#define LEDC_OUTPUT_G   2                       // Pin de salida
#define LEDC_OUTPUT_B   15                      // Pin de salida
#define LEDC_CHANNEL_R  LEDC_CHANNEL_0          // Canal de control
#define LEDC_CHANNEL_G  LEDC_CHANNEL_2          // Canal de control
#define LEDC_CHANNEL_B  LEDC_CHANNEL_3          // Canal de control
#define LEDC_DUTY_RES   LEDC_TIMER_8_BIT        // Resolucion en bit
#define LEDC_FREQUENCY  5000                    // Frecuencia de funcionamiento
#define LEDC_DUTY       0                       // Valor inicial
#define LEDC_HPOINT     0                       // Ajuste de face

int32_t led_r=0, led_g=0, led_b=0;

// PWM Config
ledc_timer_config_t ledc_timer = {
    .speed_mode = LEDC_MODE,
    .timer_num = LEDC_TIMER,
    .duty_resolution = LEDC_DUTY_RES,
    .freq_hz = LEDC_FREQUENCY,
    .clk_cfg = LEDC_AUTO_CLK
};
// LED CONFIG
ledc_channel_config_t ledc_channel_r = {
    .gpio_num = LEDC_OUTPUT_R,
    .speed_mode = LEDC_MODE,
    .channel = LEDC_CHANNEL_R,
    .intr_type = LEDC_INTR_DISABLE,
    .timer_sel = LEDC_TIMER,
    .duty = LEDC_DUTY,
    .hpoint = LEDC_HPOINT        
};
ledc_channel_config_t ledc_channel_g = {
    .gpio_num = LEDC_OUTPUT_G,
    .speed_mode = LEDC_MODE,
    .channel = LEDC_CHANNEL_G,
    .intr_type = LEDC_INTR_DISABLE,
    .timer_sel = LEDC_TIMER,
    .duty = LEDC_DUTY,
    .hpoint = LEDC_HPOINT        
};
ledc_channel_config_t ledc_channel_b = {
    .gpio_num = LEDC_OUTPUT_B,
    .speed_mode = LEDC_MODE,
    .channel = LEDC_CHANNEL_B,
    .intr_type = LEDC_INTR_DISABLE,
    .timer_sel = LEDC_TIMER,
    .duty = LEDC_DUTY,
    .hpoint = LEDC_HPOINT        
};
// FUNCIONES
void config_led(){
    // PWM
    ledc_timer_config(&ledc_timer);    
    ledc_channel_config(&ledc_channel_r);
    ledc_channel_config(&ledc_channel_g);
    ledc_channel_config(&ledc_channel_b);
}
void config_net(){
    nvs_flash_init();
    esp_netif_init();
    esp_event_loop_create_default();

    example_connect();
}
void output_led(){
    ledc_set_duty(LEDC_MODE, LEDC_CHANNEL_R, led_r);
    ledc_update_duty(LEDC_MODE, LEDC_CHANNEL_R);
    ledc_set_duty(LEDC_MODE, LEDC_CHANNEL_G, led_g);
    ledc_update_duty(LEDC_MODE, LEDC_CHANNEL_G);
    ledc_set_duty(LEDC_MODE, LEDC_CHANNEL_B, led_b);
    ledc_update_duty(LEDC_MODE, LEDC_CHANNEL_B);
}
static esp_err_t api_get_handler(httpd_req_t *req){
    // ip/r=0&g=0&b=0
    // 192.168.100.59/?r=0&g=0&b=0
    char res[30];
    char* buf;
    size_t buf_len;

    buf_len = httpd_req_get_url_query_len(req)+1;

    if(buf_len>1){
        buf = malloc(buf_len);
        if(httpd_req_get_url_query_str(req, buf, buf_len) == ESP_OK){
            char param[4];
            if(httpd_query_key_value(buf,"r", param, sizeof(param))==ESP_OK){
                led_r = atoi(param);
                printf("URL r: %ld ",led_r);
            }
            if(httpd_query_key_value(buf,"g", param, sizeof(param))==ESP_OK){
                led_g = atoi(param);
                printf("URL g: %ld ",led_g);
            }
            if(httpd_query_key_value(buf,"b", param, sizeof(param))==ESP_OK){
                led_b = atoi(param);
                printf("URL b: %ld\n",led_b);
            }
        }
        free(buf);
    }

    output_led();

    sprintf(res, "{\"r\":%ld, \"g\":%ld, \"b\":%ld}", led_r, led_g, led_b);
    
    httpd_resp_set_hdr(req, "Content-Type","application/json");
    httpd_resp_send(req, res, HTTPD_RESP_USE_STRLEN);
    return ESP_OK;
}
// Configuracion red
static const httpd_uri_t api_uri = {
    .uri = "/api",
    .method = HTTP_GET,
    .handler = api_get_handler,
    .user_ctx = NULL
};

// Crear servidor HTTP
void web_server_init(){
    httpd_handle_t server = NULL;
    httpd_config_t config = HTTPD_DEFAULT_CONFIG();

    if (httpd_start(&server, &config) == ESP_OK){
        httpd_register_uri_handler(server, &api_uri);
        return;
    }
    printf("Error al iniciar servidor\n");

}


void app_main(void)
{
    config_led();
    config_net();

    esp_netif_ip_info_t ip_info;
    esp_netif_t* netif = NULL;
    netif = esp_netif_get_handle_from_ifkey("WIFI_STA_DEF");
    if(!netif){
       printf("No hay interfaz\n"); 
    } else{
        esp_netif_get_ip_info(netif, &ip_info);
        printf("--- IP: %d.%d.%d.%d ---\n", IP2STR(&ip_info.ip));

         // salida de señal
        output_led();

        web_server_init();
    }

    vTaskDelay(1000 / portTICK_PERIOD_MS);
}
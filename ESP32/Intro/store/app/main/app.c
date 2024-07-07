#include <stdio.h>
#include <freertos/FreeRTOS.h>
#include <nvs_flash.h> // NVS (No Volatil Storage)
#include <nvs.h>

void app_main(void)
{
    printf("-- INICIO --\n");
    // SEGMENTO DE MEMORIA
    // INICIALIZAR NVS
    esp_err_t err = nvs_flash_init();
    
    printf((err != ESP_OK) ? "Failed\n" : "Done\n");
    printf("NVS Init!\n");

    // Acceder a una particion de NVS
    nvs_handle_t my_storage;
    err = nvs_open("storage1", NVS_READWRITE, &my_storage);
    printf("NVS Open - ");
    printf((err != ESP_OK) ? "Failed\n" : "Done\n");

    // Escribir en NVS
    err = nvs_set_i32(my_storage, "number", 10);
    printf("NVS Set - ");
    printf((err != ESP_OK) ? "Failed\n" : "Done\n");

    // Guardar en NVS
    err = nvs_commit(my_storage);
    printf("NVS Commit - ");
    printf((err != ESP_OK) ? "Failed\n" : "Done\n");

    // Leer NVS
    int32_t number;
    err = nvs_get_i32(my_storage, "number", &number);
    printf("NVS Get - ");
    printf((err != ESP_OK) ? "Failed\n" : "Done\n");

    printf("El valor obtenido es %ld\n", number);

    nvs_close(my_storage);
    printf("NVS Close");
    printf("Finaliza\n");
}

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"
#include <stdio.h>

TaskHandle_t taskHandle1 = NULL;
TaskHandle_t taskHandle2 = NULL;
SemaphoreHandle_t xSemaphore = NULL;

void task1(void *args){
    int count = 20;
    for(int i = 0; i < count; i++){
        printf("Task 1 count %d\n", i);
        if(i == 3){
            xSemaphoreTake(xSemaphore, portMAX_DELAY); // Toma el semáforo para pausar la tarea 2
            printf("--- Task 2 SUSPEND ---\n");
        }
        if(i == 6){
            xSemaphoreGive(xSemaphore); // Libera el semáforo para reanudar la tarea 2
            printf("--- Task 2 RESUME ---\n");
        }
        if(i == 10){
            printf("--- Task 2 DELETED ---\n");
            vTaskDelete(taskHandle2); // Elimina la tarea 2
        }
        vTaskDelay(pdMS_TO_TICKS(500)); // Agrega un retardo de 500 ms
    }
    // Elimina la tarea actual
    vTaskDelete(NULL);
}

void task2(void *args){
    int count = 12;
    for(int i = 0; i < count; i++){
        if(xSemaphoreTake(xSemaphore, portMAX_DELAY) == pdTRUE) {
            xSemaphoreGive(xSemaphore); // Libera el semáforo inmediatamente para seguir ejecutando
        }
        printf("Task 2 count %d^2=%d\n", i, i*i);
        vTaskDelay(pdMS_TO_TICKS(500)); // Agrega un retardo de 500 ms
    }
    // Elimina la tarea actual
    vTaskDelete(NULL);
}

void app_main(void){
    // Crea un semáforo binario
    xSemaphore = xSemaphoreCreateBinary();
    xSemaphoreGive(xSemaphore); // Inicialmente, el semáforo está disponible

    // Crea una tarea y ejecuta la tarea en paralelo
    BaseType_t result1 = xTaskCreate(task1, "task N1", 2048, NULL, 10, &taskHandle1); // Por defecto ejecuta en el core 0
    BaseType_t result2 = xTaskCreatePinnedToCore(task2, "task N2", 2048, NULL, 10, &taskHandle2, 1); // Indica en qué core se ejecuta la tarea

    if(result1 != pdPASS || result2 != pdPASS) {
        printf("Error creando las tareas\n");
    }
}

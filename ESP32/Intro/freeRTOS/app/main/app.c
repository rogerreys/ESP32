#include <stdio.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

TaskHandle_t taskHandle1 = NULL;
TaskHandle_t taskHandle2 = NULL;

void task1(void *args){
    int count = 20;
    for(int i=0;i<count;i++){
        printf("Task 1 count %d\n", i);
        if(i==3){
            vTaskSuspend(taskHandle2); // Pausa a la tarea 2
            printf("--- Task 2 SUSPEND ---\n");
            continue;
        }
        if(i==6){
            printf("i: %d - Ingreso\n", i);
            vTaskResume(taskHandle2); // Reanuda a la tarea 2
            printf("--- Task 2 RESUME ---\n");
            continue;
        }
        if(i==10){
            printf("i: %d - Ingreso\n", i);
            printf("--- Task 2 DELETED ---\n");
            vTaskDelete(taskHandle2); // Elimina a la tarea 2
            continue;
        }
    }
    // Elimina la tarea actual
    vTaskDelete(NULL);
}

void task2(void *args){
    int count = 12;
    for(int i=0;i<count;i++){
        printf("Task 2 count %d^2=%d\n",i, i*i);
        // vTaskDelay(pdMS_TO_TICKS(500)); // Agrega un retardo de 500 ms
    }
    // Elimina la tarea actual
    vTaskDelete(NULL);
}

void app_main(void)
{
    // Crea un tarea y ejecuta la tarea en paralelo
    xTaskCreate(task1, "task1", 4096, NULL, 10, &taskHandle1); // Por defaul ejecuta el core 0
    xTaskCreatePinnedToCore(task2, "task2", 4096, NULL, 10, &taskHandle2, 1); // Indica en que core se ejecuta la tarea
}
# Tipos de core
1. Xtensa
2. RISC-V

# Familia ESP32
1. ESP32
- Cores xtensa LX6 
- Wifi
- Bluetooth + BLE (Bluetooth Low Energy)
Datasheet: https://www.espressif.com/sites/default/files/documentation/esp32_datasheet_en.pdf

2. ESP32-C
- Cores RISC-V
- Low Energy
- Wifi
- BLE
Datasheet: https://www.espressif.com/sites/default/files/documentation/esp32-c3_datasheet_en.pdf

3. ESP32-S
- Cores Xtensa LX7
- High Speed
- WiFi
- USB-OTG
- Camera Interface
- LCD Interface
Datasheet: https://www.espressif.com/sites/default/files/documentation/esp32-s2_datasheet_en.pdf


Link fabricante: https://www.espressif.com/en

# Documentacion 
## ESP-IDF
Ref: https://docs.espressif.com/projects/esp-idf/
Contiene todos lo necesario para el desarrollo, es una guia de programacion del ESP

# Instalacion de esp
C:\Espressif\frameworks\esp-idf-v5.2.2

# Liberias
- chip_info: Obtener informacion del modulo
```code
#include "esp_chip_info.h"
```

- FreeRTOS con ESP32: Util para realizar procesos por tareas
```code
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
```

- NVS (No Volatil Storage): Almacena datos en memoria, parecido a localStorage de JS
``` code
#include <nvs_flash.h>
#include <nvs.h>
```
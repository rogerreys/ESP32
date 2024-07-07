#include <stdio.h>
#include "esp_chip_info.h"

void app_main(void)
{
    int length = 4;
    int width = 6;
    int area;

    // Calculate the area of a rectangle
    area = length * width;

    // Print the variables
    printf("Length is: %d\n", length);
    printf("Width is: %d\n", width);
    printf("Area of the rectangle is: %d\n", area);

    esp_chip_info_t chip_info;
    esp_chip_info(&chip_info);
    printf("Este es un chip tipo %s, y tiene %d cores\n", 
    CONFIG_IDF_TARGET,
    chip_info.cores);
}

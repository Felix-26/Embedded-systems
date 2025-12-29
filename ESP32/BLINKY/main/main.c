#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"


#define BLINK_LED1 2 // GPIO number for the LED1
#define BLINK_LED2 4 // GPIO number for the LED2

void blink1(void *pvParameter)
{
    gpio_reset_pin(BLINK_LED1);
    gpio_set_direction(BLINK_LED1, GPIO_MODE_OUTPUT);

    while (1) {
        printf("LED1 ON\n");
        gpio_set_level(BLINK_LED1, 1);
        vTaskDelay(1000/portTICK_PERIOD_MS);

        printf("LED1 OFF\n");
        gpio_set_level(BLINK_LED1, 0);
        vTaskDelay(1000/portTICK_PERIOD_MS);
    }
}

void blink2(void *pvParameter)
{
    gpio_reset_pin(BLINK_LED2);
    gpio_set_direction(BLINK_LED2, GPIO_MODE_OUTPUT);

    while (1) {
        printf("LED2 ON\n");
        gpio_set_level(BLINK_LED2, 1);
        vTaskDelay(500/portTICK_PERIOD_MS);

        printf("LED2 OFF\n");
        gpio_set_level(BLINK_LED2, 0);
        vTaskDelay(500/portTICK_PERIOD_MS);
    }
}

void app_main(void)
{
    xTaskCreate(&blink1, "blink1", 2048, NULL, 5, NULL);
    xTaskCreate(&blink2, "blink2", 2048, NULL, 5, NULL);
}

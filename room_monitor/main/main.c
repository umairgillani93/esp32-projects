#include <stdio.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "driver/gpio.h"
#include "esp_err.h"
#include "dht.h"

#define DHT_GPIO GPIO_NUM_4

void app_main(void)
{
    float temperature = 0;
    float humidity = 0;

    while (1)
    {
        esp_err_t err = dht_read_float_data(
            DHT_TYPE_DHT11,
            DHT_GPIO,
            &humidity,
            &temperature);

        if (err == ESP_OK)
        {
            printf("\n");
            printf("-------------------------\n");
            printf("Temperature : %.1f °C\n", temperature);
            printf("Humidity    : %.1f %%\n", humidity);
            printf("-------------------------\n");
        }
        else
        {
            printf("Read failed: %s\n", esp_err_to_name(err));
        }

        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

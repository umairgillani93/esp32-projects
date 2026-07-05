#include <stdio.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "driver/gpio.h"
#include "esp_err.h"
#include "dht.h"

#include "sensor_data.h"
#include "wifi.h"
#include "webserver.h"

#define DHT_GPIO GPIO_NUM_4

void app_main(void)
{
		wifi_init();

		vTaskDelay(pdMS_TO_TICKS(5000));

		start_webserver();

    float temperature = 0.0;
    float humidity = 0.0;

    while (1)
    {
        esp_err_t err = dht_read_float_data(
            DHT_TYPE_DHT11,
            DHT_GPIO,
            &humidity,
            &temperature);

        if (err == ESP_OK)
        {
            g_temp = temperature;
            g_humid = humidity;

            printf("\n");
            printf("-------------------------\n");
            printf("Temperature : %.1f °C\n", g_temp);
            printf("Humidity    : %.1f %%\n", g_humid);
            printf("-------------------------\n");
        }
        else
        {
            printf("Read failed: %s\n", esp_err_to_name(err));
        }

        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

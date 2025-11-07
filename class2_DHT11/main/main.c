#include "esp32-dht11.h"
#define CONFIG_DHT11_PIN GPIO_NUM_10
#define CONFIG_CONNECTION_TIMEOUT 5

void app_main(){
    dht11_t dht11_sensor;
    dht11_sensor.dht11_pin = CONFIG_DHT11_PIN;

    while(1){
        if(!dht11_read(&dht11_sensor, CONFIG_CONNECTION_TIMEOUT)){
            printf("Temperature: %.2f \n", dht11_sensor.temperature);
            printf("Humidity: %.2f \n", dht11_sensor.humidity);
        }
        vTaskDelay(2000/portTICK_PERIOD_MS);
    }
}Commit on 2025-10-19T12:00:00
Commit on 2025-10-21T12:00:00
Commit on 2025-10-27T12:00:00
Commit on 2025-10-29T12:00:00
Commit on 2025-10-22T12:00:00
Commit on 2025-11-07T12:00:00

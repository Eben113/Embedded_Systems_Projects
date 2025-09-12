#ifndef DHT11_H_
#define DHT11_H_

#include "driver/gpio.h"
#include <stdio.h>
#include <string.h>
#include <rom/ets_sys.h>
#include "esp_log.h"
#include <inttypes.h>
#include "sdkconfig.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_chip_info.h"
#include "esp_flash.h"
#include "esp_system.h"

enum dht11_status{
DHT11_CRC_ERROR = -2,
DHT11_TIMEOUT_ERROR,
DHT11_OK};

typedef struct {
    int dht11_pin;
    int status;
    double temperature;
    double humidity;
} dht11_t;

void DHT11_init(gpio_num_t);

int dht11_read();

#endif
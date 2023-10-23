#ifndef LED_H
#define LED_H

#include <zephyr/drivers/gpio.h>
#include <zephyr/kernel.h>

typedef const enum {
    LED_OFF,
    LED_ON
}led_state;

void led_init();
void led_mode(const short mode);

#endif
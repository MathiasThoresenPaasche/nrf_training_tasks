#ifndef LED_H
#define LED_H

#include <zephyr/drivers/gpio.h>
#include <zephyr/kernel.h>

typedef const enum {
    LED_OFF=0,
    LED_ON
}led_state;


typedef const enum{
    LED_NS=10,
    LED_EW,
    LED_PEDESTRIAN
}led_lane;


void led_init();
void led_mode(const short mode);
void led_flash(const short lane);
void led_lane_stop_go(const short lane, const short mode);
void led_pedestrian();

#endif
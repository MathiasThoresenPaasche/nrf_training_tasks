#ifndef BUTTON_H
#define BUTTON_H

#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/devicetree.h>
#include <zephyr/drivers/gpio.h>


typedef void(*ButtonCallback)(const short button);

typedef const enum{
    E_PEDESTRIAN_BUTTON = 100,
    W_PEDESTRIAN_BUTTON
}button_type;

void button_init(ButtonCallback ext_callback);
#endif
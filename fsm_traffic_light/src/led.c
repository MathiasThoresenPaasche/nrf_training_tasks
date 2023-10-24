#include "led.h"
#include "log.h"
#include <stdio.h>
LOG_MODULE_DECLARE(log_module);
#define SLEEP_TIME_MS 150
#define PEDESTRIAN_TIME_MS 25

// Device Tree aliases for LEDs
#define LED0_NODE DT_ALIAS(led0)
#define LED1_NODE DT_ALIAS(led1)
#define LED2_NODE DT_ALIAS(led2)
#define LED3_NODE DT_ALIAS(led3)

// GPIO specifications for LEDs
static const struct gpio_dt_spec leds[] = {
    GPIO_DT_SPEC_GET(LED0_NODE, gpios),
    GPIO_DT_SPEC_GET(LED1_NODE, gpios),
    GPIO_DT_SPEC_GET(LED2_NODE, gpios),
    GPIO_DT_SPEC_GET(LED3_NODE, gpios)
};

static const int num_led = ARRAY_SIZE(leds);

void led_init(){
    int ret;
    if (!device_is_ready(leds[0].port)) {
    LOG_ERR("Device is not ready!\n");
    return;
	}

    for (int i = 0; i < num_led; i++){
        ret = gpio_pin_configure_dt(&leds[i], GPIO_OUTPUT_INACTIVE);
        if (ret < 0) {
            return;
        }
    }
    led_mode(LED_ON);
    LOG_INF("led_init() complete\n");
}
void led_mode(const short mode){
    
    for (int i = 0; i < num_led; i++){
        gpio_pin_set_dt(&leds[i],mode);
    }
    char modeStr[20];
    snprintf(modeStr, sizeof(modeStr), "%d", mode);  //
    LOG_INF("Led mode: %s\n", modeStr);
}

void led_flash(const short lane){
    if (lane ==LED_NS){
        for (int i = 0; i < 10; i++) {
            gpio_pin_toggle_dt(&leds[0]);
            gpio_pin_toggle_dt(&leds[3]);
            k_msleep(SLEEP_TIME_MS);
        }
    }else if (lane == LED_EW)
    {
        for (int i = 0; i < 10; i++) {
            gpio_pin_toggle_dt(&leds[1]);
            gpio_pin_toggle_dt(&leds[2]);
            k_msleep(SLEEP_TIME_MS);
        }
    }
    else{
        LOG_WRN("Inccorect input to led_flash");
    }   
}

void led_lane_stop_go(const short lane, const short mode){
    if (lane ==LED_NS){
        gpio_pin_set_dt(&leds[0], mode);
        gpio_pin_set_dt(&leds[3], mode);        
    }
    else if (lane ==LED_EW){
        gpio_pin_set_dt(&leds[1], mode);
        gpio_pin_set_dt(&leds[2], mode); 
    }
    else{
        LOG_WRN("Inccorect input to led_lane_stop_go");
    }
}

void led_pedestrian(){
    for (int i = 0; i < 120; i++) {
            gpio_pin_toggle_dt(&leds[3]);
            k_msleep(PEDESTRIAN_TIME_MS);
        }
    for (int i = 0; i < 10; i++) {
            gpio_pin_toggle_dt(&leds[3]);
            k_msleep(SLEEP_TIME_MS);
        }    
}

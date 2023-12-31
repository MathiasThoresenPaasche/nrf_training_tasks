#include "led.h"
#include "log.h"
#include <stdio.h>
LOG_MODULE_DECLARE(log_module);


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
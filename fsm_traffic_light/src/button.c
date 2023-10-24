#include "button.h"
#include "log.h"


// Define aliases for buttons
#define NUM_BUTTONS 2
// #define SW0_NODE DT_ALIAS(sw0)
#define SW1_NODE DT_ALIAS(sw1)
#define SW2_NODE DT_ALIAS(sw2)
// #define SW3_NODE DT_ALIAS(sw3)
LOG_MODULE_DECLARE(log_module);


static const struct gpio_dt_spec buttons[] = {
    // GPIO_DT_SPEC_GET(SW0_NODE, gpios),
    GPIO_DT_SPEC_GET(SW1_NODE, gpios),
    GPIO_DT_SPEC_GET(SW2_NODE, gpios)//,
    // GPIO_DT_SPEC_GET(SW3_NODE, gpios)
};

static struct gpio_callback callbacks[NUM_BUTTONS];

static ButtonCallback button_callback;

void _button_pressed(const struct device *dev, struct gpio_callback *callback, uint32_t pins){
    if (callback == &callbacks[0]) {
        LOG_INF("W pedestrian button pressed");
        button_callback(W_PEDESTRIAN_BUTTON); // Notify CARD_BUTTON press
    } else if (callback == &callbacks[1]) {
        button_callback(E_PEDESTRIAN_BUTTON); // Notify PUSH_BUTTON press
        LOG_INF("E pedestrian button pressed");
    }
}


void button_init(ButtonCallback ext_callback){
    int ret;
    LOG_INF("button_init begin.");

    if (!device_is_ready(buttons[0].port)) {
        LOG_ERR("Device is not ready!\n");
        return;
	}
    for (int i = 0; i < NUM_BUTTONS; i++){
        ret = gpio_pin_configure_dt(&buttons[i], GPIO_INPUT);
        if (ret < 0) {
            LOG_ERR("Button  %d GPIO_INPUT is not configured!\n",i);
            return;
        }
	    ret = gpio_pin_interrupt_configure_dt(&buttons[i], GPIO_INT_EDGE_FALLING);
        if (ret < 0) {
            LOG_ERR("Button %d iterrupt is not configured!\n",i);
            return;
        }   
        gpio_init_callback(&callbacks[i], _button_pressed, BIT(buttons[i].pin));
        gpio_add_callback(buttons[i].port, &callbacks[i]);
    }
    button_callback = ext_callback;
    LOG_INF("button_init end.");
}
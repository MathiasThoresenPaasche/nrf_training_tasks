#include "timer.h"
#include "log.h"
#include <zephyr/kernel.h>

LOG_MODULE_DECLARE(log_module);


#define TIMER_STACKSIZE 512
#define SLEEP_TIME_MS 5000

// K_THREAD_STACK_DEFINE(timer_thread_stack, TIMER_STACKSIZE);
// static struct k_thread timer_thread_data;
static K_TIMER_DEFINE(light_timer, NULL, NULL);

void timer_thread_func(void *p1, void *p2, void *p3) {
    LOG_INF("Timer thread start");
    while (1) {
        // Start the timer with a duration of SLEEP_TIME_MS milliseconds
        k_timer_start(&light_timer, K_MSEC(SLEEP_TIME_MS), K_NO_WAIT);
        // Wait for the timer to expire
        k_timer_status_sync(&light_timer);
        LOG_INF("Timer expired. Transitioning to ew_green state.");
        
        // Access the global StateMachine variable state_machine and transition to ew_green
        // transition(&sm, ew_green);
    }
}
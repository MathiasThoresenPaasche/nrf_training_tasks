#include "fsm.h"
#include "led.h"
#include "log.h"
#include "timer.h"
#include <zephyr/kernel.h>
LOG_MODULE_DECLARE(log_module);
/* 1000 msec = 1 sec */
#define SLEEP_TIME_MS   6000
#define TIMER_STACKSIZE 512

// K_THREAD_STACK_DEFINE(timer_thread_stack, TIMER_STACKSIZE);
// static struct k_thread timer_thread_data;
// static K_TIMER_DEFINE(light_timer, NULL, NULL);

void light_timer_expire(struct  k_timer *timer_id){
    
}



void transition(StateMachine *sm, StatePtr new_state){
    sm->current_state(sm, EXIT);
    sm->current_state = new_state;
    sm->current_state(sm, ENTRY);
}
void check_pedestrian_button_if_go(StateMachine *sm){
    if (k_mutex_lock(sm->mtx, K_MSEC(100)) == 0) {
        /* mutex successfully locked */
            if(sm->pedestrian_button_pressed){
                k_mutex_unlock(sm->mtx);
                sm->current_state = ew_pedestrian_green;
                sm->current_state(sm,ENTRY);
                }

        } else {
        LOG_WRN("Cannot lock pedestrian_mtx");
        }
    k_mutex_unlock(sm->mtx);
}



void init(StateMachine *sm, Event ev){
    switch (ev)
    {
    case INIT:
        LOG_INF("init INIT");
        sm->current_state = init;
        led_init();
        transition(sm,ns_green);
        break;
    case ENTRY:
        LOG_INF("init ENTRY");
        
        break;
    case EXIT:
        led_mode(LED_OFF);
        break;    
    default:
        LOG_WRN("init ERROR default");
        break;
    }
}

void ns_green(StateMachine *sm, Event ev){
    switch (ev)
    {
    case ENTRY:
        LOG_INF("ns_green ENTRY");
        led_lane_stop_go(LED_NS,LED_ON);
        // k_thread_create(&timer_thread_data, timer_thread_stack,
        //                     K_THREAD_STACK_SIZEOF(timer_thread_stack),
        //                     timer_thread_func, NULL, NULL, NULL, 0, 
        //                     K_USER | K_INHERIT_PERMS, K_NO_WAIT);

        k_msleep(SLEEP_TIME_MS);
        transition(sm, ew_green);
        break;
    case EXIT:
        LOG_INF("ns_green EXIT");
        led_flash(LED_NS);
        led_lane_stop_go(LED_NS,LED_OFF);
        break;
    case PEDESTRIAN_BUTTON:
        LOG_INF("ns_green PEDESTRIAN_BUTTON");
        break;
    case TIMER_OUT:
        LOG_INF("ns_green TIMER_OUT");
        //TIMER OUT
        // k_timer_status_sync(&light_timer);
        // transition(sm, ew_green);
        break;    
    default:
        LOG_WRN("ns_green ERROR default");
        break;
    }
}

void ew_green(StateMachine *sm, Event ev){
    switch (ev)
    {
    case ENTRY:
        LOG_INF("ew_green ENTRY");
        led_lane_stop_go(LED_EW,LED_ON);
        check_pedestrian_button_if_go(sm);
        k_msleep(SLEEP_TIME_MS);
        check_pedestrian_button_if_go(sm);
        sm->current_state(sm,TIMER_OUT);
        break;
    case EXIT:
        led_flash(LED_EW);
        led_lane_stop_go(LED_EW,LED_OFF);
        LOG_INF("ew_green EXIT");
        break;
    case PEDESTRIAN_BUTTON:
        LOG_INF("ew_green PEDESTRIAN_BUTTON");
        break;
    case TIMER_OUT:
        LOG_INF("ew_green TIMER_OUT");
        transition(sm, ns_green);
        break;    
    default:
        LOG_WRN("ew_green ERROR default");
        break;
    }
}

void ew_pedestrian_green(StateMachine *sm, Event ev){
    switch (ev)
    {
    case ENTRY:
        LOG_INF("ew_pedestrian_green ENTRY");
        led_pedestrian();
        sm->current_state(sm,TIMER_OUT);
        break;
    case EXIT:
        LOG_INF("ew_pedestrian_green EXIT");
        if (k_mutex_lock(sm->mtx, K_MSEC(100)) == 0) {
            /* mutex successfully locked */
            sm->pedestrian_button_pressed = false;
            k_mutex_unlock(sm->mtx);
        } else {
        LOG_WRN("Cannot lock pedestrian_mtx");
        }
        k_mutex_unlock(sm->mtx);

        LOG_INF("Pedestrian_button_pressed = false");
        sm->current_state = ew_green;
        sm->current_state(sm, TIMER_OUT);
        break;
    case TIMER_OUT:
        LOG_INF("ew_pedestrian_green TIMER_OUT");
        sm->current_state(sm,EXIT);
        break;    
    default:
        LOG_WRN("ew_pedestrian_green ERROR default");
        break;
    }
}

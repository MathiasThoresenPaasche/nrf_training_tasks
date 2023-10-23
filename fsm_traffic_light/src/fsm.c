#include "fsm.h"
#include "led.h"
#include "log.h"
#include <zephyr/kernel.h>
LOG_MODULE_DECLARE(log_module);
/* 1000 msec = 1 sec */
#define SLEEP_TIME_MS   1000

K_TIMER_DEFINE(light_timer, light_timer_expire, NULL);

void light_timer_expire(struct  k_timer *timer_id){
    
}



void transition(StateMachine *sm, StatePtr new_state){
    
    sm->current_state(sm, EXIT);
    
    sm->current_state = new_state;

    sm->current_state(sm, ENTRY);
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
        led_mode(LED_OFF);
        k_msleep(SLEEP_TIME_MS);
        transition(sm, ew_green);
        break;
    case EXIT:
        LOG_INF("ns_green EXIT");
        
        break;
    case PEDESTRIAN_BUTTON:
        LOG_INF("ns_green PEDESTRIAN_BUTTON");
        break;
    case TIMER_OUT:
        LOG_INF("ns_green TIMER_OUT");
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
        led_mode(LED_ON);
        k_msleep(SLEEP_TIME_MS);
        // k_timer_start(&light_timer,K_SECONDS(3), K_NO_WAIT);
        transition(sm, ns_green);
        break;
    case EXIT:
        LOG_INF("ew_green EXIT");
        break;
    case PEDESTRIAN_BUTTON:
        LOG_INF("ew_green PEDESTRIAN_BUTTON");
        break;
    case TIMER_OUT:
        LOG_INF("ew_green TIMER_OUT");
        // k_timer_status_sync(&light_timer);
        // transition(sm, ns_green);
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
        break;
    case EXIT:
        LOG_INF("ew_pedestrian_green EXIT");
        break;
    case PEDESTRIAN_BUTTON:
        LOG_INF("ew_pedestrian_green PEDESTRIAN_BUTTON");
        break;
    case TIMER_OUT:
        LOG_INF("ew_pedestrian_green TIMER_OUT");
        break;    
    default:
        LOG_WRN("ew_pedestrian_green ERROR default");
        break;
    }
}

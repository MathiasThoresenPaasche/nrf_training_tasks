#ifndef FSM_H
#define FSM_H
#include <zephyr/kernel.h>



typedef enum{
    INIT,
    ENTRY,
    EXIT,
    PEDESTRIAN_BUTTON,
    TIMER_OUT
}Event;


typedef struct StateMachine  StateMachine;
typedef void(*StatePtr)(StateMachine * sm, Event ev);

struct StateMachine{
    StatePtr current_state;
};

void transition(StateMachine *sm, StatePtr new_state);
void light_timer_expire(struct  k_timer *timer_id);


void init(StateMachine *sm, Event ev);
void ns_green(StateMachine *sm, Event ev);
void ew_green(StateMachine *sm, Event ev);
void ew_pedestrian_green(StateMachine *sm, Event ev);



#endif
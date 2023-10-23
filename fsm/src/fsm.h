#ifndef FSM_H
#define FSM_H
#include <zephyr/kernel.h>
#include "fsm_base.h"

typedef struct Fsm Fsm;
struct Fsm{
    struct FsmBase super;
};

enum{
    CARD_SIG = 2000,
    PUSH_SIG
};

void fsm_ctr(Fsm *this);



#endif
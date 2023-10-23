#ifndef FSM_BASE_H
#define FSM_BASE_H
#include <zephyr/kernel.h>

typedef struct Event Event;
typedef struct FsmBase FsmBase;
typedef short Signal;


typedef void(*StateFptr)(FsmBase *this, const Event *const ev);


struct FsmBase{
    k_tid_t _ev_tid;
    StateFptr _state_fptr;
    struct k_queue _ev_queue;
    struct k_thread _ev_thread_data;
    k_thread_stack_t *_heap_mem;
};

struct Event{
    Signal sig;
};

enum{
    INIT_SIG=1000,
    ENTRY_SIG,
    EXIT_SIG
};

void fsm_base_ctr(FsmBase *this, StateFptr init_state_fptr);
void fsm_base_dtr(FsmBase *this);
void fsm_base_add_ev(FsmBase *this, const Event *const ev);
void fsm_base_tran(FsmBase *this, StateFptr new_state_ptr);

#endif
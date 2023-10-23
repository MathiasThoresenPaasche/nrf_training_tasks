#include "log.h"
#include "fsm_base.h"

#define FSM_MEM  1024
#define HEAP_MEM 2048

LOG_MODULE_DECLARE(log_module);
K_HEAP_DEFINE(my_heap, HEAP_MEM);

void _fsm_base_dispatch(FsmBase *this, const Event *const ev);
void _fsm_base_event_handler_thread(void *this, void *, void *);

void fsm_base_ctr(FsmBase *this, StateFptr init_state_fptr){
    LOG_INF("fsm_base_ctr begins");
    k_thread_stack_t *ptr = k_heap_alloc(&my_heap,FSM_MEM,K_NO_WAIT);
    // k_thread_stack_t *ev_handler_mem = k_heap_alloc(&fsm_heap, FSM_MEM, K_NO_WAIT);

    LOG_INF("Heap memory allocated");
    this->_heap_mem = ptr;
    if (this->_heap_mem == NULL) {
        LOG_ERR("HEAP FAILED TO ASSIGNE.");
        
    }
    LOG_INF("this got heap mem");
    k_queue_init(&this->_ev_queue);
    LOG_INF("k_queue assigned");
    this->_ev_tid = k_thread_create(&this->_ev_thread_data, this->_heap_mem,
                                        FSM_MEM, _fsm_base_event_handler_thread,
                                        this, NULL, NULL, 1, 0, K_NO_WAIT);
    // this->_ev_tid = k_thread_create(&this->_ev_thread_data,
    //                                 this->_heap_mem,FSM_MEM,
    //                                 _fsm_base_event_handler_thread,
    //                                 this,NULL,NULL, 0,0,K_NO_WAIT);

    this->_state_fptr = init_state_fptr;
    
    Event ev_entry;
    ev_entry.sig = ENTRY_SIG;
    _fsm_base_dispatch(this, &ev_entry);
    
    Event ev_init;
    ev_init.sig = INIT_SIG;
    _fsm_base_dispatch(this, &ev_init);
    LOG_INF("fsm_base_ctr end");
}

void fsm_base_add_ev(FsmBase *this, const Event *const ev){
    LOG_INF("New item added to queue");
    k_queue_append(&this->_ev_queue,(void *)ev);
}

void _fsm_base_dispatch(FsmBase *this,const Event *const ev){
    this->_state_fptr(this, ev);
}
void fsm_base_tran(FsmBase *this, StateFptr new_state_ptr){
    LOG_INF("fsm_base_tran begin");
    Event ev_exit;
    ev_exit.sig = EXIT_SIG;
    _fsm_base_dispatch(this,&ev_exit);

    this->_state_fptr = new_state_ptr;

    Event ev_entry;
    ev_entry.sig = ENTRY_SIG;
    _fsm_base_dispatch(this, &ev_entry);
    LOG_INF("fsm_base_tran end");

}

void _fsm_base_event_handler_thread(void *this,void *,void*){
    LOG_INF("_fsm_base_event_handler_thread started.");
    while(true){
        // FsmBase *this = (FsmBase *) this;// Casting to FsmBase from void *
        // const Event *const ev = (Event *)k_queue_get(&(this)->_ev_queue, K_FOREVER);
        const Event *const ev =
            (Event *)k_queue_get(&((FsmBase *)this)->_ev_queue, K_FOREVER);
        LOG_INF("fsm_base_event_handler_thread got sig");


        // LOG_INF(*(ev)->sig);
        _fsm_base_dispatch(this,ev);
        LOG_INF("_fsm_base_event_handler_thread yielding now.");
        k_yield();
    }
}

void fsm_base_dtr(FsmBase *this){
    k_thread_abort(this->_ev_tid);
    k_heap_free(&my_heap,this->_heap_mem);
}
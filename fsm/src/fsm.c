#include "fsm.h"
#include "button.h"
#include "led.h"
#include "log.h"
#include <stdio.h>

LOG_MODULE_DECLARE(log_module);

void _fsm_locked(Fsm *this, const Event * const ev);

void _fsm_open(Fsm *this, const Event * const ev){
    LOG_INF("_fsm_open begin.");
    //print
    Signal sig = ev->sig;
    char sig_str[20];
    snprintf(sig_str, sizeof(sig_str), "%d", sig);  
    //
    LOG_INF("Signal number: %s\n", sig_str); 
    switch (sig)
    {
    case ENTRY_SIG:
        LOG_INF("_fsm_open ENTRY_SIG");
        led_mode(LED_ON);
        break;
    case EXIT_SIG:
        LOG_INF("_fsm_open EXIT_SIG");
        led_mode(LED_OFF);
        break;
    case CARD_SIG:
        LOG_WRN("fsm_open CARD_SIG: Gate is already open.");
        break;
    case PUSH_SIG:
        LOG_WRN("_fsm_open PUSH_SIG: Going through gate.");
        fsm_base_tran(&this->super,(StateFptr)&_fsm_locked);
        break;

    default:
        LOG_ERR("CANT HANDLE DEFUALT");
        break;
    }

}
void _fsm_locked(Fsm *this, const Event * const ev){
    LOG_INF("_fsm_locked begin.");
    Signal sig = ev->sig; 
    char sig_str[20];
    snprintf(sig_str, sizeof(sig_str), "%d", sig);  //
    LOG_INF("Signal number: %s\n", sig_str);
    switch (sig)
    {
    case ENTRY_SIG:
        LOG_INF("_fsm_locked ENTRY_SIG");
        break;
    case EXIT_SIG:
        LOG_INF("_fsm_locked EXIT_SIG");
        break;
    case CARD_SIG:
        LOG_WRN("_fsm_locked CARD_SIG: Key card registrated. Gate is open.");
        fsm_base_tran(&this->super,(StateFptr)&_fsm_open);
        break;
    case PUSH_SIG:
        LOG_WRN("_fsm_locked PUSH_SIG: The gate is locked. Please present card to open gate.");
        break;
    default:
        LOG_ERR("CANT HANDLE DEFUALT");
        break;
    }
   
}

void _fsm_init(Fsm *this, const Event * const ev){
    LOG_INF("_fsm_init begin.");
    Signal sig = ev->sig; 
    switch (sig)
    {
    case INIT_SIG:
        LOG_INF("_fsm_init INIT_SIG");
        led_init();
        fsm_base_tran(&this->super,(StateFptr)&_fsm_locked);
        break;
    case ENTRY_SIG:
        LOG_INF("_fsm_init ENTRY_SIG");
        break;
    case EXIT_SIG:
        LOG_INF("_fsm_init EXIT_SIG");
        break;
    default:
        LOG_ERR("CANT HANDLE DEFUALT");
        break;
    }
}

void fsm_ctr(Fsm *this){
    LOG_INF("fsm_ctr begin.");
    fsm_base_ctr(&this->super,(StateFptr)&_fsm_init);
}




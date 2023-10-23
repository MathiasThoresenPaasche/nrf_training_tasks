/*
 * Copyright (c) 2016 Intel Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/kernel.h>
// #include <thread_analyzer.h>
#include "log.h"
#include "button.h"
#include "led.h"
#include "fsm.h"

#define HEAP_SIZE 2048
LOG_MODULE_DECLARE(log_module);
static StateMachine myStateMachine;


void _button_callback(const short button){
//   // Event ev;
  
//   switch (button)
//   {
//   case PUSH_BUTTON:
//     // ev.sig = PUSH_SIG;
//     fsm_base_add_ev(&fsm.super,&ev_push);
//     break;
//   case CARD_BUTTON:
//     // ev.sig = CARD_SIG;
//     fsm_base_add_ev(&fsm.super,&ev_card);
//     break;
//   default:
//     break;
//   }
}

// void new_state_machine(StateMachine *sm){
//   LOG_INF("new sm in making");
//   StatePtr new_state_ptr;
//   sm->current_state = init;
//   sm->current_state(sm,ENTRY);
//   sm->current_state(sm,INIT);
  
  
//   // StatePtr new_state = init;
//   // init(result,INIT);
//   // transition(result, new_state);
//   // return result;
//   }

void main(void)
{
  button_init(_button_callback);
  init(&myStateMachine,INIT);
  while(1){

  }
   
}
/*
 * Copyright (c) 2016 Intel Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/kernel.h>
#include <thread_analyzer.h>
#include "log.h"
#include "button.h"
#include "fsm.h"
#include "fsm_base.h"
static const Event ev_push = {.sig = PUSH_SIG};
static const Event ev_card = {.sig = CARD_SIG};
LOG_MODULE_DECLARE(log_module);
static Fsm fsm; 

void _button_callback(const short button){
  // Event ev;
  
  switch (button)
  {
  case PUSH_BUTTON:
    // ev.sig = PUSH_SIG;
    fsm_base_add_ev(&fsm.super,&ev_push);
    break;
  case CARD_BUTTON:
    // ev.sig = CARD_SIG;
    fsm_base_add_ev(&fsm.super,&ev_card);
    break;
  default:
    break;
  }
}

void main(void)
{
  LOG_INF("Main started.");
  fsm_ctr(&fsm);

  button_init(_button_callback);
  // thread_analyzer_print();
  
}
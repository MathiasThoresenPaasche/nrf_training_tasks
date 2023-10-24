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
K_MUTEX_DEFINE(pedestrian_mtx);
LOG_MODULE_DECLARE(log_module);
static StateMachine myStateMachine;


void _button_callback(const short button){
  if (k_mutex_lock(myStateMachine.mtx, K_MSEC(100)) == 0) {
    /* mutex successfully locked */
    if(!myStateMachine.pedestrian_button_pressed){
      myStateMachine.pedestrian_button_pressed = true;
    }
    k_mutex_unlock(myStateMachine.mtx);
    LOG_INF("Pedestrian_button_pressed = true");

  } else {
    LOG_WRN("Cannot lock pedestrian_mtx");
  }
  if(myStateMachine.current_state == ew_green){
    k_wakeup(myStateMachine.t_id);
  }
}

void main(void)
{
  myStateMachine.pedestrian_button_pressed = false;
  myStateMachine.mtx = &pedestrian_mtx;
  myStateMachine.t_id = k_current_get();
  button_init(_button_callback);
  init(&myStateMachine,INIT);
  // while(1){

  // }
   
}
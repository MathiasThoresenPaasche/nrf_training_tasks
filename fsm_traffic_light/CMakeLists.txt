#
# Copyright (c) 2016 Intel Corporation
#
# SPDX-License-Identifier: Apache-2.0
#

cmake_minimum_required(VERSION 3.20.0)
find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})
project(nrf_connect_sdk_fundamentals)

target_sources(app PRIVATE src/main.c)
target_sources(app PRIVATE src/log.c)
target_sources(app PRIVATE src/led.c)
target_sources(app PRIVATE src/button.c)
target_sources(app PRIVATE src/fsm.c)
# target_sources(app PRIVATE src/timer.c)


# target_sources(app PRIVATE build/zephyr/misc/generated/syscalls_links/include/zephyr/debug/thread_analyzer.h)

# target_include_directories(app PRIVATE
#     ${CMAKE_CURRENT_SOURCE_DIR}/build/zephyr/misc/generated/syscalls_links/include/zephyr/debug/)

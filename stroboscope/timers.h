#ifndef __TIMERS_H__
#define __TIMERS_H__

#include <Arduino.h>

#ifdef __cplusplus
extern "C" {
#endif

void start_timer_TC1 (uint32_t count, uint32_t channel) ;
void stop_timer_TC1 (uint32_t channel) ;

#ifdef __cplusplus
}
#endif
#endif

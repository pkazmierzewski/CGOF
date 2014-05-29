#ifndef TIMER_H_
#define TIMER_H_

#include "common.h"

typedef struct
{
  bool_e started;
  bool_e paused;
  int start_ticks;
  int paused_ticks;
}lifeTimer_t;

lifeTimer_t* timer_init ( void );
void timer_start ( lifeTimer_t* timer );
void timer_stop ( lifeTimer_t* timer );
void timer_pause ( lifeTimer_t* timer );
void timer_resume ( lifeTimer_t* timer );
int timer_get_ticks ( lifeTimer_t* timer );
bool_e timer_is_started ( lifeTimer_t* timer );
bool_e timer_is_paused ( lifeTimer_t* timer );

#endif

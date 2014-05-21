#include <stdlib.h>
#include "SDL/SDL.h"
#include "timer.h"
#include "common.h"

lifeTimer_t* timer_init ( void )
{
  lifeTimer_t* timer;
  timer = malloc ( sizeof ( lifeTimer_t ) );
  timer->started = FALSE;
  timer->paused = FALSE;
  return timer;
}

void timer_start ( lifeTimer_t* timer )
{
  timer->started = TRUE;
  timer->paused = TRUE;
  timer->start_ticks = SDL_GetTicks();
}

void timer_stop ( lifeTimer_t* timer )
{
  timer->started = FALSE;
  timer->paused = FALSE;
}

void timer_pause ( lifeTimer_t* timer )
{
  if( ( timer->started == TRUE ) && ( timer->paused == FALSE ) )
  {
    timer->paused = TRUE;
    timer->paused_ticks = SDL_GetTicks() - timer->start_ticks;
  }
}

void timer_resume ( lifeTimer_t* timer )
{
  if( timer->paused == TRUE )
  {
    timer->paused = FALSE;
    timer->start_ticks = SDL_GetTicks() - timer->paused_ticks;
    timer->paused_ticks = 0;
  }
}

int timer_get_ticks ( lifeTimer_t* timer )
{
  if( timer->started == TRUE )
  {
    if( timer->paused == TRUE )
    {
      return timer->paused_ticks;
    }
    else
    {
      return SDL_GetTicks() - timer->start_ticks;
    }
  }
  return 0;
}

bool_e timer_is_started ( lifeTimer_t* timer )
{
  return timer->started;
}

bool_e timer_is_paused ( lifeTimer_t* timer )
{
  return timer->paused;
}

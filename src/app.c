#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include "timer.h"
#include "common.h"
#include "debug.h"
#include "cell.h"
#define FRAMES_PER_SECOND 60

const int delay = 1000/FRAMES_PER_SECOND;
void main_loop ( void );
lifeTimer_t* fps;
lifeTimer_t* timer;
SDL_Surface* screen;

SDL_Surface* load_image ( char * filename )
{
  SDL_Surface* loadedImage = NULL;
  SDL_Surface* optimizedImage = NULL;
  loadedImage = IMG_Load (filename );
  if ( loadedImage != NULL )
  {
    optimizedImage = SDL_DisplayFormat ( loadedImage );
    SDL_FreeSurface ( loadedImage );
    if ( optimizedImage != NULL )
    {
      uint32_t colorkey = SDL_MapRGB ( optimizedImage->format, 0, 0xFF, 0xFF );
      SDL_SetColorKey ( optimizedImage, SDL_SRCCOLORKEY, colorkey );
    }
  }
  return optimizedImage;
}

void apply_surface ( int x, int y, SDL_Surface * source, SDL_Surface * destination, SDL_Rect * clip )
{
  SDL_Rect offset;
  offset.x = x;
  offset.y = y;
  SDL_BlitSurface ( source, clip, destination, &offset );
}

void clean_up ( void )
{
  TTF_Quit ( );
  LIFE_DBG ( "Bye Bye!" );
  SDL_Quit ( );
}

void run_app ( SDL_Surface* surface )
{
  screen = surface;
  cells_board_init ( 100, 100 );
  cells_board_set_struct ( DIEHARD, 50, 50 );
  fps = timer_init ( );
  timer = timer_init ( );
  main_loop ( );
  clean_up ( );
}

void put_pixel32 ( SDL_Surface *surface, int x, int y, Uint32 pixel )
{
  //Convert the pixels to 32 bit
  Uint32 *pixels = (Uint32 *)surface->pixels;
  //Set the pixel
  pixels[ ( y * surface->w ) + x ] = pixel;
}
int saturate (int val, int saturation)
{
  if (val > saturation)
    val = 0;
  else if (val < 0)
    val = saturation;
  return val;
}

void main_loop ( void )
{
  SDL_Event event;
  uint8_t* key_states;
  bool_e quit = FALSE;
  int coords [2] = {400, 300};
  bool_e pressed = FALSE;
  int cont = 0;
  while ( quit == FALSE )
  {
    while ( SDL_PollEvent ( &event ) )
    {
      if ( event.type == SDL_QUIT )
        quit = TRUE;
    }
    key_states = SDL_GetKeyState ( NULL );
    /*
     *if ( key_states [ SDLK_UP ] )
     *{
     *  LIFE_DBG ( "up" );
     *  put_pixel32 ( screen, coords[0], saturate(--coords[1], 600), 0xFF000000 );
     *  pressed = TRUE;
     *}
     *if ( key_states [ SDLK_DOWN ] )
     *{
     *  LIFE_DBG ( "down" );
     *  put_pixel32 ( screen, coords[0],  saturate(++coords[1], 600), 0xFF000000 );
     *  pressed = TRUE;
     *}
     *if ( key_states [ SDLK_RIGHT ] )
     *{
     *  LIFE_DBG ( "right" );
     *  put_pixel32 ( screen, saturate(++coords[0], 800), coords[1], 0xFF000000 );
     *  pressed = TRUE;
     *}
     *if ( key_states [ SDLK_LEFT ] )
     *{
     *  LIFE_DBG ( "left" );
     *  put_pixel32 ( screen, saturate(--coords[0], 800), coords[1], 0xFF000000 );
     *  pressed = TRUE;
     *}
     *if ( key_states [ SDLK_q ] )
     *  return;
     *if ( pressed == TRUE )
     *{
     *  SDL_Flip(screen);
     *  pressed = FALSE;
     *}
     */
    int color;
    timer_start ( timer );
    if ( cont++%255 == 0 )
    {
      cells_board_update ( );
      LIFE_DBG ("update");
    }
    for (int i=0; i<100; i++)
    {
      for (int j=0; j<100; j++)
      {
        color = cells_board_get_color ( i, j );
        if ( cells_board_get_state ( i, j ) )
        {
          color++;
          color =  color > 255 ? 255 : color;
        }
        else
        {
          color--;
          color =  color < 0 ? 0 : color;
        }
        cells_board_set_color ( i, j, color );
        put_pixel32 ( screen, i, j, color<<16 );
      }
    }
    SDL_Flip(screen);
    SDL_Delay ( delay - timer_get_ticks ( fps ) );
  }
} 

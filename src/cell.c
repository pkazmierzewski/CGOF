#include "debug.h"
#include "cell.h"
#include <stdlib.h>
typedef enum
{
  ALIVE = 0x00,
  DEAD,
  ALWAYS_DEAD,
  ALWAYS_ALIVE
}cellState_e;

typedef struct
{
  cellState_e state;
  int swap_state;
  int cell_color;
}cell_s;
/*typedef int cell_s;*/
cell_s** board;
int x_max;
int y_max;

static void put_diehard ( int x, int y );
static void put_crocodile ( int x, int y );
static void swap_cell ( int x, int y );
static void check_cell ( int x, int y );

int cells_board_init ( int x, int y )
{
  x_max = x-1;
  y_max = y-1;
  board = ( cell_s** )malloc( x*sizeof ( cell_s ) );
  for ( int i = 0; i<x; i++ )
    board[i] = ( cell_s* )malloc ( y*sizeof ( cell_s ) );
  
  for (int i=0; i<x; i++)
    for (int j=0; j<y; j++)
    {
      board[i][j].swap_state = 0;
      if ( j==0 || i==0 || j==(y-1) || i==(x-1) )
        board[i][j].state = ALWAYS_DEAD;
      else
        board[i][j].state = DEAD;
    }
  return 0;
}

void cells_board_set_struct ( structs_e struct_, int x, int y )
{
  switch (struct_)
  {
    case CROCODILE:
      put_crocodile ( x, y );
      break;
    case DIEHARD:
      put_diehard ( x, y );
    default:
      break;
  }
}

static void put_diehard ( int x, int y )
{
  board[x][y].state = DEAD;
  board[x+1][y].state = DEAD;
  board[x+2][y].state = DEAD;
  board[x+3][y].state = DEAD;
  board[x+4][y].state = DEAD;
  board[x+5][y].state = DEAD;
  board[x+6][y].state = ALIVE;
  board[x+7][y].state = DEAD;

  board[x][y+1].state = ALIVE;
  board[x+1][y+1].state = ALIVE;
  board[x+2][y+1].state = DEAD;
  board[x+3][y+1].state = DEAD;
  board[x+4][y+1].state = DEAD;
  board[x+5][y+1].state = DEAD;
  board[x+6][y+1].state = DEAD;
  board[x+7][y+1].state = DEAD;

  board[x][y+2].state = DEAD;
  board[x+1][y+2].state = ALIVE;
  board[x+2][y+2].state = DEAD;
  board[x+3][y+2].state = DEAD;
  board[x+4][y+2].state = DEAD;
  board[x+5][y+2].state = ALIVE;
  board[x+6][y+2].state = ALIVE;
  board[x+7][y+2].state = ALIVE;
}

void cells_board_update ( void )
{
  for (int i=1; i<x_max-1; i++)
    for (int j=1; j<y_max-1; j++)
      check_cell ( i, j );
  for (int i=1; i<x_max-1; i++)
    for (int j=1; j<y_max-1; j++)
      swap_cell ( i, j );
}

static void swap_cell ( int x, int y )
{
  if ( board[x][y].swap_state == 1 )
  {
    board[x][y].state = board[x][y].state == DEAD ? ALIVE : DEAD;
  }
}

int cells_board_get_color ( int x, int y )
{
  return board [x][y].cell_color;
}

void cells_board_set_color ( int x, int y, int color )
{
  board [x][y].cell_color = color;
}

int cells_board_get_state ( int x, int y )
{
  return board [x][y].state == DEAD || board [x][y].state == ALWAYS_DEAD ? 0 : 1;
}

static void check_cell ( int x, int y )
{
  int loc_x = x-1;
  int loc_y = y-1;
  int cont = 0;
  if ( board[x][y].state == DEAD )
  {
    for (int i=loc_x; i<loc_x+3; i++)
      for ( int j=loc_y; j<loc_y+3; j++ )
      {
        if (i == x && j == y )
          continue;
        if ( board[x][y].state == ALIVE || board[x][y].state == ALWAYS_ALIVE )
          cont++;
        if (cont >= 3)
        {
          board[x][y].swap_state = 1;
          return;
        }
      }
  }
  else
  {
    for (int i=loc_x; i<loc_x+3; i++)
      for ( int j=loc_y; j<loc_y+3; j++ )
      {
        if (i == x && j == y )
          continue;
        if ( board[x][y].state == ALIVE || board[x][y].state == ALWAYS_ALIVE )
          cont++;
        if ( !(cont ==  3||cont == 2) )
        {
          board[x][y].swap_state = 1;
          return;
        }
      }
  }
}

static void put_crocodile ( int x, int y )
{
  return;
}
/*
 *int cells_test ( void )
 *{
 *  int k = 0;
 *  for (int i=0; i<10; i++)
 *    for (int j=0; j<10; j++)
 *      board[i][j] = k++;
 *
 *  for (int i=0; i<10; i++)
 *    for (int j=0; j<10; j++)
 *      LIFE_DBG("x:%d;y:%d val:%d",i,j,board[i][j]);
 *  return 0;
 *}
 */

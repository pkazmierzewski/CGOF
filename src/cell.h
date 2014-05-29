#ifndef CELL_H_
#define CELL_H_

typedef enum
{
  CROCODILE = 0x00,
  ACORN,
  DIEHARD
}structs_e;

typedef enum
{
  ALIVE = 0x00,
  DEAD,
  ALWAYS_DEAD,
  ALWAYS_ALIVE
}cellState_e;

int cells_board_init ( int x, int y );
void cells_board_set_struct ( structs_e struct_, int x, int y );
void cells_board_update ( void );
int cells_board_get_color ( int x, int y );
void cells_board_set_color ( int x, int y, int color );
int cells_board_get_state ( int x, int y );
//int cells_test ( void );

#endif

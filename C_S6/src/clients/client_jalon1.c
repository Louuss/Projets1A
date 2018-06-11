#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include "interface.h"

/*
Bacis client which returns only strings.
 */


char const* get_player_name()
{
    return "client_0";
}


void initialize(unsigned int id, unsigned int n_players)
{
  if (id <= n_players)
    printf("Player ID : %d\n", id);
}


struct move play(enum card_id card, struct move const previous_moves[], size_t n_moves)
{

  struct move my_move;
  my_move.check = VALID;
  my_move.player = 1;
  my_move.card = 1;
  my_move.onto.x = 0;
  my_move.onto.y = 0;
  my_move.dir = NORTH;
  my_move.place = NO_MEEPLE;
  printf("I MOVE \n");
  return my_move;
}


void finalize() {
    printf("FINALIZED\n" );
}

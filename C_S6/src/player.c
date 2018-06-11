#include <stdlib.h>
#include "player.h"



/**
@brief Creates a player (initialises it). 
@param An int (corresponding to an ID)
@return A struct player.
 */
struct player * create_player(int id){
  struct player *tmp=malloc(sizeof(struct player));
  tmp->id=id;
  tmp->meep=7;
  tmp->points=0;
  return tmp;
}

/**
@brief Frees the memory used to create the struct  player.
@param A struct player
 */
void free_player(struct player* p)
{
  free(p); 
}

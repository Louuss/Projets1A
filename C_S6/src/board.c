#include <stdio.h>
#include <stdlib.h>

#include "board.h"

/**
@brief Fonction used to create a toric grid.
@param int , int
@return int
@details Exemple : a = 10, n = 10, returns 0.
 */
int mod(int a, int n){
  if(a>=0)
    return a%n;
  return mod(a+n,n);
}


/**
@brief Returns the coords of the card located North, West, East or South from a card.
@param : a direction and a position
@return : a position
@details Exemple : n = NORTH ; p = {3;4} returns {3;5}.
 */
struct position posit(enum direction n, struct position p){
  switch(n){
  case 3:
    p.x = mod(p.x + 1 ,BOARD_SIZE);
    break;
  case 0:
    p.y = mod(p.y +1 ,BOARD_SIZE);
    break;
  case 1:
    p.x = mod(p.x -1 , BOARD_SIZE);
    break;
  case 2:
    p.y = mod(p.y - 1 , BOARD_SIZE);
    break;
  }
  return p;
}


/**
@brief Returns the number of the middle place of each side for each direction
@param a direction
@return int
@details Exemple : NORTH returns 2, WEST 5, SOUTH 8 and EAST 11.
*/
int cardin(enum direction n){
  return (2 + n * 3);
}



/**
@brief Initializes the board
Param :
@return an initialised and empty board
*/
int*** init_board(){
  int *** board = malloc(sizeof(int**) * BOARD_SIZE);
  for(int i=0;i<BOARD_SIZE;i++){
    board[i]= malloc(sizeof(int*) * BOARD_SIZE);
    for(int j=0;j<BOARD_SIZE;j++){
      board[i][j] = malloc(sizeof(int) * 3);
      board[i][j][0] = SENTINEL;
    }
  }
  return board;
}


/**
@brief Initializes the game by placing the first card in the center of the board (position : {100,100}) (for a non toric board)
@param : a matrix of arrays (of size 3)
*/
void start_game(int ***board)
{
  board[0][0][0] = CARD_ROAD_STRAIGHT_CITY;
  board[0][0][1] = NORTH;
  board[0][0][2] = NO_MEEPLE;
}

/**
@brief Initializes the game by placing the first card in the center of the board (position : {100,100}) (for a non toric board)
@param A matrix of arrays (of size 3)
*/
void start_game_2(int ***board)
{
  board[100][100][0] = CARD_ROAD_STRAIGHT_CITY;
  board[100][100][1] = NORTH;
  board[100][100][2] = NO_MEEPLE;
}


/**
@brief Tells if the card is well placed (good orientation and well linked with the
other cards around)
@param The move tested, the board, a table of cards
@return A booleen
@details Exemple : A CARD_CITY_ALL_SIDES is not valid with a CARD_MONASTERY_ALONE.
*/

enum action valid_move(struct move *move, int ***board, struct card *tab_card){
  struct position pos=move->onto;
  int card = move->card;
  int compt = 0;
  for(enum direction dir=NORTH; dir<4; dir++){
    struct position p = posit(dir,pos);
    compt += (board[p.x][p.y][0] == SENTINEL);
    if(compt == 4)
      return FAILED;
    if(board[p.x][p.y][0] != SENTINEL)
      if(tab_card[board[p.x][p.y][0]].sides[opposite_side(side(board[p.x][p.y][1], dir))] !=
         tab_card[card].sides[side(move->dir, dir)])
	return FAILED;}
  return VALID;
}

/**
@brief Calculates the new number of the side corresponding to the frontiere to check, depending on the orientation of the card
@param An orientation, a side
@return A side (int)
@details Exemple : the card is positionned as the initialisation (north 2, west 5, south 8, east 11). Then, we turn the card left. Now, NORTH corresponds to WEST (etc). We need to change the numbers of the places (and put again north 2, west 5, south 8, east 11).
 */
int side(int orientation, int side_wanted){
  return 2+3*mod(-orientation+side_wanted,4);
}


/**
@brief Returns the opposite side of the actual side
@param A side (int)
@return A side (int)
@details Exemple : if takes EAST, returns WEST
*/
int opposite_side(int side) {
  return ((side +6) % 12);
}


/**
@brief Modifies the board by putting definitly a card on it (apply the move)
@param The move to apply, the board
*/
void place_move(const struct move* move, int *** board){
  int * cell = board[move->onto.x+100][move->onto.y+100];
  cell[0] = move->card;
  cell[1] = move->dir;
  cell[2] = move->place;
}



/**
@brief Fills the board with the last rounds' moves
@param Array of the last moves, the board, the number of player (makes the last moves' array's size), an array of cards.
*/
void fill_board_player(const struct move * last_n, int *** board, int n_player){
  for (int i=0; i<n_player; i++){
    if( (last_n[i].check==VALID))
       place_move(&last_n[i], board);
    }
}


/**
@brief Free the memory
@param The board
*/
void free_board(int*** board){
  for(int i =0 ; i< BOARD_SIZE; i++){
    for(int j = 0; j< BOARD_SIZE; j++){
      free(board[i][j]);
    }
    free(board[i]);
  }
  free(board);
}



/**
@debrief Verifies if the card is playable.
@param The id of the card, the array of cards, the board
@return 1 if the card can be played. Else 0.
*/
int playable(int card,struct card* cards, int*** board)
{
  struct move my_move;
  my_move.card = card;
  struct position pos;
  pos.x=-1;pos.y=-1;
  my_move.onto=pos;
  enum action valid = FAILED;

  for(int i =0; i<BOARD_SIZE; i++){
    for(int j=0; j<BOARD_SIZE; j++){
      if(board[i][j][0]==-1){
        if(!((board[i][mod(j-1, BOARD_SIZE)][0] == -1) &&
	     (board[i][mod(j+1, BOARD_SIZE)][0] == -1) &&
	     (board[mod(i-1, BOARD_SIZE)][j][0] == -1) &&
	     (board[mod(i+1, BOARD_SIZE)][j][0] == -1))){
	  // on prend la pos de la case
	  pos.x=i; pos.y=j;
	  my_move.onto = pos;

	  for(int v =0; v<4; v++) // test pour les 4 orientations
	    {
	      //changement d'orientation
	      my_move.dir =v ;
	      valid = valid_move(&my_move, board, cards); //test du move
	      if(valid==VALID)
		return 1;
	    }
	}
      }
    }

  }
  if (valid==FAILED)
    return 0;
  else
    return 1;
}


/**
@brief Function used as a graphic interface , to see where the cards are located onto the board.
@details Only called by server
 */
void display_board(int*** b,int mode,struct card tab_card[]){
  if(mode == 1){
    for(int i = 90 ; i<110;i++){
      printf("\n");
      for(int j = 90 ; j <110;j++){
	if(b[i][j][0] == -1)
	  printf("-");
  else if(i==100 && j==100)
    printf("*");
  else
	  printf("#");
      }
    }
  }

  if(mode == 2){
    for(int j = 0 ; j <BOARD_SIZE;j++){
      if(b[0][j][0] == -1)
        printf("*");
      else
        printf("|%d %d %d|",tab_card[b[0][j][0]].sides[side(b[0][j][1],WEST)],b[0][j][0],tab_card[b[0][j][0]].sides[side(b[0][j][1],3)]);
    }
  }
}



struct position convert_position_in(struct position posit){
  struct position convert_in;
  convert_in.x = 100 - posit.y;
  convert_in.y = 100 + posit.x;
  return convert_in;
}

struct position convert_position_out(struct position posit){
  struct position convert_out;
  if(posit.x > 100){
    convert_out.y = -(posit.x - 100);
  }
  else{
      convert_out.y = 100 - posit.x;
  }
  if(posit.y >= 100){
    convert_out.x =  posit.y - 100;
  }
  else{
    convert_out.x = - (100 - posit.y);
  }
  return convert_out;
}

// check if the x is in the array
// return 1 if it is
// 0 if not
int is_in(int x, int array[], int size)
{
  for(int i=0; i< size; i++)
  {
    if(array[i] == x)
      return 1;
  }
  return 0;
}

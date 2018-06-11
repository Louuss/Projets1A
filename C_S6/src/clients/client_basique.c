#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

#include <time.h>

#include "interface.h"
#include "board.h"
#include "player.h"
#include "deck.h"

int my_id;
int nb_player;
int***  board;
struct card* cards;


/**
@brief Gives the name of the player
@return A char
 */
char const* get_player_name()
{
    return "Naïve player";
}

/**
@brief Initialises the client.
@param An int (the client id), an int (the total number of players)
*/
void initialize(unsigned int id, unsigned int n_players)
{
  if (id <= n_players){
    printf("Player ID : %d\n", id);
    my_id=id;
    nb_player=n_players;

  }
  board=init_board();
  start_game_2(board);
  cards=create_card();
}

/**
@bief The loop to let the client play a move
@param An enum (of the card to play), an array of struct move (which stores the previous moves played by the other players), a size_t (to know how many moves have been done before).
@return A struct move
*/
struct move play(enum card_id card, struct move const previous_moves[], size_t n_moves)
{
  struct move my_move;
  my_move.player = my_id;
  my_move.card = card;
  struct position pos;
  pos.x=-101;pos.y=-101;
  my_move.onto=pos;
  my_move.check = FAILED;

  srand(time(NULL));

  struct move my_real_move = {1,-1,-1,pos,-1,-1};

  //card est la carte
  // create matrix
  fill_board_player(previous_moves, board, n_moves);
  //printf("premiere case %d\n",board[0][0][0]);
  // find a place
  for(int i = 0; i<BOARD_SIZE ; i++)
  {
    for (int j = 0; j<BOARD_SIZE; j++)
    {
        // i-1 j; i j-1; i+1 j ; i j+1
        //board[x][y][0] ==-1  case vide

        // si les 4 cartes autour pas vides
        //printf("i = %d j = %d\n",i,j);
        if(board[i][j][0] == -1){

        if(!((board[i][mod(j-1, BOARD_SIZE)][0] == -1) &&
             (board[i][mod(j+1, BOARD_SIZE)][0] == -1) &&
             (board[mod(i-1, BOARD_SIZE)][j][0] == -1) &&
             (board[mod(i+1, BOARD_SIZE)][j][0] == -1)))
              {
                // on prend la pos de la case
                pos.x=i; pos.y=j;
                my_move.onto = pos;
              //  printf("position %d %d\n",pos.x,pos.y);
                // test pour les 4 orientations
                for(int v =0; v<4; v++)
                {
                  //changement d'orientation
                  my_move.dir =v ;
                  //test du move
                  if(valid_move(&my_move, board, cards)==VALID){
                    my_move.place = allowed_positions[card][0];

                    my_real_move = my_move;
                    my_real_move.onto.x -= 100;
                    my_real_move.onto.y -= 100;
                    if(rand()%15 == 0)
                      return my_real_move;


                  }
                  }
                }
              }
              }
            }
          return my_real_move;

          }

/**
@brief Finalises the client play.
 */
void finalize() {
  free_card(cards);
  free_board(board);
}

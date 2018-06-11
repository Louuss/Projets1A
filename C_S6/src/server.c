#include <stdlib.h>
#include <stdio.h>
#include <dlfcn.h>
#include <stddef.h>

#include "interface.h"
#include "player.h"
#include "deck.h"
#include "board.h"

void finalize_server();

/*
Main loop for the server part.
 */
int main(int argc, char **argv) {
  int nb_player = argc - 1;
  struct player * players[nb_player]; // taleau de players ||  free ok
  size_t n_moves = nb_player; //number of moves in previous_moves || no malloc
  struct move moves[TOTAL_CARDS - 1]; //all moves done during the game || no malloc

  int banned[nb_player-1];
  int nbBanned =0;
  struct move previous_moves[nb_player]; // || no malloc
  for(int i = 0 ; i<nb_player ; i++)
    previous_moves[i].check = FAILED;


  for(int i = 0 ; i< nb_player; i++){
    players[i]=create_player(i);
    players[i]->handle = dlopen (argv[i+1], RTLD_NOW);
  }
/*
    char const *(*name)() = dlsym(players[i]->handle, "get_player_name");
    void* (*fin)() =  dlsym(players[i]->handle, "finalize");
*/
  int turn=0;

// free ok
  struct card * tab_cards = create_card();
  struct deck* deck = deck_initialization();
  int *** board = init_board();


  start_game_2(board);

  for(int i = 0;i<nb_player;i++){
    void* (*init)(unsigned int, unsigned int) = dlsym(players[i]->handle, "initialize");
    (*init)(i,nb_player);
  }

  int i = 0; // i = player playing id
  int nb_cards_unplayable = 0;


  //virer client
  //convert in/out


  while(!deck_is_empty(deck)){
      display_board(board,1,tab_cards);
      printf("\n\ntour: %d joueur:%d\n",turn,i);
      struct move (*play)(enum card_id,struct move const [], size_t) = dlsym(players[i]->handle, "play");

// check if the player is banned
      if(nb_player == nbBanned)
        break;


      if(!is_in(i, banned, nbBanned))
      {
        int carte = draw(deck);
        if (playable(carte, tab_cards,board)){
          struct move moveplayed = (*play)(carte,previous_moves, n_moves);
          struct move move_to_check = moveplayed;
          move_to_check.onto.x += 100;
          move_to_check.onto.y += 100;
          moveplayed.check = valid_move(&move_to_check, board,tab_cards);
          if(moveplayed.check==0)
            printf("Coup valide \n");
          else
            printf("Coup non valide \n");
          printf("Carte %d jouée en [%d, %d] dans la direction %d\n\n",moveplayed.card,moveplayed.onto.x,moveplayed.onto.y,moveplayed.dir);
          moves[turn] = moveplayed;
          for(int j = 0; j < nb_player - 1 ; j++)
            previous_moves[j] = previous_moves[j+1];
          previous_moves[n_moves-1] = moveplayed;

            if(moveplayed.check== FAILED)
            {
              banned[nbBanned]= i; // bans the player
              nbBanned++;
            }
            else
              place_move(&moveplayed,board);


          //dans le else
          i = (i + 1)%nb_player;
          }
        else
            nb_cards_unplayable += 1 ;

      turn++;
      }
      else
        i = (i + 1)%nb_player;
  //  break;
  }
  finalize_server();
  free_deck(deck);
  free_board(board);
  free_card(tab_cards);

  int nb_valid_moves = 0;
  for(int i = 0;i < TOTAL_CARDS-1;i++)
    if(moves[i].check == VALID)
      nb_valid_moves++;
  printf("%d coups valides joués pendant cette partie\n",nb_valid_moves);
  printf("%d cartes ont été piochées mais pas pu être jouées\n", nb_cards_unplayable);


  for(int i = 0; i< nb_player; i++)
  {
    void* (*fin)() = dlsym(players[i]->handle, "finalize");
    (*fin)();
    dlclose(players[i]->handle);
    free (players[i]);
  }

return 0;
}

/**
@brief Signalizes that the game is over
*/
void finalize_server()
{
  printf("The game is over\n" );
  printf("\nRESULTS \n");
}
 

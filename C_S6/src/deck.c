#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "interface.h"
#include "deck.h"


/**
@brief Represents the card repartition for all the cards of the game. 
@details Exemple : their are 2 cards of CARD_MONASTERY_ROAD's type.
 */
static int cards_repartition[DIFFERENT_CARDS] = {2,4,1,3/*without first card*/,5,2,1,3,2,3,3,3,2,3,2,3,1,3,2,1,8,9,4,1};

struct deck* create_deck(){
  struct deck * deck = malloc(sizeof(struct deck));
  deck->nb_cards_left = TOTAL_CARDS-1;
  deck->deck = malloc((TOTAL_CARDS-1) * sizeof(int));
  deck->head = deck->deck;
  deck->nbCards = TOTAL_CARDS-1;
  return deck;
}


/**
@brief Initializes the deck (deck = stack of cards)
Param :
@return An initialised and empty deck
*/
struct deck * deck_initialization(){
  int cardRep[DIFFERENT_CARDS];

  for(int i = 0; i< DIFFERENT_CARDS ; i++)
    cardRep[i] = cards_repartition[i];

  srand(time(NULL));
  struct deck * deck =create_deck();
  fill_deck(deck, cardRep);
  deck->head = deck->deck;
  return deck;
}

/**
@brief Verifies if the deck is empty or not.
@param A deck. 
@return 1 if the deck is empty. Else 0.
 */
int deck_is_empty(struct deck * deck){
  return (!deck->nb_cards_left);
}

/**
@brief Fills the deck with all the cards.
@param A deck, an array (containing the card repartition)
 */
void fill_deck(struct deck* deck, int cardRep[]){
  for(int i = TOTAL_CARDS-1; i>0;i--){
    int random = rand()%i;
    int k = 0;

    for(int j = cardRep[0];(random>=j);k++)
      j +=cardRep[k+1];

    *(deck->head)=k;
    cardRep[k]-=1;
    deck->head ++;
  }
}


/**
@brief Draws a card.
@param A deck
@return The card ID . -1 if the deck is empty.
 */
int draw(struct deck* deck)
{
  if(deck->nb_cards_left > 0){
    int card = *(deck->head);
    deck->head++;
    deck->nb_cards_left -= 1;
    return card;
  }
  return -1;
}


/**
@brief Free the memory allocated for the struct deck
@param A struct deck
 */
void free_deck(struct deck* deck){
  free(deck->deck);
  free(deck);
}

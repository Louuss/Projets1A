#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "../src/interface.h"
#include "../src/deck.h"

static int cards_repartition[DIFFERENT_CARDS] = {2,4,1,3/*without first card*/,5,2,1,3,2,3,3,3,2,3,2,3,1,3,2,1,8,9,4,1};


void test_deck_initialization(){
  printf("Test deck_initialization : ");
  
  int nbCartes = DIFFERENT_CARDS;
  struct deck* deck = deck_initialization();
  int tab[nbCartes];
  
  for(int i = 0; i<nbCartes;i++)
    tab[i]=0;
  
  for(int i =0 ;i<deck->nbCards;i++){
    tab[*(deck->head)]+=1;
    deck->head++;
  }
  
  for(int i = 0; i<nbCartes; i++){
    assert(tab[i]==cards_repartition[i]);
  }
  
  printf("PASSED ................ All tests\n");
  free_deck(deck);
}


void test_draw_deck_is_empty(){
  printf("Test draw : ");
  
  struct deck* deck = deck_initialization();

  int nbCartes = DIFFERENT_CARDS;
  int tab[nbCartes];
  
  for(int i = 0; i<nbCartes;i++)
    tab[i]=0;
  
  for(int i = 0 ;i< deck->nbCards;i++){
    assert(!deck_is_empty(deck));
    int c = draw(deck);
    assert(deck->nb_cards_left == TOTAL_CARDS-(2+i));
    assert( c <= DIFFERENT_CARDS);
    tab[c] += 1;
  }
  
  assert(deck->nb_cards_left == 0);
  assert(draw(deck)==-1);
  printf("PASSED ................ All tests\n");

  printf("Test deck_is_empty : ");
  assert(deck_is_empty(deck));
  printf("PASSED ................ All tests\n");
  free_deck(deck);
}


void test_fill_deck(){
  printf("Test fill_deck : ");
  
  struct deck* deck = deck_initialization();
  fill_deck(deck,cards_repartition);

  assert(deck->nb_cards_left == deck->nbCards);
  
  for(int i = 0; i<DIFFERENT_CARDS; i++){
    assert(cards_repartition[i] == 0);
  }
  
  printf("PASSED ................ All tests\n");
  free_deck(deck);
}


int  main(){
  printf("----------------------------------------------------------\n---------------------TESTS DE DECK.C---------------------\n----------------------------------------------------------\n \n");

  test_deck_initialization();
  test_draw_deck_is_empty();
  test_fill_deck();
  printf("\n");
  return 0;
}

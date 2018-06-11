#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "../src/interface.h"
#include "../src/card.h"

void test_use_card(){
  printf("Test use_card : ");

  struct card card_1 = use_card(CARD_MONASTERY_ROAD);
  assert(card_1.sides[8] == ROAD);
  assert(card_1.sides[13] == ABBEY);
  assert(card_1.sides[1] == PLAIN);
  assert(card_1.sides[5] == PLAIN);


  struct card card_2 = use_card(CARD_PLAIN_CITY_ROAD);
  assert(card_2.sides[8] == ROAD);
  assert(card_2.sides[7] == PLAIN);
  assert(card_2.sides[9] == PLAIN);
  assert(card_2.sides[2] == CITY);
  assert(card_2.sides[11] == ROAD);


  printf("PASSED ................ All tests\n");
}

void test_create_card(){
  printf("Test create_card : ");

  struct card * all_cards = create_card();
  for (int i = 1; i<14; i++){
  assert(all_cards[CARD_CITY_TUNNEL].sides[i] == use_card(CARD_CITY_TUNNEL).sides[i]);
  }

  for (int i = 1; i<14; i++){
    assert(all_cards[CARD_PLAIN_CITY_ROAD].sides[i] == use_card(CARD_PLAIN_CITY_ROAD).sides[i]);
  }


  assert(!(all_cards[8].sides[8] == use_card(9).sides[8]));

  printf("PASSED ................ All tests\n");
  free_card(all_cards);
}



int  main(){
  printf("----------------------------------------------------------\n---------------------TESTS  DE CARD.C---------------------\n----------------------------------------------------------\n \n");
  test_use_card();
  test_create_card();
  printf("\n");
  return 0;
}

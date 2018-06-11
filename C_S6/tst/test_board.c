#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "../src/interface.h"
#include "../src/board.h"
#include "../src/card.h"



void test_mod(){
  printf("Test mod : ");
  assert(mod(0,4) == 0);
  assert(mod(1,4) == 1);
  assert(mod(2,4) == 2);
  assert(mod(3,4) == 3);
  assert(mod(4,4) == 0);
  assert(mod(5,4) == 1);
  assert(mod(6,4) == 2);
  assert(mod(7,4) == 3);
  assert(mod(8,4) == 0);
  printf("PASSED ................ All tests\n");
}


void test_position_posit(){
  printf("Test position_posit : ");
  //In the middle of the board (random place)
  struct position positi;
  positi.x = 4;
  positi.y = 10;


  struct position positi1;
  positi1 = posit(NORTH, positi);
  assert(positi1.x == 4);
  assert(positi1.y == 11);

  struct position positi2;
  positi2 = posit(WEST, positi);
  assert(positi2.x == 3);
  assert(positi2.y == 10);

  struct position positi3;
  positi3 = posit(SOUTH, positi);
  assert(positi3.x == 4);
  assert(positi3.y == 9);

  struct position positi4;
  positi4 = posit(EAST, positi);
  assert(positi4.x == 5);
  assert(positi4.y == 10);


  //Right corner down (100;100)
  struct position limit;
  limit.x = 199;
  limit.y = 199;

  struct position limit1;
  limit1 = posit(WEST, limit);
  assert(limit1.x == 198);
  assert(limit1.y == 199);

  struct position limit2;
  limit2 = posit(SOUTH, limit);
  assert(limit2.x == 199);
  assert(limit2.y == 198);

  struct position limit3;
  limit3 = posit(EAST, limit);
  assert(limit3.x == 0);
  assert(limit3.y == 199);

  struct position limit4;
  limit4 = posit(NORTH, limit);
  assert(limit4.x == 199);
  assert(limit4.y == 0);


  //Left corner up (0;0)
  struct position init;
  init.x = 0;
  init.y = 0;

  struct position init1;
  init1 = posit(WEST, init);
  assert(init1.x == 199);
  assert(init1.y == 0);

  struct position init2;
  init2 = posit(SOUTH, init);
  assert(init2.x == 0);
  assert(init2.y == 199);

  struct position init3;
  init3 = posit(EAST, init);
  assert(init3.x == 1);
  assert(init3.y == 0);

  struct position init4;
  init4 = posit(NORTH, init);
  assert(init4.x == 0);
  assert(init4.y == 1);


  //Right corner up (0;72)
  struct position limit_r;
  limit_r.x = 0;
  limit_r.y = 199;

  struct position limit_r1;
  limit_r1 = posit(WEST, limit_r);
  assert(limit_r1.x == 199);
  assert(limit_r1.y == 199);

  struct position limit_r2;
  limit_r2 = posit(SOUTH, limit_r);
  assert(limit_r2.x == 0);
  assert(limit_r2.y == 198);

  struct position limit_r3;
  limit_r3 = posit(EAST, limit_r);
  assert(limit_r3.x == 1);
  assert(limit_r3.y == 199);

  struct position limit_r4;
  limit_r4 = posit(NORTH, limit_r);
  assert(limit_r4.x == 0);
  assert(limit_r4.y == 0);


  //Left corner down (72;0)
  struct position limit_l;
  limit_l.x = 199;
  limit_l.y = 0;

  struct position limit_l1;
  limit_l1 = posit(WEST, limit_l);
  assert(limit_l1.x == 198);
  assert(limit_l1.y == 0);

  struct position limit_l2;
  limit_l2 = posit(SOUTH, limit_l);
  assert(limit_l2.x == 199);
  assert(limit_l2.y == 199);

  struct position limit_l3;
  limit_l3 = posit(EAST, limit_l);
  assert(limit_l3.x == 0);
  assert(limit_l3.y == 0);

  struct position limit_l4;
  limit_l4 = posit(NORTH, limit_l);
  assert(limit_l4.x == 199);
  assert(limit_l4.y == 1);

  printf("PASSED ................ All tests\n");
}


void test_cardin(){
  printf("Test cardin : ");
  assert(cardin(NORTH) == 2);
  assert(cardin(WEST) == 5);
  assert(cardin(SOUTH) == 8);
  assert(cardin(EAST) == 11);
  printf("PASSED ................ All tests\n");
}


void test_init_board(){
  printf("Test init_board : ");

  int *** b = init_board();
  for(int i=0;i<BOARD_SIZE;i++)
    for(int j=0;j<BOARD_SIZE;j++)
      assert(b[i][j][0] == SENTINEL);

  printf("PASSED ................ All tests\n");

  free_board(b);
}


void test_start_game(){
  printf("Test start_game : ");

  int *** b = init_board();
  assert(b[100][100][0] == SENTINEL);
  start_game_2(b);

  for(int i=0;i<BOARD_SIZE;i++){
    for(int j=0;j<BOARD_SIZE;j++){
      if ((i==100) && (j==100)){
	assert(b[100][100][0] == CARD_ROAD_STRAIGHT_CITY);
	assert(b[100][100][1] == NORTH);
	assert(b[100][100][2] == NO_MEEPLE);
      }
      else
	assert(b[i][j][0] == SENTINEL);}}

  printf("PASSED ................ All tests\n");

  free_board(b);
}


void test_valid_move(){
  printf("Test valid_move : ");

  int ***board = init_board();

  struct card *tab_cards = malloc(sizeof(struct card));
  tab_cards = create_card();

  start_game_2(board);

  //Place a card onto an empty arrea
  struct move * move1 = malloc(sizeof( struct move));
  move1->card = CARD_ROAD_TURN_LEFT_CITY;
  move1->onto.x = 4;
  move1->onto.y = 5;
  move1->dir = NORTH;
  move1->place = NO_MEEPLE;
  assert(valid_move(move1, board, tab_cards) == FAILED);

  //Place a card to a valid place
  move1->onto.x = 100;
  move1->onto.y = 99;
  assert(valid_move(move1, board, tab_cards) == VALID);


  struct move * move2 = malloc(sizeof( struct move));
  move2->card = CARD_CITY_ALL_SIDES;
  move2->onto.x = 101;
  move2->onto.y = 100;
  move2->dir = NORTH;
  move2->place = NO_MEEPLE;

  //Place a card to a valid place
  assert(valid_move(move2, board, tab_cards) == VALID);


  //Create a non empty environment
  board[100][99][0] = CARD_ROAD_STRAIGHT_CITY;

  board[100][99][1] = NORTH;
  board[100][98][0] = CARD_JUNCTION_CITY;
  board[100][98][1] = NORTH;
  board[101][100][0] = CARD_CITY_ALL_SIDES;
  board[101][100][1] = NORTH;
  board[101][98][0] = CARD_CITY_THREE;
  board[101][98][1] = NORTH;


  move2->onto.x = 101;
  move2->onto.y = 99;

  //Place a card in the middle of 3 cards.
  assert(valid_move(move2, board, tab_cards) == VALID);

  board[102][99][0] = CARD_JUNCTION_FOUR;
  board[102][99][1] = NORTH;
  struct move * move3 = malloc(sizeof( struct move));
  move3->card = CARD_CITY_THREE_ROAD;
  move3->onto.x = 101;
  move3->onto.y = 99;
  move3->dir = NORTH;
  move3->place = NO_MEEPLE;

  assert(valid_move(move3, board, tab_cards) == FAILED);

  move3->dir = WEST;
  assert(valid_move(move3, board, tab_cards) == VALID);

  printf("PASSED ................ All tests\n");
  free(move3);
  free(move2);
  free(move1);
  free_card(tab_cards);
  free_board(board);
}


void test_side(){
  printf("Test side : ");

  assert(side(NORTH, NORTH)==2);
  assert(side(NORTH, WEST)==5);
  assert(side(NORTH, SOUTH)==8);
  assert(side(NORTH, EAST)==11);

  assert(side(WEST, NORTH)==11);
  assert(side(WEST, WEST)==2);
  assert(side(WEST, SOUTH)==5);
  assert(side(WEST, EAST)==8);

  assert(side(SOUTH, NORTH)==8);
  assert(side(SOUTH, WEST)==11);
  assert(side(SOUTH, SOUTH)==2);
  assert(side(SOUTH, EAST)==5);

  assert(side(EAST, NORTH)==5);
  assert(side(EAST, WEST)==8);
  assert(side(EAST, SOUTH)==11);
  assert(side(EAST, EAST)==2);

  printf("PASSED ................ All tests\n");
}


void test_opposite_side(){
  printf("Test opposite_side : ");
  assert(opposite_side(2) == 8); //NORTH
  assert(opposite_side(5) == 11); //WEST
  assert(opposite_side(8) == 2); //SOUTH
  assert(opposite_side(11) == 5); //EAST
  printf("PASSED ................ All tests\n");
}

void test_place_move(){
  printf("Test place_move : ");

  int *** board = init_board();

  struct move *move_1=malloc(sizeof(struct move));
  move_1->onto.x=2;
  move_1->onto.y=5;
  move_1->card=CARD_CITY_TUNNEL;
  move_1->dir=NORTH;

  place_move(move_1, board);
  assert(board[2+100][5+100][0]==6);


  struct move *move_2=malloc(sizeof(struct move));
  move_2->onto.x=20;
  move_2->onto.y=50;
  move_2->card=11;
  move_2->dir=NORTH;

  place_move(move_2, board);
  assert(board[20+100][50+100][0]==CARD_JUNCTION_CITY);


  struct move *move_3=malloc(sizeof(struct move));
  move_3->onto.x=1;
  move_3->onto.y=5;
  move_3->card=2;
  move_3->dir=SOUTH;

  place_move(move_3, board);
  assert(board[1+100][5+100][0]==CARD_CITY_ALL_SIDES);
  assert(board[1+100][5+100][1]==2);

  printf("PASSED ................ All tests\n");

  free(move_3);
  free(move_2);
  free(move_1);
  free_board(board);
}



void test_fill_board_player(){
  printf("Test fill_board_player : ");

  int *** board = init_board();
//  start_game(board);

  struct move * last_n = malloc(sizeof(struct move));
  last_n[0].check = VALID;
  last_n[0].player = 1 ;
  last_n[0].card = 3;
  last_n[0].onto.x = 1;
  last_n[0].onto.y = 0;
  last_n[0].dir = NORTH;
  last_n[0].place = NO_MEEPLE;

  last_n[1].check = VALID;
  last_n[1].player = 2 ;
  last_n[1].card = 11;
  last_n[1].onto.x = 2;
  last_n[1].onto.y = 0;
  last_n[1].dir = NORTH;
  last_n[1].place = NO_MEEPLE;

  fill_board_player(last_n, board, 3);
  assert(board[2+100][0+100][0] == 11);
  assert(board[1+100][0+100][0] == 3);
  assert(board[2+100][0+100][1] == 0);
  assert(board[1+100][0+100][1] == 0);


  last_n[2].check = VALID;
  last_n[2].player = 3 ;
  last_n[2].card = 2;
  last_n[2].onto.x = 0;
  last_n[2].onto.y = 1;
  last_n[2].dir = NORTH;
  last_n[2].place = NO_MEEPLE;

  last_n[3].check = VALID;
  last_n[3].player = 4  ;
  last_n[3].card = 20;
  last_n[3].onto.x = 1;
  last_n[3].onto.y = 1;
  last_n[3].dir = WEST ;
  last_n[3].place = NO_MEEPLE;


  fill_board_player(last_n, board, 6);

  assert(board[0+100][1+100][0] == 2);
  assert(board[0+100][1+100][1] == 0);
  assert(board[1+100][1+100][0] == 20);
  assert(board[1+100][1+100][1] == 1);
  
  printf("PASSED ................ All tests\n");
  free_board(board);
}


void test_convert_position_in(){
  printf("Test convert_position_in : ");

  struct position comparaison;

  //center (0;0)
  struct position centre;
  centre.x = 0;
  centre.y = 0;

  comparaison = convert_position_in(centre);
  assert(comparaison.x == 100);
  assert(comparaison.y == 100);

  //corner left up (-100;100)
  struct position limit1;
  limit1.x = -100;
  limit1.y = 100;

  comparaison = convert_position_in(limit1);
  assert(comparaison.x == 0);
  assert(comparaison.y == 0);

  //corner right up (100;100)
  struct position limit2;
  limit2.x = 100;
  limit2.y = 100;

  comparaison = convert_position_in(limit2);
  assert(comparaison.x == 0);
  assert(comparaison.y == 200);

  //corner right down (100;-100)
  struct position limit3;
  limit3.x = 100;
  limit3.y = -100;

  comparaison = convert_position_in(limit3);
  assert(comparaison.x == 200);
  assert(comparaison.y == 200);

  //corner left down (-100;-100)
  struct position limit4;
  limit4.x = -100;
  limit4.y = -100;

  comparaison = convert_position_in(limit4);
  assert(comparaison.x == 200);
  assert(comparaison.y == 0);



  
  printf("PASSED ................ All tests\n");
}

void test_convert_position_out(){
  printf("Test convert_position_out : ");

  struct position comparaison;

  //center (100;100)
  struct position centre;
  centre.x = 100;
  centre.y = 100;

  comparaison = convert_position_out(centre);
  assert(comparaison.x == 0);
  assert(comparaison.y == 0);

  //corner left up (0;0)
  struct position limit1;
  limit1.x = 0;
  limit1.y = 0;

  comparaison = convert_position_out(limit1);
  assert(comparaison.x == -100);
  assert(comparaison.y == 100);

  //corner right up (0;200)
  struct position limit2;
  limit2.x = 0;
  limit2.y = 200;

  comparaison = convert_position_out(limit2);
  assert(comparaison.x == 100);
  assert(comparaison.y == 100);

  //corner right down (200;200)
  struct position limit3;
  limit3.x = 200;
  limit3.y = 200;

  comparaison = convert_position_out(limit3);
  assert(comparaison.x == 100);
  assert(comparaison.y == -100);

  //corner left down (200;0)
  struct position limit4;
  limit4.x = 200;
  limit4.y = 0;

  comparaison = convert_position_out(limit4);
  assert(comparaison.x == -100);
  assert(comparaison.y == -100);
  
  printf("PASSED ................ All tests\n");
}



int  main(){
  printf("----------------------------------------------------------\n---------------------TESTS DE BOARD.C---------------------\n----------------------------------------------------------\n \n");
  test_mod();
  test_position_posit();
  test_cardin();
  test_init_board();
  test_start_game();
  test_valid_move();
  test_side();
  test_opposite_side();
  test_place_move();
  test_fill_board_player();
  test_convert_position_in();
  test_convert_position_out();
  printf("\n");
  return 0;
}

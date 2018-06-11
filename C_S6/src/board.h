#ifndef BOARD_H
#define BOARD_H

#include "interface.h"
#include "deck.h"
#include "card.h"

#define BOARD_SIZE  200
#define SENTINEL -1

int mod(int,int);
struct position posit(enum direction, struct position);
int cardin(enum direction);

int *** init_board();
void start_game(int *** );
void start_game_2(int *** );

enum action valid_move(struct move *, int ***, struct card *);
int side(int, int);
int opposite_side(int);

void place_move(const struct move*, int ***);
void fill_board_player(const struct move *, int ***,int);

void free_board(int*** board);

int playable(int, struct card*, int*** );
void display_board(int***, int, struct card *);

struct position convert_position_in(struct position);
struct position convert_position_out(struct position);

int is_in(int x, int array[], int size);


/*
Tableau : [abcisse] [ordonnée] [3 éléments : id de la carte , orientation, meeple?]
*/

#endif // BOARD_H

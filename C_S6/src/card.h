#ifndef CARD_H
#define CARD_H

#define NB_SIDES_CARD 14

#include "interface.h"

struct card {
  int sides[NB_SIDES_CARD];
  int shield; // bool that indicates if there is a shield on the card


/*
  the index of the array "sides" represents the position
    of the point like shown below (like the enum "place")
     3   2   1
    ___________
   |  *  *  *  |
 4 |*         *| 12
 5 |*   13    *| 11
 6 |*         *| 10
   |  *  *  *  |
   |___________|
      7  8  9

      The array can be fit with ROAD, PLAIN, CITY, or ABBEY
*/
};

enum side {
  ROAD,
  PLAIN,
  CITY,
  ABBEY,
  LAST_SIDE
};

struct card use_card(enum card_id);
struct card* create_card();
void free_card(struct card *);

#endif // CARD_H

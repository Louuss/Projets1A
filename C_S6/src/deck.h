#ifndef deck_h
#define deck_h

#define DIFFERENT_CARDS 24
#define TOTAL_CARDS 72


struct deck {
  int * deck;           // points the array of cards
  int * head;           // pointer to the next card
  int nb_cards_left;    // number of cards left in the deck
  int nbCards;          // total of cards
};

struct deck* create_deck();
struct deck * deck_initialization(); // Testée
int deck_is_empty(struct deck *); // Testée
void fill_deck(struct deck* , int*); // Testée
int draw(struct deck *); //Testée
void free_deck(struct deck *);


#endif //deck_h

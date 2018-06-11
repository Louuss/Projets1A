#ifndef player_h
#define player_h


struct player {
  int id;       // id of the player
  int meep;     // meeples available.Initially 7 meeples.
  int points;   // points earned by the player
  void* handle; // the handle of the player
};


struct player *create_player(int);
void free_player(struct player*);

#endif //player_h

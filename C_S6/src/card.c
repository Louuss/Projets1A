#include "card.h"
#include <stdlib.h>
#include <stdio.h>


/**
@brief Initialises all the positions available for all sides for a special card. 
@param A card ID
@return A struct card
 */
struct card use_card(enum card_id id){
  struct card cards ;
  switch(id)
    {
    case 0 : //CARD_MONASTERY_ROAD 0
      for(int i =1; i<=13; i++ )
        {
	  switch(i){
	  case 8:
	    cards.sides[i]=0;
	    break;
	    
	  case 13:
	    cards.sides[i]=3;
	    break;
	    
	  default:
	    cards.sides[i]=1;
	    break;
	  }
        }
      break;

    case 1 : // CARD_MONASTERY_ALONE 1
      for(int i =1; i<=13; i++ )
        {
	  switch(i)
	    {
	    case 13:
	      cards.sides[i]=3;
	      break;
	      
	    default:
	      cards.sides[i]=1;
	      break;
	    }
	}
      break;

    case 2: //CARD_CITY_ALL_SIDES 2
      for(int i =1; i<=13; i++ )
        {
          cards.sides[i]=2;
        }
      break;

    case 3: //CARD_ROAD_STRAIGHT_CITY 3
      for(int i =1; i<=13; i++ )
        {
	  switch(i)
	    {
	    case 8:
	    case 13:
	    case 2:
	      cards.sides[i]=0;
	      break;

	    case 10:
	    case 11 :
	    case 12 :
	      cards.sides[i]=2;
	      break;
	      
	    default :
	      cards.sides[i]=1;
	      break;
	    }
        }
      break;

    case 4: //CARD_CITY_ONE_SIDE,4
      for(int i =1; i<=13; i++ )
        {
	  switch(i){
	  case 1:
	  case 2:
	  case 3:
	    cards.sides[i]=2;
	    break;
	    
	  default:
	    cards.sides[i]=1;
	    break;
	  }
	}
      break;

    case 5: //CARD_CITY_TUNNEL_SHLD 5
      for(int i =1; i<=13; i++ )
        {
	  switch(i){
	  case 4:
	  case 5:
	  case 6:
	  case 10:
	  case 11:
	  case 12:
	  case 13:
	    cards.sides[i]=2;
	    break;
	  default:
	    cards.sides[i]=1;
	    break;
	  }
	}
      break;

    case 6: // CARD_CITY_TUNNEL 6
      for(int i =1; i<=13; i++ )
        {
	  switch(i){
	  case 1:
	  case 2:
	  case 3:
	  case 7:
	  case 8:
	  case 9:
	  case 13:
	    cards.sides[i]=2;
	    break;
	  default:
	    cards.sides[i]=1;
	    break;
	  }
        }
      break;


    case 7: // CARD_PLAIN_TUNNEL, 7
      for(int i =1; i<=13; i++ )
        {
	  switch(i){
	  case 1:
	  case 2:
	  case 3:
	  case 7:
	  case 8:
	  case 9:
	  case 13:
	    cards.sides[i]=1;
	    break;
	  default:
	    cards.sides[i]=2;
	    break;
	  }
        }
      break;

      
    case 8: //CARD_PLAIN_TWO_CITIES 8
      for(int i =1; i<=13; i++ )
        {
	  switch(i){
	  case 7:
	  case 8:
	  case 9:
	  case 10:
	  case 11:
	  case 12:
	    cards.sides[i]=2;
	    break;
	  default:
	    cards.sides[i]=1;
	    break;
	  }
        }
      break;

    case 9: //CARD_ROAD_TURN_RIGHT_CITY 9
      for(int i =1; i<=13; i++ )
        {
	  switch(i){
	  case 1:
	  case 2:
	  case 3:
	    cards.sides[i]=2;
	    break;
	  case 8:
	  case 11:
	  case 13:
	    cards.sides[i]=0;
	    break;
	  default:
	    cards.sides[i]=1;
	    break;
	  }
        }
      break;

      
    case 10: //CARD_ROAD_TURN_LEFT_CITY 10
      for(int i =1; i<=13; i++ )
        {
	  switch(i){
	  case 2:
	  case 5:
	  case 13:
	    cards.sides[i]=0;
	    break;
	  case 10:
	  case 11:
	  case 12:
	    cards.sides[i]=2;
	    break;
	  default:
	    cards.sides[i]=1;
	    break;
	  }
        }
      break;

      
    case 11: //CARD_JUNCTION_CITY 11
      for(int i =1; i<=13; i++ )
        {
	  switch(i){
	  case 10:
	  case 11:
	  case 12:
	    cards.sides[i]=2;
	    break;
	  case 2:
	  case 5:
	  case 8:
	  case 13:
	    cards.sides[i]=0;
	    break;
	  default:
	    cards.sides[i]=1;
	    break;
	  }
        }
      break;

    case 12: // CARD_PLAIN_CITY_SHLD 12
      for(int i =1; i<=13; i++ )
        {
	  switch(i){
	  case 1:
	  case 2:
	  case 3:
	  case 4:
	  case 5:
	  case 6:
	    cards.sides[i]=2;
	    break;
	  default:
	    cards.sides[i]=1;
	    break;
	  }
        }
      break;


    case 13: //CARD_PLAIN_CITY 13
      for(int i =1; i<=13; i++ )
        {
	  switch(i){
	  case 1:
	  case 2:
	  case 3:
	  case 4:
	  case 5:
	  case 6:
	    cards.sides[i]=2;
	    break;
	  default:
	    cards.sides[i]=1;
	    break;
	  }
        }
      break;

      
    case 14: //CARD_PLAIN_CITY_ROAD_SHLD 14
      for(int i =1; i<=13; i++ )
        {
	  switch(i){
	  case 1:
	  case 2:
	  case 3:
	  case 4:
	  case 5:
	  case 6:
	    cards.sides[i]=2;
	    break;
	  case 8:
	  case 11:
	    cards.sides[i]=0;
	    break;
	  default:
	    cards.sides[i]=1;
	    break;
	  }
        }
      break;

    case 15: //CARD_PLAIN_CITY_ROAD 15
      for(int i =1; i<=13; i++ )
        {
	  switch(i){
	  case 1:
	  case 2:
	  case 3:
	  case 4:
	  case 5:
	  case 6:
	    cards.sides[i]=2;
	    break;
	  case 8:
	  case 11:
	    cards.sides[i]=0;
	    break;
	  default:
	    cards.sides[i]=1;
	    break;
	  }
        }
      break;

      
    case 16: //CARD_CITY_THREE_SHLD 16
      for(int i =1; i<=13; i++ )
        {
	  switch(i){
	  case 7:
	  case 8:
	  case 9:
	    cards.sides[i]=1;
	    break;
	  default:
	    cards.sides[i]=2;
	    break;
	  }
        }
      break;

      
    case 17: //CARD_CITY_THREE 17
      for(int i =1; i<=13; i++ )
        {
	  switch(i){
	  case 7:
	  case 8:
	  case 9:
	    cards.sides[i]=1;
	    break;
	  default:
	    cards.sides[i]=2;
	    break;
	  }
	}
      break;

    case 18 : //CARD_CITY_THREE_ROAD_SHLD, 18
      for(int i =1; i<=13; i++ )
        {
	  switch(i){
	  case 7:
	  case 9:
	    cards.sides[i]=1;
	    break;
	  case 8:
	    cards.sides[i]=0;
	    break;
	  default:
	    cards.sides[i]=2;
	    break;
	  }
        }
      break;

    case 19 ://CARD_CITY_THREE_ROAD, 19
      for(int i =1; i<=13; i++ )
        {
	  switch(i){
	  case 7:
	  case 9:
	    cards.sides[i]=1;
	    break;
	  case 8:
	    cards.sides[i]=0;
	    break;
	  default:
	    cards.sides[i]=2;
	    break;
	  }
        }
      break;

    case 20 ://CARD_ROAD_STRAIGHT 20
      for(int i =1; i<=13; i++ )
        {
	  switch(i){
	  case 2:
	  case 8:
	  case 13:
	    cards.sides[i]=0;
	    break;
	  default:
	    cards.sides[i]=1;
	    break;
	  }
        }
      break;

    case 21: //CARD_ROAD_TURN 21
      for(int i =1; i<=13; i++ )
        {
	  switch(i){
	  case 5:
	  case 8:
	  case 13:
	    cards.sides[i]=0;
	    break;
	  default:
	    cards.sides[i]=1;
	    break;
	  }
        }
      break;

      
    case 22: //CARD_JUNCTION_THREE 22
      for(int i =1; i<=13; i++ )
        {
	  switch(i){
	  case 5:
	  case 8:
	  case 11:
	  case 13:
	    cards.sides[i]=0;
	    break;
	  default:
	    cards.sides[i]=1;
	    break;
	  }
        }
      break;

    case 23: //CARD_JUNCTION_THREE 23
      for(int i =1; i<=13; i++ )
        {
	  switch(i){
	  case 2:
	  case 5:
	  case 8:
	  case 13:
	  case 11:
	    cards.sides[i]=0;
	    break;
	  default:
	    cards.sides[i]=1;
	    break;
	  }
        }
      break;

    case 24: //LAST_CARD 24
      for (int i =0; i<=13; i++)
	cards.sides[i]=-1;
      break;}

  return cards;
}



/**
@brief Creates an array which initialises all the positions available for all sides for all cards. 
@return An array of struct card.
 */
struct card* create_card(){

  struct card* cards = malloc(24 * sizeof(struct card));

  for (int i = 0; i<LAST_CARD; i++)
    {
    
      cards[i] = use_card(i);
    }

  return cards;
}

/**
@debrief Free the memory allocated for the struct card
@param A struct card
 */
void free_card(struct card * c)
{
  free(c);
}

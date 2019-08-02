#ifndef PLAYER_H
#define PLAYER_H

#include "hand.h"

struct Player {

	string name;
	Hand hand;
	unsigned int wins, losses;
	unsigned int player_pot_size;
	unsigned int player_betting_pot;
	// constructor
	Player(char* name_);
};

ostream &operator<<(ostream &out, const Player &p);

#endif //PLAYER_H

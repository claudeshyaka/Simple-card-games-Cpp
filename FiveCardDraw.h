#ifndef FIVECARDDRAW_H
#define FIVECARDDRAW_H

#include "CSE332_lab4.h"
#include "Game.h"
#include "hand.h"

class FiveCardDraw : public Game {
public:
	FiveCardDraw(); // default constructor.
	virtual int beforeTurn(Player & plr); // before_turn method.
	virtual int Turn(Player& plr); // turn method.
	virtual int afterTurn(Player & plr); // after_turn method.
	virtual int beforeRound(); // before_round method.
	virtual int Round(); // round method.
	virtual int afterRound(); //after_turn method.
	size_t sizeOfPlayerVector(); // get the size of player's vector.
	void bettingPhase(size_t& num_plrs, bool & no_previous_bet); // Betting phase method.

protected:
	size_t dealer_position; // dealer position variable. Starts at 0.
	unsigned int common_pot_of_chips; // common pot
	Deck discard_deck; // Discard deck variable
	hand_enum playerHandRank(const Hand & hd); // check for rank of hand
};

bool pokerRankPlayers(shared_ptr<Player> plr_x, shared_ptr<Player> plr_y); // 

#endif // FIVECARDDRAW_H
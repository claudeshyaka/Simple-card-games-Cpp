#ifndef GAME_H
#define GAME_H

#include "deck.h"
#include "player.h"
#include <memory>

class Game {
public:
	static shared_ptr<Game> instance(); // instance method
	static void startGame(const string&); // start game method
	static void stopGame(); // Stop game method
	void addPlayer(const string& plr_name); // Add player method.
	shared_ptr<Player> findPlayer(const string& plr_name); // find player method.
	virtual int beforeTurn(Player& plr) = 0; // before_turn method.
	virtual int Turn(Player& plr) = 0; // Turn method.
	virtual int afterTurn(Player& plr) = 0; // After turn method.
	virtual int beforeRound() = 0; // before turn method.
	virtual int Round() = 0; // Round method.
	virtual int afterRound() = 0; // after round method.
	virtual size_t sizeOfPlayerVector() = 0; // get the size of player's vector.
protected:
	// game pointer
	static shared_ptr<Game> gm;
	// Main Deck
	Deck main_deck;
	// Vector of active players
	vector<shared_ptr<Player>> plrs_in_game;
	// Vector of non_active players
	vector<shared_ptr<Player>> plrs_in_game_non_active;
};



#endif //GAME_H

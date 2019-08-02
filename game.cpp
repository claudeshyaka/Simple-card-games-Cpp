#include "stdafx.h"
#include <iostream>
#include <memory>
#include <vector>
#include <iterator>
#include <string>

using namespace std;

#include "CSE332_lab4.h"
#include "nullbuffer.h"
#include "player.h"
#include "Game.h"
#include "FiveCardDraw.h"
#include "SevenCardStud.h"

/**************************************************/
NullBuffer null_buffer_game;
ostream null_stream_game(&null_buffer_game);

#if DEBUG
#define print_debug cout
#else
#define print_debug null_stream_game
#endif
/**************************************************/

/*
* A protected static member variable that is a pointer (or even better a shared_ptr) to Game.
* That pointer should be initialized to be singular (point to nothing).
*/
shared_ptr<Game> Game::gm = nullptr;

/*
*	A public static instance method that takes no parameters and returns a copy of the static
*	pointer member variable. If the static pointer member variable is singular (points to nothing),
*	the method should throw an instance_not_available exception (how you define this exception is up to you).
*/
shared_ptr<Game> Game::instance() {
	// Check if game pointer in null
	if (gm == nullptr) {
		game_exec_t i = INSTANCE_NOT_AVAILABLE;
		cout << "Instance not available." << endl;
		throw i;
	}
	// Copy of Game pointer
	shared_ptr<Game> ptr = gm;
	return ptr;
}

/*
*	A public static start_game method that has a void return type and takes a reference to a const C++ style string
*	as its only parameter. If the static pointer member variable is non-singular (points to something)
*	the method should throw a game_already_started exception (how you define your exceptions is again up to you).
*	If the C++ style string parameter does not contain "FiveCardDraw" the method should throw an unknown_game exception.
*	Otherwise the method should dynamically allocate an instance of the FiveCardDraw class (to be described below) and
*	store its address in the static pointer member variable: if you use a shared_ptr (which is preferred) instead of
*	a native C++ pointer, then you would use make_shared instead of new.
*/
void Game::startGame(const string& s) {
	if (gm != nullptr) {
		game_exec_t i = GAME_ALREADY_STARTED;
		cout << "Game already started." << endl;
		throw i;
	}
	else {
		if (s == "FiveCardDraw") {
			gm = make_shared<FiveCardDraw>();
		}
		else if (s == "SevenCardStud") {
			// TODO: allocate pointer for game
			gm = make_shared<SevenCardStud>();
		}
		else {
			// gm = make_shared<FiveCardDraw>();
			game_exec_t i = UNKNOWN_GAME;
			cout << "Unknown game." << endl;
			throw i;
		}
	}
}

/*
*	A public static stop_game method that takes no parameters and has a void return type.
*	If the static pointer member variable is singular the method should throw a no_game_in_progress exception.
*	If (and only if - do not do this if it is a shared_ptr) the static pointer member variable is a native C++ pointer
*	(e.g., of type Game *) the method should call delete on the static pointer member variable.
*	Finally, the method should set the static pointer member variable to be singular.
*/
void Game::stopGame() {
	if (gm == nullptr) {
		game_exec_t i = NO_GAME_IN_PROGRESS;
		cout << "No game in progress." << endl;
		throw i;
	}
	else {
		gm = nullptr;
	}
}

/*
*	A public (non-static) add_player method that takes a
*	reference to a const C++ style string as its only parameter.
*	If there is already a player in the game whose name is the same as
*	the passed C++ style string, the method should throw an already_playing exception.
*	Otherwise the method should dynamically allocate a Player with that name,
*	and then push a pointer (or shared_ptr) to the object back into
*	the game's vector of pointers to players.
*/
void Game::addPlayer(const string & pl_name) {
	// Check if player is already in playing.
	for (vector<shared_ptr<Player>>::iterator it = plrs_in_game.begin(); it != plrs_in_game.end(); ++it) {
		shared_ptr<Player> ptr_pl = *it;
		if (ptr_pl->name == pl_name) {
			game_exec_t i = ALREADY_PLAYING;
			cout << pl_name << " is already playing" << endl;
			throw i;
		}
	}
	// allocate new player.
	char* s = (char*)pl_name.c_str();
	shared_ptr<Player> pt_pl = make_shared<Player>(s);
	string in_str;

	// check player's chips count
	if (pt_pl->player_pot_size == 0) {

		cout << "The number of chips in your pot is zero." << endl
			<< " Type reset to get more chips." << endl
			<< " Type abort to cancel the join request. "<< endl;
		while (1) {
			cout << ">> ";
			cin >> in_str;

			if (in_str == "reset") {
				pt_pl->player_pot_size = 20;
				break;
			}
			else if (in_str == "abort") {
				game_exec_t i = PLAYER_CHIPS_NUM_NOT_VALID;
				throw i;
			}
			else {
				cout << "Invalid input. Try again." << endl;
			}
		}
	}
	// add player to game.
	plrs_in_game.push_back(pt_pl);

}


/*
*	A public (non-static) find_player method that takes a reference to a const C++ style
*	string as its only parameter, and either returns a pointer (or shared_ptr) to the matching
*	Player object or returns a singular pointer (or shared_ptr) if there is no player
*	in the game with that name.
*/

shared_ptr<Player> Game::findPlayer(const string &pl_name) {
	// find player with name pl_name.
	for (vector<shared_ptr<Player>>::iterator it = plrs_in_game.begin(); it != plrs_in_game.end(); ++it) {
		shared_ptr<Player> ptr_pl = *it;
		if (ptr_pl->name == pl_name) {
			return ptr_pl;
		}
	}
	return nullptr;
}

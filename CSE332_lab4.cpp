// CSE332_lab4.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <iostream>
#include <vector>
#include <set>

using namespace std;

#include "CSE332_lab4.h"
#include "nullbuffer.h"
#include "card.h"
#include "deck.h"
#include "hand.h"
#include "Game.h"
#include "FiveCardDraw.h"
#include "SevenCardStud.h"
#include "player.h"

/**************************************************/
NullBuffer null_buffer_lab4;
ostream null_stream_lab4(&null_buffer_lab4);

#if DEBUG
#define print_debug cout
#else
#define print_debug null_stream_lab4
#endif
/**************************************************/


/*
*	Print Usage function.
*/
int PrintUsage(char * prog_name, string err_msg, int err) {
	cout << "Welcome!\nThis collection of card games contains two poker games."
		<< " \nYou can choose:\n-> FiveCardDraw\n-> SevenCardStud" << endl;
	string message = "Program should be run with the name of a game followed by the names of two or more players.";
	if (err == TOO_FEW_ARGS) {
		cout << err_msg << endl;
		cout << message << endl;
		cout << "eg. Usage: " << prog_name << " <game_name> <player 1> <player 2> ..." << endl;
		return err;
	}
	else if (err = WRONG_GAME_NAME) {
		cout << err_msg << endl;
		cout << message << endl;
		cout << "eg. Usage: " << prog_name << " <game_name> <player 1> <player 2> ..." << endl;
		cout << "List of games" << endl << "-------------\n" << "-> FiveCardDraw" << endl << "-> SevenCardStud" << endl;
		return err;
	}
	else {
		return SUCCESS;
	}
}

/*
*	In your project's main function:
*
*	->	Make sure that there are at least 3 arguments to the program, in addition to the program name:
*		if not, the program should print out a usage message that says the program should be run with
*		the name of a game followed by the names of two or more players, and return a non-zero integer value to indicate failure.
*
*	->	Otherwise, the main function should call the Game class' static start_game method with the first argument after the program name,
*		and then call the Game class' static instance method to obtain a pointer (or shared_ptr) to the game object.
*
*	->	While there are still at least two players in the game, the main function should repeatedly call the game object's before_round,
*		round, and after_round methods.
*
*	->	The main function should catch any exceptions and note any non-zero return values from the called functions,
*		and if so should call the Game class' static stop_game method and return an appropriate non-zero value to indicate failure;
*		otherwise, if the program detects that there are no more players in the game it should call the Game class' static stop_game method
*		and return 0 to indicate success.
*/

int main(int argc, char **argv) {

	int r_status = ZERO;
	string msg, g_name;
	int err;

	// Set of possible games to play.
	set<string> set_of_games;
	set_of_games.insert("FiveCardDraw");
	set_of_games.insert("SevenCardStud");

	if (argc >= MAX_NUMBER_OF_ARGS) {
		if ((set_of_games.find((string)argv[ARG_ONE])) != set_of_games.end()) {
			try {
				cout << "*************Start Game!******************" << endl;
				Game::startGame((string)argv[ARG_ONE]);				// start game.
				shared_ptr<Game> game_ptr = Game::instance();		// return pointer to game.

				print_debug << "game_ptr -> " << game_ptr << endl;

				// Add players to Players vector
				int num_of_players = argc - TWO;

				print_debug << "num_of_players -> " << num_of_players << endl;

				int i = 0;
				while (i < num_of_players) {
					game_ptr->addPlayer((string)argv[TWO + i]);
					++i;
				}

				while (game_ptr->sizeOfPlayerVector() >= TWO) {
					print_debug << "call beforeRound()" << endl;
					r_status = game_ptr->beforeRound();			// Call before_round
					print_debug << "return beforeRound()" << endl;
					if (r_status == SUCCESS) {					// check before_round return status
						print_debug << "call Round()" << endl;
						r_status = game_ptr->Round();			// Call round
						print_debug << "return Round()" << endl;
						if (r_status == SUCCESS) {				// check round return status
							print_debug << "call afterRound()" << endl;
							r_status = game_ptr->afterRound();	// Call after_round
							print_debug << "return afterRound()" << endl;
							if (r_status != SUCCESS) {			// check after_round return status
								print_debug << "Return value -> " << r_status << endl;
								return r_status;
							}
						}
						else {

							print_debug << "Return value -> " << r_status << endl;
							return r_status;
						}
					}
					else {
						print_debug << "Return value -> " << r_status << endl;
						return r_status;
					}
				}
				cout << "*****************************************" << endl;
				cout << "*************Stop Game!******************" << endl;
				Game::stopGame();
				cout << "*****************************************" << endl;
				r_status = SUCCESS;
				print_debug << "Return value -> " << r_status << endl;
			}
			catch (int &ex) {
				cout << "Exception: " << ex << endl;
				cout << "*************Stop Game!******************" << endl;
				Game::stopGame();
				cout << "*****************************************" << endl;
				r_status = ex;
				print_debug << "Return value -> " << r_status << endl;
			}
			catch (hand_exc_t &hd_ex) {
				cout << "Hand Exception: " << hd_ex << endl;
				cout << "*************Stop Game!******************" << endl;
				Game::stopGame();
				cout << "*****************************************" << endl;
				r_status = hd_ex;
				print_debug << "Return value -> " << r_status << endl;
			}
			catch (deck_exec_t &dk_ex) {
				cout << "Deck Exception: " << dk_ex << endl;
				cout << "*************Stop Game!******************" << endl;
				Game::stopGame();
				cout << "*****************************************" << endl;
				r_status = dk_ex;
				print_debug << "Return value -> " << r_status << endl;
			}
			catch (game_exec_t &gm_ex) {
				cout << "Game Exception: " << gm_ex << endl;
				cout << "*************Stop Game!******************" << endl;
				Game::stopGame();
				cout << "*****************************************" << endl;
				r_status = gm_ex;
				print_debug << "Return value -> " << r_status << endl;
			}
			catch (...) {
				cout << "*************Stop Game!******************" << endl;
				cout << "All other exeptions!" << endl;
				Game::stopGame();
				cout << "*****************************************" << endl;
				r_status = UNKNOWN_EXCEPTION;
				print_debug << "Return value -> " << r_status << endl;
			}
		}
		else {
			msg = "Wrong game name.";
			err = WRONG_GAME_NAME;
			r_status = PrintUsage(argv[PROG_NAME], msg, err);
			print_debug << "Return value -> " << r_status << endl;


		}
	}
	else {
		msg = "Too few arguments.";
		err = TOO_FEW_ARGS;
		r_status = PrintUsage(argv[PROG_NAME], msg, err);
		print_debug << "Return value -> " << r_status << endl;
	}
	return r_status;
}


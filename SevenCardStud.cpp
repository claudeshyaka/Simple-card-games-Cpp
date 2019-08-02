#include "stdafx.h"

#include <iostream>
#include <string>
#include <sstream>
#include <iterator>
#include <algorithm>
#include <fstream>

using namespace std;

#include "CSE332_lab4.h"
#include "nullbuffer.h"
#include "card.h"
#include "deck.h"
#include "hand.h"
#include "game.h"
#include "SevenCardStud.h"
#include "FiveCardDraw.h"

/**************************************************/
NullBuffer null_buffer_stud;
ostream null_stream_stud(&null_buffer_stud);

#if DEBUG
#define print_debug cout
#else
#define print_debug null_stream_stud
#endif
/**************************************************/

/*
*	A public default constructor that only initializes the dealer position member
*	variable to be 0 (so that both its base class and its discard deck member
*	variable are default constructed), and then iterates through all of the 52
*	valid combinations of suit and rank as defined in the Card class enumerations
*	and passes a Card corresponding to each combination into a call to
*	the add_card method of the main deck member variable that was inherited
*	from the Game base class.
*/
SevenCardStud::SevenCardStud() : dealer_position(0), common_pot_of_chips(0) {
	for (int i = Card::card_rank::two; i <= Card::card_rank::ace; ++i) {
		for (int j = Card::card_suits::clubs; j <= Card::card_suits::spades; ++j) {
			Card c;

			print_debug << "Constructor SevenCardStud" << endl;
			c.c_rank = static_cast<Card::card_rank> (i);
			c.c_suits = static_cast<Card::card_suits> (j);
			main_deck.addCard(c);
		}
	}
}

/*
*	A public virtual before_turn method that takes a reference to a Player and returns an int.
*	The method should print out the player's name and the contents of their hand, then use cout
*	to print out a prompt asking the user which (if any) of their cards to discard, and then use
*	cin (and possibly a string stream) to obtain a response containing valid size_t values for
*	the positions of the cards to discard from the hand.
*
*	Note that this implementation should allow the user to discard either no cards, all their cards,
*	or any 1, 2, 3, or 4 of their cards. If the user gives an invalid response
*	(for example with more cards than there are in the hand or a card position that is not in the hand)
*	the method should simply continue to re-prompt the user for a valid response until one is obtained.
*
* The method should call the discard deck's add_card method to add each of those discarded cards to it,
*	call the player's hand object's remove_card method to remove those cards, and then return 0 to indicate success.
*/
int
SevenCardStud::beforeTurn(Player &plr) {
	int flag = 0;
	char c[4];
	size_t pos = 0;
	string input;
	stringstream ss;

	// Read from std input
	print_debug << "Read from std input." << endl;
	while (!flag) {
		print_debug << "flag 1 -> " << flag << endl;
		cout << "**************************************" << endl;
		cout << "Player's name: " << plr.name << endl;
		cout << plr.name << "'s hand: " << plr.hand << endl;
		cout << "**************************************" << endl;
		cout << "Pick your best five card.\nWhich card(s) would you like to discard?\n" 
			 << "Card are indexed from 1 counting from left to right."<< endl;
		cout << "e.g. 3S 2H AC \nIf you enter 1, 3C will discared." << endl;
		cout << ">> ";
		cin >> input;

		// Discard card at specified position.
		stringstream ss(input);
		ss >> c;
		if (isdigit(c[0])) {
			pos = atoi(c);
			if (pos <= 7 && pos >= 0) {
				if (pos == 0) {
					cout << "No Card discarded!" << endl;
					cout << "-----------------------------" << endl;
					cout << plr.name << "'s hand: " << plr.hand << endl;
					cout << "-----------------------------" << endl;
				}
				else {
					cout << "Discard card at position: " << pos << endl;
					discard_deck.addCard(plr.hand[pos - 1]);
					plr.hand.removeCard(pos - 1);
					print_debug << "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx" << endl;
					print_debug << discard_deck << endl;
					print_debug << "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx" << endl;
					cout << "-----------------------------" << endl;
					cout << plr.name << "'s hand: " << plr.hand << endl;
					cout << "-----------------------------" << endl;
				}
				while (1) {
					string in;
					cout << "Would you like to discard more cards (y/yes|n/no)" << endl;
					cout << ">> ";
					cin >> in;
					if (in == "yes" || in == "Yes" || in == "y" || in == "Y") {
						flag = 0;
						print_debug << "in -> " << in << " flag -> " << flag << endl;
						break;
					}
					else if (in == "no" || in == "No" || in == "n" || in == "N") {
						flag = 1;
						print_debug << "in -> " << in << " flag -> " << flag << endl;
						break;
					}
					else {
						cout << "Warning -> Invalid input!" << endl;
					}
				}
				print_debug << "flag 2 -> " << flag << endl;
			}
			else {
				ss.str(string());
				flag = 0;
				cout << "Warning -> Invalid inputs." << endl;
				cout << "Inputs must be numbers between 0 and 5." << endl;
				cout << "**************************************" << endl;
				cout << "Options: <0>, <1>, <2>, <3>, <4>, <5>." << endl;
				cout << "<0>: No cards." << endl;
				cout << "<1>: First card counting from left." << endl;
				cout << "<2>: Second card." << endl;
				cout << "<3>: Third Card." << endl;
				cout << "<4>: Fourth Card." << endl;
				cout << "<5>: Fifth card." << endl;
				cout << "<6>: Sixth card." << endl;
				cout << "<7>: Seventh card." << endl;
				cout << "**************************************" << endl;
				cout << "Try again!" << endl;
			}
			print_debug << "flag 3 -> " << flag << endl;
		}
		else {
			ss.str(string());
			flag = 0;
			cout << "Warning -> Invalid inputs." << endl;
			cout << "Inputs must be numbers between 0 and 7." << endl;
			cout << "Try again!" << endl;
		}
		print_debug << "flag 4 -> " << flag << endl;
	}
	return SUCCESS;
}

int
SevenCardStud::Turn(Player& plr) {
	return 0;
}


/*
*	A public virtual after_turn method that takes a reference to a Player and returns an int.
*	The method should print out the player's name and the contents of their hand
*	(thus showing the result after their discarded cards were replaced), and return 0 to indicate success.
*/
int
SevenCardStud::afterTurn(Player & plr) {
	cout << "**************************************" << endl;
	cout << "Player's name: " << plr.name << endl;
	cout << plr.name << "'s hand: " << plr.hand << endl;
	cout << "******************************************" << endl;
	return SUCCESS;
}


/*
*	A public virtual before_round method that takes no parameters and returns an int.
*	This method should call the main deck member variable's shuffle method and then starting with
*	the player just past the position indicated by the dealer member variable
*	(or, if the player in the last position is the dealer, starting at position 0),
*	deal one card at a time from the main deck to each player, continuing to iterate through
*	the players until each player has received five cards.
*
*	The method should then iterate once more through the players
*	(again starting just past the dealer modulo the number of players) and at each player call
*	their before_turn method, and then return 0 to indicate success.
*/
int
SevenCardStud::beforeRound() {

	int r_status = 0;
	size_t number_of_players = plrs_in_game.size(); // Number of players

	// Shuffle deck
	main_deck.shuffleDeck();

	// Get an ante of one chip from each player.
	size_t x = 0;
	while (x < number_of_players) {
		size_t current_player_position = (dealer_position + x + 1) % number_of_players;
		print_debug << "Current Player name -> " << plrs_in_game[current_player_position]->name << endl;
		print_debug << "Current Player postion -> " << current_player_position << endl;
		print_debug << "# of chips before ante is deducted -> " << plrs_in_game[current_player_position]->player_pot_size << endl;
		--plrs_in_game[current_player_position]->player_pot_size;
		print_debug << "# of chips after ante is deducted -> " << plrs_in_game[current_player_position]->player_pot_size << endl;
		++common_pot_of_chips;
		print_debug << "# of chips in the betting pot -> " << common_pot_of_chips << endl;
		++x;
	}

	

	return r_status;
}

/*
	In the first turn each player should be dealt 
	two face down cards and then one face up card.
*/

void 
SevenCardStud::firstTurn() {
	// Deal for every player in the game
	size_t idx = 0;
	while (idx < 3) {
		size_t i = 0;
		while (i < plrs_in_game.size()) { // TODO: add error checks for when we only have one player.
			size_t current_player_position = (dealer_position + i + 1) % plrs_in_game.size(); // current player.
			plrs_in_game[current_player_position]->hand << main_deck;
			++i;
		}
		++idx;
	}

	size_t plr_i = 0;
	while (plr_i < plrs_in_game.size()) {
		size_t current_player_position = (dealer_position + plr_i + 1) % plrs_in_game.size(); // current player.
		size_t card_i = 0;
		cout << plrs_in_game[current_player_position]->name << endl;
		while (card_i < plrs_in_game[current_player_position]->hand.sizeHand()) {
			if (card_i <= 1) {
				cout << "*" << "  " << flush;
			}
			if (card_i >= 2) {
				cout << plrs_in_game[current_player_position]->hand[card_i] << "  " << flush;
			}
			++card_i;
		}
		cout << endl;
		++plr_i;
	}

}

/*
 * In each of the second, third, and fourth turns each remaining 
 * player should be dealt an additional face up card.
*/
void
SevenCardStud::secondThirdFouthTurn() {
	// Deal for every player in the game
	size_t idx = 0;
	while (idx < 1) {

		size_t i = 0;
		while (i < plrs_in_game.size()) { // TODO: add error checks for when we only have one player.
			size_t current_player_position = (dealer_position + i + 1) % plrs_in_game.size(); // current player.
			plrs_in_game[current_player_position]->hand << main_deck;
			++i;
		}
		++idx;
	}

	size_t plr_i = 0;
	while (plr_i < plrs_in_game.size()) {
		size_t current_player_position = (dealer_position + plr_i + 1) % plrs_in_game.size(); // current player.
		size_t card_i = 0;
		cout << plrs_in_game[current_player_position]->name << endl;
		while (card_i < plrs_in_game[current_player_position]->hand.sizeHand()) {
			if (card_i <= 1) {
				cout << "*" << "  " << flush;
			}
			if (card_i >= 2) {
				cout << plrs_in_game[current_player_position]->hand[card_i] << "  " << flush;
			}
			++card_i;
		}
		cout << endl;
		++plr_i;
	}
}

/*
 *	In the fifth and final turn each player 
 *	should be dealt one additional face down card.
*/
void
SevenCardStud::fifthTurn() {
	// Deal for every player in the game
	size_t idx = 0;
	while (idx < 1) {
		size_t i = 0;
		while (i < plrs_in_game.size()) { // TODO: add error checks for when we only have one player.
			size_t current_player_position = (dealer_position + i + 1) % plrs_in_game.size(); // current player.
			plrs_in_game[current_player_position]->hand << main_deck;
			++i;
		}
		++idx;
	}

	size_t plr_i = 0;
	while (plr_i < plrs_in_game.size()) {
		size_t current_player_position = (dealer_position + plr_i + 1) % plrs_in_game.size(); // current player.
		size_t card_i = 0;
		cout << plrs_in_game[current_player_position]->name << endl;
		while (card_i < plrs_in_game[current_player_position]->hand.sizeHand()) {
			if (card_i <= 1) {
				cout << "*" << "  " << flush;
			}
			if (card_i >= 2 && card_i < 6) {
				cout << plrs_in_game[current_player_position]->hand[card_i] << "  " << flush;
			}

			if ( card_i == 6) {
				cout << "*" << "  " << flush;
			}
			++card_i;
		}
		cout << endl;
		++plr_i;
	}
}

/*
* Betting Phasre Method takes a unsigned int and return void.
*/

void
SevenCardStud::bettingPhase(size_t & number_of_players, bool &no_previous_bet) {


	string str1;
	size_t num_chips = 0;

	// which action to take and how many chips to bet or raise
	size_t j_1 = 0;
	while (j_1 < number_of_players) {

		size_t current_player_position = (dealer_position + j_1 + 1) % number_of_players;

		cout << plrs_in_game[current_player_position]->name << endl;

		cout << "Which action would you like to take? (check/bet)" << endl << ">> ";
		cin >> str1;


		if (str1 == "check") {

			if (no_previous_bet == true) {

				cout << "---------check--------" << endl;
				cout << "Player attributes..." << endl;
				cout << *plrs_in_game[current_player_position] << endl;
				cout << "----------------------" << endl;
				++j_1;
			}
			else {
				cout << "You cannot check. a bet has already been placed."
					<< endl << "Try again!" << endl;
			}
		}
		else if (str1 == "bet") {

			if (plrs_in_game[current_player_position]->player_pot_size != 0) {

				print_debug << "bet flab -> " << no_previous_bet << endl;

				if (no_previous_bet == true) {

					cout << "---------bet---------" << endl;
					cout << "Player attributes...  " << endl;
					cout << *plrs_in_game[current_player_position] << endl;
					cout << "----------------------" << endl << endl;

					cout << "No other player has bet so far." << endl;
					cout << "You can bet 1 or 2 chips." << endl << ">> ";
					cin >> num_chips;

					// check if bet entered is not zero.
					while (1) {
						if (num_chips == 0) {
							cout << "Warning...\nYou have bet: " << num_chips << " chips" << endl;
							cout << "Please enter a valid bet." << endl;
							cout << "number of chips in your pot: "
								<< plrs_in_game[current_player_position]->player_pot_size << endl;
							cout << ">> ";
							cin >> num_chips;
						}
						else {
							break;
						}
					}

					// check if bet entered is less than number of chips in player's pot
					while (1) {
						if (num_chips > plrs_in_game[current_player_position]->player_pot_size) {
							cout << "Warning...\nYou have bet: " << num_chips << " chips" << endl;
							cout << "You do not have that many chips in your pot." << endl;
							cout << "Please enter a valid bet." << endl;
							cout << "number of chips in your pot: "
								<< plrs_in_game[current_player_position]->player_pot_size << endl;
							cout << ">> ";
							cin >> num_chips;
						}
						else {
							break;
						}
					}

					// Enter the number of chips to bet.
					cout << "Your bet -> " << num_chips << " chips" << endl;

					// set no_previous bet flag to false.
					no_previous_bet = false;

					// deduct from player's pot
					print_debug << "# of chips in player pot before deduc. -> "
						<< plrs_in_game[current_player_position]->player_pot_size << endl;
					plrs_in_game[current_player_position]->player_pot_size -= num_chips;
					print_debug << "# of chips in player pot after deduc. -> "
						<< plrs_in_game[current_player_position]->player_pot_size << endl;

					// add to player's betting pot
					print_debug << "# of chips in bet by player before acc. -> "
						<< plrs_in_game[current_player_position]->player_betting_pot << endl;
					plrs_in_game[current_player_position]->player_betting_pot += num_chips;
					print_debug << "# of chips in bet by player after acc. -> "
						<< plrs_in_game[current_player_position]->player_betting_pot << endl;

					print_debug << "# of chips in the common pot -> " << common_pot_of_chips << endl;

					++j_1;

				}
				else {

					cout << "---------bet---------" << endl;
					cout << "Player attributes...  " << endl;
					cout << *plrs_in_game[current_player_position] << endl;
					cout << "----------------------" << endl << endl;

					cout << "How many chips would you like to bet?" << endl << ">> ";
					cin >> num_chips;

					// checkpoint: make sure bet entered is not zero.
					while (1) {
						if (num_chips == 0) {
							cout << "Warning...\nYour bet -> " << num_chips << " chips" << endl;
							cout << "Please enter a valid bet." << endl;
							cout << "number of chips in your pot: "
								<< plrs_in_game[current_player_position]->player_pot_size << endl;
							cout << ">> ";
							cin >> num_chips;
						}
						else {
							break;
						}
					}

					// check if bet entered is less than number of chips in player's pot
					while (1) {
						if (num_chips > plrs_in_game[current_player_position]->player_pot_size) {
							cout << "Warning...\nYour bet -> " << num_chips << " chips" << endl;
							cout << "You do not have that many chips in your pot." << endl;
							cout << "Please enter a valid bet." << endl;
							cout << "number of chips in your pot: "
								<< plrs_in_game[current_player_position]->player_pot_size << endl;
							cout << ">> ";
							cin >> num_chips;
						}
						else {
							break;
						}
					}

					cout << "Your bet -> " << num_chips << " chips" << endl;

					print_debug << "# of chips in player pot before deduc. -> "
						<< plrs_in_game[current_player_position]->player_pot_size << endl;
					plrs_in_game[current_player_position]->player_pot_size -= num_chips; // deduct from player's pot
					print_debug << "# of chips in player pot after deduc. -> "
						<< plrs_in_game[current_player_position]->player_pot_size << endl;

					print_debug << "# of chips in bet by player before acc. -> "
						<< plrs_in_game[current_player_position]->player_betting_pot << endl;
					plrs_in_game[current_player_position]->player_betting_pot += num_chips; // add to player's betting pot
					print_debug << "# of chips in bet by player after acc. -> "
						<< plrs_in_game[current_player_position]->player_betting_pot << endl;

					print_debug << "# of chips in the common pot -> " << common_pot_of_chips << endl;

					++j_1;
				}
			}
			else {
				cout << "Current player has no chips to bet..." << endl;
			}

			// Print names and pot size of other player in game
			cout << "---------------Other Players in the game-------------------" << endl;
			size_t j_2 = 0;
			size_t played = j_1;
			size_t other_player_position;
			while (j_2 < (number_of_players - played)) {
				other_player_position = (current_player_position + j_2 + 1) % number_of_players;
				cout << *plrs_in_game[other_player_position] << endl;
				++j_2;
			}
			cout << "-----------------------------------------------------------" << endl;

			// Other player's must either fold, call, or raise
			j_2 = 0;
			string str2;
			while (j_2 < (number_of_players - played)) {

				other_player_position = (current_player_position + j_2 + 1) % number_of_players;

				cout << plrs_in_game[other_player_position]->name << endl;

				if (plrs_in_game[other_player_position]->player_pot_size == 0) {
					cout << plrs_in_game[other_player_position]->name << " has run out of chips during phase." << endl;
					++j_2;
					++j_1;
				}
				else {

					cout << "Which action would you like to take? (fold/call/raise)" << endl << ">> ";
					cin >> str2;

					if (str2 == "fold") {

						cout << "---------fold---------" << endl;
						cout << "Player attributes...  " << endl;
						cout << *plrs_in_game[other_player_position] << endl;
						cout << "----------------------" << endl;

						// add player's chips to common pot
						common_pot_of_chips += plrs_in_game[other_player_position]->player_betting_pot;
						plrs_in_game[other_player_position]->player_betting_pot = 0;

						// Add to vector of inactive players
						plrs_in_game_non_active.push_back(plrs_in_game[other_player_position]);

						// remove player from vector of active players.
						plrs_in_game.erase(plrs_in_game.begin() + other_player_position);

						print_debug << "# of chips in the common pot -> " << common_pot_of_chips << endl;
						++j_2;
						++j_1;
					}
					else if (str2 == "call") {

						// extract the highest cummulative bet--------------------------------------------------
						size_t j_3 = 0;
						size_t player_position = 0;
						size_t highest_cummulative_bet = 0;
						size_t plr_indx = (other_player_position + 1) % number_of_players;
						while (j_3 < (number_of_players - 1)) {

							player_position = (other_player_position + j_3 + 1) % number_of_players;

							print_debug << "curr player betting pot -> " << plrs_in_game[player_position]->player_betting_pot << endl;

							highest_cummulative_bet = plrs_in_game[plr_indx]->player_betting_pot;

							if (highest_cummulative_bet <=
								plrs_in_game[player_position]->player_betting_pot) {

								plr_indx = player_position;
								highest_cummulative_bet = plrs_in_game[plr_indx]->player_betting_pot;
								print_debug << "Highest cummulative bet -> " << highest_cummulative_bet << endl;

							}
							++j_3;
						}
						//---------------------------------------------------------------------------------------

						cout << "---------call---------" << endl;
						cout << "Player attributes...  " << endl;
						cout << *plrs_in_game[other_player_position] << endl;
						cout << "----------------------" << endl;

						cout << "Player with highest cummulative bet: " << plrs_in_game[plr_indx]->name << endl;
						cout << "Bet: " << highest_cummulative_bet << " chips" << endl;

						if (highest_cummulative_bet < plrs_in_game[other_player_position]->player_pot_size) {
							cout << "Enter your bet." << endl << ">> ";
							cin >> num_chips;
							// checkpoint: make sure number of the chips is greater than highest bet.
							while (1) {
								if ((num_chips + plrs_in_game[other_player_position]->player_betting_pot) < highest_cummulative_bet) {
									cout << "Amount of chips must be equal to the highest cummulative bet." << endl;
									cout << "Try again!" << endl;
									cout << "Highest Bet: " << highest_cummulative_bet << " chips" << endl;
									cout << "Enter your bet." << endl << ">> ";
									cin >> num_chips;
								}
								else {
									break;
								}
							}

							plrs_in_game[other_player_position]->player_pot_size -= num_chips;
							plrs_in_game[other_player_position]->player_betting_pot += num_chips;

							print_debug << "Player's betting pot after increase.\n" << *plrs_in_game[other_player_position] << endl;
							print_debug << "# of chips in the common pot -> " << common_pot_of_chips << endl;
							++j_2;
							++j_1;
						}
						else {
							cout << "You do not have enough chips to call the bet. Try again." << endl;
						}

					}
					else if (str2 == "raise") {

						// extract the highest cummulative bet------------------------------------------------------
						size_t j_4 = 0;
						size_t player_position = 0;
						size_t highest_cummulative_bet = 0;
						size_t plr_indx = (other_player_position + 1) % number_of_players;

						while (j_4 < (number_of_players - 1)) {

							print_debug << "j_4 -> " << j_4 << endl;
							player_position = (other_player_position + j_4 + 1) % number_of_players;

							print_debug << "curr player betting pot -> " << plrs_in_game[player_position]->player_betting_pot << endl;

							highest_cummulative_bet = plrs_in_game[plr_indx]->player_betting_pot;

							if (highest_cummulative_bet <=
								plrs_in_game[player_position]->player_betting_pot) {

								plr_indx = player_position;
								highest_cummulative_bet = plrs_in_game[plr_indx]->player_betting_pot;
								print_debug << "Highest cummulative bet -> " << highest_cummulative_bet << endl;

							}
							++j_4;
						}
						//------------------------------------------------------------------------------------------

						// Enter amount to raise.
						cout << "---------raise---------" << endl;
						cout << "Player attributes...  " << endl;
						cout << *plrs_in_game[other_player_position] << endl;
						cout << "----------------------" << endl;

						cout << "Player with highest cummulative bet: " << plrs_in_game[plr_indx]->name << endl;
						cout << "Bet: " << highest_cummulative_bet << " chips" << endl;

						if (highest_cummulative_bet < plrs_in_game[other_player_position]->player_pot_size) {
							cout << "You can raise 1 or 2 chips in addition to the amount needed to call any previous bet or raise." << endl;
							cout << "Enter your bet." << endl << ">> ";
							cin >> num_chips;


							// checkpoint: make sure number of the chips is greater than highest bet.
							while (1) {
								if (num_chips < highest_cummulative_bet + 1) {
									cout << "Amount of chips must be greater than highest cummulative bet." << endl;
									cout << "Try again!" << endl;
									cout << "Highest Bet: " << highest_cummulative_bet << " chips" << endl;
									cout << "Enter your bet." << endl << ">> ";
									cin >> num_chips;
								}
								else {
									break;
								}
							}

							plrs_in_game[other_player_position]->player_pot_size -= num_chips;
							plrs_in_game[other_player_position]->player_betting_pot += num_chips;

							print_debug << "Player's betting pot after increase.\n" << *plrs_in_game[other_player_position] << endl;
							print_debug << "# of chips in the common pot -> " << common_pot_of_chips << endl;
							++j_2;
							++j_1;
						}
						else {
							cout << "You do not have enough chips to raise the bet. Try again." << endl;
						}

					}
					else {
						cout << "No actions recorded. Please try again." << endl;
					}
				}
			}
		}
		else {
			cout << "No action recorded. Please try again. " << endl;
		}
	}
}

/*
*	A public virtual round method that takes no parameters and returns an int.
*	The method should iterate once more through the players (again starting with the one just past the dealer),
*	and at each player calling their turn method and then their after_turn method.
*	If any player's turn method returns a non-zero value, the method should immediately return that non-zero value;
*	otherwise if it completes with no problems the method should return 0 to indicate success.
*/
int
SevenCardStud::Round() {

	int r_status = 0;
	size_t current_player_position; // next player position from dealer position
	
	// First turn
	cout << "***************First Turn***************" << endl;
	firstTurn();				
	// Betting phase 1
	cout << "***************Betting Phase 1***************" << endl;
	bool no_previous_bet = true;
	size_t number_of_players_in_phase_1 = plrs_in_game.size(); // Number of players
	bettingPhase(number_of_players_in_phase_1, no_previous_bet);

	// Second turn
	cout << "***************Second Turn***************" << endl;
	secondThirdFouthTurn();
	// Betting phase 2
	cout << "***************Betting Phase 2***************" << endl;
	size_t number_of_players_in_phase_2 = plrs_in_game.size(); // Number of players
	bettingPhase(number_of_players_in_phase_2, no_previous_bet);

	// Third turn
	cout << "***************Third Turn***************" << endl;
	secondThirdFouthTurn();
	// Betting phase 3
	cout << "***************Betting Phase 3***************" << endl;
	size_t number_of_players_in_phase_3 = plrs_in_game.size(); // Number of players
	bettingPhase(number_of_players_in_phase_3, no_previous_bet);

	// Fourth turn
	cout << "***************Fourth Turn***************" << endl;
	secondThirdFouthTurn();
	// Betting phase 4
	cout << "***************Betting Phase 4***************" << endl;
	size_t number_of_players_in_phase_4 = plrs_in_game.size(); // Number of players
	bettingPhase(number_of_players_in_phase_4, no_previous_bet);
	
	// Fifth Turn
	cout << "***************Fifth Turn***************" << endl;
	fifthTurn();
	// Betting phase 5
	cout << "***************Betting Phase 5***************" << endl;
	size_t num_of_players_in_phase_5 = plrs_in_game.size();
	bettingPhase(num_of_players_in_phase_5, no_previous_bet);

	// Put reset of the chips placed as bet in common pot.
	size_t i = 0;
	while (i < plrs_in_game.size()) {
		current_player_position = (dealer_position + i + 1) % plrs_in_game.size();
		common_pot_of_chips += plrs_in_game[current_player_position]->player_betting_pot;
		plrs_in_game[current_player_position]->player_betting_pot = 0;
	}

	return r_status;
}


/*
*	Returns an int associated with the rank of a hand.
*/
hand_enum
SevenCardStud::playerHandRank(const Hand & hd) {
	Hand hd_ = hd;
	if (hd_.straightFlush()) {
		return STRAIGHTFLUSH;
	}
	else if (hd_.fourOfKind()) {
		return FOUR_OF_KIND;
	}
	else if (hd_.fullHouse()) {
		return FULL_HOUSE;
	}
	else if (hd_.flush()) {
		return FLUSH;
	}
	else if (hd_.straight()) {
		return STRAIGHT;
	}
	else if (hd_.threeOfKind()) {
		return THREE_OF_KIND;
	}
	else if (hd_.twoPairs()) {
		return TWO_PAIRS;
	}
	else if (hd_.onePair()) {
		return ONE_PAIR;
	}
	else if (hd_.noRank()) {
		return NO_RANK;
	}
	else {
		return HAND_ERROR;
	}
}



/*
*	A public virtual after_round method that takes no parameters and returns an int.
*	This method should perform the following actions (implementing additional non-member or
*	protected member functions for some or all of these in your FiveCardDraw class is a good idea,
*	to produce a modular design and implementation of your lab solution):
*
*	->	Sort a temporary vector of pointers to players (a copy of the vector member variable)
*		according to the ranking of their hands by the poker_rank function specification from the previous lab.
*		Hint: an easy way to do this is to declare and define an overloaded poker_rank non-member function that
*		takes two pointers to players, returns false if the first pointer is singular, if it is non-singular returns
*		true if the second pointer is singular, and otherwise returns the result of calling the original poker_rank
*		function with their hands.
*
*		For the player with the highest hand (or players if multiple equivalent hands were highest) increment their number of wins.
*		For all other players, increment their number of losses.
*
*		Use the sorted temporary vector to print out a listing with each player's name, numbers of wins and losses,
*		and then current hand, in order from the player with the highest hand to the player with the lowest hand.
*
*	->	Move all cards from the players hands and from the discard deck into the main deck so that
*		the main deck has all 52 cards and the hands and discard deck are all empty.
*
*	->	Until the user says no, repeatedly ask whether any players want to leave the game:
*		if so get the names of the players (ignore any invalid player names but continue to process valid ones) and for each one
*		(1) find the player;
*		(2) open an ofstream using the player's name as the file name,
*			insert the player into the ofstream, and close the ofstream; and
*		(3) erase the player's pointer from the vector of pointers to players
*			(being careful to avoid problems with erase invalidating iterators as noted elsewhere in the assignent).
*		If (and only if) you used native C++ pointers (instead of shared_ptrs), then between steps (2) and (3)
*		you also must call delete on the player's address, but you should *not* do that if you used shared_ptrs since
*		they will take care of the deletion themselves, through reference counting.
*/
int
SevenCardStud::afterRound() {
	// Print players who folded
#if DEBUG	
	size_t inx = 0;
	while (inx <= plrs_in_game_non_active.size()) {
		print_debug << *plrs_in_game_non_active[inx];
		++inx;
	}
#endif


	// Print remaing players hands and choose best five cards
	size_t pl_indx = 0;
	while (pl_indx < plrs_in_game.size()) {
		beforeTurn(*plrs_in_game[pl_indx]);
		++pl_indx;
	}

	// temp vector.
	print_debug << "copy vector of players." << endl;
	vector<shared_ptr<Player>> tmp_vector_ptrs = plrs_in_game;
		
	// Sort
	print_debug << "sort." << endl;
	sort(tmp_vector_ptrs.begin(), tmp_vector_ptrs.end(), pokerRankPlayers);

	// Get winners rank value
	hand_enum winner = playerHandRank(tmp_vector_ptrs[0]->hand);
	print_debug << "winner's rank -> " << winner << endl;
#if DEBUG
	size_t z = 0;
	while (z < tmp_vector_ptrs.size()) {
		print_debug << playerHandRank(tmp_vector_ptrs[z]->hand) << endl;
		++z;
	}
#endif
	++tmp_vector_ptrs[0]->wins;
	tmp_vector_ptrs[0]->player_pot_size += common_pot_of_chips;

	// check for other winners and lossers
	size_t i = 1;
	vector<size_t> winner_indx;
	while (i < tmp_vector_ptrs.size()) {
		hand_enum other_winner = playerHandRank(tmp_vector_ptrs[i]->hand);
		print_debug << "other winner's rank -> " << other_winner << endl;
		if (winner == other_winner) {
			++tmp_vector_ptrs[i]->wins;
			winner_indx.push_back(i);
		}
		else {
			++tmp_vector_ptrs[i]->losses;
		}
		++i;
	}

	// Split the pot among winners
	size_t other_num_of_winners = winner_indx.size();
	if (other_num_of_winners != 0) {
		tmp_vector_ptrs[0]->player_pot_size += (common_pot_of_chips / other_num_of_winners);
		while (winner_indx.size() != 0) {
			tmp_vector_ptrs[winner_indx[winner_indx.size() - 1]]->player_pot_size += (common_pot_of_chips / other_num_of_winners);
			winner_indx.pop_back();
		}
	}


	// Print players attributes.
	print_debug << "Print active players attributes." << endl;
	size_t j = 0;
	while (j < tmp_vector_ptrs.size()) {
		cout << "-----------------------------" << endl;
		cout << tmp_vector_ptrs[j]->name << endl;
		cout << tmp_vector_ptrs[j]->wins << endl;
		cout << tmp_vector_ptrs[j]->losses << endl;
		cout << tmp_vector_ptrs[j]->hand << endl;
		cout << "-----------------------------" << endl;
		++j;
	}
	print_debug << "Print non-active players attributes." << endl;
	j = 0;
	while (j < plrs_in_game_non_active.size()) {
		cout << "-----------------------------" << endl;
		cout << plrs_in_game_non_active[j]->name << endl;
		cout << plrs_in_game_non_active[j]->wins << endl;
		cout << plrs_in_game_non_active[j]->losses << endl;
		cout << "Player folded." << endl;
		cout << "-----------------------------" << endl;
		++j;
	}

	// Move all cards in discard deck in main deck
	print_debug << "Move all cards in discard deck in main deck." << endl;
	print_debug << "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx" << endl;
	print_debug << discard_deck << endl;
	print_debug << "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx" << endl;
	while (discard_deck.sizeDeck() > 0) {
		main_deck << discard_deck;
	}
	print_debug << "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx" << endl;
	print_debug << discard_deck << endl;
	print_debug << "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx" << endl;

	// check if discard deck is empty.
	if (discard_deck.sizeDeck() != 0) {
		return DISCARD_DECK_NOT_EMPTY;
	}

	// Add non active player vector to active player vector
	while (plrs_in_game_non_active.size() > 0) {
		print_debug << *plrs_in_game_non_active[plrs_in_game_non_active.size() - 1];
		plrs_in_game.push_back(plrs_in_game_non_active[plrs_in_game_non_active.size() - 1]);
		print_debug << *plrs_in_game[plrs_in_game.size() - 1];
		plrs_in_game_non_active.pop_back();
	}

	// Move all cards in player's hands in main deck.
	print_debug << "Move all cards in player's hands in main deck." << endl;
	size_t v = 0;
	while (v < plrs_in_game.size()) {
		size_t w = 0;
		print_debug << plrs_in_game[v]->name << endl;
		print_debug << plrs_in_game[v]->hand << endl;
		while (plrs_in_game[v]->hand.sizeHand() > 0) {
			main_deck << plrs_in_game[v]->hand;
		}
		print_debug << plrs_in_game[v]->name << endl;
		print_debug << plrs_in_game[v]->hand << endl;

		//check if player's hand is empty.
		if (plrs_in_game[v]->hand.sizeHand() != 0) {
			return PLAYER_HAND_NOT_EMPTY;
		}
		++v;
	}


	// check if main deck is has 52 cards
	print_debug << "check if main deck is has 52 cards." << endl;
	print_debug << "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx" << endl;
	print_debug << main_deck.sizeDeck() << endl;
	print_debug << main_deck << endl;
	print_debug << "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx" << endl;
	if (main_deck.sizeDeck() != 52) {
		return CARDS_MAIN_DECK_NOT_52;
	}

	// Checkpoint: make sure player pot is not empty.
	//				if it is empty either quit or reset.
	size_t plr_pos = 0;
	string input;
	size_t y = 0;
	while (y < plrs_in_game.size()) {

		plr_pos = (dealer_position + y + 1) % plrs_in_game.size();
		cout << *plrs_in_game[plr_pos] << endl;

		if (plrs_in_game[plr_pos]->player_pot_size == 0) {

			cout << "Your pot is empty. You can either reset your chips count to 20"
				<< "or quit the game." << endl;

			while (1) {
				cout << "Enter decision (reset/quit)" << endl << ">>";
				cin >> input;

				if (input == "quit") {
					print_debug << "quit game." << endl;
					string file_name = plrs_in_game[plr_pos]->name + ".txt";
					ofstream output_file;
					output_file.open(file_name);
					print_debug << *plrs_in_game[plr_pos] << endl;
					output_file << *plrs_in_game[plr_pos];
					output_file.close();
					plrs_in_game.erase(plrs_in_game.begin() + plr_pos);
					break;
				}
				else if (input == "reset") {
					print_debug << "reset game." << endl;
					plrs_in_game[plr_pos]->player_pot_size = 20;
					print_debug << *plrs_in_game[plr_pos] << endl;
					break;
				}
				else {
					cout << "Invalid input. Try again." << endl;
				}
			}
		}
		++y;
	}

	// Add non active player vector to active player vector
	while (plrs_in_game_non_active.size() > 0) {
		print_debug << *plrs_in_game_non_active[plrs_in_game_non_active.size() - 1];
		plrs_in_game.push_back(plrs_in_game_non_active[plrs_in_game_non_active.size() - 1]);
		print_debug << *plrs_in_game[plrs_in_game.size() - 1];
		plrs_in_game_non_active.pop_back();
	}
	// Leaving the game-----------------------------------------------------
	string in1;
	while (plrs_in_game.size() > 0) {
		cout << "Would like you want to leave the game (yes/no)?" << endl;
		cout << ">> ";
		cin >> in1;
		if (in1 == "yes") {
			int flag = 0;
			size_t n = 0;
			string in2;
			cout << "Enter Player's name." << endl;
			cout << ">> ";
			cin >> in2;

			int *plr_pos = new int[plrs_in_game.size()];

			if (!plr_pos) {
				cout << "Warning -> Allocation of memory failed\n";
			}
			else {
				while (n < plrs_in_game.size()) {
					if (in2 == plrs_in_game[n]->name) {
						plr_pos[flag] = n;
						++flag;
					}
					++n;
				}
				if (flag != 0) {
					int t = 0;
					while (t < flag) {
						string file_name = in2 + ".txt";
						ofstream output_file;
						output_file.open(file_name);
						print_debug << *plrs_in_game[plr_pos[t]] << endl;
						output_file << *plrs_in_game[plr_pos[t]];
						output_file.close();
						plrs_in_game.erase(plrs_in_game.begin() + plr_pos[t]);
						++t;
					}
				}
				else {
					cout << "Warning -> Player's name not found!" << endl;
					cout << "********Players currenlty in the game.*********" << endl;
					size_t p = 0;
					while (p < plrs_in_game.size()) {
						cout << plrs_in_game[p]->name << endl;
						++p;
					}
					cout << "***********************************************" << endl;
				}
				delete[] plr_pos;
			}
		}
		else if (in1 == "no") {
			break;
		}
		else {
			cout << "Warning -> Invalid input. Try again!" << endl;
		}
	}
	// Join the game
	string in3;
	while (1) {
		cout << "Would you like to join the game (yes/no)?" << endl;
		cout << ">> ";
		cin >> in3;
		if (in3 == "yes") {
			string in4;
			cout << "Enter Player's name." << endl;
			cout << ">> ";
			cin >> in4;
			try {
				addPlayer(in4);
			}
			catch (game_exec_t &gm_ex) {
				if (gm_ex == ALREADY_PLAYING) {
					cout << "Player already in the game. Exception -> " << gm_ex << endl;
				}
				if (gm_ex == PLAYER_CHIPS_NUM_NOT_VALID) {
					cout << "Player did not reset chip count to 20. Exception -> " << gm_ex << endl;
				}
			}
			catch (...) {
				cout << "Other unforseen exceptions" << endl;;
			}
		}
		else if (in3 == "no") {
			break;
		}
		else {
			cout << "Warning -> Invalid input! Try again!" << endl;
		}
	}
	// increament dealer
	if (plrs_in_game.size() > 0) {
		dealer_position += 1 % plrs_in_game.size();
	}
	return SUCCESS;
}

/*
*	Number of players in the game
*/

size_t 
SevenCardStud::sizeOfPlayerVector() {
	return plrs_in_game.size();
}
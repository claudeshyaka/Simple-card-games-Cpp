#include "stdafx.h"

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

using namespace std;

#include "CSE332_lab4.h"
#include "nullbuffer.h"
#include "hand.h"
#include "player.h"


/**************************************************/
NullBuffer null_buffer_player;
ostream null_stream_player(&null_buffer_player);

#if DEBUG
#define print_debug cout
#else
#define print_debug null_stream_player
#endif
/**************************************************/



// Constructor: Reads in player's name, number of losses and wins
Player::Player(char* name_) : name((string)name_), wins(0), losses(0), hand(Hand()), 
player_pot_size(20), player_betting_pot(0) {

	string file_name = name + ".txt";

	print_debug << file_name << endl;

	string str = NULL_CHAR;
	ifstream input_file;
	input_file.open(file_name); // Open file
	if (!input_file.is_open() || !input_file.good()) {
		wins = 0;
		losses = 0;
		player_pot_size = 20;
		player_betting_pot = 0;
		cout << "Warning! Failed to open/read file for " << name << endl;
		cout << "This is a new player or previous file got corrupted!" << endl;
	}
	else {
		getline(input_file, str);

		print_debug << str << endl;

		istringstream iss1(str);
		iss1 >> name >> wins >> losses >> player_pot_size;


		print_debug << "Name: " << name << endl;
		print_debug << "Wins: " << wins << endl;
		print_debug << "Losses: " << losses << endl;
		print_debug << "Number of chips: " << player_pot_size << endl;


		input_file.close();
	}
}
// Output stream: Print players attributes.
ostream &operator<<(ostream &out, const Player &p) {
	// Add a header: name wins losses number_of_chips
	out << p.name << "\n" << p.wins << "\n" << p.losses << "\n"
		<< p.player_pot_size << endl;
	return out;
}

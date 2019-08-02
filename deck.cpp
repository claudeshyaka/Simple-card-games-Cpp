#include "stdafx.h"

#include <iostream>
#include <algorithm>
#include <random>
#include <iterator>
#include <vector>
#include <sstream>
#include <fstream>
#include <string>

// Code obtained at http://www.cplusplus.com/reference/algorithm/shuffle/
#include <chrono>       // std::chrono::system_clock

using namespace std;

#include "CSE332_lab4.h"
#include "nullbuffer.h"
#include "card.h"
#include "deck.h"

// Default constructor
Deck::Deck() {
	// empty deck.
}
// Define Deck class
Deck::Deck(char *file_name) {
	int ex = ZERO;
	ex = loadDeck(file_name);
	if (ex != ZERO) {
		throw ex;
	}
}


// Function to check validity of input.
bool IsValidInput(string str) {

	bool is_last_char_valid = false;
	bool is_firt_char_valid = false;
	string last_chars = "CcDdHhSs";
	string first_chars = "23456789JjQqKkAa";

	if (str.length() == TWO) {
		for (size_t i = ZERO; i < last_chars.length(); ++i) {

			if (str[str.length() - 1] == last_chars[i]) {	// Check if last character
				is_last_char_valid = true;		// in the input is valid
			}
		}
		for (size_t i = ZERO; i < first_chars.length(); ++i) {

			if (str[ZERO] == first_chars[i]) {	// Check if first character
				is_firt_char_valid = true;		// in the input is valid
			}
		}
	}
	else if (str.length() == THREE) {

		string s = str.substr(ZERO, TWO); // Truncate string to get first 2 characters.

		for (size_t i = ZERO; i < last_chars.length(); ++i) {

			if (str[str.length() - 1] == last_chars[i]) {	// Check if last character
				is_last_char_valid = true;		// in the input is valid
			}
		}
		if (s == "10") {
			is_firt_char_valid = true;

		}
		else {
			is_firt_char_valid = false;
		}
	}
	else { // string size is not 2 or 3.
		return false;
	}

	// First and last chars are valid
	if (is_last_char_valid && is_firt_char_valid) {
		return true;
	}
	else {
		return false;
	}
}

// Load method.
int Deck::loadDeck(char * file_name) {

	string str0 = NULL_CHAR;
	string str1 = NULL_CHAR;
	Card Cd;
	ifstream input_file;
	input_file.open(file_name); // Open file.
	if (input_file.is_open()) {	// Check is file opened successfully
		while (getline(input_file, str0)) { // read single line.
			istringstream iss1(str0); // put the input string into a string stream
			vector<string> v_string; // vector to store valid card strings
			while ((iss1 >> str1)) { // parse in str1, one string at a time
				if (str1 == "//" || str1 == "\0") {
					break;
				}
				if (IsValidInput(str1)) { // check if input is valid.
					v_string.push_back(str1);
				}
				else {
					cout << "Warning -> Invalid Input. Ignore...!" << endl;
				}
			}
			if (v_string.size() > ZERO) {
				// Push each card in the Deck vector.
				for (vector<string>::iterator it = v_string.begin(); it != v_string.end(); ++it) {
					string s = (*it);
					// Convert string to card.
					Cd.convertStringToCard(Cd, s);
					card_vector_in_deck.push_back(Cd);
				}
			}
			else {
				cout << "Warning -> Input string is empty!" << endl;
			}
			str0 = NULL_CHAR;
		}
	}
	else { // Failed to open file
		cout << "Warning -> Failed to open file..." << endl;
		return RETURN_VALUE::UNABLE_TO_OPEN_FILE;
	}
	input_file.close(); // close file
	return RETURN_VALUE::SUCCESS;
}

// shuffle Method
void Deck::shuffleDeck() {
	// Code obtained from http://www.cplusplus.com/reference/algorithm/shuffle/
	// obtain a time-based seed:
	unsigned seed = (unsigned)chrono::system_clock::now().time_since_epoch().count();
	shuffle(card_vector_in_deck.begin(), card_vector_in_deck.end(), default_random_engine(seed));
}

// Size method
size_t Deck::sizeDeck() const {
	return card_vector_in_deck.size();
}

// ostream operator<<
ostream &operator<< (ostream &out, const Deck &deck_obj) {
	string card = NULL_CHAR;
	for (vector<Card>::const_iterator it = deck_obj.card_vector_in_deck.cbegin(); it != deck_obj.card_vector_in_deck.cend(); ++it) {

		string rank = NULL_CHAR;
		string suit = NULL_CHAR;

		// Rank
		if ((*it).c_suits == Card::card_suits::diamonds) {
			suit = "D";
		}
		if ((*it).c_suits == Card::card_suits::spades) {
			suit = "S";
		}
		if ((*it).c_suits == Card::card_suits::clubs) {
			suit = "C";
		}
		if ((*it).c_suits == Card::card_suits::hearts) {
			suit = "H";
		}

		// Suit
		if ((*it).c_rank == Card::card_rank::ace) {
			rank = "A";
		}
		if ((*it).c_rank == Card::card_rank::king) {
			rank = "K";
		}
		if ((*it).c_rank == Card::card_rank::queen) {
			rank = "Q";
		}
		if ((*it).c_rank == Card::card_rank::jack) {
			rank = "J";
		}
		if ((*it).c_rank == Card::card_rank::ten) {
			rank = "10";
		}
		if ((*it).c_rank == Card::card_rank::nine) {
			rank = "9";
		}
		if ((*it).c_rank == Card::card_rank::eight) {
			rank = "8";
		}
		if ((*it).c_rank == Card::card_rank::seven) {
			rank = "7";
		}
		if ((*it).c_rank == Card::card_rank::six) {
			rank = "6";
		}
		if ((*it).c_rank == Card::card_rank::five) {
			rank = "5";
		}
		if ((*it).c_rank == Card::card_rank::four) {
			rank = "4";
		}
		if ((*it).c_rank == Card::card_rank::three) {
			rank = "3";
		}
		if ((*it).c_rank == Card::card_rank::two) {
			rank = "2";
		}

		card = rank + "" + suit;
		out << card << endl;
	}

	return out;
}

// add_card method.
void Deck::addCard(Card c) {
	card_vector_in_deck.push_back(c);
}

// const equivalent operator
bool Deck::operator==(const Deck &other) const {
	if (other.card_vector_in_deck == card_vector_in_deck) {
		return true;
	}
	else {
		return false;
	}
}


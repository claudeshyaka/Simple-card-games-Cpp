#include "stdafx.h"

#include <iostream>
#include <string>

using namespace std;
#include "CSE332_lab4.h"
#include "nullbuffer.h"
#include "card.h"


/**************************************************/
NullBuffer null_buffer_card;
ostream null_stream_card(&null_buffer_card);

#if DEBUG
#define print_debug cout
#else
#define print_debug null_stream_card
#endif
/**************************************************/

// Default constructor
Card::Card() {}

//  Overloading operator<
//   Defined so that ranks are in ascending order and
//	 and suit are also in ascending order.
bool Card::operator< (const Card & c) const {
	return ((c_rank < c.c_rank) || ((c_rank == c.c_rank) && (c_suits < c.c_suits)));
}

//  Overloading operator<=
//   Defined so that ranks are in ascending order and
//	 and suit are also in ascending order.
bool Card::operator== (const Card & c) const {
	return ((c_rank == c.c_rank) && (c_suits == c.c_suits));
}


// Convert string to card.
void Card::convertStringToCard(Card& Cd, string s) {
	string s1 = NULL_CHAR;
	string s2 = NULL_CHAR;
	if (s.length() == TWO) {
		s2 = s.substr(ZERO, ONE);
		s1 = s.substr(ONE, TWO);
		// Suits
		if (s1 == "C" || s1 == "c") {
			Cd.c_suits = Card::card_suits::clubs;
		}
		if (s1 == "S" || s1 == "s") {
			Cd.c_suits = Card::card_suits::spades;
		}
		if (s1 == "H" || s1 == "h") {
			Cd.c_suits = Card::card_suits::hearts;
		}
		if (s1 == "D" || s1 == "d") {
			Cd.c_suits = Card::card_suits::diamonds;
		}
		// Ranks
		if (s2 == "A" || s2 == "a") {
			Cd.c_rank = Card::card_rank::ace;
		}
		if (s2 == "K" || s2 == "k") {
			Cd.c_rank = Card::card_rank::king;
		}
		if (s2 == "Q" || s2 == "q") {
			Cd.c_rank = Card::card_rank::queen;
		}
		if (s2 == "J" || s2 == "j") {
			Cd.c_rank = Card::card_rank::jack;
		}
		if (s2 == "9") {
			Cd.c_rank = Card::card_rank::nine;
		}
		if (s2 == "8") {
			Cd.c_rank = Card::card_rank::eight;
		}
		if (s2 == "7") {
			Cd.c_rank = Card::card_rank::seven;
		}
		if (s2 == "6") {
			Cd.c_rank = Card::card_rank::six;
		}
		if (s2 == "5") {
			Cd.c_rank = Card::card_rank::five;
		}
		if (s2 == "4") {
			Cd.c_rank = Card::card_rank::four;
		}
		if (s2 == "3") {
			Cd.c_rank = Card::card_rank::three;
		}
		if (s2 == "2") {
			Cd.c_rank = Card::card_rank::two;
		}
	}
	else if (s.length() == THREE) {
		s2 = s.substr(ZERO, TWO);
		s1 = s.substr(TWO, THREE);
		// Suits
		if (s1 == "C" || s1 == "c") {
			Cd.c_suits = Card::card_suits::clubs;
		}
		if (s1 == "S" || s1 == "s") {
			Cd.c_suits = Card::card_suits::spades;
		}
		if (s1 == "H" || s1 == "h") {
			Cd.c_suits = Card::card_suits::hearts;
		}
		if (s1 == "D" || s1 == "d") {
			Cd.c_suits = Card::card_suits::diamonds;
		}
		// Ranks
		if (s2 == "10") {
			Cd.c_rank = Card::card_rank::ten;
		}
	}
	else {
		cout << "Invalid str length!" << endl;
	}
}


/*
* Print Card.
*/
ostream &operator<<(ostream &out_card, const Card &cd) {
	string rank = NULL_CHAR;
	string suit = NULL_CHAR;

	// Rank
	if (cd.c_suits == Card::card_suits::diamonds) {
		suit = "D";
	}
	if (cd.c_suits == Card::card_suits::spades) {
		suit = "S";
	}
	if (cd.c_suits == Card::card_suits::clubs) {
		suit = "C";
	}
	if (cd.c_suits == Card::card_suits::hearts) {
		suit = "H";
	}

	// Suit
	if (cd.c_rank == Card::card_rank::ace) {
		rank = "A";
	}
	if (cd.c_rank == Card::card_rank::king) {
		rank = "K";
	}
	if (cd.c_rank == Card::card_rank::queen) {
		rank = "Q";
	}
	if (cd.c_rank == Card::card_rank::jack) {
		rank = "J";
	}
	if (cd.c_rank == Card::card_rank::ten) {
		rank = "10";
	}
	if (cd.c_rank == Card::card_rank::nine) {
		rank = "9";
	}
	if (cd.c_rank == Card::card_rank::eight) {
		rank = "8";
	}
	if (cd.c_rank == Card::card_rank::seven) {
		rank = "7";
	}
	if (cd.c_rank == Card::card_rank::six) {
		rank = "6";
	}
	if (cd.c_rank == Card::card_rank::five) {
		rank = "5";
	}
	if (cd.c_rank == Card::card_rank::four) {
		rank = "4";
	}
	if (cd.c_rank == Card::card_rank::three) {
		rank = "3";
	}
	if (cd.c_rank == Card::card_rank::two) {
		rank = "2";
	}

	string card = rank + "" + suit;
	out_card << card << endl;

	return out_card;
}
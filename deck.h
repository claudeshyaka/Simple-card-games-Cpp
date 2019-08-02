#ifndef DECK_H
#define DECK_H

#include "hand.h"

class Deck {

public:

	// Deck
	Deck(); // default constructor
	Deck(char *file_name); // Constructor

						   // load
	int loadDeck(char *file_name); // load method

								   // shuffle
	void shuffleDeck();

	// size
	size_t sizeDeck() const;

	// add card method
	void addCard(Card cd);

	// const equivalent operator
	bool operator==(const Deck & dk) const;

	// Friend operator<<
	friend ostream &operator<< (ostream &out, const Deck &deck_obj);
	friend ostream &operator<< (Deck &d_x, Deck &d_y);
	friend ostream &operator<< (Deck &d, Hand &h);

	// A non-member insertion operator
	friend class Hand;
	friend ostream &operator<<(Hand &h, Deck &d);

private:
	// Deck vector
	vector<Card> card_vector_in_deck;
};

ostream &operator<< (ostream &out, const Deck &deck_obj);
ostream &operator<< (Hand &h, Deck &d);
ostream &operator<< (Deck &d_x, Deck &d_y);
ostream &operator<< (Deck &d, Hand &h);
bool IsValidInput(string str);

#endif // DECK_H
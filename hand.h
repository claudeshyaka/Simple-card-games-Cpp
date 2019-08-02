#ifndef HAND_H
#define HAND_H

#include <string>
#include <vector>

#include "card.h"

using std::vector;


class Hand {

public:
	// default constructor
	Hand();

	//copy constructor
	Hand(const Hand &);

	// destructor
	~Hand();

	// Assignment operator
	Hand &operator=(const Hand &);

	// const size
	size_t sizeHand() const;

	// const equivalent operator
	bool operator==(const Hand &) const;

	// const less than operator
	bool operator<(const Hand&) const;

	// A const "as string" method
	string asString() const;

	// A non-member insertion operator (operator<<)
	friend ostream &operator<<(ostream &out, const Hand &hand_obj);

	// Indexing operator[]
	Card operator[](size_t pos);

	// remove card from hand

	void removeCard(size_t pos);

	// Hand Ranks.
	bool straightFlush();
	bool fourOfKind();
	bool fullHouse();
	bool flush();
	bool straight();
	bool threeOfKind();
	bool twoPairs();
	bool onePair();
	bool noRank();

	// Sorting Hands according to extra credit descriptions
	int getStraightFlushHand(vector<Card> &);
	int getFullHouseHand(vector<Card> &);
	int getFourOfKindHand(vector<Card> &);
	int getFlushHand(vector<Card> &);
	int getStraightHand(vector<Card> &);
	int getThreeOfKindHand(vector<Card> &);
	int getTwoPairsHand(vector<Card> &);
	int getOnePairHand(vector<Card> &);
	int getNoRankHand(vector<Card> &);


	// A non-member insertion operator
	friend class Deck;
	friend ostream &operator<<(Hand &h, Deck &d);
	friend ostream &operator<< (Deck &d, Hand &h);

private:
	vector<Card> card_vector_in_hand;
};

ostream &operator<<(ostream &out, const Hand &hand_obj);
ostream &operator<<(Hand &h, Deck &d);
ostream &operator<< (Deck &d, Hand &h);
bool pokerRankHands(const Hand & h1, const Hand & h2);
#endif//HAND_H

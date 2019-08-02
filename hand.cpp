#include "stdafx.h"

#include <iostream>
#include <algorithm>
#include <random>
#include <iterator>
#include <vector>
#include <sstream>
#include <fstream>
#include <ostream>
#include <functional>

using namespace std;

#include "CSE332_lab4.h"
#include "nullbuffer.h"
#include "card.h"
#include "deck.h"
#include "hand.h"

/**************************************************/
NullBuffer null_buffer_hand;
ostream null_stream_hand(&null_buffer_hand);

#if DEBUG
#define print_debug cout
#else
#define print_debug null_stream_hand
#endif
/**************************************************/


// Default constructor
Hand::Hand() : card_vector_in_hand(card_vector_in_hand) {
}

// copy constructor
Hand::Hand(const Hand &other) : card_vector_in_hand(other.card_vector_in_hand) {
}

// Destructor
Hand::~Hand() {}

// Assignment operator. Code obtained from https://en.wikipedia.org/wiki/Assignment_operator_(C%2B%2B)
Hand &Hand::operator=(const Hand &other) {
	if (!(*this == other)) {
		card_vector_in_hand.clear();
		//copy(other.card_vector_in_hand.begin(), other.card_vector_in_hand.end(), card_vector_in_hand.begin());
		card_vector_in_hand = other.card_vector_in_hand;
	}
	return *this;
}

// Size method
size_t Hand::sizeHand() const {
	return card_vector_in_hand.size();
}

// const equivalent operator -- used the STL equal method
bool Hand::operator==(const Hand &other) const {

	if (other.card_vector_in_hand == card_vector_in_hand) {
		return true;
	}
	else {
		return false;
	}
}


// const less than operator
bool Hand::operator<(const Hand &other) const {

	bool r_status;

	if (card_vector_in_hand < other.card_vector_in_hand) {
		r_status = true;
	}
	else {
		r_status = false;
	}
	return r_status;
}

// A const "as string" method
string Hand::asString() const {

	string str = NULL_CHAR;

	for (vector<Card>::const_iterator it = card_vector_in_hand.cbegin(); it != card_vector_in_hand.cend(); ++it) {

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


		str += rank + "" + suit + " ";
	}
	return str;
}

// A non-member insertion operator (operator<<)
ostream &operator<< (ostream &out, const Hand &hand_obj) {
	string str = hand_obj.asString();
	out << str;
	return out;
}

// A non-member insertion operator
ostream &operator<< (Hand &h, Deck &d) {
	h.card_vector_in_hand.push_back(d.card_vector_in_deck.back());
	sort(h.card_vector_in_hand.begin(), h.card_vector_in_hand.end());
	d.card_vector_in_deck.pop_back();
	ostream &o = cout;
	//o << h.asString() << endl;
	return o;
}

// pokerRank function
bool pokerRankHands(const Hand & h1, const Hand & h2) {
	Hand h1_ = h1;
	Hand h2_ = h2;
	int r_status1;
	int r_status2;
	if (h1_.sizeHand() != h2_.sizeHand()) {
		hand_exc_t i = HANDS_SIZE_NOT_EQUAL;
		cout << "Number of cards in each hands is not the same!" << endl;
		throw i;
	}
	// Check hands
	if (h1_.straightFlush()) {
		if (h2_.straightFlush()) {
			vector<Card> v1;
			vector<Card> v2;
			r_status1 = h1_.getStraightFlushHand(v1);
			r_status2 = h2_.getStraightFlushHand(v2);
			if (r_status1 == hand_exc_t::EXEC_STRAIGHT_FLUSH_HAND ||
				r_status2 == hand_exc_t::EXEC_STRAIGHT_FLUSH_HAND) {
				hand_exc_t i = hand_exc_t::EXEC_STRAIGHT_FLUSH_HAND;
				cout << "Straigt flush exception." << endl;
				throw i;
			}
			if (v2[4] < v1[4]) {
				return true;
			}
			return false;
		}
		else {
			return true;
		}
	}
	else if (h1_.fourOfKind()) {
		if (h2_.fourOfKind()) {
			vector<Card> v1;
			vector<Card> v2;
			r_status1 = h1_.getFourOfKindHand(v1);
			r_status2 = h2_.getFourOfKindHand(v1);
			if (r_status1 == hand_exc_t::EXEC_FOUR_OF_KIND_HAND ||
				r_status2 == hand_exc_t::EXEC_FOUR_OF_KIND_HAND) {
				hand_exc_t i = hand_exc_t::EXEC_FOUR_OF_KIND_HAND;
				cout << "Four of a kind exception." << endl;
				throw i;
			}
			else {
				if (v2[1].c_rank < v1[1].c_rank || v2[2].c_rank < v1[2].c_rank ||
					v2[3].c_rank < v1[3].c_rank || v2[4].c_rank < v1[4].c_rank) {
					return true;
				}
				else {
					return false;
				}
			}
		}
		else if (h2_.straightFlush()) {
			return false;
		}
		else {
			return true;
		}
	}
	else if (h1_.fullHouse()) {
		if (h2_.fullHouse()) {
			vector<Card> v1;
			vector<Card> v2;
			r_status1 = h1_.getFullHouseHand(v1);
			r_status2 = h2_.getFullHouseHand(v2);
			if (r_status1 == hand_exc_t::EXEC_FULL_HOUSE_HAND ||
				r_status2 == hand_exc_t::EXEC_FULL_HOUSE_HAND) {
				hand_exc_t i = hand_exc_t::EXEC_FULL_HOUSE_HAND;
				cout << "Full house exception." << endl;
				throw i;
			}
			else {
				if (v2[0].c_rank < v1[0].c_rank || v2[1].c_rank < v1[1].c_rank || v2[2].c_rank < v1[2].c_rank) {
					return true;
				}
				else if (v2[0].c_rank == v1[0].c_rank || v2[1].c_rank == v1[1].c_rank || v2[2].c_rank == v1[2].c_rank) {
					if (v2[3].c_rank < v1[3].c_rank || v2[4].c_rank < v1[4].c_rank) {
						return true;
					}
					else {
						return false;
					}
				}
				else {
					return false;
				}
			}
		}
		else if (h2_.fourOfKind() || h2_.straightFlush()) {
			return false;
		}
		else {
			return true;
		}
	}
	else if (h1_.flush()) {
		if (h2_.flush()) {
			vector<Card> v1;
			vector<Card> v2;
			r_status1 = h1_.getFlushHand(v1);
			r_status2 = h2_.getFlushHand(v2);
			if (r_status1 == hand_exc_t::EXEC_FLUSH_HAND ||
				r_status2 == hand_exc_t::EXEC_FLUSH_HAND) {
				hand_exc_t i = hand_exc_t::EXEC_FLUSH_HAND;
				cout << "Flush exception." << endl;
				throw i;
			}
			else {
				if (v2[0].c_rank < v1[0].c_rank) {
					return true;
				}
				else if (v2[0].c_rank == v1[0].c_rank) {
					if (v2[1].c_rank < v1[1].c_rank) {
						return true;
					}
					else if (v2[1].c_rank == v1[1].c_rank) {
						if (v2[2].c_rank < v1[2].c_rank) {
							return true;
						}
						else if (v2[2].c_rank == v1[2].c_rank) {
							if (v2[3].c_rank < v1[3].c_rank) {
								return true;
							}
							else if (v2[3].c_rank == v1[3].c_rank) {
								if (v2[4].c_rank < v1[4].c_rank) {
									return true;
								}
								else {
									return false;
								}
							}
							else {
								return false;
							}
						}
						else {
							return false;
						}
					}
					else {
						return false;
					}
				}
				else {
					return false;
				}
			}
		}
		else if (h2_.fourOfKind() || h2_.fullHouse() || h2_.straightFlush()) {
			return false;
		}
		else {
			return true;
		}
	}
	else if (h1_.straight()) {
		if (h2_.straight()) {
			vector<Card> v1;
			vector<Card> v2;
			r_status1 = h1_.getStraightHand(v1);
			r_status2 = h2_.getStraightHand(v2);
			if (r_status1 == hand_exc_t::EXEC_STRAIGHT_HAND ||
				r_status2 == hand_exc_t::EXEC_STRAIGHT_HAND) {
				hand_exc_t i = hand_exc_t::EXEC_STRAIGHT_HAND;
				cout << "Straigt exception." << endl;
				throw i;
			}
			else {
				if (v2[4] < v1[4]) {
					return true;
				}
				else {
					return false;
				}
			}
		}
		else if (h2_.flush() || h2_.fullHouse() || h2_.fourOfKind() || h2_.straightFlush()) {
			return false;
		}
		else {
			return true;
		}
	}
	else if (h1_.threeOfKind()) {
		if (h2_.threeOfKind()) {
			vector<Card> v1;
			vector<Card> v2;
			r_status1 = h1_.getThreeOfKindHand(v1);
			r_status2 = h2_.getThreeOfKindHand(v2);
			if (r_status1 == hand_exc_t::EXEC_THREE_OF_KIND_HAND ||
				r_status2 == hand_exc_t::EXEC_THREE_OF_KIND_HAND) {
				hand_exc_t i = hand_exc_t::EXEC_THREE_OF_KIND_HAND;
				cout << "Three of a kind exception." << endl;
				throw i;
			}
			else {
				if (v2[0].c_rank < v1[0].c_rank || v2[1].c_rank < v1[1].c_rank || v2[2].c_rank < v1[2].c_rank) {
					return true;
				}
				else {
					return false;
				}
			}
		}
		else if (h2_.noRank() || h2_.onePair() || h2_.twoPairs()) {
			return true;
		}
		else {
			return false;
		}
	}
	else if (h1_.twoPairs()) {
		if (h2_.twoPairs()) {
			vector<Card> v1;
			vector<Card> v2;
			r_status1 = h1_.getTwoPairsHand(v1);
			r_status2 = h2_.getTwoPairsHand(v2);
			if (r_status1 == hand_exc_t::EXEC_TWO_PAIRS_HAND ||
				r_status2 == hand_exc_t::EXEC_TWO_PAIRS_HAND) {
				hand_exc_t i = hand_exc_t::EXEC_TWO_PAIRS_HAND;
				cout << "Two pairs exception." << endl;
				throw i;
			}
			else {
				if (v2[0].c_rank < v1[0].c_rank || v2[1].c_rank < v1[1].c_rank) {
					return true;
				}
				else if (v2[0].c_rank == v1[0].c_rank || v2[1].c_rank == v1[1].c_rank) {
					if (v2[2].c_rank < v1[2].c_rank || v2[3].c_rank < v1[3].c_rank) {
						return true;
					}
					else if (v2[2].c_rank == v1[2].c_rank || v2[3].c_rank == v1[3].c_rank) {
						if (v2[4] < v1[4]) {
							return true;
						}
						else {
							return false;
						}
					}
					else {
						return false;
					}
				}
				else {
					return true;
				}
			}
		}
		else if (h2_.noRank() || h2_.onePair()) {
			return true;
		}
		else {
			return false;
		}
	}
	else if (h1_.onePair()) {
		if (h2_.onePair()) {
			vector<Card> v1;
			vector<Card> v2;
			r_status1 = h1_.getOnePairHand(v1);
			r_status2 = h2_.getOnePairHand(v2);
			if (r_status1 == hand_exc_t::EXEC_ONE_PAIRS_HAND ||
				r_status2 == hand_exc_t::EXEC_ONE_PAIRS_HAND) {
				hand_exc_t i = hand_exc_t::EXEC_ONE_PAIRS_HAND;
				cout << "One pair exception." << endl;
				throw i;
			}
			else {
				if (v2[4].c_rank < v1[4].c_rank || v2[3].c_rank < v1[3].c_rank) {
					return true;
				}
				else if (v2[4].c_rank == v1[4].c_rank || v2[3].c_rank == v1[3].c_rank) {
					if (v2[2] < v1[2]) {
						return true;
					}
					else if (v2[2] == v1[2]) {
						if (v2[1] < v1[1]) {
							return true;
						}
						else if (v2[1] == v1[1]) {
							if (v2[0] < v1[0]) {
								return true;
							}
							else {
								return false;
							}
						}
						else {
							return false;
						}
					}
					else {
						return false;
					}
				}
				else {
					return false;
				}
			}
		}
		else if (h2_.noRank()) {
			return true;
		}
		else {
			return false;
		}
	}
	else if (h1_.noRank()) {
		if (h2_.noRank()) {
			vector<Card> v1;
			vector<Card> v2;
			r_status1 = h1_.getNoRankHand(v1);
			r_status2 = h2_.getNoRankHand(v2);
			if (r_status1 == hand_exc_t::EXEC_NO_RANK_HAND ||
				r_status2 == hand_exc_t::EXEC_NO_RANK_HAND) {
				hand_exc_t i = hand_exc_t::EXEC_NO_RANK_HAND;
				cout << "No rank exception." << endl;
				throw i;
			}
			else {
				if (v2[0].c_rank < v1[0].c_rank) {
					return true;
				}
				else if (v2[0].c_rank == v1[0].c_rank) {
					if (v2[1].c_rank < v1[1].c_rank) {
						return true;
					}
					else if (v2[1].c_rank == v1[1].c_rank) {
						if (v2[2].c_rank < v1[2].c_rank) {
							return true;
						}
						else if (v2[2].c_rank == v1[2].c_rank) {
							if (v2[3].c_rank < v1[3].c_rank) {
								return true;
							}
							else if (v2[3].c_rank == v1[3].c_rank) {
								if (v2[4].c_rank < v1[4].c_rank) {
									return true;
								}
								else {
									return false;
								}
							}
							else {
								return false;
							}
						}
						else {
							return false;
						}
					}
					else {
						return false;
					}
				}
				else {
					return false;
				}
			}
		}
		else {
			return false;
		}
	}
	else {
		hand_exc_t i = UNKOWN_RANK;
		cout << "*********Unknown Rank!*********" << endl;
		throw i;
	}
}

//*****************************Sort Ranks*******************************
// Sort Straight Flush
int
Hand::getStraightFlushHand(vector<Card> &v) {


	while (next_permutation(card_vector_in_hand.begin(), card_vector_in_hand.end())) {
		if (card_vector_in_hand[0] < card_vector_in_hand[1] &&
			card_vector_in_hand[1] < card_vector_in_hand[2] &&
			card_vector_in_hand[2] < card_vector_in_hand[3] &&
			card_vector_in_hand[3] < card_vector_in_hand[4]) {

			v = card_vector_in_hand;
			return SUCCESS;
		}
	}
	print_debug << "return -> " << EXEC_STRAIGHT_FLUSH_HAND << endl;
	return EXEC_STRAIGHT_FLUSH_HAND;
}

// return Four Of Kind Rank
int
Hand::getFourOfKindHand(vector<Card> &v) {
	while (next_permutation(card_vector_in_hand.begin(), card_vector_in_hand.end())) {
		if (card_vector_in_hand[1].c_rank == card_vector_in_hand[2].c_rank &&
			card_vector_in_hand[2].c_rank == card_vector_in_hand[3].c_rank &&
			card_vector_in_hand[3].c_rank == card_vector_in_hand[4].c_rank) {

			v = card_vector_in_hand;
			return SUCCESS;
		}
		//PRINT_DEBUG << *this << endl;
	}
	print_debug << "return -> " << EXEC_FOUR_OF_KIND_HAND << endl;
	return EXEC_FOUR_OF_KIND_HAND;
}

// Sort Full House
int
Hand::getFullHouseHand(vector<Card> &v) {
	while (next_permutation(card_vector_in_hand.begin(), card_vector_in_hand.end())) {
		if (card_vector_in_hand[0].c_rank == card_vector_in_hand[1].c_rank &&
			card_vector_in_hand[1].c_rank == card_vector_in_hand[2].c_rank &&
			card_vector_in_hand[3].c_rank == card_vector_in_hand[4].c_rank) {

			v = card_vector_in_hand;
			return SUCCESS;
		}
	}
	print_debug << "return -> " << EXEC_FULL_HOUSE_HAND << endl;
	return EXEC_FULL_HOUSE_HAND;
}

// Sort Straight
int
Hand::getFlushHand(vector<Card> &v) {
	while (next_permutation(card_vector_in_hand.begin(), card_vector_in_hand.end())) {
		if (card_vector_in_hand[4].c_rank < card_vector_in_hand[3].c_rank &&
			card_vector_in_hand[3].c_rank < card_vector_in_hand[2].c_rank &&
			card_vector_in_hand[2].c_rank < card_vector_in_hand[1].c_rank &&
			card_vector_in_hand[1].c_rank < card_vector_in_hand[0].c_rank) {
			v = card_vector_in_hand;
			return SUCCESS;
		}
	}
	print_debug << "return -> " << EXEC_FLUSH_HAND << endl;
	return EXEC_FLUSH_HAND;
}

// Sort straight
int
Hand::getStraightHand(vector<Card> &v) {
	while (next_permutation(card_vector_in_hand.begin(), card_vector_in_hand.end())) {
		if (card_vector_in_hand[0] < card_vector_in_hand[1] &&
			card_vector_in_hand[1] < card_vector_in_hand[2] &&
			card_vector_in_hand[2] < card_vector_in_hand[3] &&
			card_vector_in_hand[3] < card_vector_in_hand[4]) {
			v = card_vector_in_hand;
			return SUCCESS;
		}
	}
	print_debug << "return -> " << EXEC_STRAIGHT_HAND << endl;
	return EXEC_STRAIGHT_HAND;
}

// Sort Three of a Kind
int
Hand::getThreeOfKindHand(vector<Card> &v) {
	while (next_permutation(card_vector_in_hand.begin(), card_vector_in_hand.end())) {
		if (card_vector_in_hand[0].c_rank == card_vector_in_hand[1].c_rank &&
			card_vector_in_hand[1].c_rank == card_vector_in_hand[2].c_rank) {

			v = card_vector_in_hand;
			return SUCCESS;
		}
	}
	print_debug << "return -> " << EXEC_THREE_OF_KIND_HAND << endl;
	return EXEC_THREE_OF_KIND_HAND;
}

// Sort Two Pairs
int
Hand::getTwoPairsHand(vector<Card> &v) {
	while (next_permutation(card_vector_in_hand.begin(), card_vector_in_hand.end())) {
		if (card_vector_in_hand[0].c_rank == card_vector_in_hand[1].c_rank &&
			card_vector_in_hand[2].c_rank == card_vector_in_hand[3].c_rank &&
			card_vector_in_hand[2].c_rank < card_vector_in_hand[0].c_rank &&
			card_vector_in_hand[3].c_rank < card_vector_in_hand[1].c_rank) {

			v = card_vector_in_hand;
			return SUCCESS;
		}
	}
	print_debug << "return -> " << EXEC_TWO_PAIRS_HAND << endl;
	return EXEC_TWO_PAIRS_HAND;
}

// Get One Pair Hand
int
Hand::getOnePairHand(vector<Card> &v) {
	while (next_permutation(card_vector_in_hand.begin(), card_vector_in_hand.end())) {
		if (card_vector_in_hand[0] < card_vector_in_hand[1] &&
			card_vector_in_hand[1] < card_vector_in_hand[2] &&
			card_vector_in_hand[3].c_rank == card_vector_in_hand[4].c_rank) {
			v = card_vector_in_hand;
			return SUCCESS;
		}
	}
	print_debug << "return -> " << EXEC_ONE_PAIRS_HAND << endl;
	return EXEC_ONE_PAIRS_HAND;
}

// Get No Rank Hand
int
Hand::getNoRankHand(vector<Card> &v) {
	while (next_permutation(card_vector_in_hand.begin(), card_vector_in_hand.end())) {
		if (card_vector_in_hand[4].c_rank < card_vector_in_hand[3].c_rank &&
			card_vector_in_hand[3].c_rank < card_vector_in_hand[2].c_rank &&
			card_vector_in_hand[2].c_rank < card_vector_in_hand[1].c_rank &&
			card_vector_in_hand[1].c_rank < card_vector_in_hand[0].c_rank) {
			v = card_vector_in_hand;
			return SUCCESS;
		}
	}
	print_debug << "return -> " << EXEC_NO_RANK_HAND << endl;
	return EXEC_NO_RANK_HAND;
}

// **************************************************************************

// *********************************Hand Ranks*******************************
// Straight Flush
bool Hand::straightFlush() {
	int five_same_suit_cnt = ZERO;
	bool five_consc_rank_cnt = false;
	if (((card_vector_in_hand[0].c_rank + 1) == card_vector_in_hand[1].c_rank) &&
		((card_vector_in_hand[1].c_rank + 1) == card_vector_in_hand[2].c_rank) &&
		((card_vector_in_hand[2].c_rank + 1) == card_vector_in_hand[3].c_rank) &&
		((card_vector_in_hand[3].c_rank + 1) == card_vector_in_hand[4].c_rank)) {

		five_consc_rank_cnt = true;
	}

	// check for all other hands ranking conditions
	for (vector<Card>::iterator it3 = card_vector_in_hand.begin(); it3 != card_vector_in_hand.end(); ++it3) {
		vector<Card>::iterator it4 = card_vector_in_hand.begin();
		int same_suit_cnt = ZERO;

		while (it4 != card_vector_in_hand.end()) {
			if ((*it3).c_suits == (*it4).c_suits) {
				++same_suit_cnt;
			}
			++it4;
		}
		if (same_suit_cnt == FIVE) {
			++five_same_suit_cnt;
		}
	}
	if (five_same_suit_cnt == FIVE && five_consc_rank_cnt) { // straight flush
		print_debug << "straight flush" << endl;
		return true;
	}
	return false;
}

// Four of a kind
bool Hand::fourOfKind() {
	int four_same_rank_cnt = ZERO;
	// check for all other hands ranking conditions
	for (vector<Card>::iterator it3 = card_vector_in_hand.begin(); it3 != card_vector_in_hand.end(); ++it3) {
		vector<Card>::iterator it4 = card_vector_in_hand.begin();
		int same_rank_cnt_0 = ZERO;
		while (it4 != card_vector_in_hand.end()) {
			if ((*it3).c_rank == (*it4).c_rank) {
				++same_rank_cnt_0;
			}
			++it4;
		}
		if (same_rank_cnt_0 == FOUR) {
			++four_same_rank_cnt;
		}
	}
	if (four_same_rank_cnt == FOUR) { // four of a kind
		print_debug << "four of a kind" << endl;
		return true;
	}
	return false;
}

// Full House
bool Hand::fullHouse() {
	int three_same_rank_cnt = ZERO;
	int two_same_rank_cnt = ZERO;
	// check for all other hands ranking conditions
	for (vector<Card>::iterator it3 = card_vector_in_hand.begin(); it3 != card_vector_in_hand.end(); ++it3) {
		vector<Card>::iterator it4 = card_vector_in_hand.begin();
		int same_suit_cnt_0 = ZERO;
		int same_rank_cnt_0 = ZERO;
		while (it4 != card_vector_in_hand.end()) {
			if ((*it3).c_suits == (*it4).c_suits) {
				++same_suit_cnt_0;
			}
			if ((*it3).c_rank == (*it4).c_rank) {
				++same_rank_cnt_0;
			}
			++it4;
		}
		if (same_rank_cnt_0 == THREE) {
			++three_same_rank_cnt;
		}
		if (same_rank_cnt_0 == TWO) {
			++two_same_rank_cnt;
		}
	}
	if (three_same_rank_cnt == THREE && two_same_rank_cnt == TWO) { // full house
		print_debug << "full house" << endl;
		return true;
	}
	return false;
}

// Flush
bool Hand::flush() {
	int five_same_suit_cnt = ZERO;
	bool five_consc_rank_cnt = false;
	// Check for consecutive ranks
	if (((card_vector_in_hand[0].c_rank + 1) == card_vector_in_hand[1].c_rank) &&
		((card_vector_in_hand[1].c_rank + 1) == card_vector_in_hand[2].c_rank) &&
		((card_vector_in_hand[2].c_rank + 1) == card_vector_in_hand[3].c_rank) &&
		((card_vector_in_hand[3].c_rank + 1) == card_vector_in_hand[4].c_rank)) {

		five_consc_rank_cnt = true;

	}
	for (vector<Card>::iterator it3 = card_vector_in_hand.begin(); it3 != card_vector_in_hand.end(); ++it3) {
		vector<Card>::iterator it4 = card_vector_in_hand.begin();
		int same_suit_cnt_0 = 0;
		while (it4 != card_vector_in_hand.end()) {

			if ((*it3).c_suits == (*it4).c_suits) {
				++same_suit_cnt_0;
			}
			++it4;
		}
		if (same_suit_cnt_0 == FIVE) {
			++five_same_suit_cnt;
		}
	}
	if (five_same_suit_cnt == FIVE && !five_consc_rank_cnt) { // flush
		print_debug << "flush" << endl;
		return true;
	}
	return false;
}

// Straight
bool Hand::straight() {
	bool five_consc_rank_cnt = false;
	// Check for consecutive ranks
	if (((card_vector_in_hand[0].c_rank + 1) == card_vector_in_hand[1].c_rank) &&
		((card_vector_in_hand[1].c_rank + 1) == card_vector_in_hand[2].c_rank) &&
		((card_vector_in_hand[2].c_rank + 1) == card_vector_in_hand[3].c_rank) &&
		((card_vector_in_hand[3].c_rank + 1) == card_vector_in_hand[4].c_rank)) {
		five_consc_rank_cnt = true;
	}
	else if (five_consc_rank_cnt) { // straight
		print_debug << "straight" << endl;
		return true;
	}
	return false;
}

//Three of a kind
bool Hand::threeOfKind() {
	int three_same_rank_cnt = ZERO;
	int two_same_rank_cnt = ZERO;
	// check for all other hands ranking conditions
	for (vector<Card>::iterator it3 = card_vector_in_hand.begin(); it3 != card_vector_in_hand.end(); ++it3) {
		vector<Card>::iterator it4 = card_vector_in_hand.begin();
		int same_suit_cnt_0 = 0;
		int same_rank_cnt_0 = 0;
		int consc_rank_cnt_0 = 0;
		while (it4 != card_vector_in_hand.end()) {
			if ((*it3).c_rank == (*it4).c_rank) {
				++same_rank_cnt_0;
			}
			++it4;
		}
		if (same_rank_cnt_0 == THREE) {
			++three_same_rank_cnt;
		}
		if (same_rank_cnt_0 == TWO) {
			++two_same_rank_cnt;
		}
	}
	if (three_same_rank_cnt == THREE && two_same_rank_cnt == 0) { // three of a kind
		print_debug << "three of a kind" << endl;
		return true;
	}
	return false;
}

// Two Pairs
bool Hand::twoPairs() {
	int two_same_rank_cnt = ZERO;
	// check for all other hands ranking conditions
	for (vector<Card>::iterator it3 = card_vector_in_hand.begin(); it3 != card_vector_in_hand.end(); ++it3) {
		vector<Card>::iterator it4 = card_vector_in_hand.begin();
		int same_rank_cnt_0 = ZERO;
		while (it4 != card_vector_in_hand.end()) {
			if ((*it3).c_rank == (*it4).c_rank) {
				++same_rank_cnt_0;
			}
			++it4;
		}
		if (same_rank_cnt_0 == TWO) {
			++two_same_rank_cnt;
		}
	}
	if (two_same_rank_cnt == FOUR) { // two pairs
		print_debug << "two pairs" << endl;
		return true;
	}
	return false;
}

// One Pair
bool Hand::onePair() {
	int two_same_rank_cnt = ZERO;
	int three_same_rank_cnt = ZERO;
	// check for all other hands ranking conditions
	for (vector<Card>::iterator it3 = card_vector_in_hand.begin(); it3 != card_vector_in_hand.end(); ++it3) {
		vector<Card>::iterator it4 = card_vector_in_hand.begin();
		int same_rank_cnt_0 = ZERO;

		while (it4 != card_vector_in_hand.end()) {
			if ((*it3).c_rank == (*it4).c_rank) {
				++same_rank_cnt_0;
			}
			++it4;
		}
		if (same_rank_cnt_0 == THREE) {
			++three_same_rank_cnt;
		}
		if (same_rank_cnt_0 == TWO) {
			++two_same_rank_cnt;
		}
	}
	if (two_same_rank_cnt == TWO && three_same_rank_cnt == ZERO) { // one pair
		print_debug << "one pair" << endl;
		return true;
	}
	return false;
}

// No Ranks
bool Hand::noRank() {
	if (straightFlush() || fourOfKind() || fullHouse() ||
		straight() || threeOfKind() || twoPairs() || onePair()) {
		return false;
	}
	print_debug << "No Ranks" << endl;
	return true;
}


// Indexing operator[]
Card Hand::operator[](size_t pos) {
	if (pos >= card_vector_in_hand.size()) {
		int i = 0;
		i = POS_GREATER_THAN_SIZE;
		throw i;
	}
	return card_vector_in_hand.at(pos);
}

// remove
void Hand::removeCard(size_t pos) {
	if (pos >= card_vector_in_hand.size()) {
		int i = 0;
		i = POS_GREATER_THAN_SIZE;
		throw i;
	}
	card_vector_in_hand.erase(card_vector_in_hand.begin() + pos);
}

// **************************************************************************

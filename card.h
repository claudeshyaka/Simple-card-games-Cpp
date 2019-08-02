#ifndef CARD_H
#define CARD_H

struct Card {
	Card();
	enum card_suits { clubs, diamonds, hearts, spades };
	enum card_rank {
		two, three, four, five, six,
		seven, eight, nine, ten, jack,
		queen, king, ace
	};
	bool operator< (const Card &) const;
	bool operator== (const Card &) const;
	// Insert card in vector.
	void convertStringToCard(Card&, string);
	// card attributes
	card_suits c_suits;
	card_rank c_rank;
};

ostream &operator<<(ostream &out_card, const Card &cd);
#endif // CARD_H

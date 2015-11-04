#ifndef DECK_H
#define DECK_H

#include "types.h"
#include <iostream>
#include <string>
#include <vector>

enum Suit { Hearts, Spades, Diamonds, Clubs };
enum Rank {
	Two, Three, Four, Five, Six, Seven, Eight, Nine, Ten, Jack, Queen,
	King, Ace
};

ostream& operator<< (ostream& stream, const Suit& s);
ostream& operator<< (ostream& stream, const Rank& r);

struct Card
{
	Card(uint suit, uint rank);
	Suit suit;
	Rank rank;
};

ostream& operator<< (ostream& stream, const Card& c);

typedef vector<Card> Cards;

ostream& operator<< (ostream& stream, const Cards& cards);

class Deck
{
public:
	Deck();
	Cards Deal(uint n); // returns n dealt cards and REMOVES the cards from the deck object.
	void Display();
	void Shuffle();
	
private:
	Cards cards;
};

#endif
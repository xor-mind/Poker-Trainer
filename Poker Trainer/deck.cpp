#include "deck.h"
#include <ctime>
#include <random>

Card::Card(uint suit, uint rank)
{
	this->suit = Suit(suit);
	this->rank = Rank(rank);
}

ostream& operator<< (ostream& stream, const Suit& s)
{
	switch (s)
	{
		case Suit::Hearts:
			cout << "Hearts"; break;

		case Suit::Diamonds:
			cout << "Dimaonds"; break;

		case Suit::Clubs:
			cout << "Clubs"; break;

		case Suit::Spades:
			cout << "Spades"; break;

		default: 
			cerr << "ERROR - Unexpected Input" << endl;
	}

	return stream;
}

ostream& operator<< (ostream& stream, const Rank& r)
{
	switch (r)
	{
		case Rank::Two:
			cout << "Two"; break;

		case Rank::Three:
			cout << "Three"; break;

		case Rank::Four:
			cout << "Four"; break;

		case Rank::Five:
			cout << "Five"; break;

		case Rank::Six:
			cout << "Six"; break;

		case Rank::Seven:
			cout << "Seven"; break;

		case Rank::Eight:
			cout << "Eight"; break;

		case Rank::Nine:
			cout << "Nine"; break;

		case Rank::Ten:
			cout << "Ten"; break;

		case Rank::Jack:
			cout << "Jack"; break;

		case Rank::Queen:
			cout << "Queen"; break;

		case Rank::King:
			cout << "King"; break;

		case Rank::Ace:
			cout << "Ace"; break;

		default:
			cerr << "ERROR - Unexpected Input" << endl;
	}
	return stream;
}

ostream& operator<< (ostream& stream, const Card& c)
{
	cout << c.rank << " of " << c.suit;
	return stream;
}

ostream& operator<< (ostream& stream, const Cards& cards)
{
	for (const Card& c : cards)
	{
		cout << c << " ";
	}

	return stream;
}

Deck::Deck()
{
	for (uint i = 0; i < 4; ++i)
	{
		for (uint j = 0; j < 13; ++j)
		{
			cards.push_back( Card(i, j) );
		}
	}
}

Cards Deck::Deal(uint n)
{
	if (n > cards.size())
	{
		cerr << "Trying to deal more cards than are left in deck!" << endl;
	}

	Cards cards( this->cards.end() - n, this->cards.end() );
	this->cards.erase(this->cards.end() - n, this->cards.end());
	return cards;
}

void Deck::Display()
{
	for (auto c : cards )
	{
		cout << c << endl;
	}
}

void Deck::Shuffle()
{
	time_t t = time(NULL); 
	mt19937 randgen(static_cast<unsigned int>(t));
	uniform_int_distribution<int> cardPick(0, 51);

	// int c = cardPick( randgen );

	vector<Card> shuffledDeck;

	for (int i = 0; i < 51; ++i)
	{
		int k = cardPick(randgen);
		Card c = cards[k];
		cards[k] = cards[i];
		cards[i] = c;
	}
}


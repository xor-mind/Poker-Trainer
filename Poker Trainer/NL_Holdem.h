#ifndef NL_HOLDEM_H
#define NL_HOLDEM_H


#include "player.h"

class NL_Holdem
{
public:
	NL_Holdem();
	void Input();
	void Logic();
	void Output();

	bool Hand() const { return hand;  }

private:
	enum State { preflop_deal, preflop_bet, flop_deal, flop_bet, turn, river };
	Deck deck;
	Players players;
	uint btnPos, actionPos;
	uint potSize;
	State state;
	Cards flop;
	SharedGameInformation sharedGameInformation; // SharedGameInformation = SGI 
	uint smallBlind, bigBlind;
	bool hand;

	// some functions for the server to figure out what's going on
	bool ActionOnBB();

	uint CurrentPlayer();
	void NextPlayer();
	//uint ButtonPosition(int n);

	void AddPlayersToSGI();
};

#endif
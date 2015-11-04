#ifndef PLAYER_H
#define PLAYER_H

#include "deck.h"
#include "SharedGameInformation.h"
#include <memory>

//enum GameHistoryStates
//{
//	PlayerIsBtn, CardsDealt, PlayerAction
//};
//
//enum 
//
//class GameHistory
//{
//public:
//	GameHistoryStates state;
//};

class Player
{
public:
	Player();
	Player(uint stack, const string& name);
	Player(uint stack, const string& name, uint pos);
	virtual ~Player() {}

	int Bet(uint n);
	void Hand(const Cards& hand) { this->hand = hand; }
	void Stack(uint stack) { this->stack = stack; }
	uint Stack() const { return stack; }
	string Name() const { return name; }
	uint Position() const { return pos; }

	virtual SharedGameInformation::PlayerAction Input(SharedGameInformation& sharedGameInformation) = 0;
	virtual void Logic(SharedGameInformation& sharedGameInformation) = 0;
	virtual void Output() const = 0;

protected:
	uint pos;
	uint stack;
	Cards hand;
	string name;
};

class Human : public Player
{
public:
	Human(uint stack, const string& name) : Player(stack, name) {}
	Human(uint stack, const string& name, uint pos) : Player(stack, name, pos) {}
	~Human() {}
	SharedGameInformation::PlayerAction Input(SharedGameInformation& sharedGameInformation);
	void Logic(SharedGameInformation& sharedGameInformation);
	void Output() const;
};

class Callbot : public Player
{
public:
	Callbot(uint stack, const string& name) : Player(stack, name) {}
	Callbot(uint stack, const string& name, uint pos) : Player(stack, name, pos) {}
	~Callbot() {}
	SharedGameInformation::PlayerAction Input(SharedGameInformation& sharedGameInformation);
	void Logic(SharedGameInformation& sharedGameInformation);
	void Output() const;
};

typedef std::unique_ptr<Player> PlayerPtr;
typedef vector<PlayerPtr> Players;

#endif
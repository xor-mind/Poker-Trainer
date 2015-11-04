#include "player.h"

Player::Player()
{
	stack = 0;
}

Player::Player(uint stack, const string& name)
	: stack(stack), name(name) { }

Player::Player(uint stack, const string& name, uint pos)
	: stack(stack), name(name), pos(pos) { }

int Player::Bet(uint n)
{
	if (n >= stack )
		n = stack;

	stack -= n;

	return n;

}

SharedGameInformation::PlayerAction Human::Input(SharedGameInformation& sharedGameInformation)
{
	//cout << "what is your action?: ";
	//string input;
	//cin >> input;

	//if (input == "x")
	//{
	//	//
	//}
	uint callSize = sharedGameInformation.HowMuchToCall(pos);
	if ( callSize > 0)
	{
		return SharedGameInformation::PlayerAction(pos, SharedGameInformation::PlayerActionType::call, callSize);
	}
	else
		return SharedGameInformation::PlayerAction(pos, SharedGameInformation::PlayerActionType::check, 0);
}

void Human::Logic(SharedGameInformation& sharedGameInformation)
{

}

void Human::Output() const
{
	cout << hand[0] << " & " << hand[1] << endl;
}

// callbot logic //////////////////////////////////////////////////////////////
SharedGameInformation::PlayerAction Callbot::Input(SharedGameInformation& sharedGameInformation)
{
	// if there's a bet call
	// return call

	uint callSize = sharedGameInformation.HowMuchToCall(pos);
	if (callSize > 0)
	{
		return SharedGameInformation::PlayerAction(pos, SharedGameInformation::PlayerActionType::call, callSize);
	}
	else
		return SharedGameInformation::PlayerAction(pos, SharedGameInformation::PlayerActionType::check, 0);
}

void Callbot::Output() const
{
}

void Callbot::Logic(SharedGameInformation& sharedGameInformation)
{
}
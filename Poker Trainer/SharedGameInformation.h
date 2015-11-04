#ifndef SHARED_GAME_INFORMATION_H
#define SHARED_GAME_INFORMATION_H

#include "types.h"
#include <string>
#include <vector>

struct SharedGameInformation
{
	uint btnPosition;
	int currentMaxRaiseSize; // size of the largest raise 

	struct Player
	{
		uint   position;
		uint   stackSize;
		string name;

		Player(const string& name, uint position, uint stackSize)
			: name(name), position(position), stackSize(stackSize) {}
	};
	typedef vector<Player> Players;
	Players players;

	enum PlayerActionType { check, call, raise, fold };
	friend ostream& operator<< (ostream& stream, const PlayerActionType& pat)
	{
		switch (pat)
		{
			case PlayerActionType::call:
				cout << "call"; break;

			case PlayerActionType::raise:
				cout << "raises"; break;
		
			case PlayerActionType::check:
				cout << "check"; break;

			case PlayerActionType::fold :
				cout << "fold"; break;
			default:
				cerr << "ERROR - Unexpected Input" << endl;
		}

		return stream;
	}

	struct PlayerAction
	{
		PlayerAction(uint playerPos, PlayerActionType actionType, uint betSize) : playerPos(playerPos), actionType(actionType), betSize(betSize) {}
		PlayerActionType actionType;
		uint betSize;
		uint playerPos;

		bool Checked() { return (actionType == PlayerActionType::check ? true : false); }
	};
	vector<PlayerAction> playerActions;

	void AddPlayerAction(const PlayerAction& pa)
	{
		playerActions.push_back(pa);
		OutputLastAction();
	}

	uint HowMuchToCall(uint playerPos)
	{
		if (!playerActions.size())
		{
			cerr << "trying to find how much to call without any player actions in the list" << endl;
			exit(1);
		}
		// get most recent players action
		//int i = playerActions.size() - 1;
		//for (; i >= 0; --i)
		//{
		//	uint p = playerActions[i].playerPos;
		//	if (p == playerPos)
		//	{
		//		break;
		//	}
		//}

		//if (i < 0)
		//{
		//	return playerActions.back().betSize;
		//}

		//// if the most recent bet size is less than this players last bet size, he doesn't have to call anything.
		//if (playerActions.back().betSize < playerActions[i].betSize)
		//	return 0;
		//else
		//	return playerActions.back().betSize - playerActions[i].betSize; // else return the amount he has to call.
		//

		auto itr = playerActions.rbegin();
		for (; itr != playerActions.rend(); ++itr)
		{
			uint p = itr->playerPos;
			if (p == playerPos)
			{
				break;
			}
		}

		if (itr == playerActions.rend())
		{
			return playerActions.back().betSize;
		}

		if (playerActions.back().betSize < itr->betSize)
			return 0;
		else
			return playerActions.back().betSize - itr->betSize;
		
	}

	void OutputLastAction()
	{
		if (playerActions.size() > 0)
		{
			auto pa = playerActions.back();
			cout << players[pa.playerPos].name << " " << pa.actionType << "s ";
			if (pa.betSize > 0)
				cout << pa.betSize << endl;
			else
				cout << endl;
		}
	}
};

#endif
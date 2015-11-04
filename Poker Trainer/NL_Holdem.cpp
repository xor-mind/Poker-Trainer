#include "NL_Holdem.h"

NL_Holdem::NL_Holdem()
{
	players.push_back( PlayerPtr(new Human(100, "Adam", 0) ) );
	players.push_back( PlayerPtr(new Callbot(100, "CallBot", 1) ) );
	actionPos = btnPos = 0;
	potSize = 0;
	smallBlind = 1;
	bigBlind = 2;
	hand = true;

	state = preflop_deal;

	AddPlayersToSGI();
	sharedGameInformation.btnPosition = btnPos;
}

void NL_Holdem::AddPlayersToSGI()
{
	for (const auto & p : players)
	{
		static uint pos = 0;
		sharedGameInformation.players.push_back(SharedGameInformation::Player(p->Name(), pos, p->Stack()));
		pos++;
	}
}

void NL_Holdem::Input()
{
	switch (state)
	{
		case State::preflop_bet: 
		{
			auto p = players.begin() + actionPos;
			SharedGameInformation::PlayerAction pa = (*p)->Input(sharedGameInformation);

			if ( pa.actionType == SharedGameInformation::PlayerActionType::call )
			{ 
				// make sure players call what they need to or call all in.
				if (!(sharedGameInformation.HowMuchToCall(actionPos) == pa.betSize || pa.betSize == (*p)->Stack()))
				{
					cerr << "call size is invalid" << endl;
					exit(1);
				}

			}

			//if (pa.betSize != currBetSize) {
			//	cerr << "player's action doesn't correlate to current bet size";
			//	exit(1);
			//}

			sharedGameInformation.AddPlayerAction(pa);

			if (ActionOnBB() && pa.Checked() )
			{
				// go to next state in game
				state = State::flop_deal;
			}

			NextPlayer();

		} break;

		case State::flop_bet:
		{
			hand = false;
		} break;

		default:;
	}
}

void NL_Holdem::Logic()
{
	switch (state)
	{
		case State::preflop_deal:
		{
			deck.Shuffle();

			// deal cards to all players
			for ( auto& p : players)
			{
				p->Hand( deck.Deal(2) );
				p->Output();
			}

			// put blinds out
			potSize += players[CurrentPlayer()]->Bet(smallBlind);
			sharedGameInformation.AddPlayerAction(SharedGameInformation::PlayerAction(CurrentPlayer(), SharedGameInformation::PlayerActionType::raise, smallBlind));	
			NextPlayer();

			potSize += players[CurrentPlayer()]->Bet(bigBlind);
			sharedGameInformation.AddPlayerAction(SharedGameInformation::PlayerAction(CurrentPlayer(), SharedGameInformation::PlayerActionType::raise, bigBlind));
			NextPlayer();

			state = State::preflop_bet;
		}
		break;

		case State::flop_deal:
		{
			deck.Deal(1); // burn
			flop = deck.Deal(3);
			cout << flop << endl;
			state = State::flop_bet;
		} break;
	default:;
	}
}

void NL_Holdem::Output()
{
	//sharedGameInformation.playerActions.back();
	//players[actionPos]->Output();
}


uint NL_Holdem::CurrentPlayer()
{
	return actionPos;
}

void NL_Holdem::NextPlayer()
{
	actionPos++;
	if (actionPos == players.size())
		actionPos = 0;
}

bool NL_Holdem::ActionOnBB()
{
	if (actionPos != btnPos)
		return true;
	else
		return false;
}
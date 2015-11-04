#include "NL_Holdem.h"

int main()
{
	NL_Holdem nlh;
	
	while (nlh.Hand())
	{
		nlh.Input();
		nlh.Logic();
		nlh.Output();
	}

	cin.get();
}
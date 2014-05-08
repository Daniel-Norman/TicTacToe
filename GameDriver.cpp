/*
GameDriver.cpp
Copyright Daniel Norman 2014
*/
#include "Board.h";
#include <iostream>

int main()
{
	Board b(Board::Player);
	b.print();


	while (!b.getEmptySpaces().empty())
	{
		if (b.getTurn() == Board::Player)
		{
			cout << "Enter a location to place a move (1-9, q to quit): ";
			char space = 0;
			cin >> space;
			if (space < 49 || space > 57) break;

			b.play(space - 49);
		}
		else
		{
			cout << "Computer is thinking...\n";
			b.computerPlay();
		}

		b.print();

		if (b.checkWin() == 1)
		{
			cout << "Computer wins!\n";
			break;
		}
		if (b.checkWin() == -1)
		{
			cout << "You win!\n";
			break;
		}
	}
	if (b.checkWin() == 0 && b.getEmptySpaces().empty())
	{
		cout << "Tie!\n";
	}

	system("PAUSE");
	return 0;
}
/*
GameDriver.cpp
Copyright Daniel Norman 2014
*/
#include "Board.h"
#include <iostream>

int main()
{
	Board b(Board::Player);
	b.print();


	while (!b.getEmptySpaces().empty())
	{
		if (b.getEmptySpaces().size() == 1) //Play the last spot automatically
		{
			b.play(b.getEmptySpaces()[0]);
			break;
		}
		else if (b.getTurn() == Board::Player)
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

	if (b.getEmptySpaces().empty() && b.checkWin() == 0) cout << "Tie!\n";
	cout << "Try again? (y/n): ";
	char again = 'n';
	cin >> again;
	if (again == 'y' || again == 'Y') return main();

	system("PAUSE");
	return 0;
}
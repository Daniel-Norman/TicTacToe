/*
Board.cpp
Copyright Daniel Norman 2014
*/
#include "Board.h"
#include <algorithm>
#include <iostream>
#include <climits>

Board::Board(PlayerType p) : currentPlayer(p)
{
	for (int i = 0; i < BOARD_SIZE; ++i)
	{
		spaces[i] = Empty;
		emptySpaces.push_back(i);
	}
	currentPlayer = Player;
}

Board::Board(Board* source) : currentPlayer(source->getTurn())
{
	for (int i = 0; i < BOARD_SIZE; ++i)
	{
		spaces[i] = source->spaces[i];
	}
	emptySpaces = source->emptySpaces;
}

void Board::play(size_t space)
{
	if (find(emptySpaces.begin(), emptySpaces.end(), space) == emptySpaces.end())
	{
		cout << "Invalid move.\n";
		return;
	}

	SpaceType move = currentPlayer == Player ? X : O;
	spaces[space] = move;
	emptySpaces.erase(std::remove(emptySpaces.begin(), emptySpaces.end(), space), emptySpaces.end());
	currentPlayer = currentPlayer == Player ? Computer : Player;
}

void Board::print()
{
	cout << "-------------\n";
	cout << "| " << display(spaces[0]) << " | " << display(spaces[1]) << " | " << display(spaces[2]) << " |\n";
	cout << "-------------\n";
	cout << "| " << display(spaces[3]) << " | " << display(spaces[4]) << " | " << display(spaces[5]) << " |\n";
	cout << "-------------\n";
	cout << "| " << display(spaces[6]) << " | " << display(spaces[7]) << " | " << display(spaces[8]) << " |\n";
	cout << "-------------\n";
}

char* Board::display(int space)
{
	switch (space)
	{
	case X:
		return "X";
	case O:
		return "O";
	default:
		return " ";
	}
	return " ";
}

void Board::computerPlay()
{
	//Check for center spot
	if (spaces[4] == Empty)
	{
		play(4);
		return;
	}

	int choices[BOARD_SIZE][2];
	for (int i = 0; i < BOARD_SIZE; ++i)
	{
		choices[i][0] = -1;
		choices[i][1] = INT_MIN;
	}
	for (int i = 0; i < emptySpaces.size(); ++i)
	{
		Board board(this);
		board.play(emptySpaces[i]);
		choices[i][0] = emptySpaces[i];
		choices[i][1] = board.reward();
	}
	int max = INT_MIN;
	int choice = -1;

	for (int i = 0; i < BOARD_SIZE; ++i)
	{
		if (choices[i][1] > max)
		{
			max = choices[i][1];
			choice = choices[i][0];
		}
	}

	play(choice);
}

int Board::reward(int depth)
{
	int winResult = checkWin();
	if (winResult != 0)
	{
		return (1 << (8 - depth)) * winResult;
	}

	int sum = 0;

	for (int i = 0; i < emptySpaces.size(); ++i)
	{
		Board board(this);
		board.play(emptySpaces[i]);
		sum += board.reward(depth + 1);
	}

	return sum / (depth + 1);
}

//Return 1 if Computer wins, -1 if Player, 0 if neither
int Board::checkWin()
{
	if (spaces[0] != Empty && spaces[0] == spaces[1] && spaces[1] == spaces[2]) return spaces[0] == O ? 1 : -1; //top row
	if (spaces[3] != Empty && spaces[3] == spaces[4] && spaces[4] == spaces[5]) return spaces[3] == O ? 1 : -1; //middle row
	if (spaces[6] != Empty && spaces[6] == spaces[7] && spaces[7] == spaces[8]) return spaces[6] == O ? 1 : -1; //bottom row
	if (spaces[0] != Empty && spaces[0] == spaces[3] && spaces[3] == spaces[6]) return spaces[0] == O ? 1 : -1; //left column
	if (spaces[1] != Empty && spaces[1] == spaces[4] && spaces[4] == spaces[7]) return spaces[1] == O ? 1 : -1; //middle column
	if (spaces[2] != Empty && spaces[2] == spaces[5] && spaces[5] == spaces[8]) return spaces[2] == O ? 1 : -1; //right column
	if (spaces[0] != Empty && spaces[0] == spaces[4] && spaces[4] == spaces[8]) return spaces[0] == O ? 1 : -1; //diagonal L to R
	if (spaces[2] != Empty && spaces[2] == spaces[4] && spaces[4] == spaces[6]) return spaces[2] == O ? 1 : -1; //diagonal R to L
	return 0;
}
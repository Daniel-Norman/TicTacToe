/*
Board.h
Copyright Daniel Norman 2014
*/
#pragma once
#include <vector>
#define BOARD_SIZE 9
using namespace std;

class Board
{
public:
	enum SpaceType {X, O, Empty};
	enum PlayerType {Player, Computer};

	Board(PlayerType);
	Board(Board&);
	void play(size_t);
	void computerPlay();
	int checkWin();

	void print();

	int* getSpaces() { return spaces; }
	vector<int> getEmptySpaces() { return emptySpaces; }
	PlayerType getTurn() { return currentPlayer; }


private:
	int spaces[BOARD_SIZE];
	PlayerType currentPlayer;
	vector<int> emptySpaces;
	char* display(int);

	int reward(int);
};
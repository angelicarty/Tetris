#include "Board.h"
#include <stdlib.h>
#include <iostream>

#define WIDTH 13
#define HEIGHT 22

int mainBoard[HEIGHT][WIDTH];
int currentBlockPosX;
int currentBlockPosY;

bool redrawing;

void Board::clearScreen()
{
	system("cls");
}

void Board::initBoard()
{
	for (size_t i = 0; i <= HEIGHT - 2; i++) {
		for (size_t j = 0; j <= WIDTH - 2; j++) {
			//0 is down-side of border.
			if ((j == 0) || (j == WIDTH - 2) || (i == HEIGHT - 2)) {
				mainBoard[i][j] = POS_BORDER;
			}
			else {
				mainBoard[i][j] = POS_FREE;
			}
		}
	}
}

void Board::redrawBoard()
{
	if(!redrawing)
	{
		clearScreen();
		redrawing = true;
		for (size_t i = 0; i < HEIGHT - 1; i++) {
			for (size_t j = 0; j < WIDTH - 1; j++) {
				switch (mainBoard[i][j]) {
				case POS_FREE: //Empty
					std::cout << " " << std::flush;
					break;
				case POS_FILLED: //Block
					std::cout << "#" << std::flush;
					break;
				case POS_BORDER: //Border
					std::cout << "0" << std::flush;
					break;
				}
			}
			std::cout << std::endl;
		}
		redrawing = false;
	}
}

void Board::newBlock()
{
	//sets current block pos
	//generate new block

	//test
	currentBlockPosX = 5;
	currentBlockPosY = 0;
	mainBoard[currentBlockPosY][currentBlockPosX] = POS_FILLED;
}

void Board::dropBlock()
{
	for (int i = 1; i < HEIGHT - 2; i++)
	{
		if (mainBoard[currentBlockPosY + i][currentBlockPosX] != POS_FREE)
		{
			mainBoard[currentBlockPosY][currentBlockPosX] = POS_FREE;
			currentBlockPosY += i-1;
			mainBoard[currentBlockPosY][currentBlockPosX] = POS_FILLED;
		}
	}
	destroyRowCheck();
}

void Board::blockFall()
{
	switch (mainBoard[currentBlockPosY + 1][currentBlockPosX])
	{
	case POS_FREE:
		mainBoard[currentBlockPosY][currentBlockPosX] = POS_FREE;
		currentBlockPosY++;
		mainBoard[currentBlockPosY][currentBlockPosX] = POS_FILLED;
		break;
	case POS_BORDER:
		destroyRowCheck();
		break;
	case POS_FILLED:
		destroyRowCheck();
		break;
	}
	
}

void Board::moveBlock(int x, int y)
{
	//move block based on x and y

	if(mainBoard[currentBlockPosY + y][currentBlockPosX + x] == POS_FREE)
	{
		mainBoard[currentBlockPosY][currentBlockPosX] = POS_FREE;
		currentBlockPosX += x;
		currentBlockPosY += y;
		mainBoard[currentBlockPosY][currentBlockPosX] = POS_FILLED;
	}

}

void Board::rotateBlock()
{
	//rotate block
}

void Board::destroyRow(int y)
{

	std::cout << y << "destroy row \n";
	for (int k = 0; k <= WIDTH - 1; k++)
	{
		if (mainBoard[y][k] == POS_FILLED)
		{
			mainBoard[y][k] = POS_FREE;
		}
	}

	dropFrom(y);
	newBlock();
}

void Board::dropFrom(int y)
{
	for (int i = y; i >= 1; i--)
	{
		for (int j = 0; j < WIDTH-1; j++)
		{
			if (mainBoard[i][j] == POS_FILLED)
			{
				mainBoard[i][j] = POS_FREE;
				mainBoard[i - 1][j] = POS_FILLED;
			}
		}
	}
}

void Board::destroyRowCheck()
{

	std::cout << "destroy row check \n";
	for (int i = HEIGHT - 1 ; i >= 0; i--)
	{
		for (int j = 0; j <= WIDTH-1; j++)
		{
			if (mainBoard[i][j] == POS_FREE)//there's a free pos in the row, skip to next row
			{
				std::cout << j << "j \n";
				break;
			}
			if (j == WIDTH-1)//end of the line without seeing a empty
			{
				destroyRow(j);
			}
		}
	}
	newBlock();
}



bool Board::is_game_over()
{
	return false;
}


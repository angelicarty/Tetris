#include <iostream>
#include <time.h>
#include <conio.h>
#include <thread>
#include <future>
#include <chrono>
#include <assert.h>
#include <stdlib.h>


#include "Board.h"


bool keeprunning;
int count;
Board board1;

time_t start;//, end;


void choose(std::future<void> futureObj)
{

	while (futureObj.wait_for(std::chrono::milliseconds(1)) == std::future_status::timeout)
	{

		char press;
		press = _getch();

		switch (press) {
		case 'd': //right
			std::cout << "pressed d\n";
			board1.moveBlock(1, 0);
			break;
		case 'a': //left
			std::cout << "pressed a\n";
			board1.moveBlock(-1, 0);
			break;
		case 's': //down
			std::cout << "pressed s\n";
			board1.moveBlock(0, 1);
			break;
		case 'w': //rotate
			std::cout << "pressed w\n";
			break;
		case' ':
			std::cout << "pressed space\n";
			board1.dropBlock();
			break;
		case'o':
			keeprunning = false;
			std::cout << "===============\n"
				"   Game Over   \n"
				"===============\n";
			break;
		}
		board1.redrawBoard();
	}

}



int main()
{
	keeprunning = true;

	board1.initBoard();
	board1.redrawBoard();
	board1.newBlock();


	std::promise<void> exitSignal;
	std::future<void> futureObj = exitSignal.get_future();
	std::thread th(&choose, std::move(futureObj));

	count = 2;
	start = time(0);

	while (keeprunning)
	{
		if (time(0) - start >= count)
		{
			board1.blockFall();
			board1.redrawBoard();
			start = start + count;
		}
	}
	
}



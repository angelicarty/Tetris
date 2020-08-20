

class Board
{

public:

	void clearScreen();
	void initBoard();
	void redrawBoard();
	void newBlock();
	void dropBlock();
	void blockFall();
	void moveBlock(int x, int y);
	void rotateBlock();
	void destroyRow(int y);
	void dropFrom(int y);
	void destroyRowCheck();

	bool is_game_over();

	enum {
		POS_FREE, POS_FILLED, POS_BORDER
	};

private:
	bool isGameOver;
};
#pragma once

struct createShip {
	char type[3] = {'X','X','X'};
	int size=3;
	char *pieces = new char[size];
	int pointX=-1;
	int pointY=-1;
	char direction='?';
	int typeId = -1;
	int fragmentsAlive = 0;
};

class createPlayer {
public:
	createShip ships[40];
	void addShip();
	void displayShips();
	void isShipAlive(int number);
	//void shoot(gameSetter& game);
	int fleet[4] = { 4,3,2,1 };
	int shipsAlive = 0;
	int shipsOwned = 0;
	int minRow = 0, maxRow = 9;
};
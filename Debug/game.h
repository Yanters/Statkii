#pragma once
#include "player.h"

struct createReefs {
	int x = 0;
	int y = 0;
};

class gameSetter {
public:
	void displayMap();
	void displayPlayersInfo();
	void setFleet();
	void nextPlayer();
	void isThereAWinner();
	void shoot(int idGracza);
	void setBoardSize();
	void initPosition();
	void createReef();
	void setUpReefs();
	void setUpPlayersGameSize();
	void addShip();
	int gameSizeX = 10;
	int gameSizeY = 21;
	int move = 0;
	int reefsCount = 0;

	createReefs *reefs = new createReefs[210];
	createPlayer players[2];
};


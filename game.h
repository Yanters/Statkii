#pragma once
#include "structs.h"
#include "player.h"



class gameSetter {
public:
	void displayMap();
	void displayPlayersInfo();
	void setFleet();
	void nextPlayer(char playerLetter='X');
	void isThereAWinner();
	void shoot(int idGracza);
	void setBoardSize();
	void initPosition();
	void createReef();
	void setUpReefs();
	void setUpPlayersGameSize();
	void addShip();
	char **returnBoard(int printType=0);

	int gameSizeX = 10;
	int gameSizeY = 21;
	int move = 0;
	int reefsCount = 0;
	int extendedShips = 0;

	cordinates *reefs = new cordinates[210];
	createPlayer players[2];
};


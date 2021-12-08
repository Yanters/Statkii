#pragma once
#include "structs.h"
#include "player.h"



class gameSetter {
public:
	void displayMap();
	void displayPlayersInfo();
	void setFleet();
	void nextPlayer(char playerLetter = 'X');
	void isThereAWinner();
	void shoot(int idGracza, int shipID = 0, int fTypeId = 0, char fType[] = NULL);
	void setBoardSize();
	void initPosition();
	void createReef();
	void setUpReefs();
	void setUpPlayersGameSize();
	void addShip();
	void shootExtended(int playersID);
	void saveGame();
	void setSrand();
	char **returnBoard(int printType = 0, int notIncluded = -1);

	int gameSizeX = 10;
	int gameSizeY = 21;
	int move = 0;
	int reefsCount = 0;
	int extendedShips = 0;

	char AIPlayerGame = 'X';
	int AIseed = 0;
	void AIAllLogic();
	void AIsetShips();
	void setAIPlayer();
	void AISmartShootMove(char **boardAll = NULL, int cannonY = -1, int cannonX = -1, int shipSize = 0, int AIShipID = 0);

	cordinates *reefs = new cordinates[210];
	createPlayer players[2];
};


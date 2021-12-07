#pragma once
#include "structs.h"

struct createShip {
	char type[3] = { 'X','X','X' };
	int size = 3;
	char *pieces = new char[size];
	int pointX = -1;
	int pointY = -1;
	char direction = '?';
	int typeId = -1;
	int fragmentsAlive = 0;
	int avalibleMoves = 3;
	int cannonX = -1;
	int cannonY = -1;
	int avalibleShoots = 0;
	int avaliblePlanes = 0;
	char cannonDestroyed = 'N';
	char radarDestroyed = 'N';
	char engineDestroyed = 'N';
};

class createPlayer {
public:
	//, struct createReefs reefs[] = NULL
	void addShip(char **board,int addType = 0, struct cordinates reefs[]=NULL,int reefsCount=0,char playerLetter='X');
	void displayShips();
	void isShipAlive(int number);
	void setUpShips();
	void moveShip(struct cordinates reefs[]=NULL, int reefsCount=0,char **board=NULL);
	void restartAvalibleMoves();
	void restartAvalibleShoots();
	void playerVisionMap( char **boardAll=NULL,int visionOption=0);
	void addSpyPlane();
	int fleet[4] = { 4,3,2,1 };
	int MainFleet[4] = { 4,3,2,1 };
	int shipsAlive = 0;
	int shipsOwned = 0;
	int minRow = 0, maxRow = 9;
	int minCol = 0, maxCol = 9;
	int gameSizeY = 21;
	int gameSizeX = 10;
	int spyPlanesCount = 0;

	int AIseed = 0;
	int AIPlayer = 0;
	int AIError = 0;
	int AIShipsOwned = 0;
	void restartShips(struct createShip shipsRestart[]);

	//AI
	char AIShipType[3] = { 'X','X','X' };


	cordinates *spyPlanes = new cordinates[5];
	createShip *ships = new createShip[10];
};
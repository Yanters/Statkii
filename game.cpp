#include <iostream>
#include <math.h>
#include "game.h"

using namespace std;

double calculateDistance(int cannonY, int cannonX, int shootY, int shootX) {
	return sqrt(pow(abs(cannonY - shootY), 2) + pow(abs(cannonX - shootX), 2));
}

void tooFar(int typeID, char type[], int pointY,int pointX) {
	cout << "INVALID OPERATION " << char(34) << "SHOOT " << typeID << " ";
	for (int i = 0; i < 3; i++) {
		cout << type[i];
	}
	cout << " " << pointY << " " << pointX;
	cout << char(34) << ": SHOOTING TOO FAR";
	exit(0);
}

void gameSetter::displayMap() {
	int option;
	cin >> option;
	char **board = returnBoard(option);
	//Displaying Board
	if (option == 1) {
		cout << "  ";
		for (int i = 0; i < gameSizeX; i++) {
			cout << i;
		}
		cout << endl;
	}
	for (int i = 0; i < gameSizeY; i++) {
		if (option == 1) {
			if (i < 10) {
				cout << '0' << i;
			}
			else {
				cout << i;
			}
		}
		for (int j = 0; j < gameSizeX; j++) {
			cout << board[i][j];
		}
		cout << endl;
	}

	int partsRemainingA = 0, partsRemainingB = 0;

	for (int i = 0; i < players[0].shipsOwned; i++) {
		partsRemainingA += players[0].ships[i].fragmentsAlive;
	}
	for (int i = 0; i < players[1].shipsOwned; i++) {
		partsRemainingB += players[1].ships[i].fragmentsAlive;
	}
	cout << "PARTS REMAINING:: A : " << partsRemainingA << " B : " << partsRemainingB << endl;
	//Deleting Board
	for (int i = 0; i < gameSizeY; ++i) {
		delete[] board[i];
	}
	delete[] board;
}


void gameSetter::displayPlayersInfo() {
	for (int i = 0; i < 2; i++) {
		players[i].displayShips();
	}
}

void gameSetter::setFleet() {
	char playerLetter;
	cin >> playerLetter;
	int a1, a2, a3, a4;
	cin >> a1 >> a2 >> a3 >> a4;
	int idGracza = int(playerLetter) - 65;
	players[idGracza].fleet[0] = a4;
	players[idGracza].fleet[1] = a3;
	players[idGracza].fleet[2] = a2;
	players[idGracza].fleet[3] = a1;
	players[idGracza].setUpShips();
}

void gameSetter::nextPlayer(char playerLetter) {
	if (playerLetter == 'X') {
		if (move == 0) move++;
		else if (move == 1) move = 0;
	}
	else
	{
		move = int(playerLetter) - 65;
	}
}

void gameSetter::isThereAWinner() {
	if (players[0].shipsAlive == 0) {
		cout << "B won" << endl;
		exit(0);
	}
	else if (players[1].shipsAlive == 0) {
		cout << "A won" << endl;
		exit(0);
	}
}


void gameSetter::shoot(int playersIDs,int shipID,int fTypeId,char fType[]) {
	int pointX, pointY;
	cin >> pointY >> pointX;
	//cout << "Ship Size: " << players[playersIDs - 1].ships[shipID].size << " Distance: " << calculateDistance(players[playersIDs - 1].ships[shipID].cannonY, players[playersIDs - 1].ships[shipID].cannonX, pointY, pointX) << endl;

	if (pointX > gameSizeX || pointY > gameSizeY) {
		cout << "INVALID OPERATION " << char(34) << "SHOOT " << pointY << " " << pointX << char(34) << ": FIELD DOES NOT EXIST";
		exit(0);
	}

	if (playersIDs - 1 != move) {
		if (playersIDs - 1 == 1) {
			cout << "INVALID OPERATION " << char(34) << "[playerB] " << char(34) << ": THE OTHER PLAYER EXPECTED";
		}
		else {
			cout << "INVALID OPERATION " << char(34) << "[playerA] " << char(34) << ": THE OTHER PLAYER EXPECTED";

		}
		exit(0);

	}

	int canShoot = 0;

	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 4; j++) {
			canShoot += players[i].fleet[j];
		}
	}

	if (canShoot != 0) {
		cout << "INVALID OPERATION " << char(34) << "SHOOT " << pointY << " " << pointX << char(34) << ": NOT ALL SHIPS PLACED";
		exit(0);
	}

	if (extendedShips == 1 && players[playersIDs - 1].ships[shipID].cannonDestroyed == 'Y') {
		cout << "INVALID OPERATION " << char(34) << "SHOOT " << fTypeId << " ";
		for (int i = 0; i < 3; i++) {
			cout << fType[i];
		}
		cout << " " << pointY << " " << pointX;
		cout << char(34) << ": SHIP CANNOT SHOOT";
		exit(0);
	}
/**/
	//cout << endl << players[playersIDs - 1].ships[shipID].avalibleShoots << endl;
	if (players[playersIDs - 1].ships[shipID].avalibleShoots == 0) {
		cout << "INVALID OPERATION " << char(34) << "SHOOT " << fTypeId << " ";
		for (int i = 0; i < 3; i++) {
			cout << fType[i];
		}
		cout << " " << pointY << " " << pointX;
		cout << char(34) << ": TOO MANY SHOOTS";
		exit(0);
	}
	if (extendedShips == 1 && players[playersIDs - 1].ships[shipID].size < calculateDistance(players[playersIDs - 1].ships[shipID].cannonY, players[playersIDs - 1].ships[shipID].cannonX, pointY,pointX)) {
		//int typeID, char type[], int pointY,int pointX
		tooFar(fTypeId, fType, pointY, pointX);
	}

	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < players[i].shipsOwned; j++) {
			for (int k = 0; k < players[i].ships[j].size; k++) {
				if (players[i].ships[j].direction == 'N') {
					if (pointY == (players[i].ships[j].pointY + k) && pointX == (players[i].ships[j].pointX) && players[i].ships[j].pieces[k] != 'x') {
						if (players[i].ships[j].pieces[k] == '!') { players[i].ships[j].cannonDestroyed = 'Y'; }
						players[i].ships[j].pieces[k] = 'x';
						players[i].ships[j].fragmentsAlive--;
						players[i].isShipAlive(j);
					}
				}
				if (players[i].ships[j].direction == 'S') {
					if (pointY == (players[i].ships[j].pointY - k) && pointX == (players[i].ships[j].pointX) && players[i].ships[j].pieces[k] != 'x') {
						if (players[i].ships[j].pieces[k] == '!') { players[i].ships[j].cannonDestroyed = 'Y'; }
						players[i].ships[j].pieces[k] = 'x';
						players[i].ships[j].fragmentsAlive--;
						players[i].isShipAlive(j);

					}
				}
				if (players[i].ships[j].direction == 'W') {
					if (pointY == (players[i].ships[j].pointY) && pointX == ((players[i].ships[j].pointX) + k) && players[i].ships[j].pieces[k] != 'x') {
						if (players[i].ships[j].pieces[k] == '!') { players[i].ships[j].cannonDestroyed = 'Y'; }
						players[i].ships[j].pieces[k] = 'x';
						players[i].ships[j].fragmentsAlive--;
						players[i].isShipAlive(j);

					}
				}
				if (players[i].ships[j].direction == 'E') {
					if (pointY == (players[i].ships[j].pointY) && pointX == ((players[i].ships[j].pointX) - k) && players[i].ships[j].pieces[k] != 'x') {
						if (players[i].ships[j].pieces[k] == '!') { players[i].ships[j].cannonDestroyed = 'Y'; }
						players[i].ships[j].pieces[k] = 'x';
						players[i].ships[j].fragmentsAlive--;
						players[i].isShipAlive(j);

					}
				}
			}
		}
	}
	if (extendedShips == 0) {
		nextPlayer();
	}
	else {
		players[playersIDs - 1].ships[shipID].avalibleShoots--;
	}
}

void gameSetter::setUpReefs() {
	delete[] reefs;
	reefs = new cordinates[gameSizeX*gameSizeY];
}


void gameSetter::setBoardSize() {
	int boardY = 0, boardX = 0;
	cin >> boardY >> boardX;
	gameSizeX = boardX;
	gameSizeY = boardY;
	setUpReefs();
	setUpPlayersGameSize();
}

void gameSetter::initPosition() {
	char playerChar;
	int y1, y2, x1, x2;
	cin >> playerChar >> y1 >> x1 >> y2 >> x2;
	players[int(playerChar) - 65].minCol = x1;
	players[int(playerChar) - 65].maxCol = x2;
	players[int(playerChar) - 65].minRow = y1;
	players[int(playerChar) - 65].maxRow = y2;

}

void gameSetter::createReef() {
	int rX, rY;
	cin >> rY >> rX;
	if (rY > gameSizeY || rY<0 || rX>gameSizeX || rX < 0) {
		cout << "INVALID OPERATION " << char(34) << "REEF " << rY << " " << rX << char(34) << ": REEF IS NOT PLACED ON BOARD";
		exit(0);
	}
	reefs[reefsCount].x = rX;
	reefs[reefsCount].y = rY;
	reefsCount++;
}

void gameSetter::addShip() {
	char playerLetter;
	cin >> playerLetter;
	//reefs, 
	players[int(playerLetter) - 65].addShip(returnBoard(), 1, reefs, reefsCount, playerLetter);
}

void gameSetter::setUpPlayersGameSize() {
	for (int i = 0; i < 2; i++) {
		players[i].gameSizeY = gameSizeY;
		players[i].gameSizeX = gameSizeX;
	}
}

char **gameSetter::returnBoard(int printType) {
	//Creating Board

	char **board = new char*[gameSizeY];
	for (int i = 0; i < gameSizeY; ++i) {
		board[i] = new char[gameSizeX];
	}
	//Clearing board
	for (int i = 0; i < gameSizeY; i++) {
		for (int j = 0; j < gameSizeX; j++) {
			board[i][j] = ' ';
		}
	}
	//Setting values to the board
	for (int k = 0; k < 2; k++) {
		for (int p = 0; p < players[k].shipsOwned; p++) {
			if (players[k].ships[p].type[0] != 'X') {
				for (int l = 0; l < players[k].ships[p].size; l++) {
					if (players[k].ships[p].direction == 'N') {
						board[players[k].ships[p].pointY + l][players[k].ships[p].pointX] = (printType == 1 ? players[k].ships[p].pieces[l] : (players[k].ships[p].pieces[l] != '+'&& players[k].ships[p].pieces[l] != 'x' ? '+' : players[k].ships[p].pieces[l]));
					}
					if (players[k].ships[p].direction == 'S') {
						board[players[k].ships[p].pointY - l][players[k].ships[p].pointX] = (printType == 1 ? players[k].ships[p].pieces[l] : (players[k].ships[p].pieces[l] != '+' && players[k].ships[p].pieces[l] != 'x' ? '+' : players[k].ships[p].pieces[l]));
					}
					if (players[k].ships[p].direction == 'W') {
						board[players[k].ships[p].pointY][players[k].ships[p].pointX + l] = (printType == 1 ? players[k].ships[p].pieces[l] : (players[k].ships[p].pieces[l] != '+' && players[k].ships[p].pieces[l] != 'x' ? '+' : players[k].ships[p].pieces[l]));
					}
					if (players[k].ships[p].direction == 'E') {
						board[players[k].ships[p].pointY][players[k].ships[p].pointX - l] = (printType == 1 ? players[k].ships[p].pieces[l] : (players[k].ships[p].pieces[l] != '+' && players[k].ships[p].pieces[l] != 'x' ? '+' : players[k].ships[p].pieces[l]));
					}
				}
			}
		}
	}
	//reefs

	for (int i = 0; i < reefsCount; i++) {
		board[reefs[i].y][reefs[i].x] = '#';
	}
	return board;
}

void gameSetter::shootExtended(int playerIDs) {
	char type[4] = { 'X','X','X' };
	int typeID = -1;
	cin >> typeID >> type;



	int shipID = -1;
	int sameType = 0;
	for (int i = 0; i < players[playerIDs-1].shipsOwned; i++) {
		if (players[playerIDs-1].ships[i].typeId != typeID) continue;
		sameType = 0;
		for (int j = 0; j < 3; j++) {
			if (players[playerIDs-1].ships[i].type[j] == type[j]) sameType++;
		}

		if (sameType == 3) {
			shipID = i;
			break;
		}
	}

	shoot(playerIDs,shipID,typeID,type);

}

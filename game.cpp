#include <iostream>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include<time.h>
#include "game.h"

using namespace std;

double calculateDistance(int cannonY, int cannonX, int shootY, int shootX) {
	return sqrt(pow(abs(cannonY - shootY), 2) + pow(abs(cannonX - shootX), 2));
}
void tooFar(int typeID, char type[], int pointY, int pointX) {
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
	int idGracza = int(playerLetter) - 65;
	int fleetSize = 0;
	for (int i = 3; i >= 0; i--) {
		cin >> fleetSize;
		players[idGracza].fleet[i] = fleetSize;
		players[idGracza].MainFleet[i] = fleetSize;

	}
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


void gameSetter::shoot(int playersIDs, int shipID, int fTypeId, char fType[]) {
	int pointX, pointY;
	cin >> pointY >> pointX;

	if (pointX > gameSizeX || pointY > gameSizeY || pointY < 0 || pointX < 0) {
		cout << "INVALID OPERATION " << char(34) << "SHOOT ";
		if (extendedShips == 1) {
			cout << fTypeId << " ";
			for (int i = 0; i < 3; i++) {
				cout << fType[i];
			}
			cout << " ";
		}
		cout << pointY << " " << pointX;
		cout << char(34) << ": FIELD DOES NOT EXIST";
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
		cout << "INVALID OPERATION " << char(34) << "SHOOT ";
		if (extendedShips == 1) {
			cout << fTypeId << " ";
			for (int i = 0; i < 3; i++) {
				cout << fType[i];
			}
			cout << " ";
		}
		cout << pointY << " " << pointX;
		cout << char(34) << ": NOT ALL SHIPS PLACED";
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
	if (players[playersIDs - 1].ships[shipID].avalibleShoots == 0) {
		cout << "INVALID OPERATION " << char(34) << "SHOOT " << fTypeId << " ";
		for (int i = 0; i < 3; i++) {
			cout << fType[i];
		}
		cout << " " << pointY << " " << pointX;
		cout << char(34) << ": TOO MANY SHOOTS";
		exit(0);
	}
	int carType = 0;
	if (extendedShips == 1 && players[playersIDs - 1].ships[shipID].size < calculateDistance(players[playersIDs - 1].ships[shipID].cannonY, players[playersIDs - 1].ships[shipID].cannonX, pointY, pointX)) {
		carType = 0;
		if (fType[0] == 'C')carType++;
		if (fType[1] == 'A')carType++;
		if (fType[2] == 'R')carType++;

		if (carType != 3) tooFar(fTypeId, fType, pointY, pointX);
	}

	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < players[i].shipsOwned; j++) {
			for (int k = 0; k < players[i].ships[j].size; k++) {
				if (players[i].ships[j].direction == 'N') {
					if (pointY == (players[i].ships[j].pointY + k) && pointX == (players[i].ships[j].pointX) && players[i].ships[j].pieces[k] != 'x') {
						if (players[i].ships[j].pieces[k] == '!') { players[i].ships[j].cannonDestroyed = 'Y'; }
						if (players[i].ships[j].pieces[k] == '%') { players[i].ships[j].engineDestroyed = 'Y'; }
						if (players[i].ships[j].pieces[k] == '@') { players[i].ships[j].radarDestroyed = 'Y'; }
						players[i].ships[j].pieces[k] = 'x';
						players[i].ships[j].fragmentsAlive--;
						players[i].isShipAlive(j);
					}
				}
				if (players[i].ships[j].direction == 'S') {
					if (pointY == (players[i].ships[j].pointY - k) && pointX == (players[i].ships[j].pointX) && players[i].ships[j].pieces[k] != 'x') {
						if (players[i].ships[j].pieces[k] == '!') { players[i].ships[j].cannonDestroyed = 'Y'; }
						if (players[i].ships[j].pieces[k] == '%') { players[i].ships[j].engineDestroyed = 'Y'; }
						if (players[i].ships[j].pieces[k] == '@') { players[i].ships[j].radarDestroyed = 'Y'; }
						players[i].ships[j].pieces[k] = 'x';
						players[i].ships[j].fragmentsAlive--;
						players[i].isShipAlive(j);

					}
				}
				if (players[i].ships[j].direction == 'W') {
					if (pointY == (players[i].ships[j].pointY) && pointX == ((players[i].ships[j].pointX) + k) && players[i].ships[j].pieces[k] != 'x') {
						if (players[i].ships[j].pieces[k] == '!') { players[i].ships[j].cannonDestroyed = 'Y'; }
						if (players[i].ships[j].pieces[k] == '%') { players[i].ships[j].engineDestroyed = 'Y'; }
						if (players[i].ships[j].pieces[k] == '@') { players[i].ships[j].radarDestroyed = 'Y'; }
						players[i].ships[j].pieces[k] = 'x';
						players[i].ships[j].fragmentsAlive--;
						players[i].isShipAlive(j);

					}
				}
				if (players[i].ships[j].direction == 'E') {
					if (pointY == (players[i].ships[j].pointY) && pointX == ((players[i].ships[j].pointX) - k) && players[i].ships[j].pieces[k] != 'x') {
						if (players[i].ships[j].pieces[k] == '!') { players[i].ships[j].cannonDestroyed = 'Y'; }
						if (players[i].ships[j].pieces[k] == '%') { players[i].ships[j].engineDestroyed = 'Y'; }
						if (players[i].ships[j].pieces[k] == '@') { players[i].ships[j].radarDestroyed = 'Y'; }
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

void gameSetter::setAIPlayer() {
	char playerLetter[2];
	cin >> playerLetter;
	AIPlayerGame = playerLetter[0];
	players[int(playerLetter[0]) - 65].AIseed = AIseed;
	players[int(playerLetter[0]) - 65].AIPlayer = 1;
}

void gameSetter::setSrand() {
	int seed;
	cin >> seed;
	srand(seed);
	AIseed = seed;
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
	players[int(playerLetter) - 65].addShip(returnBoard(), 1, reefs, reefsCount, playerLetter);
}

void gameSetter::setUpPlayersGameSize() {
	for (int i = 0; i < 2; i++) {
		players[i].gameSizeY = gameSizeY;
		players[i].gameSizeX = gameSizeX;
	}
}

char **gameSetter::returnBoard(int printType, int notIncluded) {
	char **board = new char*[gameSizeY];
	for (int i = 0; i < gameSizeY; ++i) {
		board[i] = new char[gameSizeX];
	}
	for (int i = 0; i < gameSizeY; i++) {
		for (int j = 0; j < gameSizeX; j++) {
			board[i][j] = ' ';
		}
	}
	for (int k = 0; k < 2; k++) {
		if (k == notIncluded) continue;
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
	for (int i = 0; i < players[playerIDs - 1].shipsOwned; i++) {
		if (players[playerIDs - 1].ships[i].typeId != typeID) continue;
		sameType = 0;
		for (int j = 0; j < 3; j++) {
			if (players[playerIDs - 1].ships[i].type[j] == type[j]) sameType++;
		}
		if (sameType == 3) {
			shipID = i;
			break;
		}
	}

	shoot(playerIDs, shipID, typeID, type);
}

void gameSetter::saveGame() {
	cout << "[state]" << endl;
	cout << "BOARD_SIZE " << gameSizeY << " " << gameSizeX << endl;
	cout << "NEXT_PLAYER " << char(move + 65) << endl;

	for (int i = 0; i < 2; i++) {
		cout << "INIT_POSITION " << char(i + 65) << " " << players[i].minRow << " " << players[i].minCol << " " << players[i].maxRow << " " << players[i].maxCol << endl;
		cout << "SET_FLEET " << char(i + 65) << " ";
		for (int j = 3; j >= 0; j--) {
			cout << players[i].MainFleet[j];
			if (j != 0) {
				cout << " ";
			}
		}
		cout << endl;
		for (int j = 3; j >= 0; j--) {
			for (int k = 0; k < players[i].MainFleet[j]; k++) {
				for (int o = 0; o < players[i].shipsOwned; o++) {
					if ((players[i].ships[o].size == (j + 2)) && players[i].ships[o].typeId == k) {
						cout << "SHIP " << char(i + 65) << " " << players[i].ships[o].pointY << " " << players[i].ships[o].pointX << " " << players[i].ships[o].direction << " " << k << " ";
						for (int q = 0; q < 3; q++) {
							cout << players[i].ships[o].type[q];
						}
						cout << " ";
						for (int b = 0; b < players[i].ships[o].size; b++) {
							if (players[i].ships[o].pieces[b] != 'x') {
								cout << '1';
							}
							else {
								cout << '0';
							}
						}
						break;
					}
				}
				cout << endl;
			}
		}
	}

	if (reefsCount != 0) {
		for (int i = 0; i < reefsCount; i++)
		{
			cout << "REEF " << reefs[i].y << " " << reefs[i].x << endl;
		}
	}
	if (extendedShips == 1) {
		cout << "EXTENDED_SHIPS" << endl;
	}
	if (AIseed != 0) {
		cout << "SRAND " << AIseed++ << endl;
	}
	if (AIPlayerGame != 'X') {
		cout << "SET_AI_PLAYER " << AIPlayerGame << endl;
	}
	cout << "[state]" << endl;

}



void gameSetter::AIsetShips() {
	int saveFleets[4];
	int consFleet = 0;
	for (int i = 3; i >= 0; i--) {
		consFleet = players[int(AIPlayerGame) - 65].fleet[i];
		saveFleets[i] = consFleet;
		for (int j = 0; j < consFleet; j++) {
			players[int(AIPlayerGame) - 65].AIShipType = i;
			do {
				players[int(AIPlayerGame) - 65].AIError = 0;

				players[int(AIPlayerGame) - 65].addShip(returnBoard(), 3, reefs, reefsCount);

			} while (players[int(AIPlayerGame) - 65].AIError == 1);
		}

	}
	for (int s = (players[int(AIPlayerGame) - 65].shipsOwned - players[int(AIPlayerGame) - 65].AIShipsOwned); s < players[int(AIPlayerGame) - 65].shipsOwned; s++) {
		cout << "PLACE_SHIP " << players[int(AIPlayerGame) - 65].ships[s].pointY << " " << players[int(AIPlayerGame) - 65].ships[s].pointX << " " << players[int(AIPlayerGame) - 65].ships[s].direction << " " << players[int(AIPlayerGame) - 65].ships[s].typeId << " ";
		for (int e = 0; e < 3; e++) {
			cout << players[int(AIPlayerGame) - 65].ships[s].type[e];
		}
		cout << endl;
	}
	players[int(AIPlayerGame) - 65].restartShips(saveFleets);
	players[int(AIPlayerGame) - 65].AIGeneretedShips = 1;
}

void gameSetter::AISmartShootMove(char **boardAll, int cannonY, int cannonX, int shipSize, int AIShipID) {
	char **foggyBoard = new char*[gameSizeY];
	for (int i = 0; i < gameSizeY; ++i) {
		foggyBoard[i] = new char[gameSizeX];
	}
	for (int i = 0; i < gameSizeY; i++) {
		for (int j = 0; j < gameSizeX; j++) {
			foggyBoard[i][j] = '?';
		}
	}
	for (int i = 0; i < players[int(AIPlayerGame) - 65].shipsOwned; i++) {
		if (players[int(AIPlayerGame) - 65].ships[i].radarDestroyed = 'N') {
			for (int m = 0; m < gameSizeY; m++) {
				for (int n = 0; n < gameSizeX; n++) {
					if (players[int(AIPlayerGame) - 65].ships[i].size >= calculateDistance(players[int(AIPlayerGame) - 65].ships[i].pointY, players[int(AIPlayerGame) - 65].ships[i].pointX, m, n)) {
						foggyBoard[m][n] = 'V';
					}
				}
			}
		}
		else {
			for (int m = 0; m < gameSizeY; m++) {
				for (int n = 0; n < gameSizeX; n++) {
					if (1 >= calculateDistance(players[int(AIPlayerGame) - 65].ships[i].pointY, players[int(AIPlayerGame) - 65].ships[i].pointX, m, n)) {
						foggyBoard[m][n] = 'V';
					}
				}
			}
		}

	}
	for (int i = 0; i < players[int(AIPlayerGame) - 65].spyPlanesCount; i++) {
		for (int m = 0; m < gameSizeY; m++) {
			for (int n = 0; n < gameSizeX; n++) {
				if (2 > calculateDistance(players[int(AIPlayerGame) - 65].spyPlanes[i].y, players[int(AIPlayerGame) - 65].spyPlanes[i].x, m, n)) {
					foggyBoard[m][n] = 'V';
				}
			}
		}
	}

	for (int i = 0; i < gameSizeY; i++) {
		for (int j = 0; j < gameSizeX; j++) {
			if (foggyBoard[i][j] == 'V') {
				foggyBoard[i][j] = boardAll[i][j];
			}
		}
	}

	int shootY = -1, shootX = -1, noRepeat = 0, fullTries = 0;
	do {
		for (int i = 0; i < gameSizeY; i++) {
			if (shootY != -1)break;
			for (int j = 0; j < gameSizeX; j++) {
				if ((foggyBoard[i][j] == '!' && calculateDistance(cannonY, cannonX, i, j) <= shipSize) || (shipSize == 5 && foggyBoard[i][j] == '!'))
				{
					shootY = i;
					shootX = j;
					break;
				}
			}
		}
		if (shootY == -1) {
			for (int i = 0; i < gameSizeY; i++) {
				if (shootY != -1)break;
				for (int j = 0; j < gameSizeX; j++) {
					if ((foggyBoard[i][j] == '%' && calculateDistance(cannonY, cannonX, i, j) <= shipSize) || (shipSize == 5 && foggyBoard[i][j] == '%'))
					{

						shootY = i;
						shootX = j;
						break;
					}
				}
			}
		}
		if (shootY == -1) {
			for (int i = 0; i < gameSizeY; i++) {
				if (shootY != -1)break;
				for (int j = 0; j < gameSizeX; j++) {
					if ((foggyBoard[i][j] == '@' && calculateDistance(cannonY, cannonX, i, j) <= shipSize) || (shipSize == 5 && foggyBoard[i][j] == '@'))
					{

						shootY = i;
						shootX = j;
						break;
					}
				}
			}
		}
		if (shootY == -1) {
			for (int i = 0; i < gameSizeY; i++) {
				if (shootY != -1)break;
				for (int j = 0; j < gameSizeX; j++) {
					if ((foggyBoard[i][j] == '+' && calculateDistance(cannonY, cannonX, i, j) <= shipSize) || (shipSize == 5 && foggyBoard[i][j] == '+'))
					{
						shootY = i;
						shootX = j;
						break;
					}
				}
			}
		}
		if (shootY == -1) {
			shootY = rand() % players[int(AIPlayerGame) - 65].maxRow;
			shootX = rand() % players[int(AIPlayerGame) - 65].maxCol;
			int tries = 0, secondTries = 0;


			while (calculateDistance(cannonY, cannonX, shootY, shootX) > shipSize || foggyBoard[shootY][shootX] != '?'&&tries <= 2000) {
				shootY = rand() % gameSizeY;
				shootX = rand() % gameSizeX;
				tries++;
			}

			if (tries >= 2000 && players[int(AIPlayerGame) - 65].AIMovedShip == 0) {
				secondTries = 0;
				do {
					players[int(AIPlayerGame) - 65].AIError = 0;
					players[int(AIPlayerGame) - 65].moveShip(reefs, reefsCount, returnBoard(), AIShipID);
					secondTries++;
				} while (players[int(AIPlayerGame) - 65].AIError == 1 && secondTries <= 200);

				if (secondTries < 200) {
					players[int(AIPlayerGame) - 65].AISkipShipShoot = 1;
					players[int(AIPlayerGame) - 65].AIMovedShip = 1;
				}


			}
		}
		noRepeat = 0;

		for (int u = 0; u < players[int(AIPlayerGame) - 65].AIShootsCounter; u++) {
			if (players[int(AIPlayerGame) - 65].AIShoots[u].y == shootY && players[int(AIPlayerGame) - 65].AIShoots[u].x == shootX)
			{
				noRepeat = 1;
			}
		}

		fullTries++;
	} while (noRepeat == 1 && fullTries <= 40000 && players[int(AIPlayerGame) - 65].AIMovedShip == 0);

	if (players[int(AIPlayerGame) - 65].AISkipShipShoot != 1 && noRepeat == 0) {
		cout << "SHOOT " << players[int(AIPlayerGame) - 65].ships[AIShipID].typeId << " ";
		for (int t = 0; t < 3; t++) {
			cout << players[int(AIPlayerGame) - 65].ships[AIShipID].type[t];
		}
		cout << " " << shootY << " " << shootX << endl;
		players[int(AIPlayerGame) - 65].AIShoots[players[int(AIPlayerGame) - 65].AIShootsCounter].y = shootY;
		players[int(AIPlayerGame) - 65].AIShoots[players[int(AIPlayerGame) - 65].AIShootsCounter].x = shootX;
		players[int(AIPlayerGame) - 65].AIShootsCounter++;

	}


	for (int i = 0; i < gameSizeY; ++i) {
		delete[] boardAll[i];
		delete[] foggyBoard[i];
	}
	delete[] boardAll;
	delete[] foggyBoard;

}

void gameSetter::AIAllLogic() {
	int shipsToPlace = 0;
	cout << "======================AI======================" << endl;
	for (int i = 0; i < 4; i++) {
		shipsToPlace += players[int(AIPlayerGame) - 65].fleet[i];
	}
	if (players[int(AIPlayerGame) - 65].AIWait == 0)
	{
		cout << "[state]" << endl << "PRINT 0" << endl << "[state]" << endl << "[player" << AIPlayerGame << "]" << endl;
	}
	if (shipsToPlace != 0 && players[int(AIPlayerGame) - 65].AIGeneretedShips == 0) {
		AIsetShips();
		cout << "[player" << AIPlayerGame << "]" << endl << "[state]" << endl << "PRINT 0" << endl << "[state]" << endl;

	}
	else if (players[int(AIPlayerGame) - 65].AIWait == 0)
	{
		for (int i = 0; i < players[int(AIPlayerGame) - 65].shipsOwned; i++) {
			if (players[int(AIPlayerGame) - 65].ships[i].cannonDestroyed != 'Y') {
				for (int j = 0; j < players[int(AIPlayerGame) - 65].ships[i].size; j++) {
					if (players[int(AIPlayerGame) - 65].AISkipShipShoot == 1) { break; }

					AISmartShootMove(returnBoard(1, (int(AIPlayerGame) - 65)), players[int(AIPlayerGame) - 65].ships[i].cannonY, players[int(AIPlayerGame) - 65].ships[i].cannonX, players[int(AIPlayerGame) - 65].ships[i].size, i);
				}
			}
			players[int(AIPlayerGame) - 65].AISkipShipShoot = 0;
		}
		cout << "[player" << AIPlayerGame << "]" << endl << "[state]" << endl << "PRINT 0" << endl << "[state]" << endl;
	}


	players[int(AIPlayerGame) - 65].AIWait = 1;
	players[int(AIPlayerGame) - 65].AIError = 0;
	players[int(AIPlayerGame) - 65].AIMovedShip = 0;




}
#include <iostream>
#include "player.h"
#include "game.h"

using namespace std;

void toClose(int addType, int pointY, int pointX, char direction, int typeID, char type[], int size = 0, char stateFragments[] = NULL, char playerLetter = 'X') {
	cout << "INVALID OPERATION " << char(34);
	if (addType == 0) {
		cout << "PLACE_SHIP ";
	}
	else if (addType == 1) {
		cout << "SHIP " << playerLetter << " ";
	}
	else if (addType == 3) {
		cout << "MOVE " << typeID << " ";
	}
	if (addType != 3) {
		cout << pointY << " " << pointX << " " << direction << " " << typeID << " ";
	}
	for (int p = 0; p < 3; p++) {
		cout << type[p];
	}
	if (addType == 1) {
		cout << " ";
		for (int k = 0; k < size; k++) {
			cout << stateFragments[k];
		}
	}
	if (addType == 3) {
		cout << " " << direction;
	}
	cout << char(34) << ": PLACING SHIP TOO CLOSE TO OTHER SHIP" << endl;
	exit(0);
}

//struct createReefs reefs[],
void createPlayer::addShip(char **board,int addType, struct cordinates reefs[], int reefsCount, char playerLetter) {


	/*/// TEST

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


	for (int p = 0; p < shipsOwned; p++) {
		if (ships[p].type[0] != 'X') {
			for (int l = 0; l < ships[p].size; l++) {
				if (ships[p].direction == 'N') {
					board[ships[p].pointY + l][ships[p].pointX] = ships[p].pieces[l];
				}
				if (ships[p].direction == 'S') {
					board[ships[p].pointY - l][ships[p].pointX] = ships[p].pieces[l];
				}
				if (ships[p].direction == 'W') {
					board[ships[p].pointY][ships[p].pointX + l] = ships[p].pieces[l];
				}
				if (ships[p].direction == 'E') {
					board[ships[p].pointY][ships[p].pointX - l] = ships[p].pieces[l];
				}
			}
		}
	}
	*/



	/// TEST

	char type[4] = { 'X','X','X' };
	int  size = 3, pointX = 0, pointY = 0, typeID = -1;
	char direction;
	//PLACE_SHIP 6 0 N 0 BAT
	//PLACE_SHIP y x D i C 
	//Place the i-th ship of class C at (y,x) with direction equal to D.

	cin >> pointY >> pointX >> direction >> typeID >> type;

	if (strcmp(type, "CAR") == 0) {
		size = 5;
	}
	if (strcmp(type, "BAT") == 0) {
		size = 4;
	}
	if (strcmp(type, "CRU") == 0) {
		size = 3;
	}
	if (strcmp(type, "DES") == 0) {
		size = 2;
	}

	char *stateFragments = new char[size + 1];

	if (addType == 1) {
		cin >> stateFragments;
	}


	/*for (int i = 0; i < reefsCount; i++) {
		board[reefs[i].y][reefs[i].x] = '#';
	}
	//DISPLAY
	/*for (int i = 0; i < gameSizeY; i++) {
		for (int j = 0; j < gameSizeX; j++) {
			cout << board[i][j];
		}
		cout << endl;
	}*/

	int isSame = 0;
	int sameType = 0;
	for (int i = 0; i < shipsOwned; i++) {
		sameType = 0;
		for (int j = 0; j < 3; j++) {
			if (ships[i].type[j] == type[j]) {
				sameType++;
			}
		}
		if (sameType == 3 && ships[i].typeId == typeID) {
			cout << "INVALID OPERATION " << char(34);
			if (addType == 0) {
				cout << "PLACE_SHIP ";
			}
			else if (addType == 1) {
				cout << "SHIP ";
			}
			cout << pointY << " " << pointX << " " << direction << " " << typeID << " ";
			for (int p = 0; p < 3; p++) {
				cout << type[p];
			}
			if (addType == 1) {
				cout << " ";

				for (int k = 0; k < size; k++) {
					cout << stateFragments[k];
				}
			}
			cout << char(34) << ": SHIP ALREADY PRESENT";
			exit(0);
		}
	}



	// YYYYYYYYY   XXXXXX
	int maxPointX = pointX, maxPointY = pointY;
	if (direction == 'N') {
		maxPointY = pointY + size - 1;
	}
	if (direction == 'S') {
		maxPointY = pointY - size + 1;
	}
	if (direction == 'W') {
		maxPointX = pointX + size - 1;
	}
	if (direction == 'E') {
		maxPointX = pointX - size + 1;
	}


	if (fleet[size - 2] == 0) {
		//INVALID OPERATION "PLACE_SHIP 0 3 N 1 CAR": ALL SHIPS OF THE CLASS ALREADY SET
		cout << "INVALID OPERATION " << char(34);
		if (addType == 0) {
			cout << "PLACE_SHIP ";
		}
		else if (addType == 1) {
			cout << "SHIP ";
		}
		cout << pointY << " " << pointX << " " << direction << " " << typeID << " ";
		for (int p = 0; p < 3; p++) {
			cout << type[p];
		}
		if (addType == 1) {
			cout << " ";
			for (int k = 0; k < size; k++) {
				cout << stateFragments[k];
			}
		}
		cout << char(34) << ": ALL SHIPS OF THE CLASS ALREADY SET";
		exit(0);
	}
	//pointX > maxRow || pointX < minRow || pointY>10 || pointY < 0||maxPointX > maxRow || maxPointX < minRow || maxPointY>10 || maxPointY < 0
	if (addType == 0 && (pointY<minRow || pointY>maxRow || maxPointY<minRow || maxPointY>maxRow)) {
		//INVALID OPERATION "PLACE_SHIP 9 6 N 0 CAR": NOT IN STARTING POSITION
		cout << "INVALID OPERATION " << char(34) << "PLACE_SHIP " << pointY << " " << pointX << " " << direction << " " << typeID << " ";
		for (int i = 0; i < 3; i++) {
			cout << type[i];
		}
		cout << char(34) << ": NOT IN STARTING POSITION";
		exit(0);
	}

	/// TEST


	int offsetY = 0, offsetX = 0;
	for (int i = 0; i < size; i++) {
		offsetY = 0, offsetX = 0;
		if (direction == 'N') {
			offsetY = i;
		}
		if (direction == 'S') {
			offsetY = -i;
		}
		if (direction == 'W') {
			offsetX = i;
		}
		if (direction == 'E') {
			offsetX = -i;
		}

		if (((((pointY + offsetY) >= 0) && ((pointY + offsetY) <= 20)) && (((pointX + offsetX) >= 0) && ((pointX + offsetX) <= 9))) && (board[pointY + offsetY][pointX + offsetX] != ' ')) {
			if (board[pointY + offsetY][pointX + offsetX] == '#')
			{
				cout << "INVALID OPERATION " << char(34);
				if (addType == 0) {
					cout << "PLACE_SHIP ";
				}
				else if (addType == 1) {
					cout << "SHIP ";
				}
				cout << pointY << " " << pointX << " " << direction << " " << typeID << " ";
				for (int p = 0; p < 3; p++) {
					cout << type[p];
				}
				if (addType == 1) {
					cout << " ";
					for (int k = 0; k < size; k++) {
						cout << stateFragments[k];
					}
				}
				cout << char(34) << ": PLACING SHIP ON REEF";
				exit(0);
			}
			toClose(addType, pointY, pointX, direction, typeID, type, size, stateFragments, playerLetter);
		}

		if (((((pointY + offsetY + 1) >= 0) && ((pointY + offsetY + 1) <= 20)) && (((pointX + offsetX) >= 0) && ((pointX + offsetX) <= 9))) && (board[pointY + offsetY + 1][pointX + offsetX] != ' ' && board[pointY + offsetY + 1][pointX + offsetX] != '#')) {
			toClose(addType, pointY, pointX, direction, typeID, type, size, stateFragments, playerLetter);
		}

		if (((((pointY + offsetY - 1) >= 0) && ((pointY + offsetY - 1) <= 20)) && (((pointX + offsetX) >= 0) && ((pointX + offsetX) <= 9))) && (board[pointY + offsetY - 1][pointX + offsetX] != ' '&&board[pointY + offsetY - 1][pointX + offsetX] != '#')) {
			toClose(addType, pointY, pointX, direction, typeID, type, size, stateFragments, playerLetter);
		}
		if (((((pointY + offsetY) >= 0) && ((pointY + offsetY) <= 20)) && (((pointX + offsetX + 1) >= 0) && ((pointX + offsetX + 1) <= 9))) && (board[pointY + offsetY][pointX + offsetX + 1] != ' '&&board[pointY + offsetY][pointX + offsetX + 1] != '#')) {
			toClose(addType, pointY, pointX, direction, typeID, type, size, stateFragments, playerLetter);
		}
		if (((((pointY + offsetY) >= 0) && ((pointY + offsetY) <= 20)) && (((pointX + offsetX - 1) >= 0) && ((pointX + offsetX - 1) <= 9))) && (board[pointY + offsetY][pointX + offsetX - 1] != ' ' && board[pointY + offsetY][pointX + offsetX - 1] != '#')) {
			toClose(addType, pointY, pointX, direction, typeID, type, size, stateFragments, playerLetter);
		}
	}

	/*for (int p = 0; p < shipsOwned; p++) {
		if (ships[p].type[0] != 'X') {
			for (int l = 0; l < ships[p].size; l++) {
				if (ships[p].direction == 'N') {
					board[ships[p].pointY + l][ships[p].pointX] = ships[p].pieces[l];
				}
				if (ships[p].direction == 'S') {
					board[ships[p].pointY - l][ships[p].pointX] = ships[p].pieces[l];
				}
				if (ships[p].direction == 'W') {
					board[ships[p].pointY][ships[p].pointX + l] = ships[p].pieces[l];
				}
				if (ships[p].direction == 'E') {
					board[ships[p].pointY][ships[p].pointX - l] = ships[p].pieces[l];
				}
			}
		}
	}
	/// TEST
	*/

	fleet[size - 2]--;

	int aliveParts = 0;

	createShip ship;
	for (int i = 0; i < 3; i++) {
		ship.type[i] = type[i];
	}
	ship.size = size;

	//segmenty
	char *elements = new char[size];
	
	for (int i = 0; i < size; i++) {
		elements[i] = '+';
	}

	elements[0] = '@';
	elements[1] = '!';
	elements[size - 1] = '%';


	for (int i = 0; i < size; i++) {
		if (addType == 1) {
			if (stateFragments[i] == '1') {
				ship.pieces[i] = elements[i];
				aliveParts++;
			}
			else {
				ship.pieces[i] = 'x';
			}
		}
		else {
			ship.pieces[i] = elements[i];
			aliveParts++;
		}
	}
	//
	ship.pointX = pointX;
	ship.pointY = pointY;
	ship.typeId = typeID;
	ship.direction = direction;
	ship.fragmentsAlive = aliveParts;
	delete[] stateFragments;
	//Deleting Board
	for (int i = 0; i < gameSizeY; ++i) {
		delete[] board[i];
	}
	delete[] board;

	if (strcmp(type, "CAR") == 0) {
		ship.avalibleMoves = 2;
	}
	else {
		ship.avalibleMoves = 3;
	}

	shipsAlive++;
	shipsOwned++;
	ships[shipsOwned - 1] = ship;
}

void createPlayer::displayShips() {
	for (int i = 0; i < shipsOwned; i++) {
		cout << i + 1 << ". ";
		for (int j = 0; j < 3; j++) {
			cout << ships[i].type[j];
		}
		cout << " Size: " << ships[i].size << " Fragments: ";
		for (int k = 0; k < ships[i].size; k++) {
			cout << ships[i].pieces[k];
		}
		cout << " Direction: " << ships[i].direction << " Point Y: " << ships[i].pointY << " Point X: " << ships[i].pointX << " Fragments Alive: " << ships[i].fragmentsAlive << endl;
	}
	cout << endl;
}


void createPlayer::isShipAlive(int number) {
	if (ships[number].fragmentsAlive == 0) {
		shipsAlive--;
	}
}

void createPlayer::setUpShips() {
	int shipsSize = 0;
	shipsSize = fleet[0] + fleet[1] + fleet[2] + fleet[3];
	delete[] ships;

	ships = new createShip[shipsSize];
}

void createPlayer::moveShip(struct cordinates reefs[], int reefsCount, char **board) {
	//cout << endl << "Funkcja" << endl;
	char type[4] = { 'X','X','X' };
	int typeID = -1;
	char turnType = 'X';
	cin >> typeID >> type >> turnType;



	int shipID = -1;
	int sameType = 0;
	for (int i = 0; i < shipsOwned; i++) {
		if (ships[i].typeId != typeID) continue;
		sameType = 0;
		for (int j = 0; j < 3; j++) {
			if (ships[i].type[j] == type[j]) sameType++;
		}

		if (sameType == 3) {
			shipID = i;
			break;
		}
	}

	//brak ruchów

	if (ships[shipID].avalibleMoves == 0) {
		cout << "INVALID OPERATION " << char(34) << "MOVE " << typeID << " ";
		for (int i = 0; i < 3; i++) {
			cout << type[i];
		}
		cout << " " << turnType;
		cout << char(34) << ": SHIP MOVED ALREADY";
		exit(0);
	}

	// o jeden do przodu
	int forwardY = 0, forwardX = 0;
	int pushY = 0, pushX = 0;
	char newDirection = 'X';
	if (ships[shipID].direction == 'N') {
		forwardY = -1;
		if (turnType == 'R') {
			pushX = ships[shipID].size - 1;
			newDirection = 'E';
		}
		if (turnType == 'L') {
			pushX = -ships[shipID].size + 1;
			newDirection = 'W';
		}
	}
	if (ships[shipID].direction == 'S') {
		forwardY = 1;
		if (turnType == 'R') {
			pushX = -ships[shipID].size + 1;
			newDirection = 'W';
		}
		if (turnType == 'L') {
			pushX = ships[shipID].size - 1;
			newDirection = 'E';
		}
	}
	if (ships[shipID].direction == 'W') {
		forwardX = -1;
		if (turnType == 'R') {
			pushY = -ships[shipID].size + 1;
			newDirection = 'N';
		}
		if (turnType == 'L') {
			pushY = ships[shipID].size - 1;
			newDirection = 'S';
		}
	}
	if (ships[shipID].direction == 'E') {
		forwardX = 1;
		if (turnType == 'R') {
			pushY = ships[shipID].size - 1;
			newDirection = 'S';
		}
		if (turnType == 'L') {
			pushY = -ships[shipID].size + 1;
			newDirection = 'N';
		}
	}

	int newPointY, newPointX, newShipY, newShipX;
	newPointY = ships[shipID].pointY + forwardY;
	newPointX = ships[shipID].pointX + forwardX;

	newShipY = newPointY + pushY;
	newShipX = newPointX + pushX;

	//cout << endl << "Nowe Kordy(Y X): " << newShipY << " " << newShipX << endl;

	//OUT OF BOARD
	if (newShipX < 0 || newShipX >= gameSizeX || newShipY < 0 || newShipY >= gameSizeY) {
		//typeID >> type >> turnType
		cout << "INVALID OPERATION " << char(34) << "MOVE " << typeID << " ";
		for (int i = 0; i < 3; i++) {
			cout << type[i];
		}
		cout << " " << turnType;
		cout << char(34) << ": SHIP WENT FROM BOARD";
		exit(0);
	}

	//creating board with ships and reefs
	/*
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


	for (int p = 0; p < shipsOwned; p++) {
		if (ships[p].type[0] != 'X') {
			for (int l = 0; l < ships[p].size; l++) {
				if (!(ships[p].typeId == typeID && (strcmp(ships[p].type, ships[shipID].type) == 0)))
				{
					if (ships[p].direction == 'N') {
						board[ships[p].pointY + l][ships[p].pointX] = ships[p].pieces[l];
					}
					if (ships[p].direction == 'S') {
						board[ships[p].pointY - l][ships[p].pointX] = ships[p].pieces[l];
					}
					if (ships[p].direction == 'W') {
						board[ships[p].pointY][ships[p].pointX + l] = ships[p].pieces[l];
					}
					if (ships[p].direction == 'E') {
						board[ships[p].pointY][ships[p].pointX - l] = ships[p].pieces[l];
					}
				}
			}
		}
	}

	for (int p = 0; p < APshipsOwned; p++) {
			for (int l = 0; l < shipsAP[p].size; l++) {
					if (shipsAP[p].direction == 'N') {
						board[shipsAP[p].pointY + l][shipsAP[p].pointX] = shipsAP[p].pieces[l];
					}
					if (shipsAP[p].direction == 'S') {
						board[shipsAP[p].pointY - l][shipsAP[p].pointX] = shipsAP[p].pieces[l];
					}
					if (shipsAP[p].direction == 'W') {
						board[shipsAP[p].pointY][shipsAP[p].pointX + l] = shipsAP[p].pieces[l];
					}
					if (shipsAP[p].direction == 'E') {
						board[shipsAP[p].pointY][shipsAP[p].pointX - l] = shipsAP[p].pieces[l];
					}
			}
	}

	for (int i = 0; i < reefsCount; i++) {
		board[reefs[i].y][reefs[i].x] = '#';
	}

	for (int i = 0; i < gameSizeY; i++) {
		for (int j = 0; j < gameSizeX; j++) {
			cout << board[i][j];
		}
		cout << endl;
	}
	*/
	//Delete moving ship;
	int isSame = 0;
	for (int i = 0; i < shipsOwned; i++) {
		isSame = 0;
		if (ships[i].typeId == ships[shipID].typeId) {
			for (int j = 0; j < 3; j++) {
				if (ships[i].type[j] == ships[shipID].type[j])isSame++;
			}
		}
		if (isSame == 3) {
			for (int l = 0; l < ships[shipID].size; l++) {
				if (ships[shipID].direction == 'N') {
					board[ships[shipID].pointY + l][ships[shipID].pointX] = ' ';
				}
				if (ships[shipID].direction == 'S') {
					board[ships[shipID].pointY - l][ships[shipID].pointX] = ' ';
				}
				if (ships[shipID].direction == 'W') {
					board[ships[shipID].pointY][ships[shipID].pointX + l] = ' ';
				}
				if (ships[shipID].direction == 'E') {
					board[ships[shipID].pointY][ships[shipID].pointX - l] = ' ';
				}
			}
			break;
		}
	}

	//TO CLOSE
	int offsetY = 0, offsetX = 0;
	for (int i = 0; i < ships[shipID].size; i++) {
		offsetY = 0, offsetX = 0;
		if (newDirection == 'N') {
			offsetY = i;
		}
		if (newDirection == 'S') {
			offsetY = -i;
		}
		if (newDirection == 'W') {
			offsetX = i;
		}
		if (newDirection == 'E') {
			offsetX = -i;
		}
		if (((((newShipY + offsetY) >= 0) && ((newShipY + offsetY) <= 20)) && (((newShipX + offsetX) >= 0) && ((newShipX + offsetX) <= 9))) && (board[newShipY + offsetY][newShipX + offsetX] != ' ')) {
			if (board[newShipY + offsetY][newShipX + offsetX] == '#')
			{
				cout << "INVALID OPERATION " << char(34);
				cout << "MOVE ";
				cout << typeID << " ";
				for (int p = 0; p < 3; p++) {
					cout << type[p];
				}
				cout << turnType;
				cout << char(34) << ": PLACING SHIP ON REEF";
				exit(0);
			}
			//int addType, int pointY, int pointX, char direction, int typeID, char type[], int size=0, char stateFragments[]=NULL, char playerLetter='X'
			toClose(3, -1, -1, turnType, typeID, type);
		}

		if (((((newShipY + offsetY + 1) >= 0) && ((newShipY + offsetY + 1) <= 20)) && (((newShipX + offsetX) >= 0) && ((newShipX + offsetX) <= 9))) && (board[newShipY + offsetY + 1][newShipX + offsetX] != ' ' && board[newShipY + offsetY + 1][newShipX + offsetX] != '#')) {
			toClose(3, -1, -1, turnType, typeID, type);
		}

		if (((((newShipY + offsetY - 1) >= 0) && ((newShipY + offsetY - 1) <= 20)) && (((newShipX + offsetX) >= 0) && ((newShipX + offsetX) <= 9))) && (board[newShipY + offsetY - 1][newShipX + offsetX] != ' '&&board[newShipY + offsetY - 1][newShipX + offsetX] != '#')) {
			toClose(3, -1, -1, turnType, typeID, type);
		}
		if (((((newShipY + offsetY) >= 0) && ((newShipY + offsetY) <= 20)) && (((newShipX + offsetX + 1) >= 0) && ((newShipX + offsetX + 1) <= 9))) && (board[newShipY + offsetY][newShipX + offsetX + 1] != ' '&&board[newShipY + offsetY][newShipX + offsetX + 1] != '#')) {
			toClose(3, -1, -1, turnType, typeID, type);
		}
		if (((((newShipY + offsetY) >= 0) && ((newShipY + offsetY) <= 20)) && (((newShipX + offsetX - 1) >= 0) && ((newShipX + offsetX - 1) <= 9))) && (board[newShipY + offsetY][newShipX + offsetX - 1] != ' ' && board[newShipY + offsetY][newShipX + offsetX - 1] != '#')) {
			toClose(3, -1, -1, turnType, typeID, type);
		}
	}
	for (int i = 0; i < gameSizeY; ++i) {
		delete[] board[i];
	}
	delete[] board;
	//FINAL SETTING
	if (newDirection != 'X') {
		ships[shipID].direction = newDirection;
	}
	ships[shipID].pointY = newShipY;
	ships[shipID].pointX = newShipX;
	ships[shipID].avalibleMoves--;
}

void createPlayer::restartAvalibleMoves() {
	for (int i = 0; i < shipsOwned; i++) {
		if (strcmp(ships[i].type, "CAR") == 0) {
			ships[i].avalibleMoves = 2;
		}
		else {
			ships[i].avalibleMoves = 3;
		}
	}
}

void createPlayer::testtest(char **board) {
	for (int i = 0; i < gameSizeY; i++) {
		for (int j = 0; j < gameSizeX; j++) {
			cout << board[i][j];
		}
		cout << endl;
	}
}

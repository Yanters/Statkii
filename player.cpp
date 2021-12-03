#include <iostream>
#include "player.h"
#include "game.h"

using namespace std;


void createPlayer::addShip() {
	///char type[],int size,char direction,int pointX,int pointY
	shipsAlive++;
	shipsOwned++;
	char type[4] = { 'X','X','X' };
	int  size=3,pointX=0, pointY=0,typeID=-1;
	char direction;
	//PLACE_SHIP 6 0 N 0 BAT
	//PLACE_SHIP y x D i C 
	//Place the i-th ship of class C at (y,x) with direction equal to D.

	cin >> pointY >> pointX >> direction >> typeID >> type;

	int isSame = 0;
	int sameType = 0;
	for (int i = 0;i < shipsOwned; i++) {
		sameType = 0;
		for (int j = 0; j < 3; j++) {
if (ships[i].type[j] == type[j]) {
	sameType++;
}
		}
		if (sameType == 3 && ships[i].typeId == typeID) {
			cout << "INVALID OPERATION " << char(34) << "PLACE_SHIP " << pointY << " " << pointX << " " << direction << " " << typeID << " ";
			for (int i = 0; i < 3; i++) {
				cout << type[i];
			}
			cout << char(34) << ": SHIP ALREADY PRESENT";
			//exit(0);
		}
	}


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
		cout << "INVALID OPERATION " << char(34) << "PLACE_SHIP " << pointY << " " << pointX << " " << direction << " " << typeID << " ";
		for (int i = 0; i < 3; i++) {
			cout << type[i];
		}
		cout << char(34) << ": ALL SHIPS OF THE CLASS ALREADY SET";
		//exit(0);
	}
	//pointX > maxRow || pointX < minRow || pointY>10 || pointY < 0||maxPointX > maxRow || maxPointX < minRow || maxPointY>10 || maxPointY < 0
	if (pointY<minRow||pointY>maxRow||maxPointY<minRow||maxPointY>maxRow) {
		//INVALID OPERATION "PLACE_SHIP 9 6 N 0 CAR": NOT IN STARTING POSITION
		cout << "INVALID OPERATION " << char(34) << "PLACE_SHIP " << pointY << " " << pointX << " " << direction << " " << typeID << " ";
		for (int i = 0; i < 3; i++) {
			cout << type[i];
		}
		cout << char(34) << ": NOT IN STARTING POSITION";
		//exit(0);
	}


	fleet[size - 2]--;

	createShip ship;
	for (int i = 0; i < 3; i++) {
		ship.type[i] = type[i];
	}
	ship.size = size;
	for (int i = 0; i < size; i++) {
		ship.pieces[i] = '+';
	}
	ship.pointX = pointX;
	ship.pointY = pointY;
	ship.typeId = typeID;
	ship.direction = direction;
	ship.fragmentsAlive = size;

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
	if(ships[number].fragmentsAlive == 0){
	shipsAlive--;
}
}

/*void createPlayer::shoot(gameSetter& game) {
	int pointX, pointY;
	cin >> pointY >> pointX;
	cout << endl << "X: " << pointX << " Y: " << pointY << endl;

	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < game.players[i].shipsAlive; j++) {
			for (int k = 0; k < game.players[i].ships[j].size; k++) {
				if (game.players[i].ships[j].direction == 'N') {
					if (pointY == (game.players[i].ships[j].pointX + k) && pointX == (game.players[i].ships[j].pointY)) {
						cout << "HITTTTTT";
					}
					//board[players[k].ships[p].pointX + l][players[k].ships[p].pointY] = players[k].ships[p].pieces[l];
				}
				if (game.players[i].ships[j].direction == 'S') {
					board[players[k].ships[p].pointX - l][players[k].ships[p].pointY] = players[k].ships[p].pieces[l];
				}
				if (game.players[i].ships[j].direction == 'W') {
					board[players[k].ships[p].pointX][players[k].ships[p].pointY + l] = players[k].ships[p].pieces[l];
				}
				if (game.players[i].ships[j].direction == 'E') {
					board[players[k].ships[p].pointX][players[k].ships[p].pointY - l] = players[k].ships[p].pieces[l];
				}
			}
		}
	}
}*/


#include <iostream>
#include <math.h>
#include "game.h"

using namespace std;

void gameSetter::displayMap() {
	int option;
	cin >> option;
	//Creating Board
	char **board = new char*[gameSizeY];
	for (int i = 0; i < gameSizeY; ++i) {
		board[i] = new char[gameSizeX];
	}
	//Clearing board
	for (int i = 0; i < gameSizeY; i++) {
		for (int j = 0; j < gameSizeX; j++) {
			 board[i][j]=' ';
		}
	}
	//Setting values to the board
	for (int k = 0; k < 2; k++) {
		for (int p = 0; p < 10; p++) {
			if (players[k].ships[p].type[0] != 'X') {
				for (int l = 0; l < players[k].ships[p].size; l++) {
					if (players[k].ships[p].direction == 'N') {
						board[players[k].ships[p].pointY + l][players[k].ships[p].pointX ] = players[k].ships[p].pieces[l];
					}
					if (players[k].ships[p].direction == 'S') {
						board[players[k].ships[p].pointY - l][players[k].ships[p].pointX] = players[k].ships[p].pieces[l];
					}
					if (players[k].ships[p].direction == 'W') {
						board[players[k].ships[p].pointY ][players[k].ships[p].pointX + l] = players[k].ships[p].pieces[l];
					}
					if (players[k].ships[p].direction == 'E') {
						board[players[k].ships[p].pointY][players[k].ships[p].pointX - l] = players[k].ships[p].pieces[l];
					}
				}
			}
		}
	}

	//Displaying Board

	for (int i = 0; i < gameSizeY; i++) {
		for (int j = 0; j < gameSizeX; j++) {

			cout <<board[i][j];

		}
		cout << endl;
	}

	int partsRemainingA = 0 , partsRemainingB = 0;

	for (int i = 0; i < players[0].shipsOwned; i++) {
		partsRemainingA += players[0].ships[i].fragmentsAlive;
	}
	for (int i = 0; i < players[1].shipsOwned; i++) {
		partsRemainingB += players[1].ships[i].fragmentsAlive;
	}
	cout << "PARTS REMAINING:: A : " << partsRemainingA << " B : " << partsRemainingB<<endl;
	//Deleting Board
	for (int i = 0; i < gameSizeY ; ++i) {
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
	int idGracza = abs( 65 - int(playerLetter));
	players[idGracza].fleet[0] = a4;
	players[idGracza].fleet[1] = a3;
	players[idGracza].fleet[2] = a2;
	players[idGracza].fleet[3] = a1;
}

void gameSetter::nextPlayer() {
	if (move == 0) move++;
	else if (move == 1) move = 0;
}

void gameSetter::isThereAWinner() {
	if (players[0].shipsAlive == 0) {
		cout << "B won" << endl;
	}
	else if (players[1].shipsAlive == 0) {
		cout << "A won"<<endl;

	}
}


void gameSetter::shoot(int idGracza) {
	int pointX, pointY;
	cin >> pointY >> pointX;

	if (pointX > gameSizeX || pointY > gameSizeY) {
		cout << "INVALID OPERATION " << char(34) << "SHOOT " << pointY << " " << pointX << char(34) << ": FIELD DOES NOT EXIST";
		//exit(0);
	}

	if (idGracza - 1 != move) {
		if (idGracza-1 == 1) {
			cout << "INVALID OPERATION " << char(34) << "[playerB] " << char(34) << ": THE OTHER PLAYER EXPECTED";
		}
		else {
			cout << "INVALID OPERATION " << char(34) << "[playerA] " << char(34) << ": THE OTHER PLAYER EXPECTED";

		}
		//exit(0);

	}

	int canShoot = 0;

	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 4; j++) {
			canShoot += players[i].fleet[j];
		}
	}

		if (canShoot != 0) {
			cout << "INVALID OPERATION "<<char(34)<<"SHOOT " << pointY << " " << pointX  <<char(34) << ": NOT ALL SHIPS PLACED";
			//exit(0);
		}

	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < players[i].shipsOwned; j++) {
			for (int k = 0; k <players[i].ships[j].size; k++) {
				if (players[i].ships[j].direction == 'N') {
					if (pointY == (players[i].ships[j].pointY + k) && pointX == (players[i].ships[j].pointX)&&players[i].ships[j].pieces[k]!='x') {
						players[i].ships[j].pieces[k] = 'x';
						players[i].ships[j].fragmentsAlive--;
						players[i].isShipAlive(j);
					}
				}
				if (players[i].ships[j].direction == 'S') {
					if (pointY == (players[i].ships[j].pointY - k) && pointX == (players[i].ships[j].pointX) && players[i].ships[j].pieces[k] != 'x') {
						players[i].ships[j].pieces[k] = 'x';
						players[i].ships[j].fragmentsAlive--;
						players[i].isShipAlive(j);

					}
				}
				if (players[i].ships[j].direction == 'W') {
					if (pointY == (players[i].ships[j].pointY ) && pointX == ((players[i].ships[j].pointX) + k) && players[i].ships[j].pieces[k] != 'x') {
						players[i].ships[j].pieces[k] = 'x';
						players[i].ships[j].fragmentsAlive--;
						players[i].isShipAlive(j);

					}
				}
				if (players[i].ships[j].direction == 'E') {
					if (pointY == (players[i].ships[j].pointY) && pointX == ((players[i].ships[j].pointX) - k) && players[i].ships[j].pieces[k] != 'x') {
						players[i].ships[j].pieces[k] = 'x';
						players[i].ships[j].fragmentsAlive--;
						players[i].isShipAlive(j);

					}
				}
			}
		}
	}
	nextPlayer();
}


void gameSetter::setBoardSize() {
	int boardY=0, boardX=0;
	cin << boardY << boardX;
	gameSizeX = boardX;
	gameSizeY = boardY;
}

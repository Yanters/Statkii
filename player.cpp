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

double calculateDistanceVision(int cannonY, int cannonX, int shootY, int shootX) {
	return sqrt(pow(abs(cannonY - shootY), 2) + pow(abs(cannonX - shootX), 2));
}

void createPlayer::addShip(char **board, int addType, struct cordinates reefs[], int reefsCount, char playerLetter) {
	char type[4] = { 'X','X','X' };
	int  size = 3, pointX = 0, pointY = 0, typeID = -1;
	char direction;
	if (addType != 3) {
		cin >> pointY >> pointX >> direction >> typeID >> type;
	}

	if (addType == 3) {
		pointY = rand() % (maxRow);
		pointX = rand() % (maxCol);
		int directionType = rand() % 4;
		switch (directionType)
		{
		case 0:
			direction = 'N';
			break;
		case 1:
			direction = 'E';
			break;
		case 2:
			direction = 'S';
			break;
		case 3:
			direction = 'W';
			break;
		default:
			break;
		}
		typeID = MainFleet[AIShipType] - fleet[AIShipType];
		switch (AIShipType)
		{
		case 3:
			type[0] = 'C';
			type[1] = 'A';
			type[2] = 'R';
			break;
		case 2:
			type[0] = 'B';
			type[1] = 'A';
			type[2] = 'T';
			break;
		case 1:
			type[0] = 'C';
			type[1] = 'R';
			type[2] = 'U';
			break;
		case 0:
			type[0] = 'D';
			type[1] = 'E';
			type[2] = 'S';
			break;
		default:
			cout << "ERROR" << endl;
			break;
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

	char *stateFragments = new char[size + 1];

	if (addType == 1) {
		cin >> stateFragments;
	}

	int sameType = 0;
	for (int i = 0; i < shipsOwned; i++) {
		sameType = 0;
		for (int j = 0; j < 3; j++) {
			if (ships[i].type[j] == type[j])sameType++;
		}
		if (sameType == 3 && ships[i].typeId == typeID) {
			if (addType != 3)
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
				cout << char(34) << ": SHIP ALREADY PRESENT";
				exit(0);
			}
			else {
				AIError = 1;
			}
		}
	}



	int cannonY = pointY, cannonX = pointX;
	int maxPointX = pointX, maxPointY = pointY;
	if (direction == 'N') {
		maxPointY = pointY + size - 1;
		cannonY++;
	}
	if (direction == 'S') {
		maxPointY = pointY - size + 1;
		cannonY--;
	}
	if (direction == 'W') {
		maxPointX = pointX + size - 1;
		cannonX++;
	}
	if (direction == 'E') {
		maxPointX = pointX - size + 1;
		cannonX--;
	}


	if (fleet[size - 2] == 0) {
		if (addType != 3)
		{
			cout << "INVALID OPERATION " << char(34);
			if (addType == 0) {
				cout << "PLACE_SHIP ";
			}
			else if (addType == 1) {
				cout << "SHIP ";
			}
			cout << pointY << " " << pointX << " " << direction << " " << typeID << " ";
			cout << type;
			if (addType == 1) {
				cout << " ";

				cout << stateFragments;

			}
			cout << char(34) << ": ALL SHIPS OF THE CLASS ALREADY SET";
			exit(0);
		}
		else
		{
			AIError = 1;
		}
	}
	if (((addType == 0 || addType == 3) && (pointY<minRow || pointY>maxRow || maxPointY<minRow || maxPointY>maxRow || pointX<minCol || pointX>maxCol || maxPointX<minCol || maxPointX>maxCol))) {
		if (addType != 3)
		{
			cout << "INVALID OPERATION " << char(34) << "PLACE_SHIP " << pointY << " " << pointX << " " << direction << " " << typeID << " ";
			cout << type;
			cout << char(34) << ": NOT IN STARTING POSITION";
			exit(0);
		}
		else
		{
			AIError = 1;
		}
	}

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
		if (AIError != 1) {
			if (((((pointY + offsetY) >= 0) && ((pointY + offsetY) <= gameSizeY - 1)) && (((pointX + offsetX) >= 0) && ((pointX + offsetX) <= gameSizeX - 1))) && (board[pointY + offsetY][pointX + offsetX] != ' ')) {
				if (board[pointY + offsetY][pointX + offsetX] == '#')
				{
					if (addType != 3)
					{
						cout << "INVALID OPERATION " << char(34);
						if (addType == 0) {
							cout << "PLACE_SHIP ";
						}
						else if (addType == 1) {
							cout << "SHIP ";
						}
						cout << pointY << " " << pointX << " " << direction << " " << typeID << " ";
						cout << type;

						if (addType == 1) {
							cout << " ";
							cout << stateFragments;
						}
						cout << char(34) << ": PLACING SHIP ON REEF";
						exit(0);
					}
					else
					{
						AIError = 1;
					}
				}
				if (addType != 3)
				{
					toClose(addType, pointY, pointX, direction, typeID, type, size, stateFragments, playerLetter);
				}
				else
				{
					AIError = 1;
				}
			}

			if (((((pointY + offsetY + 1) >= 0) && ((pointY + offsetY + 1) <= gameSizeY - 1)) && (((pointX + offsetX) >= 0) && ((pointX + offsetX) <= gameSizeX - 1))) && (board[pointY + offsetY + 1][pointX + offsetX] != ' ' && board[pointY + offsetY + 1][pointX + offsetX] != '#')) {
				if (addType != 3)
				{
					toClose(addType, pointY, pointX, direction, typeID, type, size, stateFragments, playerLetter);
				}
				else
				{
					AIError = 1;
				}
			}

			if (((((pointY + offsetY - 1) >= 0) && ((pointY + offsetY - 1) <= gameSizeY - 1)) && (((pointX + offsetX) >= 0) && ((pointX + offsetX) <= gameSizeX - 1))) && (board[pointY + offsetY - 1][pointX + offsetX] != ' '&&board[pointY + offsetY - 1][pointX + offsetX] != '#')) {
				if (addType != 3)
				{
					toClose(addType, pointY, pointX, direction, typeID, type, size, stateFragments, playerLetter);
				}
				else
				{
					AIError = 1;
				}
			}
			if (((((pointY + offsetY) >= 0) && ((pointY + offsetY) <= gameSizeY - 1)) && (((pointX + offsetX + 1) >= 0) && ((pointX + offsetX + 1) <= gameSizeX - 1))) && (board[pointY + offsetY][pointX + offsetX + 1] != ' '&&board[pointY + offsetY][pointX + offsetX + 1] != '#')) {
				if (addType != 3)
				{
					toClose(addType, pointY, pointX, direction, typeID, type, size, stateFragments, playerLetter);
				}
				else
				{
					AIError = 1;
				}
			}
			if (((((pointY + offsetY) >= 0) && ((pointY + offsetY) <= gameSizeY - 1)) && (((pointX + offsetX - 1) >= 0) && ((pointX + offsetX - 1) <= gameSizeX - 1))) && (board[pointY + offsetY][pointX + offsetX - 1] != ' ' && board[pointY + offsetY][pointX + offsetX - 1] != '#')) {
				if (addType != 3)
				{
					toClose(addType, pointY, pointX, direction, typeID, type, size, stateFragments, playerLetter);
				}
				else
				{
					AIError = 1;
				}
			}
		}
	}


	createShip ship;


	if (AIError != 1) {
		fleet[size - 2]--;

		int aliveParts = 0;

		for (int i = 0; i < 3; i++) {
			ship.type[i] = type[i];
		}
		ship.size = size;

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
		ship.pointX = pointX;
		ship.pointY = pointY;
		ship.typeId = typeID;
		ship.direction = direction;
		ship.fragmentsAlive = aliveParts;
		if (strcmp(type, "CAR") == 0) {
			ship.avalibleMoves = 2;
			ship.avaliblePlanes = size;
		}
		else {
			ship.avalibleMoves = 3;
		}

		if (size > 2) {
			ship.cannonX = cannonX;
			ship.cannonY = cannonY;
			if (addType == 1 && stateFragments[1] == '1') {
				ship.avalibleShoots = size;
				ship.cannonDestroyed = 'N';
			}
			else if (addType == 1 && stateFragments[1] == '0') {
				ship.avalibleShoots = 0;
				ship.cannonDestroyed = 'Y';
			}
			else {
				ship.avalibleShoots = size;
				ship.cannonDestroyed = 'N';
			}
		}
		else {
			ship.cannonDestroyed = 'Y';
			ship.avalibleShoots = 0;
			ship.cannonX = -1;
			ship.cannonY = -1;
		}
		if (addType == 1) {
			if (stateFragments[size - 1] == '0') {
				ship.engineDestroyed = 'Y';
			}
			if (stateFragments[0] == '0') {
				ship.radarDestroyed = 'Y';
			}
		}
		shipsAlive++;
		shipsOwned++;
		ships[shipsOwned - 1] = ship;

	}
	for (int i = 0; i < gameSizeY; ++i) {
		delete[] board[i];
	}
	delete[] board;


	delete[] stateFragments;
	if (AIError != 1 && AIPlayer == 1) {
		AIShipsOwned++;
	}


}

void createPlayer::displayShips() {
	for (int i = 0; i < shipsOwned; i++) {
		cout << i + 1 << ". ";
		printf("%s", ships[i].type);

		cout << " Size: " << ships[i].size << " Fragments: ";
		printf("%s", ships[i].pieces);

		cout << " Direction: " << ships[i].direction << " Point Y: " << ships[i].pointY << " Point X: " << ships[i].pointX << " Fragments Alive: " << ships[i].fragmentsAlive << "Shoot: " << ships[i].cannonDestroyed << endl;
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



void createPlayer::moveShip(struct cordinates reefs[], int reefsCount, char **board, int ShipID) {
	char type[4] = { 'X','X','X' };
	int typeID = -1;
	char turnType = 'X';
	int shipID = -1;

	if (AIPlayer != 1 || AIWait == 1) {
		cin >> typeID >> type >> turnType;


		int sameType = 0;
		for (int i = 0; i < shipsOwned; i++) {
			sameType = 0;
			for (int j = 0; j < 3; j++) {
				if (ships[i].type[j] == type[j])sameType++;
			}
			if (ships[i].typeId == typeID && sameType == 3) {
				shipID = i;
				break;
			}
		}
	}
	else if (AIWait != 1) {
		shipID = ShipID;
		for (int i = 0; i < 3; i++) {
			type[i] = ships[ShipID].type[i];

		}
		switch (rand() % 3)
		{
		case 0:
			turnType = 'L';
			break;
		case 1:
			turnType = 'F';
			break;
		case 2:
			turnType = 'R';
			break;

		default:
			break;
		}
		typeID = ships[ShipID].typeId;
	}


	if (ships[shipID].avalibleMoves == 0) {
		if (AIPlayer != 1) {
			cout << "INVALID OPERATION " << char(34) << "MOVE " << typeID << " ";
			for (int i = 0; i < 3; i++) {
				cout << type[i];
			}
			cout << " " << turnType;
			cout << char(34) << ": SHIP MOVED ALREADY";
			exit(0);
		}
		else {
			AIError = 1;
		}
	}

	if (ships[shipID].engineDestroyed == 'Y') {
		if (AIPlayer != 1) {

			cout << "INVALID OPERATION " << char(34) << "MOVE " << typeID << " ";
			for (int i = 0; i < 3; i++) {
				cout << type[i];
			}
			cout << " " << turnType;
			cout << char(34) << ": SHIP CANNOT MOVE";
			exit(0);
		}
		else
		{
			AIError = 1;
		}
	}

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

	int  newShipY, newShipX;

	newShipY = ships[shipID].pointY + forwardY + pushY;
	newShipX = ships[shipID].pointX + forwardX + pushX;

	if (newShipX < 0 || newShipX >= gameSizeX || newShipY < 0 || newShipY >= gameSizeY) {
		if (AIPlayer != 1) {

			cout << "INVALID OPERATION " << char(34) << "MOVE " << typeID << " " << type << " " << turnType << char(34) << ": SHIP WENT FROM BOARD";;
			exit(0);
		}
		else
		{
			AIError = 1;
		}
	}

	for (int i = 0; i < shipsOwned; i++) {
		if (ships[i].typeId == ships[shipID].typeId &&strcmp(ships[i].type, ships[shipID].type) == 0) {
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
				if (AIPlayer != 1) {

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
				else
				{
					AIError = 1;
				}
			}
			if (AIPlayer != 1) {
				toClose(3, -1, -1, turnType, typeID, type);

			}
			else
			{
				AIError = 1;
			}
		}

		if (((((newShipY + offsetY + 1) >= 0) && ((newShipY + offsetY + 1) <= 20)) && (((newShipX + offsetX) >= 0) && ((newShipX + offsetX) <= 9))) && (board[newShipY + offsetY + 1][newShipX + offsetX] != ' ' && board[newShipY + offsetY + 1][newShipX + offsetX] != '#')) {
			if (AIPlayer != 1) {
				toClose(3, -1, -1, turnType, typeID, type);

			}
			else
			{
				AIError = 1;
			}
		}

		if (((((newShipY + offsetY - 1) >= 0) && ((newShipY + offsetY - 1) <= 20)) && (((newShipX + offsetX) >= 0) && ((newShipX + offsetX) <= 9))) && (board[newShipY + offsetY - 1][newShipX + offsetX] != ' '&&board[newShipY + offsetY - 1][newShipX + offsetX] != '#')) {
			if (AIPlayer != 1) {
				toClose(3, -1, -1, turnType, typeID, type);

			}
			else
			{
				AIError = 1;
			}
		}
		if (((((newShipY + offsetY) >= 0) && ((newShipY + offsetY) <= 20)) && (((newShipX + offsetX + 1) >= 0) && ((newShipX + offsetX + 1) <= 9))) && (board[newShipY + offsetY][newShipX + offsetX + 1] != ' '&&board[newShipY + offsetY][newShipX + offsetX + 1] != '#')) {
			if (AIPlayer != 1) {
				toClose(3, -1, -1, turnType, typeID, type);

			}
			else
			{
				AIError = 1;
			}
		}
		if (((((newShipY + offsetY) >= 0) && ((newShipY + offsetY) <= 20)) && (((newShipX + offsetX - 1) >= 0) && ((newShipX + offsetX - 1) <= 9))) && (board[newShipY + offsetY][newShipX + offsetX - 1] != ' ' && board[newShipY + offsetY][newShipX + offsetX - 1] != '#')) {
			if (AIPlayer != 1) {
				toClose(3, -1, -1, turnType, typeID, type);

			}
			else
			{
				AIError = 1;
			}
		}
	}
	for (int i = 0; i < gameSizeY; ++i) {
		delete[] board[i];
	}
	delete[] board;
	if (AIPlayer == 0 || (AIPlayer == 1 && AIWait == 1 && AIError == 0)) {
		if (newDirection != 'X') {
			ships[shipID].direction = newDirection;
		}
		ships[shipID].pointY = newShipY;
		ships[shipID].pointX = newShipX;
		ships[shipID].avalibleMoves--;
	}
	else if (AIPlayer == 1 && AIError == 0)
	{
		cout << "MOVE " << typeID << " ";
		for (int i = 0; i < 3; i++) {
			cout << type[i];
		}
		cout << " " << turnType << endl;
		AISkipShipShoot = 1;
	}

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
void createPlayer::restartShips(int oldFleets[]) {
	for (int i = (shipsOwned - AIShipsOwned); i < shipsOwned; i++) {
		ships[i].size = 3;
		ships[i].pointX = -1;
		ships[i].pointY = -1;
		ships[i].direction = '?';
		ships[i].typeId = -1;
		ships[i].fragmentsAlive = 0;
		ships[i].avalibleMoves = 3;
		ships[i].cannonX = -1;
		ships[i].cannonY = -1;
		ships[i].avalibleShoots = 0;
		ships[i].avaliblePlanes = 0;
		ships[i].cannonDestroyed = 'N';
		ships[i].radarDestroyed = 'N';
		ships[i].engineDestroyed = 'N';
	}
	shipsOwned = shipsOwned - AIShipsOwned;
	for (int i = 3; i >= 0; i--) {
		fleet[i] = oldFleets[i];
	}
}


void createPlayer::restartAvalibleShoots() {
	for (int i = 0; i < shipsOwned; i++) {
		if (ships[i].size > 2 && ships[i].cannonDestroyed != 1) {
			ships[i].avalibleShoots = ships[i].size;
		}
	}
}

void createPlayer::addSpyPlane() {
	int carID = 0, pointY = 0, pointX = 0;
	cin >> carID >> pointY >> pointX;

	int shipID = -1;

	for (int i = 0; i < shipsOwned; i++) {
		if (ships[i].typeId != carID) continue;

		if (strcmp(ships[i].type, "CAR") == 0) {
			shipID = i;
			break;
		}
	}

	if (ships[shipID].cannonDestroyed == 'Y') {
		cout << "INVALID OPERATION " << char(34);
		cout << "SPY ";
		cout << carID << " " << pointY << " " << pointX;
		cout << char(34) << ": CANNOT SEND PLANE";
		exit(0);
	}

	if (ships[shipID].avaliblePlanes == 0) {
		cout << "INVALID OPERATION " << char(34);
		cout << "SPY ";
		cout << carID << " " << pointY << " " << pointX;
		cout << char(34) << ": ALL PLANES SENT";
		exit(0);
	}

	cordinates spyPlane;
	spyPlane.y = pointY;
	spyPlane.x = pointX;
	spyPlanes[spyPlanesCount] = spyPlane;
	ships[shipID].avalibleShoots--;
	ships[shipID].avaliblePlanes--;
	spyPlanesCount++;
}


void createPlayer::playerVisionMap(char **boardAll, int visionOption) {

	char **foggyBoard = new char*[gameSizeY];
	for (int i = 0; i < gameSizeY; ++i) {
		foggyBoard[i] = new char[gameSizeX];
	}
	for (int i = 0; i < gameSizeY; i++) {
		for (int j = 0; j < gameSizeX; j++) {
			foggyBoard[i][j] = '?';
		}
	}
	for (int i = 0; i < shipsOwned; i++) {
		if (ships[i].radarDestroyed = 'N') {
			for (int m = 0; m < gameSizeY; m++) {
				for (int n = 0; n < gameSizeX; n++) {
					if (ships[i].size >= calculateDistanceVision(ships[i].pointY, ships[i].pointX, m, n)) {
						foggyBoard[m][n] = 'V';
					}
				}
			}
		}
		else {
			for (int m = 0; m < gameSizeY; m++) {
				for (int n = 0; n < gameSizeX; n++) {
					if (1 >= calculateDistanceVision(ships[i].pointY, ships[i].pointX, m, n)) {
						foggyBoard[m][n] = 'V';
					}
				}
			}
		}

	}
	for (int i = 0; i < spyPlanesCount; i++) {
		for (int m = 0; m < gameSizeY; m++) {
			for (int n = 0; n < gameSizeX; n++) {
				if (2 > calculateDistanceVision(spyPlanes[i].y, spyPlanes[i].x, m, n)) {
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

	if (visionOption == 1) {
		cout << "  ";
		for (int i = 0; i < gameSizeX; i++) {
			cout << i;
		}
		cout << endl;
	}
	for (int i = 0; i < gameSizeY; i++) {
		if (visionOption == 1) {
			if (i < 10) {
				cout << '0' << i;
			}
			else {
				cout << i;
			}
		}
		for (int j = 0; j < gameSizeX; j++) {
			cout << foggyBoard[i][j];
		}
		cout << endl;
	}

}
#include <iostream>
#include "player.h"
#include "game.h"

#define commandLength 20

using namespace std;

void stateCommands(gameSetter& game) {
	char command2[commandLength];
	while (cin >> command2) {
		if (strcmp(command2, "[state]") == 0) {
			break;
		}
		if (strcmp(command2, "PRINT") == 0) {
			game.displayMap();
		}
		if (strcmp(command2, "SET_FLEET") == 0) {
			game.setFleet();
		}
		if (strcmp(command2, "NEXT_PLAYER") == 0) {
			game.nextPlayer();
		}
	}
}

void playerCommands(gameSetter& game, int playerIDs){
	char command2[commandLength];
	while (cin >> command2) {
		if (strcmp(command2, "[playerA]") == 0|| strcmp(command2, "[playerB]") == 0) {
			break;
		}
		if (strcmp(command2, "PLACE_SHIP")==0) {
			game.players[playerIDs-1].addShip();
		}
		if (strcmp(command2, "SHOOT") == 0) {
			game.shoot(playerIDs);
			game.isThereAWinner();
		}
		if (strcmp(command2, "WYPISZ") == 0) {
			game.players[playerIDs - 1].displayShips();
		}

	}
}


int main()
{
	cout << endl;
	gameSetter game;

	createPlayer gracz;
	createPlayer gracz2;
	gracz2.minRow = 11;
	gracz2.maxRow = 20;

	game.players[0] = gracz;
	game.players[1] = gracz2;

	char command[commandLength];


	while (cin >> command) {
		if (strcmp(command, "[state]") == 0) {
			stateCommands(game);
		}
		if (strcmp(command, "[playerA]") == 0) {
			playerCommands(game,1);
		}
		if (strcmp(command, "[playerB]") == 0) {
			playerCommands(game,2);
		}
		if (strcmp(command, "exit") == 0) {
			return 0;
		}
		if (strcmp(command, "wypisz") == 0) {
			cout << endl;
			for (int i = 0; i < 2; i++) {
				cout << "Player " << i << ": ";
				for (int j = 3; j >= 0; j--) {
					cout << game.players[i].fleet[j] << " ";

				}
			}
			cout << endl;
		}

	}
	int n;
	cin >>n;
	return 0;
}


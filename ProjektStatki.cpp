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
			char let = 'X';
			cin >> let;
			game.nextPlayer(let);
		}
		if (strcmp(command2, "BOARD_SIZE") == 0) {
			game.setBoardSize();
		}
		if (strcmp(command2, "INIT_POSITION") == 0) {
			game.initPosition();
		}
		if (strcmp(command2, "REEF") == 0) {
			game.createReef();
		}
		if (strcmp(command2, "SHIP") == 0) {
			game.addShip();
		}
		if (strcmp(command2, "EXTENDED_SHIPS") == 0) {
			game.extendedShips = 1;
		}
	}
}

void playerCommands(gameSetter& game, int playerIDs) {
	char command2[commandLength];
	while (cin >> command2) {
		if (strcmp(command2, "[playerA]") == 0 || strcmp(command2, "[playerB]") == 0) {
			game.players[playerIDs - 1].restartAvalibleMoves();
			game.nextPlayer();
			break;
		}
		if (strcmp(command2, "PLACE_SHIP") == 0) {
			game.players[playerIDs - 1].addShip(game.returnBoard(),0,game.reefs,game.reefsCount);
		}
		if (strcmp(command2, "SHOOT") == 0) {
			game.shoot(playerIDs);
			game.isThereAWinner();
		}
		if (strcmp(command2, "MOVE") == 0) {
			game.players[playerIDs - 1].moveShip(game.reefs,game.reefsCount,game.returnBoard());
		}
		if (strcmp(command2, "WYPISZ") == 0) {
			game.players[playerIDs - 1].displayShips();
		}
		if (strcmp(command2, "testtt") == 0) {
			game.players[playerIDs - 1].testtest(game.returnBoard());
		}
	}
}


int main()
{
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
			playerCommands(game, 1);
		}
		if (strcmp(command, "[playerB]") == 0) {
			playerCommands(game, 2);
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

	return 0;
}


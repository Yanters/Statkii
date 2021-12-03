#pragma once
#include "player.h"



class gameSetter {
	public:
		void displayMap();
		void displayPlayersInfo();
		void setFleet();
		void nextPlayer();
		void isThereAWinner();
		void shoot(int idGracza);
		void setBoardSize();
		int gameSizeX = 10;
		int gameSizeY = 21;
		int move = 0;

		createPlayer players[2];
};


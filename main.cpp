#include "game.h"

int main(){
	srand((unsigned)time(NULL));

	SDGame* game = new SDGame;
	game->play();

	delete game;
	//system("pause");
	return 0;
}
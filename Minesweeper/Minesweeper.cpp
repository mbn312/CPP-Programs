#include "Minesweeper.h"

//main function used to test the project
int main() {
	int x, y;
	Minesweeper game;
	char r;
	cout << endl;
	//loops until the user hits a bomb or wins the game
	while (game.getGameOver() == false) {
		cout << "\tx-position = ";
		cin >> x;
		game.setX(x);
		cout << "\ty-position = ";
		cin >> y;
		game.setY(y);
		cout << endl;
		game.startTurn();
		//when the game is over prints out the result and starts a new game if the user chooses to do so
		if(game.getGameOver() == true) {
			game.getResult();
			cout << "\tStart new game?[Y/N]: ";
			cin >> r;
			if(r == 'Y' || r == 'y') {
				cout << string(100, '\n' );
				game.newGame();
			}
		}
	}
	return 0;
}
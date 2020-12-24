#include "Poker.h"

int main() {
	int numPlayers;
	string name;
	vector<Player> list;
	//loops until the user is in the correct range
	do{
	cout << "Enter Number Of Players (2-7)? ";
	cin >> numPlayers;
	}while(numPlayers < 2 || numPlayers > 7);
	
	Game game(numPlayers);
	//for loop to enter all the players information in
	for(int i = 0; i < numPlayers; i++) {
		cout << "Enter player name: ";
		cin >> name;
		Player nPlayer(name);
		game.addPlayer(nPlayer);
	}

	game.playRound();
	return 0;
}
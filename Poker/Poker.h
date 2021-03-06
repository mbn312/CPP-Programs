#ifndef POKER_H_
#define POKER_H_
#include <vector>
#include "Deck.h"
#include "Player.h"
#include <string>
#include <limits>

class Game {
private:
	Deck deck;
	vector<Player> players;
	int count = 0;
public:
	Game(int numPlayers) {
		deck.shuffle();
	}

	void addPlayer(Player p) {
		players.push_back(p);
	}

	Deck getDeck() {
		return deck;
	}

	//deals cards to all the users and calculates the outcomes of the hands
	void dealCards() {
		for (int i = 0; i < players.size(); i++) {
			for (int x = 0; x < 5; x++) {
				players.at(i).addCard(deck.getDeck().at(count++));
			}
			players.at(i).calculateOutcome();
		}
	}

	//checks the outcomes to see how is the winner
	Player getWinner() {
		Player winner = players.at(0);
		for (int i = 1; i < players.size(); i++) {
			if (players.at(i).getOutcome() == winner.getOutcome()) {
				if(players.at(i).getHigh() > winner.getHigh()) {
					winner = players.at(i);
				}
			} else if (players.at(i).getOutcome() > winner.getOutcome()) {
				winner = players.at(i);
			}
		}
		return winner;
	}


	void printHand(int i) {
			cout << "\n" << players.at(i).getName() << "'s hand:" << endl;
			for (int x = 0; x < 5; x++) {
				players.at(i).getHand().at(x).printName();
			}
			players.at(i).calculateOutcome();
	}

	void replaceCards(int i) {
		vector<int> index;
		int input;
		int numReplace;

		cout<< "\n" << players.at(i).getName()<< " enter number of cards to replace: ";
		cin >> numReplace;
		while(numReplace > 0) {
			cout << "\nEnter position to replace(Starting from 1): ";
			cin >> input;
			index.push_back(input-1);
			numReplace--;
		}
		for(int x = 0; x < index.size(); x++) {
			players.at(i).replaceCard(index.at(x),deck.getDeck().at(count++));
		}
	}

	void printAllOutcomes() {
		for(int i = 0; i < players.size(); i++) {
			printHand(i);
			players.at(i).printOutcome();
		}
	}

	void playRound() {
		dealCards();
		string ready;
		for(int i = 0; i < players.size(); i++) {
			cout << "\n\n" << string(60,'-') << endl;

			cout << "\n" << players.at(i).getName()<< "'s Turn. Type 'Ready' to continue.\n";
			cin >> ready;
			cout << endl;

			printHand(i);
			replaceCards(i);
		}

		printAllOutcomes();
		cout << "\n" << getWinner().getName() << " is the winner!!!!!!!" << endl;
		deck.shuffle();
		count = 0;
	}




};

#endif /* POKER_H_ */
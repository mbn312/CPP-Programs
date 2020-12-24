#ifndef DECK_H_
#define DECK_H_
#include <vector>
#include "Card.h"
#include <cstdlib>
#include <ctime>

using namespace std;

class Deck {
private:
	vector<Card> deck;
public:
	//constructor creates 52 cards and places it in the deck
	Deck() {
		for(int i =TWO; i <= ACE ; i++) {
			for(int x = SPADES; x <= HEARTS; x++) {
				Card insert(x,i);
				deck.push_back(insert);
			}
		}
	}

	//uses srand to randomly change 52 cards positions
	void shuffle() {
		srand(time(0));
		for(int i = 0 ; i < 100; i++) {
			int random = (rand() % 51) + 1;
			int rand2 = (rand() %51) + 1;
			Card temp = deck.at(random);
			deck.at(random) = deck.at(rand2);
			deck.at(rand2) = temp;
		}
	}

	//returns deck
	vector<Card> getDeck() {
		return deck;
	}

	void printDeck() {
		for(int i =0; i< 52; i++) {
			deck.at(i).printName();
		}
	}


};

#endif /* DECK_H_ */
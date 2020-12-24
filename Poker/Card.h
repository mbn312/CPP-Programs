#ifndef CARD_H_
#define CARD_H_
#include <iostream>
#include <string>

using namespace std;

//enum for the type of suits
enum Suit {
	SPADES,CLUBS,DIAMONDS,HEARTS
};

//enum for the ranks of the cards
enum Rank {
	TWO = 2, THREE = 3, FOUR = 4, FIVE = 5, SIX = 6, SEVEN = 7, EIGHT = 8, NINE = 9, TEN = 10, JACK = 11,QUEEN = 12, KING = 13, ACE = 14
};

class Card {
private:
	int suit;
	int rank;

public:
	//constructors to create cards
	Card () {
		suit = SPADES;
		rank = TWO;
	}
	Card(int s, int r) {
		suit = s;
		rank = r;
	}

	//getter and setter methods to access private variables
	void setRank(int r) {
		rank = r;
	}

	int getSuit() {
		return suit;
	}

	int getRank() {
		return rank;
	}

	//uses switch case to print out the names of the cards
	void printName() {
		switch(rank) {
		case(JACK):
				cout << "Jack";
				break;
		case(QUEEN):
		cout << "Queen";
				break;
		case(KING):
		cout << "King";
				break;
		case(ACE):
		cout << "Ace";
				break;
		default:
			cout << rank;
			break;
		}

		switch(suit) {
		case(SPADES):
		cout << " of Spades" << endl;
				break;
		case(CLUBS):
		cout <<" of Clubs"<< endl;
				break;
		case(DIAMONDS):
		cout <<" of Diamonds"<< endl;
				break;
		case(HEARTS):
		cout <<" of Hearts"<< endl;
				break;
		}

	}


};

#endif /* CARD_H_ */
#ifndef PLAYER_H_
#define PLAYER_H_
#include <vector>
#include "Deck.h"


using namespace std;
//enum for the possible outcomes
enum Outcome {
	NOPAIR,ONEPAIR,TWOPAIR,THREEOFKIND,STRAIGHT,FLUSH,FULLHOUSE,FOUROFKIND,STRAIGHTFLUSH,ROYALFLUSH
};

class Player {
Outcome currentOutcome;
vector<Card> hand;
string name;
int high;
public:
	Player(string n) {
		currentOutcome = NOPAIR;
		name = n;
		high = 0;
	}

	Outcome getOutcome() {

		return currentOutcome;
	}

	int getHigh() {
		return high;
	}

	vector<Card> getHand() {
		return hand;
	}

	//adds card to hand
	void addCard(Card card) {
		hand.push_back(card);
	}

	//replaces card at inputted position in hand
	void replaceCard(int position, Card card) {
		hand.at(position) = card;
	}

	string getName() {
		return name;
	}

	//checks to see if all the suits are the same
	bool isFlush() {
		bool result = true;
		for (int i = 1; i < 5; i++) {
			if (getHand().at(i).getSuit()
					!= getHand().at(i - 1).getSuit()) {
				result = false;
				i = 5;
			}
		}
		return result;
	}

	//checks to see if the numbers are in order
	bool isStraight() {
		bool result = true;
		sort();
		for (int i = 1; i < 5; i++) {
			if (getHand().at(i).getRank()
					!= (getHand().at(i - 1).getRank() + 1)) {
				result = false;
			}
		}
		return result;
	}

	//checks to see there is multiple of a kind
	int getLikeKind() {
		vector<int> temp(5, 0);
		temp.at(0) = getHand().at(0).getRank();
		int result = 0;
		int count;

		for(int y=0; y < 5; y++) {
			count = 0;
			for(int z = y+1; z < 5; z++) {
				if(getHand().at(y).getRank() == getHand().at(z).getRank()) {
					if(count == 0 || getHand().at(y).getRank() > high) {
						high = getHand().at(y).getRank();
					}
					count++;
			}
			}
			if(count > result) {
				result = count;
			}
		}
		return result;
	}


	//checks to see if you have all the royals
	bool testRoyal() {
		int sum = 0;
		for(int i = 0; i < 5; i++) {
			sum += getHand().at(i).getRank();
		}
		if(sum == 60) {
			return true;
		} else {
			return false;
		}
	}

	//checks to see if you have multiple pairs
	bool testMultPairs() {
		vector<Card> temp = hand;
		int test = 100;
		int r = 0;
		for(int i = 0; i < 5; i++) {
			for(int x = i+1; x < 5; x++) {
				if(temp.at(i).getRank() == temp.at(x).getRank()) {
					r++;
					temp.at(i).setRank(test--);
					temp.at(x).setRank(test--);
					x=5;
				}
			}
		}
		if(r > 1) {
			return true;
		} else {
		return false;
		}
	}

	//checks your cards to see what your outcome is
	void calculateOutcome() {
		sort();
		high = hand.at(4).getRank();
		if(isFlush()) {
			if(testRoyal()) {
				currentOutcome =ROYALFLUSH;
			} else if(isStraight()) {
				currentOutcome =STRAIGHTFLUSH;
			} else {
				currentOutcome =FLUSH;
			}
		} else if (isStraight()) {
			currentOutcome =STRAIGHT;
		} else {
			int temp = getLikeKind();
			if(temp == 3) {
				currentOutcome =FOUROFKIND;
			} else if(temp == 2) {
				if(testMultPairs()) {
					currentOutcome =FULLHOUSE;
				} else {
					currentOutcome =THREEOFKIND;
				}
			} else if(temp == 1) {
				if(testMultPairs()) {
					currentOutcome =TWOPAIR;
				} else {
					currentOutcome =ONEPAIR;
				}
			} else {
				currentOutcome =NOPAIR;
			}
		}
	}

	//prints out the outcome
	void printOutcome(){
		string output;
		switch(currentOutcome) {
		case(NOPAIR):
				output = "No Pair";
				break;
		case(ONEPAIR):
				output = "One Pair";
				break;
		case(TWOPAIR):
				output = "Two Pair";
				break;
		case(THREEOFKIND):
				output = "Three Of A Kind";
				break;
		case(STRAIGHT):
				output = "Straight";
				break;
		case(FLUSH):
				output = "Flush";
				break;
		case(FULLHOUSE):
				output = "Full House";
				break;
		case(FOUROFKIND):
				output = "Four Of A Kind";
				break;
		case(STRAIGHTFLUSH):
				output = "Straight Flush";
				break;
		case(ROYALFLUSH):
				output = "Royal Flush";
				break;
		}

		cout << getName() << " has a " << output  << "." << endl;
	}

	//sorts a users hand
	void sort() {
		vector<Card> sorter(5);
		sorter.insert(sorter.begin(),hand.at(0));
		for(int i = 1; i < 5; i++) {
			for(int x = 0; x <= i; x++) {
				if(hand.at(i).getRank() < sorter.at(x).getRank() || x == i) {
					sorter.insert(sorter.begin()+x,hand.at(i));
					x=5;
				}
			}
		}
		hand = sorter;
	}

};

#endif /* PLAYER_H_ */
#ifndef RYGGAME_H_
#define RYGGAME_H_
#include <iostream>
#include <string>
#include <ctime>

using namespace std;

class Game {
private:
	int correct;
	int red = 0;
	int yellow = 0;
	int green = 0;
public:
	//constructor makes sure that a new random correct number is chosen for each game
	Game() {
		srand(time(0));
		correct = rand() % 899 + 100;
		//correct = 123;
		//cout << correct << endl;
	}

	//getter method that returns the correct number
	int getCorrect() {
		return correct;
	}

	//sets the red, yellow, and green to the correct results
	void setRGY(int guess, int correct) {
		//calls on the reset method so that the results are not added on to the previous ones
		reset();

		int c[3];
		int g[3];

		//loops to get individual digits of the guess and correct variables to make it easier to compare
		for (int i = 2; i >= 0; i--) {

			c[i] = correct % 10;
			g[i] = guess % 10;
			correct = correct / 10;
			guess = guess / 10;

		}

		//loops to compare the digits of the two variables
		for (int y = 0; y < 3; y++) {
			if (g[y] == c[y]) {
				green++;
			} else {
				red++;
				for (int z = 0; z < 3; z++) {
					//if digit is same as any of the correct digits(besides on spaces that are green) switches from red to yellow
					if (g[y] == c[z] && g[z] != c[z]) {
						yellow++;
						red--;
						//sets z to 3 to exit loop when a yellow is found;
						z = 3;
					}
				}
			}
		}
	}

	//prints out the results of a users guess
	void result(int guess) {
		//calls on the setRGY function to get set the number of reds, yellows, and greens that there are
		setRGY(guess, correct);

		cout << endl << "You Have: " << red << " red" << endl << "\t" << green
				<< " green" << endl << "\t" << yellow << " yellow" << endl;

	}

	//resets variables red, green, and yellow to zero
	void reset() {
		red = 0;
		green = 0;
		yellow = 0;
	}
};

#endif /* RYGGAME_H_ */

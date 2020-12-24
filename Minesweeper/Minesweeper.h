#ifndef MINESWEEPER_H_
#define MINESWEEPER_H_

#include <cstdlib>
#include <ctime>
#include <iostream>
#include <string>
#include <vector>

using namespace std;
//used give more functionality to the itAdjacent method
enum Command {
	BUILD, ZERO, NONZERO
};

class Minesweeper {
private:
	vector<int> dim;
	vector<vector<char>> display;
	vector<vector<char>> result;
	vector<int> cur;
	vector<vector<int>> bombs;
	bool gameOver, win;
	unsigned int turnCounter;
public:
	//uses a default construct to start the game
	Minesweeper() {
		dim = vector<int>(2, 5);
		cur = vector<int>(2);
		//newGame function sets up a new game
		newGame();
	}

	//randomly generates locations for the bombs
	void createBombs() {
		srand(time(NULL));
		//number of bombs equal to the average of the number or rows and columns
		int num = (dim[0] + dim[1]) / 2;
		bombs.assign(num, vector<int>(2));
		for (unsigned int b = 0; b < bombs.size(); b++) {
			cur[0] = (rand() % dim[0]);
			cur[1] = (rand() % dim[1]);
			bombs.at(b) = cur;
			//if the location already has a bomb it chooses a new one
			if (result[cur[0]][cur[1]] != 'B') {
				result[cur[0]][cur[1]] = 'B';
			} else {
				b--;
			}
		}
		//calls on the itAdjacent method to set the number of adjacent bombs to each square
		for (unsigned int i = 0; i < bombs.size(); i++) {
			itAdjacent(bombs.at(i).at(0), bombs.at(i).at(1), BUILD);
		}
	}

	//iterates through the all the adjacent squares of given coordinates and completes requested command
	void itAdjacent(int r, int c, Command d) {
		for (int i = -1; i < 2; i++) {
			if ((r + i) >= 0 && (r + i) < dim[0]) {
				for (int x = -1; x < 2; x++) {
					if ((c + x) >= 0 && (c + x) < dim[1]
							&& isdigit(result.at(r + i).at(c + x))) {
						switch (d) {
						case ZERO:
							if (result.at(r + i).at(c + x) != display.at(r + i).at(c + x)) {
								display.at(r + i).at(c + x) = result.at(r + i).at(c + x);
								turnCounter++;
								//if the adjacent value is zero, it will recursively call function to show the adjacent values for these coordinates.
								if (result.at(r + i).at(c + x) == '0')  {
									itAdjacent(r + i,c + x,ZERO);
								}
							}
							break;
						case BUILD:
							cur[0] = (int) (result.at(r + i).at(c + x));
							cur[0]++;
							result.at(r + i).at(c + x) = cur[0];
							break;
						}
					}
				}
			}
		}
	}

	//checks to see if the inputed x-coordinate is valid and sets it to variable
	void setX(int x) {
		while (x > dim[1] || x < 1) {
			cout << "\n\tERROR: Entered position is out of bounds." << endl;
			cout << "\tInput must be between 1 and " << dim[1]
					<< ". Please try again." << endl;
			cout << "\tx-position = ";
			cin >> x;
		}
		cur[1] = (x - 1);
	}

	//checks to see if the inputed y-coordinate is valid and sets it to variable
	void setY(int y) {
		while (y > dim[0] || y < 1) {
			cout << "\n\tERROR: Entered position is out of bounds." << endl;
			cout << "\tInput must be between 1 and " << dim[0]
					<< ". Please try again." << endl;
			cout << "\ty-position = ";
			cin >> y;
		}
		cur[0] = (y - 1);
	}

	//prints out the board with hidden values
	void printDisplay() {
		cout << "\n\t" << string(60, '-') << "\n" << endl;
		for (int r = 0; r < dim[0]; r++) {
			cout << "\t";
			for (int c = 0; c < dim[1]; c++) {
				cout << display.at(r).at(c) << " ";
			}
			cout << endl;
		}
	}

	//checks to see if there is a bomb at user inputed coordinate or if the user wins the game and reacts accordingly
	void startTurn() {
		if (result.at(cur[0]).at(cur[1]) == 'B') {
			gameOver = true;
		} else {
			if(display.at(cur[0]).at(cur[1]) != result.at(cur[0]).at(cur[1])) {
			display.at(cur[0]).at(cur[1]) = result.at(cur[0]).at(cur[1]);
			turnCounter++;
			if(result.at(cur[0]).at(cur[1]) == '0') {
				//if it is zero, it will iterate adjacent coordinates to display values
				itAdjacent(cur[0],cur[1],ZERO);
			}
			}
			printDisplay();
		}
		//if only the bombs are left, the user wins
		if (turnCounter == ((dim[0] * dim[1]) - bombs.size())
				&& gameOver == false) {
			gameOver = true;
			win = true;
		}
	}

	//returns whether or not the game has ended
	bool getGameOver() {
		return gameOver;
	}

	//prints out the result of the game and display the board with all the values
	void getResult() {
		cout << "\n\t" << string(60, '-') << "\n" << endl;
		if (win == true) {
			cout << "\n\tCongratulations! You Win!" << endl;
		} else {
			cout << "\n\tYou Lose. Better Luck Next Time." << endl;
		}
		printBoard();
		cout << endl;
	}

	//asks user for board dimensions and starts a new game
	void newGame() {
		char z;
		printTitle();
		cout << "\tCurrent Size: " << dim[0] << "x" << dim[1] << endl;
		cout << "\tChange Dimensions?[Y/N]: ";
		cin >> z;
		if (z == 'Y' || z == 'y') {
			cout << "\n\t# of Rows: ";
			cin >> dim[0];
			cout << "\t# of Columns: ";
			cin >> dim[1];
		} else {
			cout << endl;
		}
		reset();
		printDisplay();
	}

	//resets the boards, and randomizes the bombs
	void reset() {
		display.assign(dim[0], vector<char>(dim[1], '*'));
		result.assign(dim[0], vector<char>(dim[1], '0'));
		createBombs();
		gameOver = false;
		win = false;
		turnCounter = 0;
	}

	//prints out the boards with all the values shown
	void printBoard() {
		cout << endl;
		for (int r = 0; r < dim[0]; r++) {
			cout << "\t";
			for (int c = 0; c < dim[1]; c++) {
				cout << result.at(r).at(c) << " ";
			}
			cout << endl;
		}
	}

	void printTitle() {
		cout << "\t" << string(60, '=') << "\n" << endl;
		cout << "\t\tMinesweeper\n" << endl;
		cout << "\t" << string(60, '=') << "\n" << endl;
	}
};

#endif /* MINESWEEPER_H_ */
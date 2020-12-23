#include "RYGGame.h"
#include <iostream>
#include <string>

using namespace std;

int main() {
	Game game;
	int guess;
	cout << "=======================================================================================================" << endl
		<< "RYG Guessing Game" << endl 
		<< "-------------------------------------------------------------------------------------------------------" << endl
		<< "You are trying to guess a three digit number," <<endl
		<< "Green: A digit is in the number and in the correct place." <<endl
		<< "Yellow: A digit is in the number and not in right place" <<endl
		<< "Red: A digit is not in the number" << endl
		<< "The number of red, yellow and green digits will be returned after each guess." << endl
		<< "=======================================================================================================" << endl;

		
	cout << endl << "Enter a guess:" << endl;
	cin >> guess;

	//loops until the user input is correct
	while (guess != game.getCorrect()) {
		//calls the result function from the Game class
		game.result(guess);
		cout << endl << "Enter in another guess:" << endl;
		cin >> guess;
	}


	cout << endl << "CONGRATULATIONS, YOU ARE CORRECT!" << endl;
	return 0;
}


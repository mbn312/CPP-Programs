#include <iostream>
#include <string>
#include <iterator>
#include <map>
#include <limits>
#include <fstream>

using namespace std;

int main() {
	ifstream file;
	string filename, word;
	char x = ' ';
	bool first = false;
	bool n;
	map<string, int> wordCount;
	map<string, int>::iterator itr;
    cout << string(100,'=') << endl;
    cout << "\tWord Counter" << endl;
    cout << string(100, '-') << endl;
    cout << "\n\tProgram takes in an input file and returns all of the words \n\tand the number of occurences of each word.\n" << endl;
    cout << string(100, '=') << endl;
	cout << "\n\tEnter file name: ";
	cin >> filename;

	file.open(filename);
	while (!file.eof() && x != -1) {
		n = true;
		x = file.get();
		while (!iswspace(x) && !ispunct(x) && x != -1) {
			if (isupper(x)) {
				x = tolower(x);
			}
			word = word + x;
			x = file.get();
		}
		if (first == false) {
			first = true;
			wordCount.insert(make_pair(word, 1));
		} else {
			for (itr = wordCount.begin(); itr != wordCount.end(); ++itr) {
				if (word == (*itr).first) {
					((*itr).second)++;
					n = false;
				}
			}
			if (n == true && word.size() != 0) {
				wordCount.insert(wordCount.end(), { word, 1 });
			}
		}
		word.clear();
	}
	file.close();


	cout << "\n\tWORD" << "\t\t" << "COUNT\n" << endl;

	for (itr = wordCount.begin(); itr != wordCount.end(); ++itr) {
		if((*itr).first.size() < 8) {
		cout << "\t" << (*itr).first << "\t\t" << (*itr).second << endl;
		} else {
			cout << "\t" << (*itr).first << "\t" << (*itr).second << endl;
		}
	}

    cout << "\n\tPress ENTER to close.";
    cin.sync();
    cin.get();

	return 0;
}
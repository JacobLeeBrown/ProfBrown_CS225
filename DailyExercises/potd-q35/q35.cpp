#include <iostream>
#include <fstream>
using namespace std;

int main () {
	ofstream myoutfile;
	myoutfile.open ("text.txt");
	myoutfile << "Writing this to a file.\n";
	myoutfile << "I like big butts and I cannot lie.\n";
	myoutfile.close();

	ifstream myinfile;
	myinfile.open("text.txt");
	string word;
	if (myinfile.is_open()) {
		/* Reads a line from `myinfile` into `word` until the file ends. */
		while (getline(myinfile, word)) {
			cout << word << endl;
		}
	}
	myinfile.close();
  return 0;
}
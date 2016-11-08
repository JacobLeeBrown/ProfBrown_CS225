#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <algorithm>
using namespace std;

int main () {
	ifstream myinfile;
	myinfile.open("text.txt");
	string line;
	if (myinfile.is_open()) {
		/* Reads a line from `myinfile` into `word` until the file ends. */
		while (getline(myinfile, line)) {
			string temp = line;
    		std::transform(temp.begin(), temp.end(), temp.begin(), ::tolower);
			if(temp.find("purple") != std::string::npos)
			{
				cout << line << endl;
			}
		}
	}
	myinfile.close();
  return 0;
}
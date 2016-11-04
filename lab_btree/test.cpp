#include <vector>
#include <iostream>
#include <string>
#include <sstream>
#include <cstring>
#include <stdexcept>

#include "btree.h"

using namespace std;

int main()
{
	vector<int> data = {};
	cout << "Please enter keys (end list with -1): " << endl;
	int curVal;
	cin >> curVal;
	while(curVal != -1)
	{
		data.push_back(curVal);
		cin >> curVal;
	}
	
	// Prints "1" just fine, meaning the damn vector is empty
	// cout << data.empty() << endl;

	cout << "Please enter the value you would insert: " << endl;
	int search;
	cin >> search;

	int idx = (int)insertion_idx(data, search);
	cout << "Should insert " << search << " at index: " << idx << endl;
	return 0;
}
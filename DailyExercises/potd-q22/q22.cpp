#include <iostream>
#include <string>
#include <map>

using namespace std;

int main()
{
	char str[256];
	cout << "Please enter your phrase: " << endl;
	cin.getline(str, 256);
	map<int, int> m;
	int i = 0;
	while(str[i] != '\0')
	{
		if(str[i] != ' ')
		{
			int letter = str[i];
			// cout << str[i] << ", " << letter << endl;
			if(letter < 'a')
			{
				// cout << "Test" << endl;
				letter += 32;
			}
			m[letter]++;
			// cout << "Incremented " << (char)letter << " of current value " << m[letter] << endl;
		}
		i++;
	}
	
	int curMax = 0;
	int modeIndex = 0;
	for(int i = 97; i < 123; i++)
	{
		if(m[i] > curMax)
		{
			curMax = m[i];
			modeIndex = i;
		}
	}
	char modeLetter = (char)(modeIndex);
	
	cout << "The most frequent character is " << modeLetter << endl;
}
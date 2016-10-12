#include <iostream>
#include <string>
using namespace std;

int main()
{
	string word;
	do{
		cout << "Please enter a word: ";
		cin >> word;
		cout << endl;
		if(word[0] == 'q' || word[0] == 'Q')
		{
			continue;
		}
		else if(word[0] == 'a' ||
				word[0] == 'e' ||
				word[0] == 'i' ||
				word[0] == 'o' ||
				word[0] == 'u' ||
				word[0] == 'y' ||
				word[0] == 'A' ||
				word[0] == 'E' ||
				word[0] == 'I' ||
				word[0] == 'O' ||
				word[0] == 'U' ||
				word[0] == 'Y')
		{
			word = word + "ay";
		}
		else
		{
			size_t i = 0;
			while(i < word.length())
			{
				word = word + word[0];
				word.erase(0,1);
				if(	word[0] == 'a' ||
					word[0] == 'e' ||
					word[0] == 'i' ||
					word[0] == 'o' ||
					word[0] == 'u' ||
					word[0] == 'y' ||
					word[0] == 'A' ||
					word[0] == 'E' ||
					word[0] == 'I' ||
					word[0] == 'O' ||
					word[0] == 'U' ||
					word[0] == 'Y')
				{
					break;
				}
				i++;
			}
			word = word + "ay";
		}
		cout << word << endl;
	}while(word[0] != 'q');
	return 0;
}
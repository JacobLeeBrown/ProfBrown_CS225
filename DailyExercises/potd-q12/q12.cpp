#include <iostream>
#include <cmath>
#define PI 3.1415926

using namespace std;

int main()
{
	char input = 'a';
	cout << "Enter \"s\" or \"c\":" << endl;
	cin >> input;
	while(input != 'q' && input != 's' && input != 'c')
	{
		cout << "Invalid input. Please enter \"s\" or \"c\":" << endl;
		cin >> input;
	}
	if(input == 'q')
	{	
		return 0;
	}
	
	int val;

	cout << "Enter a number:" << endl;
	cin >> val;
	
	if(input == 's')
	{
		cout << "Sin(" << val << ") = " << sin(val*PI/180) << endl;
	}
	else if(input == 'c')
	{
		cout << "Cos(" << val << ") = " << cos(val*PI/180) << endl;
	}
	return 0;
}
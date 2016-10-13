#include <iostream>
#include <string>

using namespace std;

int main()
{
	int n;
	cin >> n;
	int** array = new int*[n*n];
	for(int i = 0; i < n; i++)
	{
		for(int j = 0; j < n; j++)
		{
			array[i*n + j] = new int(i + j);
			cout << (i+j) << " ";
		}
		cout << endl;
	}
	
	for(int k = 0; k < n*n; k++)
	{
		delete array[k];
	}
	delete[] array;
	return 0;
}
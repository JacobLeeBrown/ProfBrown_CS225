#include <iostream>
using namespace std;

int main()
{
	int *p = NULL;
	// the loop will try to access a null pointer, resulting in a seg fault
	for(int i = 0; i < 10; i++)
	{
		p[i] = 1;
	}
	return 0;
}
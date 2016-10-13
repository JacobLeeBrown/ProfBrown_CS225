#include <cmath>
#include <iostream>
using namespace std;

int get_length(int array[])
{
	int i = 0;
	while(array[i] >= 0)
	{
		i++;
	}
	i++;
	return i;
}

double* raise(int array[], int power)
{
	int length = get_length(array);
	double *vals = new double[length];
	for(int i = 0; i < length-1; i++)
	{
		vals[i] = pow(array[i], power);
	}
	vals[length-1] = array[length-1];
	return vals;
}
/*
int main()
{
	int array[] = {1, 2, 3, 4, -1};
	int power = 2;
	double *newVals = raise(array, 2);
	for(int i = 0; i < 5; i++)
	{
		cout  << array[i] << "^" << power << " = " << newVals[i] << endl;
	}
	return 0;
}*/
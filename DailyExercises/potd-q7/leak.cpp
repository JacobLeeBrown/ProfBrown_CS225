int main()
{
	int *p = new int[3];
	// it will leak memory because it both assigns values to indices that don't exist
	// and it does not delete the memory when it is done
	for(int i = 0; i < 10; i++)
	{
		p[i] = 1;
	}
	return 0;
}
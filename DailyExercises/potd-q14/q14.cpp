#include <iostream>
using namespace std;

class square
{
	private:
		double * length;
		string name;
	public:
		square()
		{
			name = "mysquare";
			length = new double(2.0);	
		}
		square(square const &other)
		{
			name = other.name;
			//cout << "test" << endl;
			length = other.length;
			cout << "I am copying!" << endl;
		}
		~square()
		{
			delete length;
		}
};

int main()
{
	square *s = new square();
	cout << "I am copying!" << endl;	// mo\thod 1: just print it
	square  jbb(*s);					// method 2: use the copy construo
	return 0;
}
#include <iostream>
using namespace std;

class Food
{
	private:
		string name;
		int quantity;
	public:
		Food()
		{
			name = "pizza";
			quantity = 69;
		}
		void setName(string newName)
		{
			name = newName;
		}
		string getName()
		{
			return name;
		}
		void setQuantity(int newQuantity)
		{
			quantity = newQuantity;
		}
		int getQuantity()
		{
			return quantity;
		}
};

void increaseQuantity(Food *f)
{
	int amount = (f->getQuantity());
	amount++;
	f->setQuantity(amount);
}

int main()
{
	Food *rahul = new Food();
	cout << "Rahul has " << rahul->getQuantity() << " slices of pizza!" << endl;
	increaseQuantity(rahul);
	cout << "Rahul has " << rahul->getQuantity() << " slices of pizza!" << endl;
	
	return 0;
}
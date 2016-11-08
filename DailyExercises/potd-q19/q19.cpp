#include <iostream>
#include <string>
using namespace std;

class Food{
    private:
        string name;
        int quantity;
    public:
        Food();
        void setName(string newName);
        void setQuantity(int newQuantity);
        string getName();
        int getQuantity() const;
		bool operator>(const Food& other);
};

Food::Food(){name = "food"; quantity = 0;}
void Food::setName(string newName){name = newName;}
void Food::setQuantity(int newQuantity){quantity = newQuantity;}
string Food::getName(){return name;}
int Food::getQuantity() const {return quantity;}
bool Food::operator>(const Food& other)
{
	if(quantity > other.quantity)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void increaseQuantity(Food * food){
    (*food).setQuantity((*food).getQuantity() + 1);
}

template <class T>
T more(T a, T b)
{
	return (a > b ? a:b);
}

int main(){
    Food apples, oranges, greater;
    apples.setName("apples");
    apples.setQuantity(5);
    oranges.setName("oranges");
    oranges.setQuantity(3);
    greater = more<Food>(apples, oranges);
    cout << "We have more " << greater.getName() << endl;
    return 0;
}

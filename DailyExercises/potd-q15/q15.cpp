#include <iostream>
#include <string>
using namespace std;

class Square{
    private:
        string name;
        double * lengthptr;
    public:
        Square();
        Square(const Square & old);
        ~Square();
        void setName(string newName);
        void setLength(double newVal);
        string getName() const;
        double getLength() const;
		void print();
		Square & operator+(const Square & other);
		Square & operator=(const Square & other);
};

Square::Square(){
    name = "mysquare";
    lengthptr = new double;
    *lengthptr = 2.0;
}

void Square::setName(string newName){name = newName;}
void Square::setLength(double newVal){*lengthptr = newVal;}
string Square::getName() const {return name;}
double Square::getLength() const {return *lengthptr;}

Square::Square(const Square & other){
    cout << "I am copying!" << endl;
    name = other.getName();
    lengthptr = new double;
    *lengthptr = other.getLength();
}

Square::~Square(){
    delete lengthptr;
}

Square & Square::operator+(const Square & other)
{
	Square *addedSquare = new Square();
	addedSquare->name = this->name + other.name;
	*(addedSquare->lengthptr) = *lengthptr + *(other.lengthptr);
	return *addedSquare;
}

// We need to overload the assignment operator because it's
// 1. undefined for this class and
// 2. needed as part of the Big 3 (copy constructor, destructor, and assignment operator)
Square & Square::operator=(const Square & other)
{
	Square *newSquare = new Square(other);
	return *newSquare;
}

void Square::print()
{
	cout << "Name: " << name << "\nLength Ptr: " << lengthptr << "\nLength: " << 
		*lengthptr << "\n" << endl;
}

int main(){
    Square a;
	//a.print();
    Square b = a;
	//b.print();
    Square c(a);
	//c.print();
	//Square d = c + a;
	//c.print();
	//d.print();
    return 0;
}

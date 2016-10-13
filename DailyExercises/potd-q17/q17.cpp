#include <iostream>
using namespace std;

class Animal
{
	private:
		string animal_type;
	protected:
		string food_type;
	public:
		Animal()
		{
			animal_type = "cat";
			food_type = "fish";
		}
		Animal(string t, string f)
		{
			animal_type = t;
			food_type = f;
		}
		virtual ~Animal()
		{
			// nothing
		}
		string get_type()
		{
			return animal_type;
		}
		void set_type(string newType)
		{
			animal_type = newType;
		}
		string get_food()
		{
			return food_type;
		}
		void set_food(string newFood)
		{
			food_type = newFood;
		}
		virtual void print()
		{
			cout << "I am a " << animal_type << "." << endl;
		}
};

class Pet : public Animal
{
	private:
		string name;
		string owner_name;
	public:
		Pet():Animal()
		{
			name = "Fluffy";
			owner_name = "Cinda";
		}
		Pet(string a, string f, string n, string o):Animal(a, f)
		{
			name = n;
			owner_name = o;
		}
		string get_name()
		{
			return name;
		}
		void set_name(string newName)
		{
			name = newName;
		}
		string get_owner_name()
		{
			return owner_name;
		}
		void set_owner_name(string newOwner)
		{
			owner_name = newOwner;
		}
		void print()
		{
			Animal::print();
			cout << "My name is " << name << "." << endl;
		}
};

int main()
{
	Pet a;
	a.print();
	return 0;
}
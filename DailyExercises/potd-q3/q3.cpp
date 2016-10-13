#include <string>

using namespace std;

class Pet{
	// Variables will be private as to leave access to the methods only
	private:
		string name;
		int birth_year;
		string type;
		string owner_name;
	// Methods are public as to allow access and modification to the private variables
	public:
		Pet();
		string get_name();
		void set_name(string new_name);
		int get_birth_year();
		void set_birth_year(int new_birth_year);
		string get_type();
		void set_type(string new_type);
		string get_owner_name();
		void set_owner_name(string new_owner_name);
};

Pet::Pet()
{
	name = "Neil";
	birth_year = 1997;
	type = "monkey";
	owner_name = "Jacob";
}

string Pet::get_name()
{
	return name;
}
void Pet::set_name(string new_name)
{
	name = new_name;
}

int Pet::get_birth_year()
{
	return birth_year;
}
void Pet::set_birth_year(int new_birth_year)
{
	birth_year = new_birth_year;
}

string Pet::get_type()
{
	return type;
}
void Pet::set_type(string new_type)
{
	type = new_type;
}

string Pet::get_owner_name()
{
	return owner_name;
}
void Pet::set_owner_name(string new_owner_name)
{
	owner_name = new_owner_name;
}


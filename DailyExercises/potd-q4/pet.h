#ifndef _PET_H
#define _PET_H

#include <string>
using namespace std;

class Pet {
	public:
		// Constructors
		Pet();
		Pet(string iname, int ibirth_year, string itype, string iowner_name);
		// Other member functions
		void setName(std::string newName);
		void setBY(int newBY);
		void setType(std::string newType);
		void setOwnerName(std::string newName);
		string getName();
		int getBY();
		string getType();
		string getOwnerName();

	private:
		string name;
		int birth_year;
		string type;
		string owner_name;
};

#endif

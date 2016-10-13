#include "pet.h"

// Constructors
Pet::Pet()
{
	name = "Rover";
	birth_year = 2016;
	type = "dog";
	owner_name = "Cinda";
}

Pet::Pet(string iname, int ibirth_year, string itype, string iowner_name)
{
	name = iname;
	birth_year = ibirth_year;
	type = itype;
	owner_name = iowner_name;
}

void Pet::setName(std::string newName) {
  name = newName;
}

void Pet::setBY(int newBY) {
  birth_year = newBY;
}

void Pet::setType(std::string newType) {
  type = newType;
}

void Pet::setOwnerName(std::string newName) {
  owner_name = newName;
}

std::string Pet::getName() {
  return name;
}

int Pet::getBY() {
  return birth_year;
}

std::string Pet::getType() {
  return type;
}

std::string Pet::getOwnerName() {
  return owner_name;
}

/**
 * @file room.cpp
 */

#include <iostream>
#include "room.h"

Room::Room()
    : capacity(0), count(0), max_letters(26), letters(NULL), letterCount(0)
{
}

Room::Room(const string& init_name, int init_capacity)
    : name(init_name),
      capacity(init_capacity),
      count(0),
      max_letters(26),
      letterCount(0)
{
    letters = new Letter[max_letters];
}

Room::Room(const Room& other)
{
    copy(other);
}

Room& Room::operator=(const Room& other)
{
    if (this != &other) {
        clear();
        copy(other);
    }
    return *this;
}

Room::~Room()
{
    clear();
}

void Room::addLetter(const Letter& L)
{
    letters[letterCount++] = L;
    count += L.count;
}

int Room::spaceRemaining()
{
    return capacity - count;
}

void Room::print()
{
    cout << name << " (" << count << "/" << capacity << "):";
    for (int L = 0; L < letterCount; L++)
        cout << " " << letters[L].letter;
    cout << endl;
}

void Room::clear()
{
	if (letters != NULL)
        delete[] letters;
}

void Room::copy(const Room& other)
{
    name = other.name;
    capacity = other.capacity;
    count = other.count;
    letterCount = other.letterCount;
    letters = new Letter[26];
	for(int i = 0; i < letterCount; i++)
	{
		letters[i] = other.letters[i];
	}
}

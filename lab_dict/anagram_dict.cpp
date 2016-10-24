/**
 * @file anagram_dict.cpp
 * Implementation of the AnagramDict class.
 *
 * @author Matt Joras
 * @date Winter 2013
 */

#include "anagram_dict.h"

#include <algorithm> /* I wonder why this is included... This lab blows */
#include <fstream>
#include <iostream>

using std::string;
using std::vector;
using std::ifstream;
using std::cout;
using std::endl;

/**
 * Debugging function that prints out a vector
 */
void print_vector(vector<string> list)
{
	for(auto str : list)
	{
		cout << str << ", ";
	}
	cout << endl;
}

/**
 * Constructs an AnagramDict from a filename with newline-separated
 * words.
 * @param filename The name of the word list file.
 */
AnagramDict::AnagramDict(const string& filename)
{
	// turn the file into a vector of all of the words
	vector<string> words = file_to_vector(filename);
	// for every word in the vector
	for(auto word : words)
	{
		// cout << "Current word: " << word << endl;
		// prepare key value by sorting the current word
		string sorted_word = word;
		std::sort(sorted_word.begin(), sorted_word.end());
		// cout << "Sorted key  : " << sorted_word << endl;

		// try to find that key
		auto lookup = dict.find(sorted_word);
		// if that key already exists, we have found an anagram
		if (lookup != dict.end())
		{
			// cout << "Key found, inserting: " << word << endl;
			// add it to the key's vector of anagrams
			(lookup->second).push_back(word);
		} 
		else
		{
			// cout << "Key not found, adding: " << sorted_word << endl;
			// create a new entry in the dictionary for this sorted word
			dict[sorted_word] = vector<string>();
			// add the current word to the new entry to start the list of possible anagrams
			dict[sorted_word].push_back(word);
		}
		// print_vector(dict[sorted_word]);
	}
}

/**
 * Constructs an AnagramDict from a vector of words.
 * @param words The vector of strings to be used as source words.
 */
AnagramDict::AnagramDict(const vector<string>& words)
{
	// for every word in the vector
	for(auto word : words)
	{
		// prepare key value by sorting the current word
		string sorted_word = word;
		std::sort(sorted_word.begin(), sorted_word.end());
		// try to find that key
		auto lookup = dict.find(sorted_word);
		// if that key already exists, we have found an anagram
		if (lookup != dict.end())
		{
			// add it to the key's vector of anagrams
			(lookup->second).push_back(word);
		} 
		else
		{
			// create a new entry in the dictionary for this sorted word
			dict[sorted_word] = vector<string>();
			// add the current word to the new entry to start the list of possible anagrams
			dict[sorted_word].push_back(word);
		}
	}
}

/**
 * @param word The word to find anagrams of.
 * @return A vector of strings of anagrams of the given word. Empty
 * vector returned if no anagrams are found or the word is not in the
 * word list.
 */
vector<string> AnagramDict::get_anagrams(const string& word) const
{
	vector<string> anagrams;
	string sorted_word = word;
	std::sort(sorted_word.begin(), sorted_word.end());
	auto lookup = dict.find(sorted_word);
	if(lookup != dict.end())
	{
		if((lookup->second).size() >= 1)
		{
			anagrams = lookup->second;
		}
	}
    return anagrams;
}

/**
 * @return A vector of vectors of strings. Each inner vector contains
 * the "anagram siblings", i.e. words that are anagrams of one another.
 * NOTE: It is impossible to have one of these vectors have less than
 * two elements, i.e. words with no anagrams are ommitted.
 */
vector<vector<string>> AnagramDict::get_all_anagrams() const
{
    vector<vector<string>> all_anagrams;
    // for each entry in our AnagramDict
    for(auto entry : dict)
    {
    	// if the string vector for the current sorted key is greater than 1 entry,
    	// we have multiple words that are anagrams of eachother
    	if((entry.second).size() > 1)
    	{
    		// push that vector to the return variable
    		all_anagrams.push_back(entry.second);
    	}
    }
    return all_anagrams;
}

/**
 * Takes a filename and transforms it to a vector of all words in that file.
 * @param filename The name of the file that will fill the vector
 */
vector<string> AnagramDict::file_to_vector(const string& filename) const
{
    vector<string> out;
	ifstream wordsFile(filename);
	string word;
	if (wordsFile.is_open())
	{
		// Reads a word from `wordsFile` into `word` until the file ends.
		while (wordsFile >> word)
		{
			// push the word onto the vector
			out.push_back(word);
		}
	}
    return out;
}
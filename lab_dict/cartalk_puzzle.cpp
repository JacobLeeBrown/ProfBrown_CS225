/**
 * @file cartalk_puzzle.cpp
 * Holds the function which solves a CarTalk puzzler.
 *
 * @author Matt Joras
 * @date Winter 2013
 */

#include <fstream>

#include "cartalk_puzzle.h"

using namespace std;

/**
 * Solves the CarTalk puzzler described here:
 * http://www.cartalk.com/content/wordplay-anyone.
 * @return A vector of "StringTriples" (a typedef'd std::tuple, see top of
 * cartalk_puzzle.h). Returns an empty vector if no solutions are found.
 * @param d The PronounceDict to be used to solve the puzzle.
 * @param word_list_fname The filename of the word list to be used.
 */
vector<StringTriple> cartalk_puzzle(PronounceDict d,
                                    const string& word_list_fname)
{
    vector<StringTriple> out;
	ifstream wordsFile(word_list_fname);
	string word;
	if (wordsFile.is_open()) {
		/* Reads a line from `wordsFile` into `word` until the file ends. */
		while (getline(wordsFile, word)) {
			string drop1 = word;
			string drop2 = word;
			if(word.length() > 1)
			{
				// Drops the first letter from the current word, storing the result in drop1
				drop1 = word.substr(1);
				// Stores only the first letter in drop2 (atm ignoring the 2nd letter and all that follow)
				drop2 = word[0];
			}
			if(word.length() > 2)
			{
				// Concatenates the rest of the word to drop2, ignoring the 2nd letter
				drop2 += word.substr(2);
			}
			if(d.homophones(word, drop1) && 
			   d.homophones(word, drop2))
			{
				out.push_back(std::make_tuple(word, drop1, drop2));
			}
		}
	}
    return out;
}

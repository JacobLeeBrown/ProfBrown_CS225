/**

 * @file common_words.cpp
 * Implementation of the CommonWords class.
 *
 * @author Zach Widder
 * @date Fall 2014
 */

#include "common_words.h"

#include <fstream>
#include <string>
#include <vector>
#include <iostream>
#include <iterator>
#include <algorithm>

using std::string;
using std::vector;
using std::ifstream;
using std::cout;
using std::endl;
using std::feof;

string remove_punct(const string& str)
{
	string ret;
	std::remove_copy_if(str.begin(), str.end(), std::back_inserter(ret),
						std::ptr_fun<int, int>(&std::ispunct));
	return ret;
}

/**
 * Constructs a CommonWords object from a vector of filenames.
 * @param filenames The list of filenames to read.
 */
CommonWords::CommonWords(const vector<string>& filenames)
{
	// initialize all member variables
	init_file_word_maps(filenames);
	init_common();
}

/**
 * @param n The number of times to word has to appear.
 * @return A vector of strings. The vector contains all words that appear
 * in each file >= n times.
 */
void CommonWords::init_file_word_maps(const vector<string>& filenames)
{
	// make the length of file_word_maps the same as the length of filenames
	file_word_maps.resize(filenames.size());

	// go through all files
	for (size_t i = 0; i < filenames.size(); i++)
	{
		// get the corresponding vector of words that represents the current file
		vector<string> words = file_to_vector(filenames[i]);

		// Local variable to hold the current file map data
		map<string, unsigned int> cur_file_map;
		// For each word in the words vector
		for(auto & word : words)
		{
			// Try to find the current word in the current file map data
			auto lookup = cur_file_map.find(word);
			// If it is there, just increment the frequency of the word
			if (lookup != cur_file_map.end())
			{
				(lookup->second)++;
				//cout << "\"" << word << "\" exists with frequency: " << lookup->second << endl;
			} 
			// Else, initialize the new key with a value of 1 (because this occurence of the word is the first)
			else
			{
				cur_file_map[word] = 1;
				//cout << "\"" << word << "\" does not exists, init with freq: " << cur_file_map[word] << endl;
			}
		}
		// Once we've accounted for all words, assign the local variable to its respective index in file_word_maps
		file_word_maps[i] = cur_file_map;
	}
}

/**
 * Initializes #common.
 */
void CommonWords::init_common()
{
	// For each file word map in file_word_maps
	for(auto & file_map : file_word_maps)
	{
		// for each word in the current file word map
		for(auto & word : file_map)
		{
			// See if common already has that word
			auto lookup = common.find(word.first);
			// If it does, just increment its value (which keeps track of the # of files it is in)
			if (lookup != common.end())
			{
				(lookup->second)++;
			} 
			// Else, initialize the new key with a value of 1 (because this occurence of the word is the first)
			else
			{
				common[word.first] = 1;
			}
		}
	}
}

/**
 * @param n The number of times to word has to appear.
 * @return A vector of strings. The vector contains all words that appear
 * in each file >= n times.
 */
vector<string> CommonWords::get_common_words(unsigned int n) const
{
	vector<string> out;
	// For every word we have encountered accross all files
	for(auto & word : common)
	{
		// Check that the word appears in all files
		if(word.second == file_word_maps.size())
		{
			bool word_appears = true;
			// If so, for each file word map, check the word's frequency
			for(auto & file_map : file_word_maps)
			{
				auto lookup = file_map.find(word.first);
				// Check if the word appears *less than* n times
				if(lookup->second < n)
				{
					// If so, mark the respective boolean and break now
					word_appears = false;
					break;
				}
			}
			if(word_appears)
			{
				out.push_back(word.first);
			}
		}
	}
	return out;
}

/**
 * Takes a filename and transforms it to a vector of all words in that file.
 * @param filename The name of the file that will fill the vector
 */
vector<string> CommonWords::file_to_vector(const string& filename) const
{
	ifstream words(filename);
	vector<string> out;

	if (words.is_open())
	{
		std::istream_iterator<string> word_iter(words);
		while (!words.eof())
		{
			out.push_back(remove_punct(*word_iter));
			++word_iter;
		}
	}
	return out;
}
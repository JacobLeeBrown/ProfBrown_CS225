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

CommonWords::CommonWords(const vector<string>& filenames)
{
    // initialize all member variables
    init_file_word_maps(filenames);
    init_common();
}

/**
 * @param filenames The vector of names of the files that will be used.
 * 
 * file_word_maps holds a map for each file. Each map associates a word in 
 * that file to the number of times it has been seen in that file.
 * */
void CommonWords::init_file_word_maps(const vector<string>& filenames)
{
	// make the length of file_word_maps the same as the length of filenames
	file_word_maps.resize(filenames.size());

	// go through all files
	for (size_t i = 0; i < filenames.size(); i++)
	{
		// get the corresponding vector of words that represents the current file
		vector<string> words = file_to_vector(filenames[i]);
		// go through every word in each file
		for(size_t j = 0; j < words.size(); j++)
		{
			if(file_word_maps[i].find(words[j]) != file_word_maps[i].end())
			{
				file_word_maps[i].find(words[j])->second++; 
			}
			else
			{
				file_word_maps[i].insert(std::pair<string, unsigned int>(words[j],1));
			}
		}
	}
}

/**
 * "Common" maps a word to the number of documents that word appears in
 */
void CommonWords::init_common()
{
    /* Your code goes here! */
	if(file_word_maps.empty()) return;
	//first find the smallest document to decrease runtime
	common = file_word_maps[0];
	for(size_t i = 0; i < file_word_maps.size(); i++){
		if(i+1 != file_word_maps.size()){
			if(file_word_maps[i].size() < file_word_maps[i+1].size())
				common = file_word_maps[i+1];
		}
	}

	// go through every file's word count maps
	for(size_t i = 0; i < file_word_maps.size(); i++){
		// compare only 2 seperate books
		if(file_word_maps[i] != common){
			// stay within bounds
			if(i+1 != file_word_maps.size()){
				// try to find every word from common in this book
				for(std::map<string, unsigned int>::iterator iter = common.begin(); iter != common.end(); iter++){
					// if a word is not found, remove it from common
					if(file_word_maps[i].find(iter->first) == file_word_maps[i].end())
						common.erase(iter);
				}
			}
			else{return;}
		}
		else{i++;}
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
    /* Your code goes here! */
    	std::map<string, unsigned int>::const_iterator iter = common.begin();
    	while(iter != common.end()){
		if(iter->second >= n)
			out.push_back(iter->first);
		iter++;
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

    if (words.is_open()) {
        std::istream_iterator<string> word_iter(words);
        while (!words.eof()) {
            out.push_back(remove_punct(*word_iter));
            ++word_iter;
        }
    }
    return out;
}
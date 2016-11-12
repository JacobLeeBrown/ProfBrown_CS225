/**
 * @file word_counter.cpp
 * Implementation of the WordFreq class.
 *
 * @author Chase Geigle
 * @date Spring 2011
 * @date Spring 2012
 */

using std::vector;
using std::pair;
using std::string;
using std::ifstream;
using std::istringstream;
using std::cout;
using std::endl;

template <template <class K, class V> class Dict>
WordFreq<Dict>::WordFreq(const string& infile)
    : filename(infile)
{
    /* nothing */
}

template <template <class K, class V> class Dict>
vector<pair<string, int>> WordFreq<Dict>::getWords(int threshold) const
{
	TextFile infile(filename);
	// Instantiate our dictionary with inital size 256
	Dict<string, int> hashTable(256);
	while(infile.good())
	{
		// Grab the next word from the file
		string word = infile.getNextWord();
		// Incremement the table's respective index
		hashTable[word]++;
	}
	// Instantiate return vector
	vector<pair<string, int>> ret;
	// Iterate over the hash table looking for words with great enough freqency
	typename Dict<string, int>::iterator it;
	for(it = hashTable.begin(); it != hashTable.end(); it++)
	{
		// If the word's count is greater than or equal to the threshold, push it to the return vector
		if(it->second >= threshold) ret.push_back(*it);
	}

	return ret;
}

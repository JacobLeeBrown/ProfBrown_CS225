/**
 * @file schashtable.cpp
 * Implementation of the SCHashTable class.
 *
 * @author Chase Geigle
 * @date Spring 2011
 * @date Summer 2012
 */

#include "schashtable.h"

using hashes::hash;
using std::list;
using std::pair;

template <class K, class V>
SCHashTable<K, V>::SCHashTable(size_t tsize)
{
    if (tsize <= 0)
        tsize = 17;
    size = findPrime(tsize);
    table = new list<pair<K, V>>[size];
    elems = 0;
}

template <class K, class V>
SCHashTable<K, V>::~SCHashTable()
{
    delete[] table;
}

template <class K, class V>
SCHashTable<K, V> const& SCHashTable<K, V>::
operator=(SCHashTable<K, V> const& rhs)
{
    if (this != &rhs) {
        delete[] table;
        table = new list<pair<K, V>>[rhs.size];
        for (size_t i = 0; i < rhs.size; i++)
            table[i] = rhs.table[i];
        size = rhs.size;
        elems = rhs.elems;
    }
    return *this;
}

template <class K, class V>
SCHashTable<K, V>::SCHashTable(SCHashTable<K, V> const& other)
{
    table = new list<pair<K, V>>[other.size];
    for (size_t i = 0; i < other.size; i++)
        table[i] = other.table[i];
    size = other.size;
    elems = other.elems;
}

template <class K, class V>
void SCHashTable<K, V>::insert(K const& key, V const& value)
{
    ++elems;
    if (shouldResize())
        resizeTable();
    pair<K, V> p(key, value);
    size_t idx = hash(key, size);
    table[idx].push_front(p);
}

template <class K, class V>
void SCHashTable<K, V>::remove(K const& key)
{
	// If the member variable table is non-existant, we aint gonna find no key
	if(table == NULL) return;

	// If it does exist, let's go ahead and get the index of where we're storing that bitch
	size_t idx = hash(key, size);

	// If the linked list is of size zero at the respective index, the key does not exist
	if(table[idx].size() == 0) return;

	// If the linked list does exist, we have to search it
	// Instantiate iterator for the "bucket"
	typename list<pair<K, V>>::iterator it;
	it = table[idx].begin();
	for (it = table[idx].begin(); it != table[idx].end(); it++) {
		if (it->first == key)	// If the iterator's first component (the key) is equal to the key we're looking for
		{
			// ERASE DAT MOTHAFUCKA
			table[idx].erase(it);
			// Be sure to keep elements updated
			elems--;
			return;
		}
	}
	// We didn't find it :(
	return;
}

template <class K, class V>
V SCHashTable<K, V>::find(K const& key) const
{
    size_t idx = hash(key, size);
    typename list<pair<K, V>>::iterator it;
    for (it = table[idx].begin(); it != table[idx].end(); it++) {
        if (it->first == key)
            return it->second;
    }
    return V();
}

template <class K, class V>
V& SCHashTable<K, V>::operator[](K const& key)
{
    size_t idx = hash(key, size);
    typename list<pair<K, V>>::iterator it;
    for (it = table[idx].begin(); it != table[idx].end(); it++) {
        if (it->first == key)
            return it->second;
    }

    ++elems;
    if (shouldResize())
        resizeTable();

    idx = hash(key, size);
    pair<K, V> p(key, V());
    table[idx].push_front(p);
    return table[idx].front().second;
}

template <class K, class V>
bool SCHashTable<K, V>::keyExists(K const& key) const
{
    size_t idx = hash(key, size);
    typename list<pair<K, V>>::iterator it;
    for (it = table[idx].begin(); it != table[idx].end(); it++) {
        if (it->first == key)
            return true;
    }
    return false;
}

template <class K, class V>
void SCHashTable<K, V>::clear()
{
    delete[] table;
    table = new list<pair<K, V>>[17];
    size = 17;
    elems = 0;
}

template <class K, class V>
void SCHashTable<K, V>::resizeTable()
{
	/** ~~~ Attempt 1 ~~~ */
	// Store old member variables for later
	size_t oldSize = size;
	list<pair<K, V>>* oldTable = table;

	// Update member variables to their new sizes
    size = findPrime(size*2);
    table = new list<pair<K, V>>[size];
    /* ~~~ Following line throws error for some reason even though I was using an insert that should fix elems ~~~ */
    //elems = 0; // reset elems because we're using member function insert

    // For the size of the old table
    for(size_t i = 0; i < oldSize; i++)
    {
    	// If the current index of the table had elements in it
    	if(oldTable[i].size() > 0)
    	{
    		// Instantiate an iterator for the current bucket
			typename list<pair<K, V>>::iterator it;
    		it = oldTable[i].begin();
    		while(it != oldTable[i].end())
    		{
    			/* ~~~ Let's try not re-inserting, and leaving elems alone ~~~ */
    			// my_resize_insert(it->first, it->second);
				size_t idx = hash(it->first, size);
				table[idx].push_front(*it);
    			it = oldTable[i].erase(it);
    		}
    	}
    }
    delete[] oldTable;
	return;
}
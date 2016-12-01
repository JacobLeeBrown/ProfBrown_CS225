/**
 * @file dsets.cpp
 * Implementation of DisjointSets class.
 */

#include "dsets.h"

void DisjointSets::addelements(int num)
{
	for(int i = 0; i < num; i++)
		_elems.push_back(-1);
}

int DisjointSets::find(int elem)
{
	// If the parent of the current element is a negative value, it is a root
	if(_elems[elem] < 0)
		return elem;
	// Else, implement path compression and return the updated value
	else
	{
		// Updates current element's parent to the root of the set
		_elems[elem] = find(_elems[elem]);
		return _elems[elem];
	}
}

void DisjointSets::setunion(int a, int b)
{
	// Check for valid elements
	if(a < 0 || b < 0 || a >= (int)_elems.size() || b >= (int)_elems.size())
		return;
	// Check that the elements aren't already in the same set
	int r1 = find(a);
	int r2 = find(b);
	if(r1 == r2)
		return;

	unionBySize(r1, r2);
}

void DisjointSets::deleteElems()
{
	int size = _elems.size();
	for(int i = 0; i < size; i++)
		_elems.pop_back();
}

void DisjointSets::unionBySize(int r1_idx, int r2_idx)
{
	// Obtain the new size of the unioned set (still works with negative values)
	int newSize = _elems[r1_idx] + _elems[r2_idx];
	// Check which set is larger in terms of size, then update parent values
	if(isBigger(r1_idx, r2_idx))
	{
		_elems[r2_idx] = r1_idx;
		_elems[r1_idx] = newSize;
	}
	else
	{
		_elems[r1_idx] = r2_idx;
		_elems[r2_idx] = newSize;
	}

}

bool DisjointSets::isBigger(int r1_idx, int r2_idx)
{
	// Does <= comparison because sizes are stored as negative magnitudes
	return _elems[r1_idx] <= _elems[r2_idx];
}
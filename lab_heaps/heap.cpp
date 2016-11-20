/**
 * @file heap.cpp
 * Implementation of a heap class.
 */

template <class T, class Compare>
size_t heap<T, Compare>::root() const
{
	// Let's index at 0 cuz f*ck the norm
    return 0;
}

template <class T, class Compare>
size_t heap<T, Compare>::leftChild(size_t currentIdx) const
{
	// Easy, multiple index by 2, add 1 for left child
	return currentIdx*2 + 1;
}

template <class T, class Compare>
size_t heap<T, Compare>::rightChild(size_t currentIdx) const
{
	// Easy, multiple index by 2, add 2 for right child
	return currentIdx*2 + 2;
}

template <class T, class Compare>
size_t heap<T, Compare>::parent(size_t currentIdx) const
{
	// Little trickier than indexing at 1, have to subtract some modular
	// arithmetic based on even or odd index
	return currentIdx/2 - (1 - currentIdx%2);
}

template <class T, class Compare>
bool heap<T, Compare>::hasAChild(size_t currentIdx) const
{
	// A node with no child will cannot have a left child, so check that
	// its left child's index would be within the size of the array
	if(leftChild(currentIdx) < _elems.size())
		return true;
	else
		return false;
}

template <class T, class Compare>
size_t heap<T, Compare>::maxPriorityChild(size_t currentIdx) const
{
	// Obtain indices of both children
	size_t lChild_idx = leftChild(currentIdx);
    size_t rChild_idx = rightChild(currentIdx);
    // If the right child is outside of the array, it does not exist, so
    // return the index of the left child by default
	if(rChild_idx >= _elems.size())
		return lChild_idx;
	// Else use highPriority functor to get proper index
    else
    	return (higherPriority(_elems[lChild_idx], _elems[rChild_idx])
    		? lChild_idx : rChild_idx);
}

template <class T, class Compare>
void heap<T, Compare>::heapifyDown(size_t currentIdx)
{
	// If the node has a child, we have to check if it needs to go down
	if(hasAChild(currentIdx))
	{
		// Obtain index of higher priority / smaller valued child
		size_t minChildIdx = maxPriorityChild(currentIdx);
		// If that child has higher priority than the parent, swap
		if(higherPriority(_elems[minChildIdx], _elems[currentIdx]))
		{
			std::swap(_elems[currentIdx], _elems[minChildIdx]);
			// Since we swapped, recurse to the same node we just swapped
    		heapifyDown(minChildIdx);
		}
	}
}

template <class T, class Compare>
void heap<T, Compare>::heapifyUp(size_t currentIdx)
{
	if (currentIdx == root())
		return;
	size_t parentIdx = parent(currentIdx);
	if (higherPriority(_elems[currentIdx], _elems[parentIdx]))
    {
		std::swap(_elems[currentIdx], _elems[parentIdx]);
		heapifyUp(parentIdx);
	}
}

template <class T, class Compare>
heap<T, Compare>::heap()
{
	// Does nothing because member heap vector is rooted at index 0

	// #DicksOutForHarambe
}

template <class T, class Compare>
heap<T, Compare>::heap(const std::vector<T>& elems)
{
	// Copy parameter to member storage
	_elems = elems;
	// Starting at the parent of the last node (thus the last node 
	// with a child), heapify down all previous nodes until we hit
	// the root (index of zero)
	for(int i = (int)parent(_elems.size() - 1); i >= 0; i--)
		heapifyDown((size_t)i);
}

template <class T, class Compare>
T heap<T, Compare>::pop()
{
	// If the storage is empty, nothing to pop
	if(_elems.size() == 0) return;
	// Else, temperarily store the root value (will be returned later)
	T retVal = _elems[root()];
	// Assign last node value to root
	_elems[root()] = _elems[_elems.size() - 1];
	// Remove the last node from the array
	_elems.pop_back();
	// Heapify down the root
	heapifyDown(root());
	// Return the original root value
	return retVal;
}

template <class T, class Compare>
T heap<T, Compare>::peek() const
{
	// Easy mode, return root value
	return _elems[root()];
}

template <class T, class Compare>
void heap<T, Compare>::push(const T& elem)
{
	// Add the element to the array and then heapify it up
    _elems.push_back(elem);
    heapifyUp(_elems.size() - 1);
}

template <class T, class Compare>
bool heap<T, Compare>::empty() const
{
	// Easy mode, use given vector empty() function
    return _elems.empty();
}

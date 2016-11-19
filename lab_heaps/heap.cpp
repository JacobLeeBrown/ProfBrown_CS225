/**
 * @file heap.cpp
 * Implementation of a heap class.
 */

template <class T, class Compare>
size_t heap<T, Compare>::root() const
{
    return 0;
}

template <class T, class Compare>
size_t heap<T, Compare>::leftChild(size_t currentIdx) const
{
	return currentIdx*2 + 1;
}

template <class T, class Compare>
size_t heap<T, Compare>::rightChild(size_t currentIdx) const
{
	return currentIdx*2 + 2;
}

template <class T, class Compare>
size_t heap<T, Compare>::parent(size_t currentIdx) const
{
	return currentIdx/2 - (1 - currentIdx%2);
}

template <class T, class Compare>
bool heap<T, Compare>::hasAChild(size_t currentIdx) const
{
	if(leftChild(currentIdx) < _elems.size())
		return true;
	else
		return false;
}

template <class T, class Compare>
size_t heap<T, Compare>::maxPriorityChild(size_t currentIdx) const
{
	size_t lChild_idx = leftChild(currentIdx);
    size_t rChild_idx = rightChild(currentIdx);
	if(rChild_idx >= _elems.size())
		return lChild_idx;
    else
    	return (higherPriority(_elems[lChild_idx], _elems[rChild_idx])
    		? lChild_idx : rChild_idx);
}

template <class T, class Compare>
void heap<T, Compare>::heapifyDown(size_t currentIdx)
{
	if(hasAChild(currentIdx))
	{
		size_t minChildIdx = maxPriorityChild(currentIdx);
		if(higherPriority(_elems[minChildIdx], _elems[currentIdx]))
		{
			std::swap(_elems[currentIdx], _elems[minChildIdx]);
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
}

template <class T, class Compare>
heap<T, Compare>::heap(const std::vector<T>& elems)
{
	/*for(size_t i = 0; i < elems.size(); i++)
		push(elems[i]);*/
	_elems = elems;
	for(int i = (int)parent(_elems.size() - 1); i >= 0; i--)
		heapifyDown((size_t)i);
}

template <class T, class Compare>
T heap<T, Compare>::pop()
{
	T retVal = _elems[root()];
	_elems[root()] = _elems[_elems.size() - 1];
	_elems.pop_back();
	heapifyDown(root());
	return retVal;
}

template <class T, class Compare>
T heap<T, Compare>::peek() const
{
	return _elems[root()];
}

template <class T, class Compare>
void heap<T, Compare>::push(const T& elem)
{
    _elems.push_back(elem);
    heapifyUp(_elems.size() - 1);
}

template <class T, class Compare>
bool heap<T, Compare>::empty() const
{
    return _elems.empty();
}

#include <iostream>
/**
 * @file list.cpp
 * Doubly Linked List (MP 3).
 *
 * @author Chase Geigle
 * @date (created) Fall 2011
 * @date (modified) Spring 2012, Fall 2012
 *
 * @author Jack Toole
 * @date (modified) Fall 2011
 */
 
/**
 * Destroys the current List. This function should ensure that
 * memory does not leak on destruction of a list.
 */
template <class T>
List<T>::~List()
{
	clear();
}

/**
 * Destroys all dynamically allocated memory associated with the current
 * List class.
 */
template <class T>
void List<T>::clear()
{
    ListNode * curr = head;
	while(curr != NULL)
	{
		ListNode * temp = curr;
		curr = curr->next;
		/*temp->prev = NULL;
		temp->next = NULL;
		temp->data = 0;*/
		delete temp;
	}
}

/**
 * Inserts a new node at the front of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <class T>
void List<T>::insertFront(T const& ndata)
{
    ListNode * newNode = new ListNode(ndata);
	newNode->prev = NULL;
	if(head != NULL)
	{
		newNode->next = head;
		head->prev = newNode;
	}
	else
	{
		newNode->next = NULL;
		tail = newNode;
	}
	head = newNode;
	length++;
}

/**
 * Inserts a new node at the back of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <class T>
void List<T>::insertBack(const T& ndata)
{
    ListNode * newNode = new ListNode(ndata);
	newNode->next = NULL;
	if(tail != NULL)
	{
		newNode->prev = tail;
		tail->next = newNode;
	}
	else
	{
		newNode->prev = NULL;
		head = newNode;
	}
	tail = newNode;
	length++;
}

/**
 * Inserts a new node at the back of the List.
 * This function **SHOULD NOT** create a new ListNode.
 *
 * @param nNode The node to be inserted.
*/
template <class T>
void List<T>::insertBack(ListNode*& nNode)
{
	nNode->next = NULL;
	if(tail != NULL)
	{
		nNode->prev = tail;
		tail->next = nNode;
	}
	else
	{
		nNode->prev = NULL;
		head = nNode;
	}
	tail = nNode;
	length++;
}

/**
 * Reverses the current List.
 */
template <class T>
void List<T>::reverse()
{
    reverse(head, tail);
}

/**
 * Fixes the head and tail pointers of the list if needed.
*/
template <class T>
void List<T>::fixEnds()
{
	// cout << "Running " << __func__ << "()" << endl;
	// if head's prev is not null, it is not the head, so move it back
	if(head->prev != NULL)
	{
		ListNode * temp = head;
		while(temp->prev != NULL)
		{
			temp = temp->prev;
		}
		head = temp;
	}
	// if tail's next is not null, it is not the tail, so move it backwards
	if(tail->next != NULL)
	{
		ListNode * temp = tail;
		while(temp->next != NULL)
		{
			temp = temp->next;
		}
		tail = temp;
	}
}

/**
 * Helper function to reverse a sequence of linked memory inside a List,
 * starting at startPoint and ending at endPoint. You are responsible for
 * updating startPoint and endPoint to point to the new starting and ending
 * points of the rearranged sequence of linked memory in question.
 *
 * @param startPoint A pointer reference to the first node in the sequence
 *  to be reversed.
 * @param endPoint A pointer reference to the last node in the sequence to
 *  be reversed.
 */
template <class T>
void List<T>::reverse(ListNode*& startPoint, ListNode*& endPoint)
{
	// check edge cases
    if(startPoint == endPoint)
	{
		return;
	}
	else if(startPoint == NULL || endPoint == NULL)
	{
		cout << "Passed NULL pointer" << endl;
		return;
	}
	else if(empty())
	{
		return;
	}
	
	// the start and end nodes are special cases
	ListNode * curr = startPoint;
	ListNode * last = endPoint;
	// get temp pointers for both the first and last pointers
	ListNode * cNTemp = curr->next;
	ListNode * cPTemp = curr->prev;
	ListNode * lNTemp = last->next;
	ListNode * lPTemp = last->prev;
	// exchange their pointers appropriately
	curr->next = lNTemp;
	curr->prev = cNTemp;
	last->next = lPTemp;
	last->prev = cPTemp;
	// update passed pointers as well as out of range nodes
	startPoint = last;
	endPoint = curr;
	if(cPTemp != NULL)
	{
		cPTemp->next = startPoint;
	}
	if(lNTemp != NULL)
	{
		lNTemp->prev = endPoint;
	}
	
	// update current to the next node in the orginal list
	curr = cNTemp;
	// until curr reaches last (which was updated already), switch each
	// individual node's next and prev pointers
	while(curr != last)
	{
		ListNode * nTemp = curr->next;
		ListNode * pTemp = curr->prev;
		curr->next = pTemp;
		curr->prev = nTemp;
		curr = nTemp;
	}
	
	// fix head or tail pointers if needed
	fixEnds();
}

/**
 * Reverses blocks of size n in the current List. You should use your
 * reverse( ListNode * &, ListNode * & ) helper function in this method!
 *
 * @param n The size of the blocks in the List to be reversed.
 */
template <class T>
void List<T>::reverseNth(int n)
{
	if(empty())
	{
		return;
	}
	else if(n == 1)
	{
		// just return if n==1 because the list will be the same
		return;
	}
	else if(n > length)
	{
		reverse();
		return;
	}
	ListNode * curr = head;
	// now the fun begins
	// start i at 1 because we're counting, not indexing
	int i = 1;
	// instantiate a temporary pointer to keep track of each reverse start
	ListNode * start = curr;
	// curr will keep track of the end of the reverse
	cout << "Reversing every " << n << " nodes." << endl;
	while(curr != NULL)
	{
		/*cout << "Index  : " << i << endl;
		cout << "Start  : " << start << "\n" << 
		"  Data : " << start->data << endl;
		cout << "Current: " << curr << "\n" << 
		"  Data : " << curr->data << endl;
		cout << endl;*/
		// special case once we hit the end of the list
		if(curr == tail)
		{
			//cout << "\nREVERSING LAST TIME nodes " << start->data << ", " << curr->data << "\n" << endl;
			reverse(start, curr);
			break;
		}
		// once i == n, we know to flip
		if(i == n)
		{
			// ListNode * curNTemp = curr->next;
			//cout << "\nREVERSING nodes " << start->data << ", " << curr->data << "\n" << endl;
			reverse(start, curr);
			i = 1;	// reset i
			start = curr->next; // update start
		}
		else
		{
			i++; // just increment i
		}
		// update curr
		curr = curr->next;
	}
}

/**
 * Removes target node from list, fixing surrounding pointers.
 *
 * @param target The node to be removed.
 * 
 * @return target Passed node, now separate from the list.
*/
template <class T>
typename List<T>::ListNode * List<T>::remove(ListNode*& target)
{
	if(target == NULL)
	{
		return 0;
	}
	else if(target == head)
	{
		target->next->prev = NULL;
	}
	else if(target == tail)
	{
		target->prev->next = NULL;
	}
	else
	{
		target->next->prev = target->prev;
		target->prev->next = target->next;
	}
	target->next = NULL;
	target->prev = NULL;
	length--;
	return target;
}

/**
 * Modifies the List using the waterfall algorithm.
 * Every other node (starting from the second one) is removed from the
 * List, but appended at the back, becoming the new tail. This continues
 * until the next thing to be removed is either the tail (**not necessarily
 * the original tail!**) or NULL.  You may **NOT** allocate new ListNodes.
 * Note that since the tail should be continuously updated, some nodes will
 * be moved more than once.
 */
template <class T>
void List<T>::waterfall()
{
	ListNode * curr = head;
	int i = 1;
	while(curr != tail && curr != NULL)
	{
		if(i == 2)
		{
			ListNode * temp = curr->next;
			curr = remove(curr);
			insertBack(curr);
			curr = temp;
			i = 1;
		}
		else
		{
			i++;
			curr = curr->next;
		}
	}
}

/**
 * Splits the given list into two parts by dividing it at the splitPoint.
 *
 * @param splitPoint Point at which the list should be split into two.
 * @return The second list created from the split.
 */
template <class T>
List<T> List<T>::split(int splitPoint)
{
    if (splitPoint > length)
        return List<T>();

    if (splitPoint < 0)
        splitPoint = 0;
	
    ListNode* secondHead = split(head, splitPoint);

    int oldLength = length;
    if (secondHead == head) {
        // current list is going to be empty
        head = NULL;
        tail = NULL;
        length = 0;
    } else {
        // set up current list
        tail = head;
        while (tail->next != NULL)
            tail = tail->next;
        length = splitPoint;
    }

    // set up the returned list
    List<T> ret;
    ret.head = secondHead;
    ret.tail = secondHead;
    if (ret.tail != NULL) {
        while (ret.tail->next != NULL)
            ret.tail = ret.tail->next;
    }
    ret.length = oldLength - splitPoint;
    return ret;
}

/**
 * Helper function to split a sequence of linked memory at the node
 * splitPoint steps **after** start. In other words, it should disconnect
 * the sequence of linked memory after the given number of nodes, and
 * return a pointer to the starting node of the new sequence of linked
 * memory.
 *
 * This function **SHOULD NOT** create **ANY** new List objects!
 *
 * @param start The node to start from.
 * @param splitPoint The number of steps to walk before splitting.
 * @return The starting node of the sequence that was split off.
 */
template <class T>
typename List<T>::ListNode* List<T>::split(ListNode* start, int splitPoint)
{
	ListNode * curr = start;
	for(int i = 0; i < splitPoint; i++)
	{
		curr = curr->next;
	}
	curr->prev->next = NULL;
    return curr;
}

/**
 * Merges the given sorted list into the current sorted list.
 *
 * @param otherList List to be merged into the current list.
 */
template <class T>
void List<T>::mergeWith(List<T>& otherList)
{
    // set up the current list
    head = merge(head, otherList.head);
    tail = head;

    // make sure there is a node in the new list
    if (tail != NULL) {
        while (tail->next != NULL)
            tail = tail->next;
    }
    length = length + otherList.length;

    // empty out the parameter list
    otherList.head = NULL;
    otherList.tail = NULL;
    otherList.length = 0;
}

/**
 * Helper function to merge two **sorted** and **independent** sequences of
 * linked memory. The result should be a single sequence that is itself
 * sorted.
 *
 * This function **SHOULD NOT** create **ANY** new List objects.
 *
 * @param first The starting node of the first sequence.
 * @param second The starting node of the second sequence.
 * @return The starting node of the resulting, sorted sequence.
 */
template <class T>
typename List<T>::ListNode* List<T>::merge(ListNode* first, ListNode* second)
{
    // Check if either parameter is null, meaning one list is empty
	// just return the other list
	if(first == NULL)
	{
		return(second);
	}
	if(second == NULL)
	{
		return(first);
	}
	
	// Figure out which list's head will be the merge's head (theHead)
	ListNode * theHead;
	ListNode * curr;
	if(first->data < second->data)
	{
		theHead = first;
		// first head is now incrementing through its respective list
		first = first->next;
	}
	else // else if (first->data >= second->data)
	{
		theHead = second;
		// second head is now incrementing through its respective list
		second = second->next;
	}
	// curr will increment through the merged list
	curr = theHead;
	
	// while *either* list is *not* empty
	while(first != NULL && second != NULL)
	{
		// similar to setting theHead, increment respective iterators
		// based on which list is contributing the next node
		if(first->data < second->data)
		{
			// link new next node with curr's next and it's prev
			curr->next = first;
			first->prev = curr;
			curr = first; // curr = curr->next;
			first = first->next;
		}
		else // else if (first == NULL || (second != NULL && first->data >= second->data))
		{
			// link new next node with curr's next and it's prev
			curr->next = second;
			second->prev = curr;
			curr = second; // curr = curr->next;
			second = second->next;
		}
	}
	
	// check which bastard gave up early, and assign the rest of the victor
	if(first == NULL)
	{
		curr->next = second;
		second->prev = curr;
	}
	else // else if(second == NULL)
	{
		curr->next = first;
		first->prev = curr;
	}
	first = theHead;
	second = NULL;
	return(theHead);
}

/**
 * Sorts the current list by applying the Mergesort algorithm.
 */
template <class T>
void List<T>::sort()
{
    if (empty())
        return;
    head = mergesort(head, length);
    tail = head;
    while (tail->next != NULL)
        tail = tail->next;
}

/**
 * Sorts a chain of linked memory given a start node and a size.
 * This is the recursive helper for the Mergesort algorithm (i.e., this is
 * the divide-and-conquer step).
 *
 * @param start Starting point of the chain.
 * @param chainLength Size of the chain to be sorted.
 * @return A pointer to the beginning of the now sorted chain.
 */
template <class T>
typename List<T>::ListNode* List<T>::mergesort(ListNode* start, int chainLength)
{
	// base case
	if(chainLength == 1)
	{
		return start;
	}
	else
	{
		// get half the current chainLength
		int half = chainLength/2;
		// split the current chain
		ListNode * start2 = split(start, half);
		// mergesort the first half
		ListNode * temp = start;
		start = mergesort(temp, half);
		// mergesort the second half
		ListNode * sorted2 = mergesort(start2, chainLength-half);
		// merge the two halves
		return merge(start, sorted2);
	}
}

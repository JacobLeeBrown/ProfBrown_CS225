/**
 * @file list.cpp
 * Singly Linked List (lab_gdb).
 *
 * @author Chase Geigle
 * @date (created) Fall 2011
 * @date (modified) Spring 2012, Fall 2012
 *
 * @author Jack Toole
 * @date (modified) Fall 2011
 *
 * @author Veer Dedhia
 * @date (modified) Spring 2014
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
	// newNode->prev = NULL;
	if(head != NULL)
	{
		newNode->next = head;
		// head->prev = newNode;
	}
	else
	{
		newNode->next = NULL;
		// tail = newNode;
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
    // @todo Graded in lab_gdb
    // NOTE: Do not use this implementation for MP3!
    ListNode* temp = head;

    if (temp == NULL) {
        head = new ListNode(ndata);
    } 
	else {
        ListNode * prev = temp;
		while (temp != NULL)
		{
			prev = temp;
            temp = temp->next;
		}
        temp = new ListNode(ndata);
		prev->next = temp;
    }
	length++;
}

/**
 * Reverses the current List.
 */
template <class T>
void List<T>::reverse()
{
    head = reverse(head, NULL, length);
}

/**
 * Helper function to recursively reverse the enitre sequence of
 * linked memory inside a List.
 *
 * @param curr The current node we are reversing
 * @param prev The node that should be placed before the current node in the
 * final reversed list
 * @param len The length of the remaining list to be reversed
 */
template <class T>
typename List<T>::ListNode* List<T>::reverse(ListNode* curr, ListNode* prev,
                                             int len)
{
    if(curr == NULL)
	{
		return NULL;
	}
    ListNode* temp;
    if (len <= 1)
	{
		curr->next = prev;
		return curr;
	}
	else{
        temp = reverse(curr->next, curr, len - 1);
        curr->next = prev;
        return temp;
    }
}

/**
 * Shuffles the current list by applying a perfect shuffle once. This entails
 * splitting the list in half, then interleaving the two halves.
 * For example:
 * start : < 1, 2, 3, 4, 5 >
 * split : < 1, 2, 3 >    < 4, 5 >
 * final : < 1, 4, 2, 5, 3 >
 */
template <class T>
void List<T>::shuffle()
{
    if(empty())
	{
		return;
	}

    // Find the center, and split the list in half
    // one should point at the start of the first half-list
    // two should point at the start of the second half-list
    ListNode *one, *two, *prev, *temp;
    one = two = prev = temp = head;

	
    for (int i = 0; i < ((length / 2) + (length % 2)); i++) {
        prev = two;
        two = two->next;
    }
    prev->next = NULL;

    // interleave
    while (two != NULL) {
        temp = one->next;
        one->next = two;
		prev = two;
        two = two->next;
		prev->next = temp;
        one = temp;
    }
}

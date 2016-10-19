#include "linkedlist.h"
#include <iostream>
using namespace std;

bool removeAt(LinkedList &mylist, int pos)
{
	if(mylist.head == NULL || pos < 0)
	{
		return 1;
	}
	Node * curr = mylist.head;
	Node * prev = NULL;
	int i = 0;
	while(curr != NULL)
	{
		if(i == pos)
		{
			if(curr == mylist.head)
			{
				mylist.head = curr->next;
			}
			else
			{
				prev->next = curr->next;
			}
			delete curr;
			return 1;
		}
		i++;
		prev = curr;
		curr = curr->next;
	}
	return 0;
}

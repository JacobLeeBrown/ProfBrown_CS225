#include "linkedlist.h"

Node * removeAt(LinkedList &mylist, int pos)
{
	if(mylist.head == NULL || pos < 0)
	{
		return NULL;
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
			return curr;
		}
		i++;
		prev = curr;
		curr = curr->next;
	}
	return NULL;
}

void insert(LinkedList &mList, Node *& newNode)
{
	if(mList.head == NULL)
	{
		mList.head = newNode;
		return;
	}
	Node * curr = mList.head;
	while(curr->next != NULL)
	{
		curr = curr->next;
	}
	curr->next = newNode;
	newNode->next = NULL;
}

void merge(LinkedList* lst1,
           LinkedList* lst2,
           LinkedList* mrg)
{
	int i1 = 0;
	int i2 = 0;
	int im = 0;
	Node * curr = lst1->head;
	if(curr->data > lst2->head->data)
	{
		curr = lst2->head;
	}
	while(curr != NULL)
	{
		
	}
	return;
}

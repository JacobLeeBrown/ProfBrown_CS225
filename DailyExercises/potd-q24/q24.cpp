#include <iostream>
using namespace std;

struct node
{
    int val;
    node * next;
};

void printList(node * head)
{
    if(head == NULL){
        cout << "Empty list" << endl;
        return;
    }
    node * temp = head;
    int count = 0;
    while(temp != NULL){
        cout << "Node " << count << ": " << temp ->val << endl;
        count++;
        temp = temp->next;
    }
}

void insertSorted(node ** head, node * insert)
{
	if(*head == NULL)
	{
		*head = insert;
		return;
	}
	if((*head)->val > insert->val)
	{
		insert->next = *head;
		*head = insert;
		return;
	}
	node * cur = *head;
	while(cur->next != NULL)
	{
		if(((cur->next)->val) > insert->val)
		{
			insert->next = cur->next;
			cur->next = insert;
			return;
		}
		cur = cur->next;
	}
	cur->next = insert;
	return;
}

void insertSorted(node ** head, int data)
{
	node * newNode = new node;
	newNode->val = data;
	newNode->next = NULL;
	insertSorted(head, newNode);
}

int main()
{
	node * list = NULL;
	insertSorted(&list, 10);
	insertSorted(&list, 2);
	insertSorted(&list, 4);
	insertSorted(&list, -1);
	insertSorted(&list, 8);
	insertSorted(&list, 9);
	insertSorted(&list, 5);
	insertSorted(&list, 2);
	insertSorted(&list, 6);
	insertSorted(&list, 6);
	insertSorted(&list, 3);
	insertSorted(&list, -5);
	printList(list);

	node * cur = list;
	while(cur != NULL)
	{
		node * temp = cur->next;
		delete cur;
		cur = temp;
	}
	
    return 0;
}

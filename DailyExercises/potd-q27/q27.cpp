#include <iostream>
using namespace std;

struct node{
    int val;
    node * next;
};

void printList(node * head){
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

void insertSorted(node ** head, node * insert){
    node * temp = *head;
    if(temp == NULL){
        *head = insert;
        insert->next = NULL;
        return;
    }
    if(temp->val >= insert->val){   // this node becomes the new head
        insert->next = temp;
        *head = insert;
    }
    else{
        node * prev = *head;
        temp = temp->next;
        while(temp != NULL){
            if(temp->val >= insert->val){
                insert->next = temp;
                prev->next = insert;
                return;
            }
            temp = temp->next;
            prev = prev->next;
        }
        // we reached the end of list, this node must go at the end
        // prev points to last node, temp points to NULL
        prev->next = insert;
        insert->next = NULL;
    }
}

void sortList(node ** head){
    node * newHead = NULL;
    node * curHead = *head;
    node * insert;
    while(curHead != NULL){
        insert = curHead;
        curHead = curHead->next;
        insert->next = NULL;
        insertSorted(&newHead, insert);
    }
    *head = newHead;
}

node * shuffle(node * a, node * b){
    if(a == NULL) return b;
    if(b == NULL) return a;
    node * aptr = a;
    node * bptr = b;
    while(aptr->next != NULL && bptr->next != NULL){
        node * tempa = aptr;
        aptr = aptr->next;
        node * tempb = bptr;
        bptr = bptr->next;
        tempa->next = tempb;
        tempb->next = aptr;
    }
    if(aptr->next == NULL){ // tack on rest of b
        aptr->next = bptr;
    }
    else{   // bptr->next == NULL
        // add last b node to a list
        node * tempa = aptr;
        aptr = aptr->next;
        tempa->next = bptr;
        bptr->next = aptr;
    }
    return a;
}

void insert(node ** head, int data)
{
	node* newNode = new node;
	newNode->val = data;
	// cout << "Adding node with value: " << data << endl;
	if(*head == NULL)
	{
		*head = newNode;
		// cout << "Assigned new head node" << endl;
		return;
	}
	else
	{
		node* cur = *head;
		while(cur->next != NULL)
		{
			cur = cur->next;
		}
		cur->next = newNode;
	}
	return;
}

bool listContains(node * list, int data)
{
	if(list == NULL)
	{
		return false;
	}
	node * cur = list;
	while(cur != NULL)
	{
		if(cur->val == data)
		{
			return true;
		}
		cur = cur->next;
	}
	return false;
}

node * intersection(node * a, node * b){
	node * newList = NULL;
	node * curA = a;
	while(curA != NULL)
	{
		int curVal = curA->val;
		node * curB = b;
		while(curB != NULL)
		{
			if(curVal == curB->val && !listContains(newList, curVal))
			{
				node * newNode = new node;
				newNode->val = curVal;
				newNode->next = NULL;
				insertSorted(&newList, newNode);
			}
			curB = curB->next;
		}
		curA = curA->next;
	}
	return newList;
}

int main(){
    node * list1 = NULL;
	node * list2 = NULL;
	int curVal = 0;
	cout << "Please enter a list of values for list1 (end with -1):" << endl;
	cin >> curVal;
	while(curVal != -1)
	{
		// cout << "Inserting node with value: " << curVal << endl;
		insert(&list1, curVal);
		cin >> curVal;
	}
	printList(list1);
	cout << "Please enter a list of values for list2 (end with -1):" << endl;
	cin >> curVal;
	while(curVal != -1)
	{
		// cout << "Inserting node with value: " << curVal << endl;
		insert(&list2, curVal);
		cin >> curVal;
	}
	printList(list2);
	cout << "\nNow intersecting Lists 1 and 2\n" << endl;
	node * list3 = intersection(list1, list2);
	printList(list3);
	node * cur = list3;
	while(cur != NULL)
	{
		node * temp = cur->next;
		delete cur;
		cur = temp;
	}
    return 0;
}

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

node * shuffle(node * a, node * b){
	node * newHead = a;
	node * curA = a;
	node * curB = b;
	while(curA != NULL)
	{
		node * tempA = curA->next;
		node * tempB = curB->next;
		curA->next = curB;
		curB->next = tempA;
		curA = tempA;
		curB = tempB;
	}
	return newHead;
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
	cout << "\nNow shuffling Lists 1 and 2\n" << endl;
	node * list3 = shuffle(list1, list2);
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

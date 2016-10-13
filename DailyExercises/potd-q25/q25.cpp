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

void insertSorted(node ** head, int data){
	node* newNode = new node;
	newNode->val = data;
	insertSorted(head, newNode);
}

void sortList(node ** list)
{
	/** My attempt at a bubble sort **/
	bool flag = true; // set flag to true to start first pass
	int temp;
	node * head = *list;
	node * cur1 = head->next;
	while((cur1 != NULL) && flag)
	{
		flag = false;
		node * cur2 = head;
		while(cur2->next != NULL)
		{
			if ((cur2->next)->val < cur2->val)
			{ 
				temp = cur2->val; // swap elements
				cur2->val = (cur2->next)->val;
				(cur2->next)->val = temp;
				flag = true; // indicates that a swap occurred.
			}
			cur2 = cur2->next;
		}
		cur1 = cur1->next;
	}
	return; 
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
    node * list = NULL;
	int curVal = 0;
	cout << "Please enter a list of values (end with -1):" << endl;
	cin >> curVal;
	while(curVal != -1)
	{
		// cout << "Inserting node with value: " << curVal << endl;
		insert(&list, curVal);
		cin >> curVal;
	}
	printList(list);
	cout << "\n ~~Now Sorting List~~ \n" << endl;
	sortList(&list);
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

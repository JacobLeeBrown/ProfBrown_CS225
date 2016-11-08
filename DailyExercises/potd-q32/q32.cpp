#include <iostream>
using namespace std;

struct node{
    int val;
    node * next;
};

void printList(node * head){
    while(head){
        cout << head->val << " ";
        head = head->next;
    }
}

node *createList(int arr[], int size){
    node * ret = new node;
    ret->val = arr[0];
    node * temp = ret;
    for(int i = 1; i < size; i ++){
        temp->next = new node;
        temp = temp->next;
        temp->val = arr[i];
    }
    temp->next = NULL;
    return ret;
}

void push(node ** head, node * n)
{
	if(*head == NULL)
	{
		*head = n;
		return;
	}
	node * cur = *head;
	while(cur->next != NULL)
	{
		cur = cur->next;
	}
	cur->next = n;
}

node * pop(node ** head)
{
	node * temp = *head;
	*head = (*head)->next;
	return temp;
}

void requeue(node ** head, int times)
{
	if(*head == NULL)
	{
		return;
	}
	for(int i = 0; i < times; i++)
	{
		push(head, pop(head));
	}
}

int main(){
    int arr[8] = {1, 2, 3, 4, 5, 6, 7, 8};
    node * n = createList(arr, 8);
    printList(n);
    requeue(&n, 5);
    cout << endl;
    printList(n);
    return 0;
}

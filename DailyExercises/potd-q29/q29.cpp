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

void sortList(node ** list)
{
    node * cur = *list;
    int count1 = 0;
    int count3 = 0;
    int count5 = 0;
    while(cur != NULL)
    {
        switch(cur->val){
            case 1:
                count1++;
                break;
            case 3: 
                count3++;
                break;
            default:
                count5++;
                break;
        }
        cur = cur->next;
    }
    cur = *list;
    while(cur != NULL)
    {
        if(count1 > 0)
        {
            cur->val = 1;
            count1--;
        }
        else if(count3 > 0)
        {
            cur->val = 3;
            count3--;
        }
        else
        {
            cur->val = 5;
            count5--;
        }
        cur = cur->next;
    }
}

int main(){
    int arr[6] = {1, 3, 3, 5, 1, 5};
    node * n = createList(arr, 6);
    printList(n);
    cout << endl;
    sortList(&n);
    printList(n);
    return 0;
}

#include <iostream>
using namespace std;

class Stack{
    private:
        struct node{
            int val;
            node * next;
        };
        node * head;
        int size;
    public:
        Stack();
        ~Stack();
        int getSize();
        bool isEmpty();
        void push(int value);
        int pop();
        void print();
};

Stack::Stack()
{
    head = NULL;
    size = 0;
}

Stack::~Stack()
{
    node * cur = head;
    while(cur != NULL)
    {
        node * temp = cur->next;
        delete cur;
        cur = temp;
    }
}

int Stack::getSize()
{
    return size;
}

bool Stack::isEmpty()
{
    if(size == 0)
    {
    	return true;
    }
    return false;
}

void Stack::push(int value)
{
	node * n = new node;
	n->val = value;

	node * temp = head;
	head = n;
	n->next = temp;
	size++;
}

int Stack::pop()
{
	if(isEmpty())
	{
		return 0;
	}

	node * temp = head;
	int data = temp->val;
	head = head->next;
	size--;
	delete temp;
	return data;
}

void Stack::print()
{
	if(isEmpty())
	{
		cout << "List is empty!" << endl;
	}
	node * cur = head;
	while(cur != NULL)
	{
		cout << cur->val;
		if(cur->next != NULL)
		{
			cout << ", ";
		}
		cur = cur->next;
	}
	cout << endl;
}

int main(){
    Stack a;
    a.print();
    cout << "is empty " << a.isEmpty() << endl;
    a.push(1);
    a.push(2);
    a.push(3);
    cout << "popped " << a.pop() << endl;
    cout << "size: " << a.getSize() << endl;
    cout << "is empty " << a.isEmpty() << endl;
    a.print();
    
    return 0;
}

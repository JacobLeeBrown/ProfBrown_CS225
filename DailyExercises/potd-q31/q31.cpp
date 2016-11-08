#include <iostream>
using namespace std;

class Queue{
    private:
        struct node{
            int val;
            node * next;
        };
        node * head;
        int size;
    public:
        Queue();
        ~Queue();
        int getSize();
        bool isEmpty();
        void push(int value);
        int pop();
        void print();
};

Queue::Queue()
{
    head = NULL;
    size = 0;
}

Queue::~Queue()
{
    node * cur = head;
    while(cur != NULL)
    {
        node * temp = cur->next;
        delete cur;
        cur = temp;
    }
}

int Queue::getSize()
{
    return size;
}

bool Queue::isEmpty()
{
    if(size == 0)
    {
    	return true;
    }
    return false;
}

void Queue::push(int value)
{
	node * n = new node;
	n->val = value;

	node * temp = head;
	head = n;
	n->next = temp;
	size++;
}

int Queue::pop()
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

int main(){
    Queue a;
    a.print();
    cout << "is empty " << a.isEmpty() << endl;
    a.push(1);
    a.push(2);
    a.push(3);
    a.print();
    cout << "popped " << a.pop() << endl;
    a.pop();
    a.pop();
    cout << "size: " << a.getSize() << endl;
    cout << "is empty " << a.isEmpty() << endl;
    a.print();
    
    return 0;
}

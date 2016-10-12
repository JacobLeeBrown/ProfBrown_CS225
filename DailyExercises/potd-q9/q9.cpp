#include <iostream>

int main(){
	// a is an array of int pointers
    int ** a = new int *[2];
    int b = 3;
	// a[0] is a pointer to an int on the stack
    a[0] = &b;
	// a[1] is allocated memory for an int on the heap
    a[1] = new int;
	// 5 is stored on the heap
    *(a[1]) = 5;
	// c is a pointer to int pointer on the heap
    int ** c = new int *;
	// the pointer c points to is allocated to the heap
    *c = new int;
	// d contains the address of c
    int *** d = &c;

	delete a[1];
	delete[] a;
	delete *c;
	delete c;
	
	d = NULL;
	
    return 0;
}

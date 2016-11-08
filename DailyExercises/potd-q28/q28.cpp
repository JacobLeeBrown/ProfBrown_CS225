#include <iostream>
using namespace std;

struct node{
    int val;
    node * left;
    node * right;
};

void printTree(node * root){
    if(root == NULL){
        cout << "NULL ";
        return;
    }
    printTree(root->left);
    cout << root->val << " ";
    printTree(root->right);
}

void insertRight(node * root, node * n)
{
	if(root->right == NULL)
	{
		root->right = n;
	}
	else
	{
		insertRight(root->right, n);
	}
}

bool isLeaf(node * n)
{
	if(n->left == NULL && n->right == NULL)
	{
		return true;
	}
	return false;
}

void smoosh(node * root){
	if(isLeaf(root))
	{
		return;
	}
	node * temp = root->right;
	if(root->left != NULL)
	{
		root->right = root->left;
		root->left = NULL;
		smoosh(root->right);
		insertRight(root, temp);
	}
	smoosh(temp);
	return;
}

int main(){
    node * root = new node;
    root->val = 1;
    node * temp = root;
    temp->left = new node;
    temp->left->val = 2;
    temp = temp->left;
    temp->left = new node;
    temp->left->val = 3;
    temp->left->left = NULL;
    temp->left->right = NULL;
    temp->right = new node;
    temp->right->val = 4;
    temp->right->left = NULL;
    temp->right->right = NULL;
    temp = root;
    temp->right = new node;
    temp->right->val = 5;
    temp->right->left = NULL;
    temp = temp->right;
    temp->right = new node;
    temp->right->val = 6;
    temp->right->left = NULL;
    temp->right->right = NULL;
    printTree(root);
    cout << endl;
    smoosh(root);
    printTree(root);
    cout << endl;
    return 0;
}

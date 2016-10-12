/**
 * @file binarytree.cpp
 * Definitions of the binary tree functions you'll be writing for this lab.
 * You'll need to modify this file.
 */

/**
 * @return The height of the binary tree. Recall that the height of a binary
 *  tree is just the length of the longest path from the root to a leaf, and
 *  that the height of an empty tree is -1.
 */
template <typename T>
int BinaryTree<T>::height() const
{
    // Call recursive helper function on root
    return height(root);
}

/**
 * Private helper function for the public height function.
 * @param subRoot
 * @return The height of the subtree
 */
template <typename T>
int BinaryTree<T>::height(const Node* subRoot) const
{
    // Base case
    if (subRoot == NULL)
        return -1;

    // Recursive definition
    return 1 + max(height(subRoot->left), height(subRoot->right));
}

/**
 * Prints out the values of the nodes of a binary tree in order.
 * That is, everything to the left of a node will be printed out before that
 * node itself, and everything to the right of a node will be printed out after
 * that node.
 */
template <typename T>
void BinaryTree<T>::printLeftToRight() const
{
    // Call recursive helper function on the root
    printLeftToRight(root);

    // Finish the line
    cout << endl;
}

/**
 * Private helper function for the public printLeftToRight function.
 * @param subRoot
 */
template <typename T>
void BinaryTree<T>::printLeftToRight(const Node* subRoot) const
{
    // Base case - null node
    if (subRoot == NULL)
        return;

    // Print left subtree
    printLeftToRight(subRoot->left);

    // Print this node
    cout << subRoot->elem << ' ';

    // Print right subtree
    printLeftToRight(subRoot->right);
}

/**
 * Flips the tree over a vertical axis, modifying the tree itself
 *  (not creating a flipped copy).
 */
template <typename T>
void BinaryTree<T>::mirror()
{
    // Call recursive helper function on the root
	mirror(root);
}

/**
 * Private helper function for the public mirror function.
 * @param subRoot The current node in the recursion
 */
template <typename T>
void BinaryTree<T>::mirror(Node* subRoot) const
{
	if(subRoot == NULL)
	{
		return;
	}
	// Switch the two children nodes
	Node* tempR = subRoot->right;
	subRoot->right = subRoot->left;
	subRoot->left = tempR;
	
	// Now switch the two subtrees rooted at the children
	mirror(subRoot->left);
	mirror(subRoot->right);
}

/**
 * @return True if an in-order traversal of the tree would produce a
 *  nondecreasing list output values, and false otherwise. This is also the
 *  criterion for a binary tree to be a binary search tree.
 */
template <typename T>
bool BinaryTree<T>::isOrdered() const
{
    // Call recursive helper function on the root
    return isOrdered(root);
}

/**
 * Private helper function for the public isOrdered function.
 * @param subRoot The current node in the recursion
 */
template <typename T>
bool BinaryTree<T>::isOrdered(const Node* subRoot) const
{
	if(subRoot == NULL)
	{
		return true;
	}
	// Check if the left child is greater than the parent
	if(subRoot->left != NULL)
	{
		if((subRoot->left)->elem > subRoot->elem)
		{
			return false;
		}
	}
	// Check if the right child is less than apparent
	if(subRoot->right != NULL)
	{
		if((subRoot->right)->elem < subRoot->elem)
		{
			return false;
		}
	}
	// If neither case fails, return the recursive call on each child
	return (isOrdered(subRoot->left) && isOrdered(subRoot->right));
}
/**
 * Prints out all the possible paths from the root of the tree to any leaf node.
 * That is, all sequences starting at the root node and continuing downwards,
 * ending at a leaf node. Paths ending in a left node should be printed before
 * paths ending in a node further to the right.
 */
template <typename T>
void BinaryTree<T>::printPaths() const
{
	vector<const Node*> v;
    // Call recursive helper function on the root
	printPaths(root, v);
}

/**
 * Private helper function for the public printPaths function.
 * @param subRoot The current node in the recursion
 * @param v The vector keeping track of the current path
 */
template <typename T>
void BinaryTree<T>::printPaths(const Node* subRoot, vector<const Node*> & v) const
{
	if(subRoot == NULL)
	{
		return;
	}
	// Push current node onto vector
	v.push_back(subRoot);
	// If it is a leaf node, print the current path stored in the vector
	if(isLeafNode(subRoot))
	{
		cout << "Path: ";
		printVector(v);
		cout << endl;
		// Pop the leaf node and return
		v.pop_back();
		return;
	}
	// Else this is a parent node and we need to print the paths coming from the children
	printPaths(subRoot->left, v);
	printPaths(subRoot->right, v);
	// When that's all done, pop the current node
	v.pop_back();
}

/**
 * Private helper function to determine leaf nodes.
 * @param leaf The node to be checked
 */
template <typename T>
bool BinaryTree<T>::isLeafNode(const Node* leaf) const
{
	if(leaf == NULL)
	{
		return false;
	}
	else if(leaf->right == NULL && leaf->left == NULL)
	{
		return true;
	}
	return false;
}

/**
 * Private helper function to print vectors.
 * @param v The vector to be printed
 */
template <typename T>
void BinaryTree<T>::printVector(const vector<const Node*> v) const
{
	for(int i = 0; i < (int)v.size(); i++)
	{
		cout << v[i]->elem << " ";
	}
}

/**
 * Each node in a tree has a distance from the root node - the depth of that
 * node, or the number of edges along the path from that node to the root. This
 * function returns the sum of the distances of all nodes to the root node (the
 * sum of the depths of all the nodes). Your solution should take O(n) time,
 * where n is the number of nodes in the tree.
 * @return The sum of the distances of all nodes to the root
 */
template <typename T>
int BinaryTree<T>::sumDistances() const
{
    // Call recursive helper function on the root
    return sumDistances(root, 0);
}

/**
 * Private helper function for the public sumDistances function.
 * @param subRoot The current node in the recursion
 * @param dis The current distance from the root
 * @return The sum of distances for all descendant nodes
 */
template <typename T>
int BinaryTree<T>::sumDistances(const Node* subRoot, int dis) const
{
	// If the current node doesn't exist, return 0
	if(subRoot == NULL)
	{
		return 0;
	}
	// Initialize sum to be the current distance
	int sum = dis;
	// Inncrease sum for the descendants' distances
	sum += sumDistances(subRoot->left, dis + 1);
	sum += sumDistances(subRoot->right, dis + 1);
	return sum;
}








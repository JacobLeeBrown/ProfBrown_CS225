/**
 * @file btree.cpp
 * Implementation of a B-tree class which can be used as a generic dictionary
 * (insert-only). Designed to take advantage of caching to be faster than
 * standard balanced binary search trees.
 *
 * @author Matt Joras
 * @date Winter 2013
 */

using std::vector;

/**
 * Finds the value associated with a given key.
 * @param key The key to look up.
 * @return The value (if found), the default V if not.
 */
template <class K, class V>
V BTree<K, V>::find(const K& key) const
{
    return root == nullptr ? V() : find(root, key);
}

/**
 * Private recursive version of the find function.
 * @param subroot A reference of a pointer to the current BTreeNode.
 * @param key The key we are looking up.
 * @return The value (if found), the default V if not.
 */
template <class K, class V>
V BTree<K, V>::find(const BTreeNode* subroot, const K& key) const
{
	if(subroot == NULL) return V();

    size_t idx = insertion_idx(subroot->elements, key);
	//std::cout << *subroot << "\t Looking for key: " << key << std::endl;

    /* If idx is a valid index and the key there is the key we
     * are looking for, we are done. */
    if(chk_for_key((subroot->elements), idx, key))
	{
		//std::cout << "Found key " << key << " with val: " << (subroot->elements)[idx].value << std::endl;
		return (subroot->elements)[idx].value;
	}
    /* Otherwise, we need to figure out which child to explore. For this we
     * can actually just use idx directly. E.g.
     * | 1 | 5 | 7 | 8 |
     * Suppose we are looking for 6. idx is 2. This means we want to
     * explore the child between 5 and 7. The children vector has a pointer for
     * each of the horizontal bars. The index of the horizontal bar we want is
     * 2, which is conveniently the same as idx. If the subroot is
     * a leaf and we didn't find the key in it, then we have failed to find it
     * anywhere in the tree and return the default V.
     */
	else if(!(subroot->is_leaf))
	{
		return find((subroot->children)[idx], key);
	}
	else // subroot->is_leaf
	{
		return V();
	}
}

/**
 * Inserts a key and value into the BTree. If the key is already in the
 * tree do nothing.
 * @param key The key to insert.
 * @param value The value to insert.
 */
template <class K, class V>
void BTree<K, V>::insert(const K& key, const V& value)
{
    /* Make the root node if the tree is empty. */
    if (root == nullptr) {
        root = new BTreeNode(true, order);
    }
    insert(root, DataPair(key, value));
    /* Increase height by one by tossing up one element from the old
     * root node. */
    if (root->elements.size() >= order) {
        BTreeNode* new_root = new BTreeNode(false, order);
        new_root->children.push_back(root);
        split_child(new_root, 0);
        root = new_root;
    }
}

/**
 * Splits a child node of a BTreeNode. Called if the child became too large.
 * @param parent The parent whose child we are trying to split.
 * @param child_idx The index of the child in its parent's children vector.
 */
template <class K, class V>
void BTree<K, V>::split_child(BTreeNode* parent, size_t child_idx)
{
    /* The child we want to split. */
    BTreeNode* child = parent->children[child_idx];
    /* The "left" node is the old child, the right child is a new node. */
    // BTreeNode* new_left = child; // Just modify the child node?
    BTreeNode* new_right = new BTreeNode(child->is_leaf, order);

    /* E.g.
     * | 3 | 6 | 8 |
     * Mid element is at index (3 - 1) / 2 = 1 .
     * Mid child (bar) is at index 4 / 2 = 2 .
     * E.g.
     * | 2 | 4 |
     * Mid element is at index (2 - 1) / 2 = 0 .
     * Mid child (bar) is at index 3 / 2 = 1 .
     * This definition is to make this BTree act like the visualization at
     * https://www.cs.usfca.edu/~galles/visualization/BTree.html
     */
    size_t mid_elem_idx = (child->elements.size() - 1) / 2;
    size_t mid_child_idx = child->children.size() / 2;

    /* Iterator for where we want to insert the new child. */
    auto child_itr = parent->children.begin() + child_idx + 1;
    /* Iterator for where we want to insert the new element. */
    auto elem_itr = parent->elements.begin() + child_idx;
    /* Iterator for the middle element. */
    auto mid_elem_itr = child->elements.begin() + mid_elem_idx;
    /* Iterator for the middle child. */
    auto mid_child_itr = child->children.begin() + mid_child_idx;

	/* Assume we are splitting the 3 6 8 child.
	 * We want the following to happen.
	 *     | 2 |
	 *    /     \
	 * | 1 |   | 3 | 6 | 8 |
	 *
	 * Insert a pointer into parent's children which will point to the
	 * new right node. The new right node is empty at this point.
	 *     | 2 |   |
	 *    /     \
	 * | 1 |   | 3 | 6 | 8 |
	 */

    (parent->children).insert(child_itr, new_right);

	/* Insert the mid element from the child into its new position in the
	 * parent's elements. At this point the median is still in the child.
	 *     | 2 | 6 |
	 *    /     \
	 * | 1 |   | 3 | 6 | 8 |
	 */

    (parent->elements).insert(elem_itr, (child->elements)[mid_elem_idx]);
    // Simultaneously remove the middle element from child's elements and update mid_elem_itr
    mid_elem_itr = (child->elements).erase(mid_elem_itr);

	/* Now we want to copy over the elements (and children) to the right
	 * of the child median into the new right node, and make sure the left
	 * node only has the elements (and children) to the left of the child
	 * median.
	 *     | 2 | 6 |
	 *    /   /     \
	 * | 1 | | 3 | | 8 |
	 */

    // Copying children pointers to new_right and removing them from original child
    while(mid_child_itr != (child->children).end())
    {
    	(new_right->children).push_back(*mid_child_itr);
    	mid_child_itr = (child->children).erase(mid_child_itr);
    }
    // Copying element data to new_right and removing them from original child
    while(mid_elem_itr != (child->elements).end())
    {
    	(new_right->elements).push_back(*mid_elem_itr);
    	mid_elem_itr = (child->elements).erase(mid_elem_itr);
    }
}

/**
 * Private recursive version of the insert function.
 * @param subroot A reference of a pointer to the current BTreeNode.
 * @param pair The DataPair to be inserted.
 * Note: Original solution used std::lower_bound, but making the students
 * write an equivalent seemed more instructive.
 */
template <class K, class V>
void BTree<K, V>::insert(BTreeNode* subroot, const DataPair& pair)
{
	size_t insert_idx = insertion_idx(subroot->elements, pair);
	// std::cout << *subroot << "\t Current node, inserting data pair: (" << pair.key << ", " << pair.value << ")" << std::endl;
    /* There are two cases to consider.
     * If the subroot is a leaf node and the key doesn't exist in the subroot, we
     * should simply insert the pair into subroot.
     */
	if(chk_for_key((subroot->elements), insert_idx, pair))
	{
		return;
	}

	if(subroot->is_leaf)
	{
		//std::cout << *subroot << "\t Insert Current Node: (" << pair.key << ", " << pair.value << ")" << std::endl;
		(subroot->elements).insert((subroot->elements).begin() + insert_idx, pair);
		return;
	}

    /* Otherwise (subroot is not a leaf and the key doesn't exist in subroot)
     * we need to figure out which child to insert into and call insert on it.
     * After this call returns we need to check if the child became too large
     * and thus needs to be split to maintain order.
     */

	else // !subroot->is_leaf
	{
		//std::cout << "Going to child node." << std::endl;
		insert((subroot->children)[insert_idx], pair);
		if((((subroot->children)[insert_idx])->elements).size() >= order)
		{
			split_child(subroot, insert_idx);
		}
	}
}
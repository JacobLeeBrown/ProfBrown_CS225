/**
 * @file dests.h
 * Disjoint sets implementation.
 *
 * @author Jacob "Boss" Brown
 * @date Fall 2016
 *
 * In memory of our lord and savior, Harambe.
 */

#ifndef _DSETS_H_
#define _DSETS_H_

#include <vector>

using std::vector;

/**
 * DisjointSets class: Implemented with the optimizations discussed in class, as
 * up-trees stored in a single vector of ints. Specifically, path compression 
 * and union-by-size are used. Each place in the vector represents a node. (Note
 * that this means that the elements in our universe are indexed starting at 0.)
 * A nonnegative number is the index of the parent of the current node; a 
 * negative number in a root node is the negative of the set size.
 */
class DisjointSets
{
	public:

		/**
		 * Creates n unconnected root nodes at the end of the vector.
		 *
		 * @param num 	The number of nodes to create
		 */
		void addelements(int num);

		/**
		 * Obtains the index of the root of the set that the given elem (given
		 * by its index, although they're synonymous) is in. Simultaneously
		 * updates all traversed elements' parents to be the root in order to
		 * comply with path compression as discussed in class.
		 *
		 * @param elem 	Index of element in set we want the root of
		 *
		 * @return 		Index of the root of the set the given element resides
		 */
		int find(int elem);

		/**
		 * This function should be implemented as union-by-size.
		 *
		 * That is, when you setunion two disjoint sets, the smaller (in terms 
		 * of number of nodes) should point at the larger. This function works 
		 * as described in lecture, except that you should not assume that the 
		 * arguments to setunion are roots of existing uptrees.
		 *
		 * Your setunion function SHOULD find the roots of its arguments before 
		 * combining the trees. If the two sets are the same size, make the tree
		 * containing the second argument point to the tree containing the 
		 * first. (Note that normally we could break this tie arbitrarily, but 
		 * in this case we want to control things for grading.)
		 *
		 * @param a 	Index of the first element to union
		 * @param b 	Index of the second element to union
		 */
		void setunion(int a, int b);

		/**
		 * Can't delete variable of type DisjointSets, so making this to allow
		 * for clearing the private member storage.
		 */
		void deleteElems();

	private:
		/** 
		 * Private member storage for the elements of this family of disjoint
		 * sets.
		 */
		vector<int> _elems;

		/**
		 * Connects two disjoint sets in the way that increases distance to the
		 * root for the least amount of nodes.
		 *
		 * @param r1_idx 	Index of the root of one of the sets being unioned
		 * @param r2_idx 	Index of the the root of the other set being unioned
		 */
		void unionBySize(int r1_idx, int r2_idx);

		/**
		 * Determines if one set contains *as many* or more nodes than another. 
		 * Returns true if both sets are the same size as to meet with grading
		 * criteria.
		 *
		 * @param r1_idx 	Index of the root of one of the sets
		 * @param r2_idx 	Index of the the root of the other set
		 *
		 * @return True if the first set is larger than or equal to the second
		 * 		   in size, false otherwise
		 */
		bool isBigger(int r1_idx, int r2_idx);
};

// #include "dsets.cpp"
#endif
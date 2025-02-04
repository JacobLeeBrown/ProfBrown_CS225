/**
 * @file kdtree.cpp
 * Implementation of KDTree class.
 */
#include <cmath>

template <int Dim>
bool KDTree<Dim>::smallerDimVal(const Point<Dim>& first,
								const Point<Dim>& second, int curDim) const
{
	return (first[curDim] != second[curDim]) ? (first[curDim] < second[curDim]) : (first < second);
}

template <int Dim>
bool KDTree<Dim>::shouldReplace(const Point<Dim>& target,
								const Point<Dim>& currentBest,
								const Point<Dim>& potential) const
{
	int dist_potential_target =	0;
	int dist_curBest_target = 0;
	for(int i = 0; i < Dim; i++)
	{
		dist_potential_target += (potential[i] - target[i]) * (potential[i] - target[i]);
		dist_curBest_target += (currentBest[i] - target[i]) * (currentBest[i] - target[i]);
	}
	return (dist_potential_target != dist_curBest_target) ?
			(dist_potential_target < dist_curBest_target) : (potential < currentBest);
}

/*
*  we have a vector Points that is sorted so as to give us a KDTree.
*  we need to implement findnearestneighbor on it.
*  TWO PARTS:
*  		search to find smallest hyperrectangle that contains the point
* 		backtrack to see if any other hyperrectangles within the radius contain the point
*/
template <int Dim>
Point<Dim> KDTree<Dim>::findNearestNeighbor(const Point<Dim>& query) const
{
	size_t rootIndex = (points.size()-1)/2;

	return findNearestNeighborHelper( query, 0, points.size()-1, 0, points[ rootIndex ] );
}

template <int Dim>
Point<Dim> KDTree<Dim>::findNearestNeighborHelper(const Point<Dim>& query,
								size_t leftIndex, size_t rightIndex, int curDim,
								Point<Dim> currentBest ) const
{
	int nextDim = (curDim+1)%Dim;
	bool leftFlag = true;

	if ( leftIndex == rightIndex ) // we are at a leaf
	{	// check current node against currentBest
		if (  shouldReplace( query, currentBest, points[rightIndex] )  )
		{ // overwrite currentBest if current node is better
			currentBest = points[rightIndex];
		}
		return currentBest;
	}

	// WE'RE NOT AT A LEAF NODE: THERE IS A SUBTREE.
	// recurse down the half of the tree that our query point is in.
	size_t subrootIndex = (leftIndex + rightIndex)/2;
	// if subtree[curDim] < query && subtree < rightIndex,
		// recurse, moving lower bound to the right.
	if ( subrootIndex < rightIndex && smallerDimVal( points[subrootIndex], query, curDim ) )
	{
		currentBest = findNearestNeighborHelper( query, subrootIndex+1, rightIndex, nextDim, currentBest );
		leftFlag = false;
	}
	// if subtree[currDim] > query && subtree > leftindex
		// recurse, moving upper bound to the left.
	if ( subrootIndex > leftIndex && smallerDimVal( query, points[subrootIndex], curDim ) )
	{
		currentBest = findNearestNeighborHelper( query, leftIndex, subrootIndex-1, nextDim, currentBest );
		leftFlag = true;
	}

	// we have recursed down one of the two leaf nodes, and possibly updated currentBest.
	// we must check if non-leaf nodes are closer.

	// check if our current node, which cannot be a leaf node, is closer to our search point than
		// our currentbest, (which is a leaf node).
	if (  shouldReplace( query, currentBest, points[subrootIndex] )  )
	{
		currentBest = points[subrootIndex];
	}

    if ( pow(points[subrootIndex][curDim] - query[curDim],2) <= dist(query, currentBest) )
    {
        if ( leftFlag && rightIndex > subrootIndex )
            currentBest = findNearestNeighborHelper( query, subrootIndex+1, rightIndex, nextDim, currentBest );
        if ( !leftFlag && leftIndex < subrootIndex )
            currentBest = findNearestNeighborHelper( query, leftIndex, subrootIndex-1, nextDim, currentBest );
    }

	return currentBest;
}

template<int Dim>
int KDTree<Dim>::dist( const Point<Dim> & first, const Point<Dim> & second) const
{
    int retval = 0;
    for(int i = 0; i < Dim; i++)
    {
        retval += pow(first[i] - second[i], 2);
    }
    return retval;
}

template <int Dim>
KDTree<Dim>::KDTree(const vector<Point<Dim>>& newPoints)
{
	points = newPoints;
	KDTree_sort(points, 0, 0, points.size()-1);
}

template <int Dim>
void KDTree<Dim>::KDTree_sort(vector<Point<Dim>>& points, int curDim, 
										size_t l_idx, size_t r_idx)
{
	// Base case: If the left index is ever equal to or greater than the right, we're done
	if(l_idx >= r_idx || points.size() == 0 || r_idx >= points.size() || l_idx < 0) return;

	// cout << "KDTree_sort called on dim: " << curDim << ", (l,r): " << l_idx << ", " << r_idx << ")" << endl;

	// Set the mid point of the current sub-list (dividing by 2 automatically floors the index)
	size_t mid = l_idx + (r_idx - l_idx)/2;
	// Set the median point of the current sub-list
	my_quick_select(points, curDim, l_idx, r_idx, mid);

	// Sort the left side of the median, but based on the next dimension
	KDTree_sort(points, (curDim + 1) % Dim, l_idx, mid - 1);
	// Sort the right side of the median, but based on the next dimension
	KDTree_sort(points, (curDim + 1) % Dim, mid + 1, r_idx);
}

template <int Dim>
void KDTree<Dim>::my_quick_select(vector<Point<Dim>>& points, int curDim, 
										size_t l_idx, size_t r_idx, size_t target_idx)
{
	// Base Case: Current sub-list has only 1 element, so return that element
	if(l_idx == r_idx)
	{
		return;
	}
	// Just pick some arbitrary point for the pivot. I chose the middle index
	size_t piv_idx = (l_idx + r_idx)/2;
	// Update the pivot index (and point) to the right location *based on the current dim*
	piv_idx = my_partition(points, curDim, l_idx, r_idx, piv_idx);
	// If the pivot index is the target index, we've got our man
	if(target_idx == piv_idx)
	{
		return;
	}
	// Target is short of pivot, try again in range before pivot
	else if(target_idx < piv_idx)
	{
		my_quick_select(points, curDim, l_idx, piv_idx - 1, target_idx);
	}
	// Target is long of pivot, try again in range after pivot
	else // target_idx > piv_idx
	{
		my_quick_select(points, curDim, piv_idx + 1, r_idx, target_idx);
	}
}

template <int Dim>
size_t KDTree<Dim>::my_partition(	vector<Point<Dim>>& points, int curDim, 
									size_t l_idx, size_t r_idx, size_t piv_idx)
{
	// Obtain the point at the pivot index
	Point<Dim> piv_pt = points[piv_idx];
	// Switch the pivot with the end of the partition
	my_swap(points, r_idx, piv_idx);
	// Obtain index of where we will start storing "smaller" values
	size_t st_idx = l_idx;
	// for every index within this section of the given list
	for(size_t i = l_idx; i < r_idx; i++)
	{
		// if the current point is "smaller" than the pivot value
		if(smallerDimVal(points[i], piv_pt, curDim))
		{
			// Swap the current point with the point at the store index
			my_swap(points, st_idx, i);
			// Increment the store index
			st_idx++;
		}
	}
	// Now that we're done, swap the original pivot point to where it will be in between two partitions,
	// the one on the left with all "smaller" values, and the one on the right with all "larger" values
	my_swap(points, r_idx, st_idx);

	return st_idx;
}

template <int Dim>
void KDTree<Dim>::my_swap(vector<Point<Dim>>& points, size_t idx_1, size_t idx_2)
{
	Point<Dim> temp = points[idx_1];
	points[idx_1] = points[idx_2];
	points[idx_2] = temp;
}

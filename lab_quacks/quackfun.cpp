/**
 * @file quackfun.cpp
 * This is where you will implement the required functions for the
 *  stacks and queues portion of the lab.
 */

namespace QuackFun {

/**
 * Sums items in a stack.
 * @param s A stack holding values to sum.
 * @return The sum of all the elements in the stack, leaving the original
 *  stack in the same state (unchanged).
 *
 * @note You may modify the stack as long as you restore it to its original
 *  values.
 * @note You may use only two local variables of type T in your function.
 *  Note that this function is templatized on the stack's type, so stacks of
 *  objects overloading the + operator can be summed.
 * @note We are using the Standard Template Library (STL) stack in this
 *  problem. Its pop function works a bit differently from the stack we
 *  built. Try searching for "stl stack" to learn how to use it.
 * @hint Think recursively!
 */
template <typename T>
T sum(stack<T>& s)
{
    T total = T();
	if(s.empty())
	{
		// do nothing - base case;
	}
	else
	{
		T temp = s.top();
		s.pop();
		total = temp + sum(s);
		s.push(temp);
	}
    return total; 	// stub return value (0 for primitive types). Change this!
					// Note: T() is the default value for objects, and 0 for
					// primitive types
}

/**
 * Reverses even sized blocks of items in the queue. Blocks start at size
 * one and increase for each subsequent block.
 * @param q A queue of items to be scrambled
 *
 * @note Any "leftover" numbers should be handled as if their block was
 *  complete.
 * @note We are using the Standard Template Library (STL) queue in this
 *  problem. Its pop function works a bit differently from the stack we
 *  built. Try searching for "stl stack" to learn how to use it.
 * @hint You'll want to make a local stack variable.
 */
template <typename T>
void scramble(queue<T>& q)
{
    stack<T> s;
    // start round off at 1 to denote beginning of sequence
	int round = 1;
	while(!q.empty())
	{
		// endBreak will cover special case of queue ending before round amount
		// of elements have been added to the stack
		int endBreak = 0;
		bool broke = 0;
		// for as many elements as the nth round
		for(int i = 0; i < round; i++)
		{
			// increment endBreak to keep track of successfully moved elements
			endBreak++;
			// push q's front element to s and then pop it
			s.push(q.front());
			q.pop();
			// if q is empty early, that means we hit the end before the full loop
			// could finish, so we break now and set bool broke to true
			if(q.empty())
			{
				broke = 1;
				break;
			}
		}
		// if it's an even round, we need to reverse the n elements we just added
		if(round % 2 == 0)
		{
			int min = round;
			if(broke)
			{
				min = endBreak;
			}
			reverse(s, min);
		}
		round++;
	}
	int length = s.size();
	reverse(s, length);
	for(int i = 0; i < length; i++)
	{
		q.push(s.top());
		s.pop();
	}
}

template <typename T>
void reverse(stack<T>& s, int amount)
{
	queue<T> q;
	// top of stack goes to front of queue
	for(int i = 0; i < amount; i++)
	{
		q.push(s.top());
		s.pop();
	}
	// front of queue goes to bottom of stack
	for(int i = 0; i < amount; i++)
	{
		s.push(q.front());
		q.pop();
	}
	// amount elements get reversed
	return;
}

/**
 * @return true if the parameter stack and queue contain only elements of
 *  exactly the same values in exactly the same order; false, otherwise.
 *
 * @note You may assume the stack and queue contain the same number of items!
 * @note There are restrictions for writing this function.
 * - Your function may not use any loops
 * - In your function you may only declare ONE local boolean variable to use in
 *   your return statement, and you may only declare TWO local variables of
 *   parametrized type T to use however you wish.
 * - No other local variables can be used.
 * - After execution of verifySame, the stack and queue must be unchanged. Be
 *   sure to comment your code VERY well.
 */
template <typename T>
bool verifySame(stack<T>& s, queue<T>& q)
{
    bool retVal = true;
	// if we've reached the end of the stack, we gucci
	if(s.empty())
	{
		return retVal;
	}
	// get the temp element from the stack and pop it
	T sTemp = s.top();
	s.pop();
	// we're recursively calling *before* checking values in order to ger to
	// the bottom of the stack to compare to the back of 
	retVal = verifySame(s, q);
	// now we're st the bottom of the stack, which should match the front of the queue
	if(sTemp != q.front())
	{
		retVal = false;
	}
	// to keep queue the same, just push the front element, then pop it
	q.push(q.front());
	q.pop();
	// push back the stack element we popped earlier
	s.push(sTemp);
    return retVal;
}

}

#include <vector>
#include <iostream>
#include <string>
#include <sstream>
#include <cstring>
#include <stdexcept>

#include "kdtree.h"
#include "point.h"
#include "coloredout.h"

// compile command: clang++ -std=c++1y -stdlib=libc++ -Wall test.cpp -o test

// non-functional. was trying to copy paste shit from testkdtree.cpp but to no avail. throws compiler error
// on my local machine about the color module they use. not worth debugging imo.

// use testkdtree.cpp.

bool is_terminal = false;
bool is_colored = false;
colored_out::enable_t color_scheme = colored_out::DISABLE;

void output_header(string name, string desc)
{
    const string bar(79, '~');
    cout << bar << endl;
    colored_out::output_bold(name, cout, color_scheme);
    cout << " - " << desc << endl;
    cout << bar << endl;
}

template <typename T>
inline std::string to_string(const T& value)
{
    std::ostringstream ss;
    ss << value;
    return ss.str();
}

template <int K>
void testLinearCtor(int size)
{
    output_header("testLinearCtor<" + to_string(K) + ">(" + to_string(size) + ")",
                  "constructs a " + to_string(K) +
                  "D tree of points 0 through " + to_string(size - 1));

    vector<Point<K>> points;
    points.reserve(size);
    for (int i = 0; i < size; i++) {
        Point<K> p;
        for (int j = 0; j < K; j++)
            p[j] = i;
        points.push_back(p);
    }

    KDTree<K> tree(points);

    cout << endl << "~  ";
    colored_out::output_bold("Tree Diagram", cout, color_scheme);
    cout << "  ~    ~    ~    ~    ~    ~    ~";
    cout << endl;
    tree.printTree(cout, color_scheme);
    cout << endl;
}

/**
 * Test the KDTree Nearest Neighbor Search
 */
template <int K>
void testLinearNNS(int size)
{
    output_header("testLinearNNS<" + to_string(K) + ">(" + to_string(size) + ")",
                  "findNearestNeighbor on a " + to_string(K) +
                  "D tree of elements 0 to " + to_string(size - 1));

    vector<Point<K>> points;
    points.reserve(size);
    for (int i = 0; i < size; i++) {
        Point<K> p;
        for (int j = 0; j < K; j++)
            p[j] = i;
        points.push_back(p);
    }

    KDTree<K> tree(points);

    for (size_t i = 0; i < points.size(); i++) {
        cout << "findNearestNeighbor(" << points[i] << ") = ";
        cout << tree.findNearestNeighbor(points[i]) << endl;
    }

    cout << endl;
}

using namespace std;

int main()
{
	/*
	cout << "Please enter keys (end list with -1): " << endl;
	int curVal;
	cin >> curVal;

	cout << "Please enter the value you would insert: " << endl;
	int search;
	cin >> search;
	*/

	testLinearCtor<1>(10);

	return 0;
}


/**
 * @file graph_tools.cpp
 * This is where you will implement several functions that operate on graphs.
 * Be sure to thoroughly read the comments above each function, as they give
 *  hints and instructions on how to solve the problems.
 */

#include "graph_tools.h"

/**
 * Finds the minimum edge weight in the Graph graph.
 * THIS FUNCTION IS GRADED.
 *
 * @param graph - the graph to search
 * @return the minimum weighted edge
 *
 * @todo Label the minimum edge as "MIN". It will appear blue when
 *  graph.savePNG() is called in minweight_test.
 *
 * @note You must do a traversal.
 * @note You may use the STL stack and queue.
 * @note You may assume the graph is connected.
 *
 * @hint Initially label vertices and edges as unvisited.
 */
int GraphTools::findMinWeight(Graph& graph)
{
	// Be sure everything is set as unexplored
	setAllUnexplored(graph);
	// Initialize the queue we'll use to BFS this graph
	queue<Vertex> queueV;
	// Obtain a random vertex to begin our BFS traversal and set as VISITED
	Vertex begin = graph.getStartingVertex();
	graph.setVertexLabel(begin, "VISITED");
	queueV.push(begin);

	/** For this function, we need to keep track of the minimum edge weight and
	 *  the vertices the edge connects
	 */
	// Initialize the variables
	int min = -1;
	Vertex a;
	Vertex b;

	// Begin BFS
	while(!queueV.empty())
	{
		// Get the front most vertex
		Vertex cur = queueV.front();
		// Obtain the adjacent vertices of the current vertex
		vector<Vertex> adjV = graph.getAdjacent(cur);
		// Pop the front most (current) vertex from the queue
		queueV.pop();
		// For each adjacent vertex in the adjacent vertex vector
		for(auto adj : adjV)
		{
			// If the vertex label is UNEXPLORED
			if(graph.getVertexLabel(adj) == "UNEXPLORED")
			{
				// Set this vertex and the edge between it and cur appropriately
				graph.setVertexLabel(adj, "VISITED");
				graph.setEdgeLabel(cur, adj, "DISCOVERY");
				// Push the vertex onto the queue for next BFS iteration
				queueV.push(adj);
			}
			// Else if the edge label is UNEXPLORED and the vertex isn't
			else if(graph.getEdgeLabel(cur, adj) == "UNEXPLORED")
			{
				// Set the edge between the adjacent and current vertices
				graph.setEdgeLabel(cur, adj, "CROSS");
			}

			/* Check for new minimum edge */
			if(min == -1 || graph.getEdgeWeight(cur, adj) < min)
			{
				// Update respective variables
				min = graph.getEdgeWeight(cur, adj);
				a = cur;
				b = adj;
			}
		}
	}

	// Once done searching through the whole graph, mark minimum edge
	graph.setEdgeLabel(a, b, "MIN");
	// Return the minimum edge weight of the graph
	return min;
}

/**
 * Returns the shortest distance (in edges) between the Vertices
 *  start and end.
 * THIS FUNCTION IS GRADED.
 *
 * @param graph - the graph to search
 * @param start - the vertex to start the search from
 * @param end - the vertex to find a path to
 * @return the minimum number of edges between start and end
 *
 * @todo Label each edge "MINPATH" if it is part of the minimum path
 *
 * @note Remember this is the shortest path in terms of edges,
 *  not edge weights.
 * @note Again, you may use the STL stack and queue.
 * @note You may also use the STL's unordered_map, but it is possible
 *  to solve this problem without it.
 *
 * @hint In order to draw (and correctly count) the edges between two
 *  vertices, you'll have to remember each vertex's parent somehow.
 */
int GraphTools::findShortestPath(Graph& graph, Vertex start, Vertex end)
{
	// Be sure everything is set as unexplored
	setAllUnexplored(graph);

	// Initialize the queue we'll use to traverse the graph
	queue<Vertex> queueV;
	// Use start vertex to begin our BFS traversal and set as VISITED
	graph.setVertexLabel(start, "VISITED");
	queueV.push(start);
	
	/** For this function, we need to keep track of the number of edges we
	 *  traverse over and some way to know the parents of each vertex
	 */
	int count = 0;
	unordered_map<Vertex, Vertex> parents;

	// Begin BFS
	while(!queueV.empty())
	{
		// Get the front most vertex
		Vertex cur = queueV.front();
		// Obtain the adjacent vertices of the current vertex
		vector<Vertex> adjV = graph.getAdjacent(cur);
		// Pop the front most (current) vertex from the queue
		queueV.pop();
		// For each adjacent vertex in the adjacent vertex vector
		for(auto adj : adjV)
		{
			// If the vertex label is UNEXPLORED
			if(graph.getVertexLabel(adj) == "UNEXPLORED")
			{
				// Set this vertex as VISITED and add it as a child
				graph.setVertexLabel(adj, "VISITED");
				parents[adj] = cur;
				// Push the vertex onto the queue for next BFS iteration
				queueV.push(adj);
			}
		}
	}

	// Now that we're done with the BFS, we need to set the min path
	Vertex cur = end;
	while(cur != start)
	{
		count++;
		graph.setEdgeLabel(cur, parents[cur], "MINPATH");
		cur = parents[cur];
	}
	return count;
}

/**
 * Finds a minimal spanning tree on a graph.
 * THIS FUNCTION IS GRADED.
 *
 * @param graph - the graph to find the MST of
 *
 * @todo Label the edges of a minimal spanning tree as "MST"
 *  in the graph. They will appear blue when graph.savePNG() is called.
 *
 * @note Use your disjoint sets class from MP 7.1 to help you with
 *  Kruskal's algorithm. Copy the files into the libdsets folder.
 * @note You may call std::sort instead of creating a priority queue.
 */
void GraphTools::findMST(Graph& graph)
{
	// Be sure everything is set as unexplored
	setAllUnexplored(graph);
	// Get all of the edges in the graph
    vector<Edge> edges = graph.getEdges();
   	// Sort them with the help of a self-defined comparator
    sort(edges.begin(), edges.end(), mySort);
    // Get all of the vertices in the graph
    vector<Vertex> vertices = graph.getVertices();

    // Now make a DisjointSets to keep track used vertices
    DisjointSets v;
    v.addelements(vertices.size());

    // For each edge in the graph
    for(auto edge : edges)
    {
    	// Obtain the vertices this edge
    	Vertex a = edge.source;
    	Vertex b = edge.dest;
    	// Check if their respective sets have been unioned yet
    	if(v.find(a) != v.find(b))
    	{
    		// If not, union them and set the edge as part of the MST
    		v.setunion(a, b);
    		graph.setEdgeLabel(a, b, "MST");
    	}
    }
}

void GraphTools::setAllUnexplored(Graph& graph)
{
	// Initialize the queue we'll use to breadth-first traverse this graph
	queue<Vertex> queueV;
	// Obtain a random vertex to begin our traversal and set as UNEXPLORED
	Vertex begin = graph.getStartingVertex();
	graph.setVertexLabel(begin, "UNEXPLORED");
	queueV.push(begin);
	// Begin BFS
	while(!queueV.empty())
	{
		// Get the front most vertex
		Vertex cur = queueV.front();
		// Obtain the adjacent vertices of the current vertex
		vector<Vertex> adjV = graph.getAdjacent(cur);
		// Pop the front most (current) vertex from the queue
		queueV.pop();
		// For each adjacent vertex in the adjacent vertex vector
		for(auto adj : adjV)
		{
			// If the vertex label is not already UNEXPLORED
			if(graph.getVertexLabel(adj) != "UNEXPLORED")
			{
				// Set this vertex and the edge between it and cur as UNEXPLORED
				graph.setVertexLabel(adj, "UNEXPLORED");
				graph.setEdgeLabel(cur, adj, "UNEXPLORED");
				// Push the vertex onto the queue for next BFS iteration
				queueV.push(adj);
			}
			// Else if the edge label is not already UNEXPLORED
			else if(graph.getEdgeLabel(cur, adj) != "UNEXPLORED")
			{
				// Set the edge between the adjacent and current vertices
				graph.setEdgeLabel(cur, adj, "UNEXPLORED");
			}
		}
	}
}

bool GraphTools::mySort(Edge a, Edge b)
{
	return (a.weight < b.weight);
}
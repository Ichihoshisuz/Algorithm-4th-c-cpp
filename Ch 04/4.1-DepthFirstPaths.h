#pragma once

#include "4.0-Graph.h"
#include <stack>

class DepthFirstPaths
{
public:
	DepthFirstPaths(std::ifstream& input, int s);
	DepthFirstPaths(const DepthFirstPaths& dfp) = delete;
	DepthFirstPaths& operator=(const DepthFirstPaths& dfp) = delete;
	~DepthFirstPaths();

	int size() { return G.size_Vertexes(); }
	bool hasPathTo(int v) { return marked[v]; }
	std::stack<int>& pathTo(std::stack<int>& s, int v);

private:
	bool* marked;
	int* edgeTo;
	int start;
	Graph G;
	void search(Graph& g, int v);
};

DepthFirstPaths::DepthFirstPaths(std::ifstream& input, int s):G(input), start(s)
{
	std::allocator<bool> alloc_bool;
	std::allocator<int> alloc_int;
	marked = alloc_bool.allocate(G.size_Vertexes());
	edgeTo = alloc_int.allocate(G.size_Vertexes());
	for (int i = 0; i < G.size_Vertexes(); ++i)
	{
		alloc_bool.construct(marked + i, false);
		alloc_int.construct(edgeTo + i);
	}
	edgeTo[s] = s;
	search(G, s);
}

DepthFirstPaths::~DepthFirstPaths()
{
	std::allocator<bool> alloc_bool;
	std::allocator<int> alloc_int;
	for (int i = 0; i < G.size_Vertexes(); ++i)
	{
		alloc_bool.destroy(marked + i);
		alloc_int.destroy(edgeTo + i);
	}
	alloc_bool.deallocate(marked, G.size_Vertexes());
	alloc_int.deallocate(edgeTo, G.size_Vertexes());
}

void DepthFirstPaths::search(Graph& g, int v)
{
	if (marked[v] == true)
		return;
	marked[v] = true;
	Bag& b = g.Bag_with_v(v);
	for (int i = 0; i < b.size(); ++i)
	{
		int w = b.getValue();
		b.incr();
		if (marked[w] == false)
		{
			edgeTo[w] = v;
			search(g, w);
		}
	}
}

std::stack<int>& DepthFirstPaths::pathTo(std::stack<int>& s, int v)
{
	if (!hasPathTo(v))
		return s;
	while (v != start)
	{
		s.push(v);
		v = edgeTo[v];
	}
	s.push(v);
	return s;
}
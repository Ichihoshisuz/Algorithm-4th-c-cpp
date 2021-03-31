#pragma once

#include <memory>
#include <queue>
#include <stack>
#include "4.0-Graph.h"

class BreadthFirstPaths
{
public:
	BreadthFirstPaths(std::ifstream& input, int s);
	BreadthFirstPaths(const BreadthFirstPaths& bfp) = delete;
	BreadthFirstPaths& operator=(const BreadthFirstPaths& bfp) = delete;
	~BreadthFirstPaths();

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

void BreadthFirstPaths::search(Graph& g, int v)
{
	marked[v] = true;
	std::queue<int> q;
	q.push(v);
	while (!q.empty())
	{
		Bag& b = g.Bag_with_v(q.front());
		for (int i = 0; i < b.size(); ++i)
		{
			int w = b.getValue();
			b.incr();
			if (!marked[w])
			{
				marked[w] = true;
				edgeTo[w] = q.front();
				q.push(w);
			}
		}
		q.pop();
	}
}

BreadthFirstPaths::BreadthFirstPaths(std::ifstream& input, int s):G(input), start(s)
{
	std::allocator<bool> alloc_bool;
	std::allocator<int> alloc_int;
	int n = G.size_Vertexes();
	marked = alloc_bool.allocate(n);
	edgeTo = alloc_int.allocate(n);
	for (int i = 0; i < n; ++i)
	{
		alloc_bool.construct(marked + i, false);
		alloc_int.construct(edgeTo + i);
	}
	edgeTo[start] = s;
	search(G, start);
}

BreadthFirstPaths::~BreadthFirstPaths()
{
	std::allocator<bool> alloc_bool;
	std::allocator<int> alloc_int;
	int size = G.size_Vertexes();
	for (int i = 0; i < size; ++i)
	{
		alloc_bool.destroy(marked + i);
		alloc_int.destroy(edgeTo + 1);
	}
	alloc_bool.deallocate(marked, size);
	alloc_int.deallocate(edgeTo, size);
}

std::stack<int>& BreadthFirstPaths::pathTo(std::stack<int>& s, int v)
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
#pragma once

#include "4.0-Graph.h"
#include <stack>

class CC
{
public:
	CC(std::ifstream& input);
	CC(const CC& dfp) = delete;
	CC& operator=(const CC& dfp) = delete;
	~CC();

	int size() { return G.size_Vertexes(); }
	int id_count(int v) { return id[v]; }
	int components() { return count; }
	bool connented(int v, int w) { return marked[v] == marked[w]; }

private:
	bool* marked;
	int* id;
	int count;
	Graph G;
	void search(Graph& g, int v);
};

CC::CC(std::ifstream& input):G(input)
{
	std::allocator<bool> alloc_bool;
	std::allocator<int> alloc_int;
	marked = alloc_bool.allocate(G.size_Vertexes());
	id = alloc_int.allocate(G.size_Vertexes());
	for (int i = 0; i < G.size_Vertexes(); ++i)
	{
		alloc_bool.construct(marked + i, false);
		alloc_int.construct(id + i);
	}
	count = 0;
	for (int s = 0; s < G.size_Vertexes(); ++s)
	{
		if (!marked[s])
		{
			id[s] = count;
			search(G, s);
			++count;
		}
	}
}

CC::~CC()
{
	std::allocator<bool> alloc_bool;
	std::allocator<int> alloc_int;
	for (int i = 0; i < G.size_Vertexes(); ++i)
	{
		alloc_bool.destroy(marked + i);
		alloc_int.destroy(id + i);
	}
	alloc_bool.deallocate(marked, G.size_Vertexes());
	alloc_int.deallocate(id, G.size_Vertexes());
}

void CC::search(Graph& g, int v)
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
			id[w] = count;
			search(g, w);
		}
	}
}

#pragma once

#include <stack>
#include "Digraph.h"
#include <iostream>

class DirectedCycle
{
public:
	DirectedCycle(Digraph& G);
	DirectedCycle(const DirectedCycle&) = delete;
	DirectedCycle& operator=(const DirectedCycle&) = delete;
	~DirectedCycle();

	bool hasCycle() { return !cycle.empty(); }
	void showCycle();
	
private:
	int size;
	bool* marked;
	bool* onStack;
	int* edgeTo;
	std::stack<int> cycle;
	void dfs(Digraph& G, int v);
};

void DirectedCycle::dfs(Digraph& G, int v)
{
	if (!cycle.empty())
		return;
	onStack[v] = true;
	marked[v] = true;
	Bag& b = G.Bag_with_v(v);
	for (int i = 0; i < b.size(); ++i)
	{
		int w = b.getValue();
		b.incr();
		if (!marked[w])
		{
			edgeTo[w] = v;
			dfs(G, w);
		}
		else if (onStack[w])
		{
			for (int x = v; x != w; x = edgeTo[x])
				cycle.push(x);
			cycle.push(w);
			cycle.push(v);
		}
	}
	onStack[v] = false;
}


DirectedCycle::DirectedCycle(Digraph& G):size(G.size_Vertexes())
{
	std::allocator<bool> alloc_bool;
	std::allocator<int> alloc_int;
	marked = alloc_bool.allocate(size);
	onStack = alloc_bool.allocate(size);
	edgeTo = alloc_int.allocate(size);
	for (int i = 0; i < size; ++i)
	{
		alloc_bool.construct(marked + i, false);
		alloc_bool.construct(onStack + i, false);
		alloc_int.construct(edgeTo + i, INT_MAX);
	}
	for (int v = 0; v < size; ++v)
	{
		if (!marked[v])
			dfs(G, v);
	}
}

DirectedCycle::~DirectedCycle()
{
	std::allocator<bool> alloc_bool;
	std::allocator<int> alloc_int;
	for (int i = 0; i < size; ++i)
	{
		alloc_bool.destroy(marked + i);
		alloc_bool.destroy(onStack + i);
		alloc_int.destroy(edgeTo + i);
	}
	alloc_bool.deallocate(marked, size);
	alloc_bool.deallocate(onStack, size);
	alloc_int.deallocate(edgeTo, size);
}

void DirectedCycle::showCycle()
{
	while (!cycle.empty())
	{
		std::cout << cycle.top() << " ";
		cycle.pop();
	}
}
#pragma once

#include "Digraph.h"
#include <vector>

class DirectedDFS
{
public:
	DirectedDFS(Digraph& G, int s);
	DirectedDFS(Digraph& G, const std::vector<int>& s);
	DirectedDFS(const DirectedDFS&) = delete;
	DirectedDFS& operator=(const DirectedDFS&) = delete;
	~DirectedDFS();

	bool isMarked(int v) { return marked[v]; }


private:
	bool* marked;
	int start;
	int N;
	void dfs(Digraph& G, int v);
};

DirectedDFS::DirectedDFS(Digraph& G, int s) :start(s),N(G.size_Vertexes())
{
	std::allocator<bool> alloc;
	marked = alloc.allocate(N);
	for (int i = 0; i < N; ++i)
		alloc.construct(marked + i, false);
	dfs(G, s);
}

DirectedDFS::DirectedDFS(Digraph& G, const std::vector<int>& v) :N(G.size_Vertexes())
{
	std::allocator<bool> alloc;
	marked = alloc.allocate(N);
	for (int i = 0; i < N; ++i)
		alloc.construct(marked + i, false);
	for (auto s : v)
		dfs(G, s);
}

DirectedDFS::~DirectedDFS()
{
	std::allocator<bool> alloc;
	for (int i = 0; i < N; ++i)
		alloc.destroy(marked + i);
	alloc.deallocate(marked, N);
}

void DirectedDFS::dfs(Digraph& G, int v)
{
	marked[v] = true;
	Bag& b = G.Bag_with_v(v);
	for (int i = 0; i < b.size(); ++i)
	{
		int w = b.getValue();
		b.incr();
		if (!marked[w])
			dfs(G, w);
	}
}
#pragma once

#include <iostream>
#include <memory>
#include <stack>
#include <queue>
#include "Digraph.h"

class DepthFirstOrder
{
public:
	DepthFirstOrder(Digraph& G);
	DepthFirstOrder(const Digraph&) = delete;
	DepthFirstOrder& operator=(const Digraph&) = delete;
	~DepthFirstOrder();
	
	void show_pre();
	void show_post();
	void show_reverse_post();
	std::queue<int>& return_post();

private:
	bool* marked;
	std::queue<int> pre;
	std::queue<int> post;
	std::stack<int> reverse_post;
	void dfs(Digraph& G, int v);
};

void DepthFirstOrder::dfs(Digraph& G, int v)
{
	pre.push(v);
	marked[v] = true;
	Bag& b = G.Bag_with_v(v);
	for (int i = 0; i < b.size(); ++i)
	{
		int w = b.getValue();
		b.incr();
		if (!marked[w])
			dfs(G, w);
	}
	post.push(v);
	reverse_post.push(v);
}

DepthFirstOrder::DepthFirstOrder(Digraph& G)
{
	std::allocator<bool> alloc_bool;
	marked = alloc_bool.allocate(G.size_Vertexes());
	for (int i = 0; i < G.size_Vertexes(); ++i)
		alloc_bool.construct(marked + i, false);
	for (int v = 0; v < G.size_Vertexes(); ++v)
	{
		if (!marked[v])
			dfs(G, v);
	}
}

DepthFirstOrder::~DepthFirstOrder()
{
	std::allocator<bool> alloc_bool;
	for (int i = 0; i < pre.size(); ++i)
		alloc_bool.destroy(marked + i);
	alloc_bool.deallocate(marked, pre.size());
}

void DepthFirstOrder::show_pre()
{
	while (!pre.empty())
	{
		std::cout << pre.front() << " ";
		pre.pop();
	}
	std::cout << std::endl;
}

void DepthFirstOrder::show_post()
{
	while (!post.empty())
	{
		std::cout << post.front() << " ";
		post.pop();
	}
	std::cout << std::endl;
}

void DepthFirstOrder::show_reverse_post()
{
	while (!reverse_post.empty())
	{
		std::cout << reverse_post.top() << " ";
		reverse_post.pop();
	}
	std::cout << std::endl;
}

std::queue<int>& DepthFirstOrder::return_post()
{
	return post;
}
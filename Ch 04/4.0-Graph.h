#pragma once

#include <iostream>
#include <fstream>
#include <memory>
#include "Bag_Int.h"

class Graph
{
public:
	Graph(int v);
	Graph(std::ifstream& input);
	Graph(Graph& g);
	Graph& operator=(Graph& g);
	~Graph();

	void addEdge(int v, int w);
	int size_Vertexes() { return V; }
	int size_Edges() { return E; }
	void show();
	Bag& Bag_with_v(int v) { return bags[v]; }


private:
	int V;
	int E;
	int use;
	Bag* bags;
};

Graph::Graph(int v) :V(v), E(0), use(1)
{
	std::allocator<Bag> alloc;
	bags = alloc.allocate(v);
	Bag* p = bags;
	for (int i = 0; i < v; ++i)
		alloc.construct(p++);
}

Graph::Graph(std::ifstream& input)
{
	input >> V >> E;
	use = 1;
	std::allocator<Bag> alloc;
	bags = alloc.allocate(V);
	Bag* p = bags;
	for (int i = 0; i < V; ++i)
		alloc.construct(p++);
	int v;
	int w;
	while (input >> v >> w)
		addEdge(v, w);
}

Graph::Graph(Graph& g)
{
	V = g.V;
	E = g.E;
	use = ++g.use;
	bags = g.bags;
}

Graph& Graph::operator=(Graph& g) 
{
	++g.use;
	if (--use == 0)
	{
		std::allocator<Bag> alloc;
		Bag* p = bags;
		for (int i = 0; i < V; ++i)
			alloc.destroy(p++);
		alloc.deallocate(bags, V);
	}
	V = g.V;
	E = g.E;
	use = g.use;
	bags = g.bags;
	return *this;
}

Graph::~Graph()
{
	if (--use == 0)
	{
		std::allocator<Bag> alloc;
		Bag* p = bags;
		for (int i = 0; i < V; ++i)
			alloc.destroy(p++);
		alloc.deallocate(bags, V);
	}
}

void Graph::show()
{
	for (int i = 0; i < V; ++i)
		bags[i].show();
}

void Graph::addEdge(int v, int w)
{
	bags[v].add(w);
	bags[w].add(v);
}

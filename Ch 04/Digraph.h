#pragma once

#include <iostream>
#include <fstream>
#include <memory>
#include "Bag_Int.h"

class Digraph
{
public:
	Digraph(int v);
	Digraph(std::ifstream& input);
	Digraph(Digraph& g);
	Digraph& operator=(Digraph& g);
	~Digraph();

	void addEdge(int v, int w);
	int size_Vertexes() { return V; }
	int size_Edges() { return E; }
	int count() { return use; }
	void show();
	Bag& Bag_with_v(int v) { return bags[v]; }
	std::shared_ptr<Digraph> reverse();


private:
	int V;
	int E;
	int use;
	Bag* bags;
};

Digraph::Digraph(int v) :V(v), E(0), use(1)
{
	std::allocator<Bag> alloc;
	bags = alloc.allocate(v);
	Bag* p = bags;
	for (int i = 0; i < v; ++i)
		alloc.construct(p++);
}

Digraph::Digraph(std::ifstream& input)
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

Digraph::Digraph(Digraph& g)
{
	V = g.V;
	E = g.E;
	use = ++g.use;
	bags = g.bags;
}

Digraph& Digraph::operator=(Digraph& g)
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

Digraph::~Digraph()
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

void Digraph::show()
{
	for (int i = 0; i < V; ++i)
	{
		std::cout << i << ": ";
		bags[i].show();
	}
}

void Digraph::addEdge(int v, int w)
{
	bags[v].add(w);
	++E;
}

std::shared_ptr<Digraph> Digraph::reverse()
{
	Digraph R(V);
	for (int v = 0; v < V; ++v)
	{
		Bag& b = bags[v];
		for (int i = 0; i < b.size(); ++i)
		{
			int w = b.getValue();
			b.incr();
			R.addEdge(w, v);
		}
	}
	return std::make_shared<Digraph>(R);
}

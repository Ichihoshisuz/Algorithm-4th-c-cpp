#pragma once

#include "Digraph.h"
#include "4.4.1-DirectedCycle.h"
#include "DepthFirstOrder.h"

class Topological
{
public:
	Topological(Digraph& G);
	Topological(const Topological&) = delete;
	Topological& operator=(const Topological&) = delete;
	~Topological() {  };

	bool isDAG() { return order.empty(); }
	void show_order();

private:
	std::queue<int> order;
};

Topological::Topological(Digraph& G)
{
	DirectedCycle cyclefinder(G);
	if (!cyclefinder.hasCycle())
	{
		DepthFirstOrder dfo(G);
		order = dfo.return_post();
	}
}

void Topological::show_order()
{
	while (!order.empty())
	{
		std::cout << order.front() << " ";
		order.pop();
	}
	std::cout << std::endl;
}
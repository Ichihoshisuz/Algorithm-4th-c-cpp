#pragma once

#include <memory>
#include <iostream>
class Node
{
	friend class Bag;
public:
	Node() : val(0), next(nullptr) {}
	Node(int v, Node* p) : val(v), next(p) {}
	Node(const Node& p) :val(p.val), next(p.next) {}
	Node& operator=(const Node& p)
	{
		val = p.val;
		next = p.next;
		return *this;
	}
	~Node() {}

	Node& operator++();
	Node operator++(int);

	int getValue() { return val; }

private:
	int val;
	Node* next;
};

Node& Node::operator++()
{
	if (next == nullptr)
		return *this;
	val = next->val;
	next = next->next;
	return *this;
}

Node Node::operator++(int)
{
	if (next == nullptr)
		return *this;
	Node ret = *this;
	++* this;
	return ret;
}

class Bag
{
public:
	Bag() :N(0),use(1), top(nullptr),curr(nullptr) {}
	explicit Bag(Bag& b)
	{
		N = b.N;
		use = ++b.use;
		top = b.top;
		curr = b.curr;
	}
	Bag& operator=(Bag& b)
	{
		++b.use;
		if (--use == 0)
		{
			for (int i = 0; i < N; ++i)
			{
				Node* p = top;
				top = top->next;
				std::allocator<Node> alloc;
				alloc.destroy(p);
				alloc.deallocate(p, 1);
			}
		}
		N = b.N;
		use = b.use;
		top = b.top;
		curr = b.curr;
		return *this;
	}


	bool isEmpty() { return N == 0; }
	int size() { return N; }
	void add(int val);
	int getValue() { return curr->getValue(); }
	void incr();
	void show();

	~Bag()
	{
		if (--use == 0)
		{
			for (int i = 0; i < N; ++i)
			{
				Node* p = top;
				top = top->next;
				std::allocator<Node> alloc;
				alloc.destroy(p);
				alloc.deallocate(p, 1);
			}
		}
	}
private:
	int N;
	int use;
	Node* top;
	Node* curr;
};

// 注意next其实向下指。
void Bag::add(int val)
{
	Node* p = top;
	std::allocator<Node> alloc;
	top = alloc.allocate(1);
	curr = top;
	alloc.construct(top, val, p);
	++N;
}

void Bag::show()
{
	for (Node* p = top; p != nullptr; p = p->next)
		std::cout << p->val << " ";
	std::cout << std::endl;
}

void Bag::incr()
{
	if (curr->next == nullptr)
	{
		curr = top;
		return;
	}
	curr = curr->next;
}
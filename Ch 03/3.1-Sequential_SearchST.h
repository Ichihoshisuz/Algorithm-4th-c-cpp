#pragma once

#include <stdlib.h>
#include <iostream>
#include <limits>

struct Node
{
	char Key;
	int value;
	struct Node* next;
};

typedef struct Node Node;

void ini(Node* p, char c, int v)
{
	p = (Node*)malloc(sizeof(Node));
	p->Key = c;
	p->value = v;
	p->next = nullptr;
}

void ini(Node* p)
{
	ini(p, '\0', 0);
}

Node*& new_Node(char c, int v, Node* first)
{
	Node* p = (Node*)malloc(sizeof(Node));
	p->Key = c;
	p->value = v;
	p->next = first;
	return p;
}

bool equals(char k1, char k2)
{
	if (k1 == k2)
		return true;
	return false;
}

int get(Node*& first, char c)
{
	for (Node* x = first; x != nullptr; x = x->next)
	{
		if (equals(c, x->Key))
			return x->value;
	}
	return std::numeric_limits<int>::max();
}

void put(Node*& first, char c, int v)
{
	for (Node* x = first; x != nullptr; x = x->next)
	{
		if (equals(c, x->Key))
		{
			x->value = v;
			return;
		}
	}
	first = new_Node(c, v, first);
	return;
}

void delete_Node(Node*& first, char c)
{
	if (first != nullptr)
	{
		Node* prec = first;
		Node* curr = first->next;

		if (equals(c, prec->Key))
		{
			first = curr;
			free(prec);
			return;
		}

		while (curr != nullptr)
		{
			if (equals(c, curr->Key))
			{
				prec->next = curr->next;
				free(curr);
				return;
			}
			prec = prec->next;
			curr = curr->next;
		}
	}
	return;
}

void delete_Node(Node*& first)
{
	if (first != nullptr)
	{
		while (first != nullptr)
		{
			Node* x = first->next;
			free(first);
			first = x;
		}
	}
	std::cout << "OK!" << std::endl;
	return;
}

int size(Node* first)
{
	int count = 0;
	for (Node* x = first; x != nullptr; x = x->next)
		++count;
	return count;
}

void show(Node* first)
{
	for (Node* x = first; x != nullptr; x = x->next)
	{
		std::cout << x->Key << "  " << x->value << std::endl; 
	}
}
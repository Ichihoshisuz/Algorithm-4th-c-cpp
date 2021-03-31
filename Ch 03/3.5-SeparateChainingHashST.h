#pragma once

#include "3.1-Sequential_SearchST.h"
#include <iostream>
#include <string>

struct SeparateChainingHashST
{
	int N;
	int M;
	Node** array_p;
};

void ini_SeparateChainingHashST(SeparateChainingHashST& st, int m)
{
	if (m == 0)
		return;
	st.M = m;
	st.array_p = (Node**)malloc(sizeof(Node*) * m);
	for (int i = 0; i < m; ++i)
		st.array_p[i] = nullptr;
}

void ini_SeparateChainingHashST(SeparateChainingHashST& st)
{
	ini_SeparateChainingHashST(st, 37);
}

unsigned hash_SCH(const std::string& key, int m)
{
	unsigned hashVal = 0;
	for (auto p : key)
		hashVal = 37 * hashVal + p;
	return hashVal % m;
}

unsigned hash_SCH(char key, int m)
{
	return key % m;
}

int get_SCH(SeparateChainingHashST& st, char key)
{
	return get(st.array_p[hash_SCH(key, st.M)], key);
}

void put_SCH(SeparateChainingHashST& st, char key, int val)
{
	int index = hash_SCH(key, st.M);
	put(st.array_p[index], key, val);
}

void put_SCH(SeparateChainingHashST& st, char key, int val, int offset)
{
	put(st.array_p[offset], key, val);
}

void keys()
{
	return;
}

void show_SCH(SeparateChainingHashST& st)
{
	for (int i = 0; i < st.M; ++i)
	{
		for (Node* x = st.array_p[i]; x != nullptr; x = x->next)
		{
			std::cout << x->Key << "  " << x->value << " ";
		}
		std::cout << std::endl;
	}
}

void delete_SCH(SeparateChainingHashST& st)
{
	for (int i = 0; i < st.M; ++i)
	{
		delete_Node(st.array_p[i]);
	}
	free(st.array_p);
}
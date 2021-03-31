#pragma once

#include <iostream>
#include <stdlib.h>
#include <stdexcept>
#include <cmath>

struct LinearProbingHashST
{
	int N;
	int M;
	char* keys;
	int* vals;
};

void ini_LPH(LinearProbingHashST& st, int m)
{
	if (m == 0)
		return;
	st.N = 0;
	st.M = m;
	st.keys = (char*)malloc(sizeof(char) * m);
	st.vals = (int*)malloc(sizeof(int) * m);
	for (int i = 0; i < m; ++i)
	{
		st.keys[i] = '\0';
		st.vals[i] = INT_MAX;
	}

}

void ini_LPH(LinearProbingHashST& st)
{
	ini_LPH(st, 16);
}

unsigned hash_LPH(char key ,int m)
{
	return key % 7;
}

void resize(LinearProbingHashST& st, int capacity)
{
	if (capacity <= st.N)
		return;
	char* keys = (char*)malloc(sizeof(char) * capacity);
	int* vals = (int*)malloc(sizeof(int) * capacity);
	if (keys == NULL || vals == NULL)
		return;
	for (int i = 0; i < capacity; ++i)
	{
		keys[i] = '\0';
		vals[i] = INT_MAX;
	}
	for (int i = 0; i < st.M; ++i)
	{
		if (st.keys[i] != '\0')
		{
			unsigned j = hash_LPH(st.keys[i], capacity);
			while (keys[j] != '\0')
				j = (j + 1) % capacity;
			keys[j] = st.keys[i];
			vals[j] = st.vals[i];
		}
	}
	free(st.keys);
	free(st.vals);
	st.keys = keys;
	st.vals = vals;
	st.M = capacity;
}

void put_LPH(LinearProbingHashST& st, char key, int val)
{
	if (st.N >= st.M / 2)
		resize(st, st.M * 2);
	unsigned i = hash_LPH(key, st.M);
	while (st.keys[i] != '\0')
	{
		if (key == st.keys[i])
		{
			st.vals[i] = val;
			return;
		}
		i = (i + 1) % st.M;
	}
	st.keys[i] = key;
	st.vals[i] = val;
	++st.N;
}

void put_LPH(LinearProbingHashST& st, char key, int val, int offset)
{

	unsigned i = offset;
	while (st.keys[i] != '\0')
	{
		if (key == st.keys[i])
		{
			st.vals[i] = val;
			return;
		}
		i = (i + 1) % st.M;
	}
	st.keys[i] = key;
	st.vals[i] = val;
	++st.N;
}


int get_LPH(LinearProbingHashST& st, char key)
{
	if (st.N == 0)
		return INT_MAX;
	for (int i = hash_LPH(key, st.M); st.keys[i] != '\0'; i = (i + 1) % st.M)
	{
		if (st.keys[i] == key)
			return st.vals[i];
	}
	return INT_MIN;
}

bool contains_LPH(LinearProbingHashST& st, char key)
{
	if (st.N == 0)
		return false;
	for (unsigned i = hash_LPH(key, st.M); st.keys[i] != '\0'; i = (i + 1) % st.M)
	{
		if (st.keys[i] == key)
			return true;
	}
	return false;
}

void delete_LPH(LinearProbingHashST& st)
{
	free(st.keys);
	free(st.vals);
}

void delete_LPH(LinearProbingHashST& st, char key)
{
	if (!contains_LPH(st, key))
		return;
	unsigned i = hash_LPH(key, st.M);
	while (st.keys[i] != key)
		i = (i + 1) % st.M;
	st.keys[i] = '\0';
	st.vals[i] = INT_MAX;
	--st.N;
	if (st.N > 0 && st.N == st.M / 8)
	{
		resize(st, st.M / 2);
		return;
	}
	i = (i + 1) % st.M;
	while (st.keys[i] != '\0')
	{
		char tempKey = st.keys[i];
		int tempVal = st.vals[i];
		st.keys[i] = '\0';
		st.vals[i] = INT_MAX;
		--st.N;
		put_LPH(st, tempKey, tempVal);
		i = (i + 1) % st.M;
	}
}

void show_LPH(LinearProbingHashST& st)
{
	if (st.N == 0)
		return;
	for (int i = 0; i < st.M; ++i)
	{
		if (st.vals[i] == INT_MAX)
		{
			std::cout << "   ";
			continue;
		}
		std::cout << st.keys[i] << "  ";
	}
	std::cout << std::endl;

	for (int i = 0; i < st.M; ++i)
	{
		if (st.vals[i] == INT_MAX)
		{
			std::cout << "   ";
			continue;
		}
		int h = hash_LPH(st.keys[i], st.M);
		std::cout << h << " ";
		if (h < 10)
			std::cout << " ";
	}
	std::cout << std::endl;
	for (int i = 0; i < st.M; ++i)
	{
		if (st.vals[i] == INT_MAX)
		{
			std::cout << "   ";
			continue;
		}
		std::cout << st.vals[i] << " ";
		if (st.vals[i] < 10)
			std::cout << " ";
	}
	
	std::cout << std::endl;
}
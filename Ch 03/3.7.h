#pragma once
#pragma once

#include <iostream>
#include <memory>
#include <stdexcept>
#include <cmath>

class LinearProbingHashST
{
public:
	LinearProbingHashST() :LinearProbingHashST(17) {}
	LinearProbingHashST(int m);
	LinearProbingHashST(const LinearProbingHashST& st) = delete;
	LinearProbingHashST& operator=(const LinearProbingHashST& st) = delete;
	~LinearProbingHashST();
	
	bool contains(char key);
	void put(char key, int val);
	void put(char key, int val, int offset);
	int get(char key);
	void delete_elements(char key);
	void show();

private:
	int N;
	int M;
	char* keys;
	int* vals;
	unsigned hash(char key, int m);
	void resize(int capacity);
};

LinearProbingHashST::LinearProbingHashST(int m):N(0)
{
	if (m == 0)
		M = 1;
	M = m;
	std::allocator<char> alloc_char;
	std::allocator<int> alloc_int;
	keys = alloc_char.allocate(M);
	vals = alloc_int.allocate(M);
	for (int i = 0; i < M; ++i)
	{
		alloc_char.construct(keys + i, '\0');
		alloc_int.construct(vals + i, INT_MAX);
	}
}

LinearProbingHashST::~LinearProbingHashST()
{
	std::allocator<char> alloc_char;
	std::allocator<int> alloc_int;
	for (int i = 0; i < M; ++i)
	{
		alloc_char.destroy(keys + i);
		alloc_int.destroy(vals + i);
	}
	alloc_char.deallocate(keys, M);
	alloc_int.deallocate(vals, M);
}

bool LinearProbingHashST::contains(char key)
{
	if (N == 0)
		return false;
	for (unsigned i = hash(key, M); keys[i] != '\0'; i = (i + 1) % M)
	{
		if (keys[i] == key)
			return true;
	}
	return false;
}

unsigned LinearProbingHashST::hash(char key, int m)
{
	return key % 7;
}

void LinearProbingHashST::resize(int capacity)
{
	std::allocator<char> alloc_char;
	std::allocator<int> alloc_int;
	char* temp_keys = alloc_char.allocate(capacity);
	int* temp_vals = alloc_int.allocate(capacity);
	for (int i = 0; i < capacity; ++i)
	{
		alloc_char.construct(temp_keys + i, '\0');
		alloc_char.construct(temp_vals + i, INT_MAX);
	}
	for (int i = 0; i < M; ++i)
	{
		if (keys[i] != '\0')
		{
			unsigned j = hash(keys[i], capacity);
			while (temp_keys[j] != '\0')
				j = (j + 1) % capacity;
			temp_keys[j] = keys[i];
			temp_vals[j] = vals[i];
		}
	}
	for (int i = 0; i < M; ++i)
	{
		alloc_char.destroy(keys + i);
		alloc_int.destroy(vals + i);
	}
	keys = temp_keys;
	vals = temp_vals;
	M = capacity;
}

void LinearProbingHashST::put(char key, int val)
{
	if (N >= M / 2)
		resize(M * 2);
	unsigned i = hash(key, M);
	while (keys[i] != '\0')
	{
		if (keys[i]==key)
		{
			vals[i] = val;
			return;
		}
		i = (i + 1) % M;
	}
	keys[i] = key;
	vals[i] = val;
	++N;
}

void LinearProbingHashST::put(char key, int val, int offset)
{

	unsigned i = offset;
	while (keys[i] != '\0')
	{
		if (key == keys[i])
		{
			vals[i] = val;
			return;
		}
		i = (i + 1) % M;
	}
	keys[i] = key;
	vals[i] = val;
	++N;
}

int LinearProbingHashST::get(char key)
{
	if (N == 0)
		return INT_MAX;
	for (int i = hash(key, M); keys[i] != '\0'; i = (i + 1) % M)
	{
		if (keys[i] == key)
			return vals[i];
	}
	return INT_MIN;
}

void LinearProbingHashST::delete_elements(char key)
{
	if (!contains(key))
		return;
	unsigned i = hash(key, M);
	while (keys[i] != key)
		i = (i + 1) % M;
	keys[i] = '\0';
	vals[i] = INT_MAX;
	--N;
	if (N > 0 && N == M / 8)
	{
		resize(M / 2);
		return;
	}
	i = (i + 1) % M;
	while (keys[i] != '\0')
	{
		char temp_key = keys[i];
		int temp_val = vals[i];
		keys[i] = '\0';
		vals[i] = INT_MAX;
		--N;
		put(temp_key, temp_val);
		i = (i + 1) % M;
	}
}

void LinearProbingHashST::show()
{
	if (N == 0)
		return;
	for (int i = 0; i < M; ++i)
	{
		if (vals[i] == INT_MAX)
		{
			std::cout << "   ";
			continue;
		}
		std::cout << keys[i] << "  ";
	}
	std::cout << std::endl;

	for (int i = 0; i < M; ++i)
	{
		if (vals[i] == INT_MAX)
		{
			std::cout << "   ";
			continue;
		}
		int h = hash(keys[i], M);
		std::cout << h << " ";
		if (h < 10)
			std::cout << " ";
	}
	std::cout << std::endl;
	for (int i = 0; i < M; ++i)
	{
		if (vals[i] == INT_MAX)
		{
			std::cout << "   ";
			continue;
		}
		std::cout << vals[i] << " ";
		if (vals[i] < 10)
			std::cout << " ";
	}

	std::cout << std::endl;
}
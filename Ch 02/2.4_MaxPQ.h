#pragma once
#include <iostream>
#include <stdlib.h>
#include <cmath>

struct MaxPQ
{
	char* Keys;
	int N;
};

typedef struct MaxPQ MaxPQ;

void iniMaxPQ(MaxPQ& pq)
{
	pq.N = 0;
	pq.Keys = (char*)malloc(sizeof(char));
}

void iniMaxPQ(MaxPQ& pq, int maxN)
{
	pq.N = 0;
	pq.Keys = (char*)malloc(maxN * sizeof(char));
}

int size_MaxPQ(MaxPQ& pq)
{
	return pq.N;
}

bool isEmpty(MaxPQ& pq)
{
	return pq.N == 0;
}

bool less_MaxPQ(MaxPQ& pq, int i, int j)
{
	return pq.Keys[i] < pq.Keys[j];
}

void exch_MaxPQ(MaxPQ& pq, int i, int j)
{
	char temp = pq.Keys[i];
	pq.Keys[i] = pq.Keys[j];
	pq.Keys[j] = temp;
}

void swim(MaxPQ& pq, int k)
{
	while (k > 1 && less_MaxPQ(pq, k / 2, k))
	{
		exch_MaxPQ(pq, k / 2, k);
		k = k / 2;
	}
}

void sink(MaxPQ& pq, int k)
{
	while (2 * k <= pq.N)
	{
		int j = 2 * k;
		if (j < pq.N && less_MaxPQ(pq, j, j + 1))
			++j;
		if (!less_MaxPQ(pq, k, j))
			break;
		exch_MaxPQ(pq, k, j);
		k = j;
	}
}

void insert(MaxPQ& pq, char c)
{
	++pq.N;
	pq.Keys[pq.N] = c;
	swim(pq, pq.N);
}

char delMax(MaxPQ& pq)
{
	char temp = pq.Keys[1];
	exch_MaxPQ(pq, 1, pq.N);
	--pq.N;
	sink(pq, 1);
	return temp;
}

void show_MaxPQ(MaxPQ& pq)
{
	int count = 1;
	for (int i = 1; i < pq.N + 1; ++i)
	{
		if (i == pow(2, count))
		{
			std::cout << std::endl;
			++count;
		}
		std::cout << pq.Keys[i] << " ";
	}
	std::cout << std::endl;
}


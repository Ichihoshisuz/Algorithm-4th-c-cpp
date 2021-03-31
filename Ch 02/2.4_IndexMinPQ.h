#pragma once
#include <iostream>
#include <stdexcept>
#include <stdlib.h>
#include <cmath>

struct IndexMinPQ
{
	char* Keys;
	int* pq;
	int* qp;
	int N;
	int curr;

	IndexMinPQ(size_t maxN)
	{
		N = maxN;
		curr = 0;
		Keys = (char*)malloc((maxN+1) * sizeof(char));
		pq = (int*)malloc((maxN+1) * sizeof(int));
		qp = (int*)malloc((maxN+1) * sizeof(int));
		for (int i = 0; i <= maxN; ++i)
		{
			pq[i] = 0;
			qp[i] = -1;
		}
	}
	~IndexMinPQ()
	{
		free(pq);
		free(qp);
		free(Keys);
	}
};

typedef struct IndexMinPQ IndexMinPQ;

void ini_IndexMinPQ(IndexMinPQ& index_pq, int maxN)
{

}

int size_IndexMinPQ(IndexMinPQ& index_pq)
{
	return index_pq.curr;
}

bool isEmpty(IndexMinPQ& index_pq)
{
	return index_pq.curr == 0;
}

bool contains(IndexMinPQ& index_pq, int k)
{
	if (k < index_pq.curr)
		return index_pq.qp[k] != -1; 
	else
		throw std::runtime_error("数组越界");
}

bool more_IndexMinPQ(IndexMinPQ& index_pq, int index1, int index2)
{
	int k1 = index_pq.pq[index1];
	int k2 = index_pq.pq[index2];
	return index_pq.Keys[k1] > index_pq.Keys[k2];
}

void exch_IndexMinPQ(IndexMinPQ& index_pq, int index1, int index2)
{

	int k1 = index_pq.pq[index1];
	int k2 = index_pq.pq[index2];
	index_pq.qp[k1] = index2;
	index_pq.qp[k2] = index1;
	index_pq.pq[index1] = k2;
	index_pq.pq[index2] = k1;
}

void swim(IndexMinPQ& index_pq, int k)
{
	while (k > 1 && more_IndexMinPQ(index_pq, k / 2, k))
	{
		exch_IndexMinPQ(index_pq, k / 2, k);
		k = k / 2;
	}
}

void sink(IndexMinPQ& index_pq, int k)
{
	while (k * 2 <= index_pq.curr)
	{
		int j = 2 * k;
		if (j < index_pq.curr && more_IndexMinPQ(index_pq, j, j + 1))
			++j;
		if (!more_IndexMinPQ(index_pq, k, j))
			break;
		exch_IndexMinPQ(index_pq, k, j);
		k = j;
	}
}


void insert_IndexMinPQ(IndexMinPQ& index_pq, int k, char key)
{
	if (k <= index_pq.N)
	{
		++index_pq.curr;
		index_pq.pq[index_pq.curr] = k;
		index_pq.qp[k] = index_pq.curr;
		index_pq.Keys[k] = key;
		swim(index_pq, index_pq.curr);
		
	}
	else
		std::cout << "插入失败" << std::endl;
}

void change_IndexMinPQ(IndexMinPQ& index_pq, int k, char key)
{
	if (contains(index_pq, k))
	{
		index_pq.Keys[k] = key;
		sink(index_pq, index_pq.qp[k]);
		swim(index_pq, index_pq.qp[k]);
	}
	else
		std::cout << "非法访问" << std::endl;
}

void delete_IndexMinPQ(IndexMinPQ& index_pq, int k)
{
	if (contains(index_pq, k))
	{
		int index = index_pq.qp[k];
		exch_IndexMinPQ(index_pq, index, index_pq.curr);
		--index_pq.curr;
		swim(index_pq, index_pq.curr);
		sink(index_pq, index_pq.curr);
		index_pq.qp[k] = -1;
	}
}

int delMin(IndexMinPQ& index_pq)
{
	int i = index_pq.pq[1];
	exch_IndexMinPQ(index_pq, 1, index_pq.curr);
	--index_pq.curr;
	sink(index_pq, 1);
	index_pq.qp[index_pq.pq[index_pq.curr + 1]] = -1;
	return i;
}

char min(IndexMinPQ& index_pq)
{
	return index_pq.Keys[index_pq.pq[1]];
}

int min_Index(IndexMinPQ& index_pq)
{
	return index_pq.pq[1];
}


void show_with_Index(IndexMinPQ& index_pq)
{
	int count = 1;
	for (int i = 1; i <= index_pq.curr; ++i)
	{
		if (i == pow(2, count))
		{
			std::cout << std::endl;
			++count;
		}
		std::cout << index_pq.Keys[index_pq.pq[i]] << " ";
	}
	std::cout << std::endl;
}

void show(IndexMinPQ& index_pq)
{

}
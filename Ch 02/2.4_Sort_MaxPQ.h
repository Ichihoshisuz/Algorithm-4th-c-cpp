#pragma once

#include "LIFO_动态调整数组大小的实现.h"
#include "Sort_Example.h"

bool less_MaxPQ_Si(Stack_Of_Int& si, int i, int j)
{
	return si.a[--i] < si.a[--j];
}

void exch_MaxPQ_Si(Stack_Of_Int& si, int index1, int index2)
{
	int temp = si.a[--index1];
	si.a[index1] = si.a[--index2];
	si.a[index2] = temp;
}

void sink(Stack_Of_Int& si, int k, int N)
{
	while (2 * k <= N)
	{
		int j = 2 * k;
		if (j < N && less_MaxPQ_Si(si, j, j + 1))
			++j;
		if (!less_MaxPQ_Si(si, k, j))
			break;
		exch_MaxPQ_Si(si, k, j);
		k = j;
	}
}

void MaxPQ_Sort(Stack_Of_Int& si)
{
	int N = size(si);
	for (int i = N / 2; i >= 1; --i)
		sink(si, i, N);
	while (N > 1)
	{
		exch_MaxPQ_Si(si, 1, N);
		--N;
		sink(si, 1, N);
	}
}
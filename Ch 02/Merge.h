#pragma once

#include "Sort_Example.h"
#include <cmath>

void merge(Stack_Of_Int& si, Stack_Of_Int& aux, int lo, int mid, int hi)
{
	int i = lo;
	int j = mid + 1;

	for (int k = i; k <= hi; ++k)
		aux.a[k] = si.a[k];

	for (int k = i; k <= hi; ++k)
	{
		if (i > mid)
			si.a[k] = aux.a[j++];
		else if (j > hi)
			si.a[k] = aux.a[i++];
		else if (less_Sort(aux.a[i], aux.a[j]))
			si.a[k] = aux.a[i++];
		else
			si.a[k] = aux.a[j++];
	}
}

void Merge_Sort(Stack_Of_Int& si, Stack_Of_Int& aux, int lo, int hi)
{
	if (lo >= hi)
		return;

	int mid = lo + (hi - lo) / 2;
	Merge_Sort(si, aux, lo, mid);
	Merge_Sort(si, aux, mid + 1, hi);
	merge(si, aux, lo, mid, hi);
}

void Merge_Sort(Stack_Of_Int& si)
{
	Stack_Of_Int aux;
	initialization(aux, si.N);
	Merge_Sort(si, aux, 0, si.N - 1);
	free(aux.a);
}

void MergeBU_Sort(Stack_Of_Int& si)
{
	Stack_Of_Int aux;
	initialization(aux, si.N);
	for (int sz = 1; sz < si.N; sz += sz)
	{
		for (int lo = 0; lo < si.N - sz; lo += sz + sz)
		{
			int hi = lo + sz + sz - 1;
			if (si.N - 1 < hi)
				hi = si.N - 1;
			merge(si, aux, lo, lo + sz - 1, hi);
		}
	}
	free(aux.a);
}
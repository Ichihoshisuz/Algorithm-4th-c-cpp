#pragma once

#include "Sort_Example.h"

int partition(Stack_Of_Int& si, int lo, int hi)
{
	int i = lo;
	int j = hi + 1;

	int v = si.a[lo];

	while (true)
	{
		while (less_Sort(si.a[++i], v))
			if (i == hi)
				break;
		while (less_Sort(v, si.a[--j]));
		if (i >= j)
			break;
		exchange_Sort(si.a, i, j);
	}
	exchange_Sort(si.a, lo, j);
	return j;
}

void Insertion_Sort_Improve(Stack_Of_Int& si, int lo, int hi)
{
	int length = hi + 1;
	for (int i = lo; i < length; ++i)
	{
		int temp = si.a[i];
		int j = i - 1;
		while (j > lo - 1 && less_Sort(temp, si.a[j]))
		{
			si.a[j + 1] = si.a[j];
			--j;
		}
		si.a[j + 1] = temp;
	}
}

//毫无卵用.jpg
int partition_Improve_Discard(Stack_Of_Int& si, int lo, int hi)  //毫无卵用
{
	if (si.a[lo] < si.a[lo + 1] && si.a[lo] < si.a[lo + 2])
	{
		if (si.a[lo + 1] < si.a[lo + 2])
			exchange_Sort(si.a, lo, lo + 1);
		else
			exchange_Sort(si.a, lo, lo + 2);
	}
	else if (si.a[lo] > si.a[lo + 1] && si.a[lo] > si.a[lo + 2])
	{
		if (si.a[lo + 1] > si.a[lo + 2])
			exchange_Sort(si.a, lo, lo + 1);
		else
			exchange_Sort(si.a, lo, lo + 2);
	}

	int v = si.a[lo];
	int temp = si.a[hi];
	si.a[hi] = si.a[lo];

	int i = lo;
	int j = hi;
	

	while (true)
	{
		while (less_Sort(si.a[++i], v));
		while (less_Sort(v, si.a[--j]));
		if (i >= j)
			break;
		exchange_Sort(si.a, i, j);
	}
	if (v<temp)
	{
		si.a[hi] = temp;
		exchange_Sort(si.a, lo, j);
	}
	else if(v>temp)
	{
		si.a[lo] = temp;
		exchange_Sort(si.a, hi, i);
		return i;
	}
	else
	{
		if (i != j)
		{
			exchange_Sort(si.a, lo, j);
			exchange_Sort(si.a, hi, i);
			return i;
		}
		else
			exchange_Sort(si.a, j + 1, hi);
	}

	return j;
}

//2020.7.5追加
int partition_Test(Stack_Of_Int& si, int lo, int hi)
{
	int i = lo;
	int j = hi;
	int v = si.a[lo];

	while (less_Sort(si.a[++i], v))
		if (i == hi)
			break;
	if (v < si.a[j])
		while (less_Sort(v, si.a[--j]));
		


	while (i < j)
	{
		exchange_Sort(si.a, i, j);
		while (less_Sort(si.a[++i], v));
		while (less_Sort(v, si.a[--j]));
	}
	exchange_Sort(si.a, lo, j);
	return j;
}

int partition_Improve(Stack_Of_Int& si, int lo, int hi)
{
	if (si.a[lo] < si.a[lo + 1] && si.a[lo] < si.a[lo + 2])
	{
		if (si.a[lo + 1] < si.a[lo + 2])
			exchange_Sort(si.a, lo, lo + 1);
		else
			exchange_Sort(si.a, lo, lo + 2);
	}
	else if (si.a[lo] > si.a[lo + 1] && si.a[lo] > si.a[lo + 2])
	{
		if (si.a[lo + 1] > si.a[lo + 2])
			exchange_Sort(si.a, lo, lo + 1);
		else
			exchange_Sort(si.a, lo, lo + 2);
	}

	int i = lo;
	int j = hi + 1;

	int v = si.a[lo];

	while (true)
	{
		while (less_Sort(si.a[++i], v));
		while (less_Sort(v, si.a[--j]));
		if (i >= j)
			break;
		exchange_Sort(si.a, i, j);
	}
	exchange_Sort(si.a, lo, j);
	return j;
}

void Quick_Sort(Stack_Of_Int& si, int lo, int hi)
{
	if (hi - lo <= 10)
	{
		Insertion_Sort_Improve(si, lo, hi);
		return;
	}
	int j = partition(si, lo, hi);
	Quick_Sort(si, lo, j - 1);
	Quick_Sort(si, j + 1, hi);
}

void Quick_Sort_Improve(Stack_Of_Int& si, int lo, int hi)
{
	if (hi - lo <= 10)
	{
		Insertion_Sort_Improve(si, lo, hi);
		return;
	}
	int j = partition_Improve(si, lo, hi);
	Quick_Sort(si, lo, j - 1);
	Quick_Sort(si, j + 1, hi);
}

void Quick_Sort_Test(Stack_Of_Int& si, int lo, int hi)
{
	if (hi - lo <= 10)
	{
		Insertion_Sort_Improve(si, lo, hi);
		return;
	}
	int j = partition_Test(si, lo, hi);
	Quick_Sort_Test(si, lo, j - 1);
	Quick_Sort_Test(si, j + 1, hi);
}

void Quick_Sort(Stack_Of_Int& si)
{
	Quick_Sort(si, 0, si.N - 1);
}

void Quick_Sort_Test(Stack_Of_Int& si)
{
	Quick_Sort_Test(si, 0, si.N - 1);
}

void Quick_Sort_Improve(Stack_Of_Int& si)
{
	int lo = 0;
	int hi = si.N - 1;
	if (si.a[lo] < si.a[lo + 1] && si.a[lo] < si.a[lo + 2])
	{
		if (si.a[lo + 1] < si.a[lo + 2])
			exchange_Sort(si.a, lo, lo + 1);
		else
			exchange_Sort(si.a, lo, lo + 2);
	}
	else if (si.a[lo] > si.a[lo + 1] && si.a[lo] > si.a[lo + 2])
	{
		if (si.a[lo + 1] > si.a[lo + 2])
			exchange_Sort(si.a, lo, lo + 1);
		else
			exchange_Sort(si.a, lo, lo + 2);
	}

	int i = lo;
	int j = hi + 1;

	int v = si.a[lo];
	while (true)
	{
		while (less_Sort(si.a[++i], v))
			if (i == hi)
				break;
		while (less_Sort(v, si.a[--j]));
		if (i >= j)
			break;
		exchange_Sort(si.a, i, j);
	}
	exchange_Sort(si.a, lo, j);

	int index_max = i;
	while (i <= hi)
	{
		if (less_Sort(si.a[index_max], si.a[++i]))
			index_max = i;
		exchange_Sort(si.a, index_max, hi);
	}
	Quick_Sort(si, lo, j - 1);
	Quick_Sort(si, j + 1, hi);
}
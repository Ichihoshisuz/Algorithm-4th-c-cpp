#pragma once
#include "Sort_Example.h"

void Insertion_Sort(Stack_Of_Int& si)
{
	int length = size(si) - 1;
	for (int i = 0; i < length; ++i)
	{
		for (int j = i + 1; j > 0 && less_Sort(si.a[j], si.a[j-1]); --j)
		{
			exchange_Sort(si.a, j, j - 1);
		}
	}
}

void Insertion_Sort_Sentry(Stack_Of_Int& si)
{
	{
		int length = size(si) - 1;
		int min = 0;
		for (int i = 1; i < length + 1; ++i)
		{
			if (!less_Sort(si.a[min], si.a[i]))
				min = i;
		}
		exchange_Sort(si.a, 0, min);
		for (int i = 1; i < length; ++i)
		{
			for (int j = i + 1; less_Sort(si.a[j], si.a[j - 1]); --j)
			{
				exchange_Sort(si.a, j, j - 1);
			}
		}
	}
}

void Insertion_Sort_Improve(Stack_Of_Int& si)
{
	int length = size(si);
	for (int i = 1; i < length; ++i)
	{
		int temp = si.a[i];
		int j = i - 1;
		while(j > -1 && less_Sort(temp, si.a[j]))
		{
			si.a[j + 1] = si.a[j];
			--j;
		}
		si.a[j + 1] = temp;
	}
}

void Insertion_Sort_Sentry_Improve(Stack_Of_Int& si)
{
	int length = size(si);
	int min = 0;
	for (int i = 1; i < length; ++i)
	{
		if (si.a[min] > si.a[i])
			min = i;
	}
	int exch = si.a[0];
	si.a[0] = si.a[min];
	si.a[min] = exch;
	for (int i = 2; i < length; ++i)
	{
		int temp = si.a[i];
		int j = i - 1;
		while (less_Sort(temp, si.a[j]))
		{
			si.a[j + 1] = si.a[j];
			--j;
		}
		si.a[j + 1] = temp;
	}
}
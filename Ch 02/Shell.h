#pragma once
#include "Sort_Example.h"

void Shell_Sort(Stack_Of_Int& si)
{
	int N = size(si);
	int h = 1;
	while (h < N / 3)
		h = h * 3 + 1;
	while (h >= 1)
	{
		for (int i = h; i < N; ++i)
		{
			for (int j = i; j >= h && less_Sort(si.a[j], si.a[j - h]); j -= h)
				exchange_Sort(si.a, j, j - h);
		}
		h = h / 3;
	}
}

void Shell_Sort_Improve(Stack_Of_Int& si, Stack_Of_Int& order)
{
	int N = size(si);
	int order_size = size(order);
	int index = 0;
	while (index < order_size && order.a[index] < N)
		++index;
	while (index >= 1)
	{
		int h = order.a[--index];
		for (int i = h; i < N; ++i)
		{
			for (int j = i; j >= h && less_Sort(si.a[j], si.a[j - h]); j -= h)
				exchange_Sort(si.a, j, j - h);
		}
	}

}
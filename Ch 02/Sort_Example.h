#pragma once

#include "LIFO_动态调整数组大小的实现.h"
#include <iostream>

bool less_Sort(int i, int j)
{
	return i < j;
}

void exchange_Sort(int vi[], int index_1, int index_2)
{
	int temp = vi[index_1];
	vi[index_1] = vi[index_2];
	vi[index_2] = temp;
}

void show(Stack_Of_Int& si)
{
	for (int i = 0; i < size(si); ++i)
	{
		std::cout << si.a[i] << " ";
		if ((i + 1) % 10 == 0)
			std::cout << std::endl;
	}
	std::cout << std::endl;
}

bool isSorted(Stack_Of_Int& si)
{
	for (int i = 0; i < size(si) - 1; ++i)
	{
		if (less_Sort(si.a[i + 1], si.a[i]))
			return false;
	}
	return true;
}

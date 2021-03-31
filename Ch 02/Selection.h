#pragma once
#include "Sort_Example.h"

void Selection_Sort(Stack_Of_Int& si)
{
	if (size(si) == 0)
		return;
	for (int i = 0; i < size(si) - 1; ++i)
	{
		int min = i;
		for (int j = i + 1; j < size(si); ++j)
		{
			if (less_Sort(si.a[j], si.a[min]))
				min = j;
		}
		exchange_Sort(si.a, i, min);
	}
}



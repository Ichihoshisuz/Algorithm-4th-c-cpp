#pragma once

#include "Sort_Example.h"

void Quick3way_Sort(Stack_Of_Int& si, int lo, int hi)
{
	if (hi <= lo)
		return;

	int lt = lo;
	int i = lo;
	int gt = hi;
	int v = si.a[lo];

	while (i<=gt)
	{
		if (si.a[i] < v)
		{
			exchange_Sort(si.a, i, lt);
			++i;
			++lt;
		}
		else if (si.a[i] > v)
		{
			exchange_Sort(si.a, i, gt);
			--gt;
		}
		else
			++i;
	}
	Quick3way_Sort(si, lo, lt - 1);
	Quick3way_Sort(si, gt + 1, hi);
}

void Quick3way_Sort(Stack_Of_Int& si)
{
	Quick3way_Sort(si, 0, si.N - 1);
}
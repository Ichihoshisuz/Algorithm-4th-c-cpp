#include <stdlib.h>

struct Stack_Of_Int
{
	int capacity;
	int N;
	int* a;
};
typedef struct Stack_Of_Int Stack_Of_Int;

void initialization(Stack_Of_Int& si)
{
	si.capacity = 1;
	si.N = 0;
	si.a = (int*)malloc(si.capacity * sizeof(int));
}

void resize(Stack_Of_Int& si, int max)
{
	int* temp = (int*)malloc(max * sizeof(int));
	for (int i = 0; i < si.N; ++i)
		temp[i] = si.a[i];
	free(si.a);
	si.a = temp;
	si.capacity = max;
}

void push(Stack_Of_Int& si, int val)
{
	if (si.N == si.capacity)
		resize(si, si.capacity * 2);
	si.a[si.N] = val;
	++si.N;
}

int pop(Stack_Of_Int& si)
{
	--si.N;
	int temp = si.a[si.N];
	if (si.N > 0 && si.N == si.capacity / 4)
		resize(si, si.capacity / 2);
	return temp;
}


#include <stdlib.h>
#include "����.h"

struct Bag
{
	int N;
	Node* top;
};
typedef struct Bag Bag;

void initialization(Bag& sl)
{
	sl.N = 0;
	sl.top = nullptr;
}

bool isEmpty(Bag& sl)
{
	return sl.N == 0;
}

int size(Bag& sl)
{
	return sl.N;
}

// ע��next��ʵ����ָ��
void add(Bag& sl, int val)
{
	Node* p = sl.top;
	sl.top = (Node*)malloc(sizeof(Node));
	sl.top->val = val;
	sl.top->next = p;
	++sl.N;
}

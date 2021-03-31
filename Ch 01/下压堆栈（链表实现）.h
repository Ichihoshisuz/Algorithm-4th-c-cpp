#include <stdlib.h>
#include "链表.h"

struct Stack_Of_List
{
	int N;
	Node* top;
};
typedef struct Stack_Of_List Stack_Of_List;

void initialization(Stack_Of_List& sl)
{
	sl.N = 0;
	sl.top = nullptr;
}

bool isEmpty(Stack_Of_List& sl)
{
	return sl.N == 0;
}

int size(Stack_Of_List& sl)
{
	return sl.N;
}

// 注意next其实向下指。
void push(Stack_Of_List& sl, int val)
{
	Node* p = sl.top;
	sl.top = (Node*)malloc(sizeof(Node));
	sl.top->val = val;
	sl.top->next = p;
	++sl.N;
}

int pop(Stack_Of_List& sl)
{
	int val = sl.top->val;
	Node* temp = sl.top;
	sl.top = sl.top->next;
	--sl.N;
	free(temp);
	return val;
}
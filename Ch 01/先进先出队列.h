#include "链表.h"

struct Queue
{
	int N;
	Node* first;
	Node* last;
};
typedef struct Queue Queue;

void initialization(Queue& q)
{
	q.N = 0;
	q.first = nullptr;
	q.last = nullptr;
}

bool isEmpty(Queue& q)
{
	return q.first == nullptr;
}

int size(Queue& q)
{
	return q.N;
}


void enqueue(Queue& q, int val)
{
	Node* p = q.last;
	q.last = (Node*)malloc(sizeof(Node));
	q.last->val = val;
	q.last->next = nullptr;
	if (q.first == nullptr)
		q.first = q.last;
	else
		p->next = q.last;	// 防止没malloc的情况下直接用
	++q.N;
}

int dequeue(Queue& q)
{
	Node* p = q.first;
	int val = p->val;
	q.first = q.first->next;
	if (q.first == nullptr)
		q.last = nullptr;
	--q.N;
	free(p);
	return val;
}
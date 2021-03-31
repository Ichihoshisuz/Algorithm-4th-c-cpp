#include <iostream>
using namespace std;

struct Node
{
	int val;
	struct Node* next;
};
typedef struct Node Node;

void traversal(Node*& begin)
{
	for (Node* p = begin; p != nullptr; p = p->next)
		cout << p->val << " ";
	cout << endl;
}

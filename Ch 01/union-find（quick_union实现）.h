#include <stdlib.h>

struct UF
{
	int size;
	int count;
	int* id;
};
typedef struct UF UF;

void initialization(UF& uf, int n)
{
	uf.size = n;
	uf.count = n;
	uf.id = (int*)malloc(n * sizeof(int));
	for (int i = 0; i < n; ++i)
		uf.id[i] = i;
}

int count(UF& uf)
{
	return uf.count;
}

int find(UF& uf, int p)
{
	while (p != uf.id[p])
		p = uf.id[p];
	return  p;
}

bool connected(UF& uf, int p, int q)
{
	return find(uf, p) == find(uf, q);
}

void union_algorithm(UF& uf, int p, int q)
{
	int pRoot = find(uf, p);
	int qRoot = find(uf, q);
	if (pRoot == qRoot)
		return;
	uf.id[pRoot] = qRoot;
	--uf.count;
}

void delete_UF(UF& uf)
{
	free(uf.id);
}

#pragma once

#include <iostream>
#include <climits>
#include <stdlib.h>
#include <queue>
#include <cmath>
#include <string>

struct Node
{
	char key;
	int val;
	int N;
	Node* left;
	Node* right;
	int id;
	int layer;
};

Node* new_Node(Node* x, char key, int val, int N, int k, int l)
{
	x = (Node*)malloc(sizeof(Node));
	x->key = key;
	x->val = val;
	x->N = N;
	x->left = nullptr;
	x->right = nullptr;
	x->id = k;
	x->layer = l;
	return x;
}

int size(Node* x)
{
	if (x == nullptr)
		return 0;
	return x->N;
}

int get_BST(Node* x, char key)
{
	if (x == nullptr)
		return INT_MAX;
	else if (key < x->key)
		return get_BST(x->left, key);
	else if (key > x->key)
		return get_BST(x->right, key);
	else
		return x->val;
}

Node* put_BST(Node* x, char key, int val, int k, int l)
{
	if (x == nullptr)
		x = new_Node(x, key, val, 1, k, l);
	else if (key < x->key)
		x->left = put_BST(x->left, key, val, k + x->id, l + 1);
	else if (key > x->key)
		x->right = put_BST(x->right, key, val, k + 1 + x->id, l + 1);
	else
		x->val = val;
	x->N = size(x->left) + size(x->right) + 1;
	return x;
}

char min_BST(Node* x)
{
	if (x->left == nullptr)
		return x->key;
	return min_BST(x->left);
}

char max_BST(Node* x)
{
	if (x->right == nullptr)
		return x->key;
	return max_BST(x->right);
}

int max_layer(Node* x, int& c)
{
	if(x==nullptr)
		return -1;
	if (x->left != nullptr)
		max_layer(x->left, c);
	if (x->right != nullptr)
		max_layer(x->right, c);
	if (x->layer > c)
		c = x->layer;
	return c;
}

Node* floor_Private(Node* x, char key)
{
	if (x == nullptr)
		return x;
	if (key == x->key)
		return x;
	else if (key < x->key)
		return floor_Private(x->left, key);
	Node* y = floor_Private(x->right, key);
	if (y != nullptr)
		return y;
	else
		return x;
}

char floor_BST(Node* x, char key)
{
	x = floor_Private(x, key);
	if (x == nullptr)
		return '\0';
	else
		return x->key;
}

Node* ceiling_Private(Node* x, char key)
{
	if (x == nullptr)
		return x;
	if (key == x->key)
		return x;
	else if (key > x->key)
		return ceiling_Private(x->right, key);
	Node* y = ceiling_Private(x->left, key);
	if (y != nullptr)
		return y;
	else
		return x;
}

char ceiling_BST(Node* x, char key)
{
	x = ceiling_Private(x, key);
	if (x == nullptr)
		return '\0';
	else
		return x->key;
}

Node* select_Private(Node* x, int n)
{
	if (x == nullptr)
		return x;
	int t = size(x->left);
	if (n < t)
		return select_Private(x->left, n);
	else if (n > t)
		return select_Private(x->right, n - t - 1);//这里算是重点。
	else
		return x;
}

char select_BST(Node* x, int n)
{
	x = select_Private(x, n);
	if (x == nullptr)
		return '\0';
	else
		return x->key;
}

int rank_Private(Node* x, char key)
{
	if (x == nullptr)
		return 0;
	if (key < x->key)
		return rank_Private(x->left, key);
	else if (key > x->key)
		return 1 + size(x->left) + rank_Private(x->right, key);
	else
		return size(x->left);
}

int rank_BST(Node* x, char key)
{
	return rank_Private(x, key);
}

void change_id_layer(Node* x, int id, int layer)
{
	if (x == nullptr)
		return;
	x->id = id;
	x->layer = layer;
	change_id_layer(x->left, x->id + id, layer + 1);
	change_id_layer(x->right, x->id + id + 1, layer + 1);
}

Node* deleteMin_Private(Node* x, int mode)
{
	if (x->left == nullptr)
	{
		Node* temp = x->right;
		
		if (mode == 0)
		{
			change_id_layer(x->right, x->id, x->layer);
			free(x);
		}
		return temp;
	}
	x->left= deleteMin_Private(x->left, mode);
	x->N = 1 + size(x->left) + size(x->right);
	return x;
}

void delteMin(Node*& x)
{
	if (x == nullptr)
		return;
	x = deleteMin_Private(x, 0);

}

Node* deleteKey_Private(Node* x, char key)
{
	if (x == nullptr)
		return x;
	if (key < x->key)
		x->left = deleteKey_Private(x->left, key);
	else if (key > x->key)
		x->right = deleteKey_Private(x->right, key);
	else
	{
		Node* temp = x;
		if (x->left == nullptr)
		{
			x = x->right;
			change_id_layer(x, temp->id, temp->layer);
			free(temp);
			return x;
		}
		else if (x->right == nullptr)
		{
			x = x->left;
			change_id_layer(x, temp->id, temp->layer);
			free(temp);
			return x;
		}
		x = x->right;
		while (x->left != nullptr)
			x = x->left;
	
		x->right = deleteMin_Private(temp->right, 1);
		x->left = temp->left;
		change_id_layer(x, temp->id, temp->layer);
		free(temp);
	}
	x->N = 1 + size(x->left) + size(x->right);
	return x;
}

void deleteKey(Node*& x, char key)
{
	if (x == nullptr)
		return;
	x = deleteKey_Private(x, key);
}

void delete_All(Node* x)
{
	if (x == nullptr)
		return;
	delete_All(x->left);
	delete_All(x->right);
	free(x);
}

void keys_Private(Node* x, std::queue<char>& q, char lo, char hi)
{
	if (x == nullptr)
		return;
	if (lo < x->key)
		keys_Private(x->left, q, lo, hi);
	if (lo <= x->key && x->key <= hi)	//注意相等的情形。
		q.push(x->key);
	if (x->key < hi)
		keys_Private(x->right, q, lo, hi);
}

void keys_BST(Node* x, std::queue<char>& q)
{
	keys_Private(x, q, min_BST(x), max_BST(x));
}

void keys_BST(Node* x, std::queue<char>& q, char lo, char hi)
{
	keys_Private(x, q, lo, hi);
}

void show_BST(Node* x)
{
	if (x == nullptr)
		return;
	int ml = 0;
	ml = max_layer(x, ml) + 1;
	ml = pow(2, ml) - 1;
	int pl = ml / 2;
	std::queue<Node*> q;
	q.push(x);
	int count = 0;
	int prec = -1;
	
	while (!q.empty())
	{
		if (q.front()->left != nullptr)
			q.push(q.front()->left);
		if (q.front()->right != nullptr)
			q.push(q.front()->right);
		if (count < q.front()->layer)
		{
			prec = -1;
			++count;
			std::cout << std::endl << std::endl;
			pl = pl / 2;
			ml = ml / 2;
		}
		int c = q.front()->id - prec;
		int temp = 0;//记录空格数
		if (prec == -1)
		{
			temp = pl;
			if (c > 1)
				++temp;
			--c;
		}
		temp = temp + (ml * c);
		if (c > 1)
			temp = temp + c - 1;
		std::string str(temp, ' ');
		std::cout << str << q.front()->key;
		prec = q.front()->id;
		temp = 0;
		q.pop();
	}
}
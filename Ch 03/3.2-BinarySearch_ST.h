#pragma once
#include <iostream>
#include <stdlib.h>
#include <vector>

struct BinarySearch_ST
{
	int* vals;
	char* keys;
	int N;
	int capacity;
};

void ini_ST(BinarySearch_ST& st, int capacity)
{
	st.vals = (int*)malloc(sizeof(int) * (capacity + 1));
	st.keys = (char*)malloc(sizeof(char) * (capacity + 1));
	st.N = 0;
	st.capacity = capacity;

}

int size(BinarySearch_ST& st)
{
	return st.N;
}

bool isEmpty(BinarySearch_ST& st)
{
	return st.N == 0;
}

bool isFull(BinarySearch_ST& st)
{
	return st.N == st.capacity;
}

int rank_ST(BinarySearch_ST&st, char key)
{
	int lo = 0;
	int hi = st.N - 1;
	while (lo <= hi)
	{
		int mid = (lo + hi) / 2;
		if (key < st.keys[mid])
			hi = mid - 1;
		else if (key > st.keys[mid])
			lo = mid + 1;
		else
			return mid;
	}
	//这玩意简单来说就是找到一个当前 key 应该插入的位置。
	return lo;
}


int get(BinarySearch_ST& st, char key)
{
	if (isEmpty(st))
	{
		std::cout << "当前为空" << std::endl;
		return -1;
	}
	int i = rank_ST(st, key);
	if (i < st.N && key == st.keys[i])
		return st.vals[i];
	else
	{
		std::cout << "查找失败" << std::endl;
		return -1;
	}
}

void put(BinarySearch_ST& st, char key, int val)
{
	int i = rank_ST(st, key);
	if (i < st.N&& key == st.keys[i])
	{
		st.vals[i] = val;
		return;
	}
	if (isFull(st))
		return;
	else
	{
		for (int j = st.N; j > i; --j)
		{
			st.keys[j] = st.keys[j - 1];
			st.vals[j] = st.vals[j - 1];
		}
	}
	st.keys[i] = key;
	st.vals[i] = val;
	++st.N;
}

void delete_ST(BinarySearch_ST& st)
{
	free(st.keys);
	free(st.vals);
}

void delete_ST(BinarySearch_ST& st, char key)
{
	int i = rank_ST(st, key);
	if (i < st.N && key == st.keys[i])
	{
		for (int j = i; j < st.N - 1; ++j)
		{
			st.keys[j] = st.keys[j + 1];
			st.vals[j] = st.vals[j + 1];
			--st.N;
		}
	}
	else
		std::cout << "没有该项，删除失败" << std::endl;
}

char min(BinarySearch_ST& st)
{
	return st.keys[0];
}

char max(BinarySearch_ST& st)
{
	return st.keys[st.N - 1];
}

char select(BinarySearch_ST& st, int k)
{
	return st.keys[k];
}

char ceiling(BinarySearch_ST& st, char key)
{
	int i = rank_ST(st, key);
	if (i < st.N)
		return st.keys[i];
	else
		return '\0';
}

char floor(BinarySearch_ST& st, char key)
{
	int i = rank_ST(st, key);
	if (key == st.keys[i])
		return st.keys[i];
	else if (i == 0)
	{
		std::cout << "没有小于等于 key 的最大键" << std::endl;
		return '\0';
	}
	else
		return st.keys[i - 1];
}

void show_ST(BinarySearch_ST& st)
{
	for (int i = 0; i < st.N; ++i)
	{
		std::cout << st.keys[i] << " " << st.vals[i] << std::endl;
	}
}

//keys的实现直接省略了。
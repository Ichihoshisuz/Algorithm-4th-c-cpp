//���ֲ���
int BinarySearch(int key, int a[], size_t size)
{
	int low = 0;
	int high = size - 1;
	while (low <= high)
	{
		int mid = low + (high - low) / 2;  //�ص㣺��ֹ���
		if (key < a[mid])
			high = mid - 1;
		else if (key > a[mid])
			low = mid + 1;
		else
			return mid;
	}
	return -1;
}

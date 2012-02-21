#include <iostream>
#include <cmath>
#include <vector>
#include <string.h>
#include <ctime>
#include <map>
#include <algorithm>

using namespace std;
int const LEN = 10000;

int buf0[LEN];
int buf1[LEN];
int buf2[LEN];

void radix_sort(int* arr1, int * arr2, int len)
{
	int cnt[256];
	int shift = 0;

	for (int l = 0; l < 4; l++)
	{
		memset(cnt, 0, sizeof(cnt));
		for (int i = 0; i < len; i++)
			cnt[(arr1[i] >> shift) & 0xff]++;

		int sum = 0;
		for (int i = 0; i < 256; i++)
		{
			int pos = sum;
			sum += cnt[i];
			cnt[i] = pos;
		}

		for (int i = 0; i < len; i++)
		{
			int index = (arr1[i] >> shift) & 0xff;
			arr2[cnt[index]++] = arr1[i];
		}

		swap(arr1, arr2);
		shift += 8;
	}
}

int main()
{

	srand((int) time(NULL));
	for (int i = 0; i < LEN; i++)
		buf0[i] = rand() % 100000;

	radix_sort(buf1, buf2, LEN);

	return 0;
}


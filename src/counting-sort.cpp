#include <assert.h>
#include <limits.h>
#include <time.h>

#include <algorithm>
#include <iostream>
#include <vector>

void counting_sort(const int src[],  int dst[], int array_len) {

	// 1. pick out the min and max of the array.
	int min = INT_MAX, max = INT_MIN;
	for (int i = 0; i < array_len; i ++) {
		if (src[i] < min) {
			min = src[i];
		}
		if (src[i] > max) {
			max = src[i];
		}
	}
	// 2. create a counting array, and do the counting.
	const int counting_array_len = max - min + 1;
	int *c = new int[counting_array_len];
	for (int i = 0; i < array_len; i ++) {
		c[src[i] - min] ++;
	}
	// 3. accumulate the counting.
	for (int i = 1; i < counting_array_len; i ++) {
		c[i] += c[i - 1];
	}
	// 4. sort to the 'dst'.
	for ( int i = 0; i < array_len; i ++) {
		int num = src[i];
		dst[c[num - min] - 1] = num;
		c[num - min] --;
	}
}

int main() {
	srand(time(NULL));
	const int ARRAY_LEN = 1000;
	const int INT_RANGE = 100000;
	int *array = new int[ARRAY_LEN];
	int *dest = new int[ARRAY_LEN];
	for (int i = 0; i < ARRAY_LEN; i ++) {
		array[i] = rand() % INT_RANGE;
	}

	// Sort in standard way
	std::vector<int> v(array, array + ARRAY_LEN);
	std::sort(v.begin(), v.end());

	// Sort in our way
	counting_sort(array, dest, ARRAY_LEN);

	// Compare them
	for (int i = 0; i < ARRAY_LEN; i ++)
	{
		//std::cout << v[i] << "&" << dest[i] << ", ";
		assert(v[i] == dest[i]);
	}
}

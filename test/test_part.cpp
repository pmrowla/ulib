#include <stdio.h>
#include <assert.h>
#include <ulib/part_tpl.h>

#define LESSTHAN(x, y) (*(x) < *(y))

DECLARE_PART(test, int, LESSTHAN);

int main()
{
	int data[] = { 4, -1, 3, 100, 9 };

	// call part() to partition the array into two parts, with the
	// first 'num' elements be the num smallest, and the num-th
	// element be the largest of the first 'num' elements.
	part_test(data, data + 2, data + sizeof(data)/sizeof(data[0]));

	assert(data[0] < data[2]);
	assert(data[1] < data[2]);
	assert(data[2] == 4);

	printf("passed\n");

	return 0;
}

#include <stdio.h>
#include <ulib/rand_tpl.h>

int main()
{
	uint64_t u, v, w;

	RAND_NR_INIT(u, v, w, 0UL);

	for (int i = 0; i < 100; i++)
		printf("rand number = %llx\n", (unsigned long long)RAND_NR_NEXT(u, v, w));

	uint64_t h = 0;

	printf("rand int mix1 = %llx\n", (unsigned long long)RAND_INT_MIX64(h));
	printf("rand int mix2 = %llx\n", (unsigned long long)RAND_INT2_MIX64(h));

	printf("passed\n");

	return 0;
}

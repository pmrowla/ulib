#include <time.h>
#include <stdio.h>
#include <assert.h>
#include <ulib/rand_tpl.h>

int main()
{
	uint64_t u, v, w;
	uint64_t seed = time(0);

	RAND_NR_INIT(u, v, w, seed);

	for (int i = 0; i < 100; i++)
		printf("rand number = %llx\n", (unsigned long long)RAND_NR_NEXT(u, v, w));

	uint64_t h = 0;

	printf("rand int mix1 = %llx\n", (unsigned long long)RAND_INT_MIX64(h));
	printf("rand int mix2 = %llx\n", (unsigned long long)RAND_INT2_MIX64(h));

	for (int i = 0; i < 1000; ++i) {
		uint64_t s = h;
		RAND_INT3_MIX64(h);
		uint64_t t = h;
		RAND_INT3_MIX64_INV(t);
		printf ("mix3: s = %016zux, t = %016zux\n", s, t);
		assert(s == t);
	}

	printf("passed\n");

	return 0;
}

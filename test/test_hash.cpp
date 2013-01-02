#include <time.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <assert.h>
#include <ulib/hash.h>
#include <ulib/alignhash.h>

using namespace ulib;

int main()
{
	char buf[4096] = { 0 };
	align_hash_set<uint64_t> hashes;

	for (unsigned s = 0; s < 1000; ++s) {
		for (unsigned i = 0; i < sizeof(buf); ++i) {
			uint64_t hash = hash_fast64(buf, i, s);
			if (hashes.contain(hash)) {
				fprintf(stderr, "%016llx already exists\n",
					(unsigned long long) hash);
				exit(EXIT_FAILURE);
			} else
				hashes.insert(hash);
		}
	}

	uint64_t nil = 0;

	printf("0 fasthash64: %016llx\n", (unsigned long long)hash_fast64(&nil, sizeof(nil), 0));
	printf("1 fasthash64: %016llx\n", (unsigned long long)hash_fast64(&nil, sizeof(nil), 1));
	printf("0 fasthash32: %08x\n",	hash_fast32(&nil, sizeof(nil), 0));
	printf("1 fasthash32: %08x\n",	hash_fast32(&nil, sizeof(nil), 1));

	printf("passed\n");

	return 0;
}

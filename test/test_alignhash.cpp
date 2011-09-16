#include <stdio.h>
#include <assert.h>
#include <alignhash.h>

struct key_struct
{
	const unsigned char *str;

	operator uint64_t() const
	{
		uint64_t hash = 0;

		for (const unsigned char *p = str; *p; ++p)
			hash += hash * 33 + *p;

		return hash;
	}
};

int main()
{
	align_hash_map<int,int> map;

	map[1] = 100;
	map[1000] = 101;

	assert(100 == map[1]);
	assert(101 == map[1000]);

	align_hash_map<key_struct, int> keymap;

	key_struct key;

	key.str = (const unsigned char *)"hello world";
	keymap[key] = 999;

	assert(999 == keymap[key]);

	printf("passed\n");
	
	return 0;
}

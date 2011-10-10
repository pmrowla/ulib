#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <ulib/hash.h>
#include <ulib/alignhash.h>

struct str {
	const char *c_str;
	
	str(const char *s = 0)
	: c_str(s) { }

	operator size_t() const
	{ return hash_djb2((const unsigned char *)c_str); }

	bool operator==(const str &other) const
	{ return strcmp(c_str, other.c_str) == 0; }
};

int main()
{
	align_hash_map<str, int> months;
  
	months["january"] = 31;
	months["february"] = 28;
	months["march"] = 31;
	months["april"] = 30;
	months["may"] = 31;
	months["june"] = 30;
	months["july"] = 31;
	months["august"] = 31;
	months["september"] = 30;
	months["october"] = 31;
	months["november"] = 30;
	months["december"] = 31;
  
	assert(months["september"] == 30);
	assert(months["april"] == 30);
	assert(months["february"] == 28);
	assert(months["december"] == 31);

	printf("passed\n");

	return 0;
}

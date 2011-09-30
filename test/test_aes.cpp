#include <ulib/aes.h>  // put at the beginning for independence test
#include <ulib/hexdump.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

const unsigned char test_key1[16] = 
{ 0x80 };
const unsigned char test_vec1[16] =
{ 0x0e, 0xdd, 0x33, 0xd3, 0xc6, 0x21, 0xe5, 0x46, 0x45, 0x5b, 0xd8, 0xba, 0x14, 0x18, 0xbe, 0xc8 };

const unsigned char test_key2[16] =
{ 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff };
const unsigned char test_vec2[16] =
{ 0xa1, 0xf6, 0x25, 0x8c, 0x87, 0x7d, 0x5f, 0xcd, 0x89, 0x64, 0x48, 0x45, 0x38, 0xbf, 0xc9, 0x2c };

int main()
{
	AES_KEY key;

	AES_set_encrypt_key(test_key1, 128, &key);
	unsigned char output1[16] = { 0 };
	print_hex_dump_bytes("KEY\t", DUMP_PREFIX_OFFSET, test_key1, sizeof(test_key1));
	AES_encrypt(output1, output1, &key);
	print_hex_dump_bytes("VEC\t", DUMP_PREFIX_OFFSET, output1, sizeof(output1));
	assert(memcmp(test_vec1, output1, sizeof(test_vec1)) == 0);

	AES_set_encrypt_key(test_key2, 128, &key);
	unsigned char output2[16] = { 0 };
	print_hex_dump_bytes("KEY\t", DUMP_PREFIX_OFFSET, test_key2, sizeof(test_key2));
	AES_encrypt(output2, output2, &key);
	print_hex_dump_bytes("VEC\t", DUMP_PREFIX_OFFSET, output2, sizeof(output2));
	assert(memcmp(test_vec2, output2, sizeof(test_vec2)) == 0);

	const unsigned char zeros[16] = { 0 };

	AES_set_decrypt_key(test_key1, 128, &key);
	unsigned char output3[16] = { 0 };
	AES_decrypt(test_vec1, output3, &key);
	assert(memcmp(output3, zeros, sizeof(output3)) == 0);

	AES_set_decrypt_key(test_key2, 128, &key);
	unsigned char output4[16] = { 0 };
	AES_decrypt(test_vec2, output4, &key);
	assert(memcmp(output4, zeros, sizeof(output4)) == 0);

	printf("passed\n");

	return 0;
}

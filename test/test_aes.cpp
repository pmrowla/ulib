#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <ulib/aes.h>

int main()
{
	AES_KEY key;
	unsigned char zeros[32] = { 0 };  // 256-bit key
	unsigned char  src[128] = { 0 };  // plaintext
	unsigned char src1[128] = { 1 };  // plaintext
	unsigned char dest[128] = { 0 };  // ciphertext
	unsigned char ivec[AES_BLOCK_SIZE] = { 0 };
	

	assert(AES_set_encrypt_key(zeros, 256, &key) == 0);	
	AES_encrypt(src, dest, &key);
	assert(AES_set_decrypt_key(zeros, 256, &key) == 0);
	AES_decrypt(dest, src1, &key);
	assert(memcmp(src1, src, AES_BLOCK_SIZE) == 0);

	assert(AES_set_encrypt_key(zeros, 256, &key) == 0);
	AES_cbc_encrypt(src, dest, sizeof(src), &key, ivec, 1);
	memset(ivec, 0, sizeof(ivec));
	assert(AES_set_decrypt_key(zeros, 256, &key) == 0);
	AES_cbc_encrypt(dest, src1, sizeof(dest), &key, ivec, 0);
	assert(memcmp(src1, src, sizeof(src1)) == 0);

	printf("passed\n");

	return 0;
}

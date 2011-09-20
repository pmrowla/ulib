/* The MIT License

   Copyright (C) 2011 Zilong Tan (tzlloch@gmail.com)

   Permission is hereby granted, free of charge, to any person obtaining
   a copy of this software and associated documentation files (the
   "Software"), to deal in the Software without restriction, including
   without limitation the rights to use, copy, modify, merge, publish,
   distribute, sublicense, and/or sell copies of the Software, and to
   permit persons to whom the Software is furnished to do so, subject to
   the following conditions:

   The above copyright notice and this permission notice shall be
   included in all copies or substantial portions of the Software.

   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
   EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
   MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
   NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
   BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
   ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
   CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
   SOFTWARE.
*/

#include "internal.h"
#include "rc4.h"

void rc4_init(const unsigned char *key_data_ptr, int key_data_len, rc4_key_t * key)
{
	unsigned char index1;
	unsigned char index2;
	unsigned char *state;
	short counter;

	state = &key->state[0];
	for (counter = 0; counter < 256; counter++)
		state[counter] = counter;
	key->x = 0;
	key->y = 0;
	index1 = 0;
	index2 = 0;
	for (counter = 0; counter < 256; counter++) {
		index2 = (key_data_ptr[index1] + state[counter] + index2) % 256;
		SWAP(state[counter], state[index2]);
		index1 = (index1 + 1) % key_data_len;
	}
}

void rc4_crypt(unsigned char *buffer_ptr, int buffer_len, rc4_key_t * key)
{
	unsigned char x;
	unsigned char y;
	unsigned char *state;
	unsigned char xorIndex;
	short counter;

	x = key->x;
	y = key->y;

	state = &key->state[0];
	for (counter = 0; counter < buffer_len; counter++) {
		x = (x + 1) % 256;
		y = (state[x] + y) % 256;
		SWAP(state[x], state[y]);
		xorIndex = (state[x] + state[y]) % 256;
		buffer_ptr[counter] ^= state[xorIndex];
	}
	key->x = x;
	key->y = y;
}

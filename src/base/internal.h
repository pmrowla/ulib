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

#ifndef __ULIB_INTERNAL_H
#define __ULIB_INTERNAL_H

#include <stdio.h>

#define SWAP(x, y) do {				\
		typeof(x) _tmp = (x);		\
		(x) = (y);			\
		(y) = _tmp;			\
	} while (0)

#define min(x, y) ({				\
	typeof(x) _min1 = (x);			\
	typeof(y) _min2 = (y);			\
	(void) (&_min1 == &_min2);		\
	_min1 < _min2 ? _min1 : _min2; })

#define max(x, y) ({				\
	typeof(x) _max1 = (x);			\
	typeof(y) _max2 = (y);			\
	(void) (&_max1 == &_max2);		\
	_max1 > _max2 ? _max1 : _max2; })

/*
 * Internal implementation of fast memory swapping
 */ 
static inline void __memswp(void *x, void *y, size_t size)
{
	void *end;
	size_t *p, *q;
	unsigned char *h, *v;
	
	p = (size_t *)x;
	q = (size_t *)y;
	end = p + size / sizeof(*p);

	while (p != end) {
		SWAP(*p, *q);
		p++;
		q++;
	}

	h = (unsigned char *)p;
	v = (unsigned char *)q;

#if __WORDSIZE == 64
	switch (size & 7) {
#else
	switch (size & 3) {
#endif
	case 7: SWAP(h[6], v[6]);
	case 6: SWAP(h[5], v[5]);
	case 5: SWAP(h[4], v[4]);
	case 4: SWAP(h[3], v[3]);
	case 3: SWAP(h[2], v[2]);
	case 2: SWAP(h[1], v[1]);
	case 1: SWAP(h[0], v[0]);
	}
}

#endif  /* __ULIB_INTERNAL_H */

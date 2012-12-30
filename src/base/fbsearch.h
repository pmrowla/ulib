/* The MIT License

   Copyright (C) 2011, 2012 Zilong Tan (eric.zltan@gmail.com)

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

#ifndef __ULIB_FBSEARCH_H
#define __ULIB_FBSEARCH_H

#include <sys/types.h>

#ifdef __cplusplus
extern "C" {
#endif

	/**
	 * findline - find a match line
	 * @fd:     file descriptor
	 * @comp:   line compare function
	 * @param:  parameter for @comp (e.g., target line)
	 * @maxlen: max line length, including the '\n'
	 * Note: lines in fd must be sorted in ascending order with respect to
	 * @comp.
	 *
	 * return -1 if the line was not found, or offset to the line
	 * otherwise.
	 */
	ssize_t findline(int fd, int (*comp) (const char *, void *),
			 void *param, int maxlen);

	/* find the first match line */
	ssize_t findfirstline(int fd, int (*comp) (const char *, void *),
			      void *param, int maxlen);

#ifdef __cplusplus
}
#endif
#endif              /* __ULIB_FBSEARCH_H */

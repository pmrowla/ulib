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

#ifndef __ULIB_TREEUTILS_H
#define __ULIB_TREEUTILS_H

#include <stdio.h>
#include "tree.h"

#ifdef __cplusplus
extern "C" {
#endif

size_t tree_height(struct tree_root *root);

/* consistency checks:
 * 1. left < parent < right;
 * 2. parent pointers are correct; */
int tree_verify(struct tree_root *root,
		int (*compare) (const void *, const void *));

/* recursively count the number of nodes */
size_t tree_count(struct tree_root *root);

/* print each path of the tree */
void tree_print(struct tree_root *root,
		void (*callback) (struct tree_root *));

#ifdef __cplusplus
}
#endif
#endif		    /* __ULIB_TREEUTILS_H */

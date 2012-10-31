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

#ifndef __ULIB_TREE_H
#define __ULIB_TREE_H

/* to avoid conflicts with C++ new operator */
#define new _new_

struct tree_root {
	struct tree_root *left, *right;
	struct tree_root *parent;
};

/* avl_root is derived from tree_root */
struct avl_root {
	struct avl_root *left, *right;
	struct avl_root *parent;
	int balance:3;
};

#define NIL (void *)0

#define TREE_ROOT_INIT { NIL, NIL, NIL }

#define TREE_ROOT(name)				\
	struct tree_root name = TREE_ROOT_INIT

#define INIT_TREE_ROOT(ptr) do {			\
		(ptr)->left = NIL; (ptr)->right = NIL;	\
		(ptr)->parent = NIL;			\
	} while (0)

#define AVL_ROOT_INIT { NIL, NIL, NIL, 0 }

#define AVL_ROOT(name)				\
	struct avl_root name = AVL_ROOT_INIT;

#define INIT_AVL_ROOT(ptr) do {			\
		INIT_TREE_ROOT(ptr);		\
		(ptr)->balance = 0;		\
	} while (0)

/* emptiness tests */
#define TREE_EMPTY(ptr)   ((ptr) == NIL)
#define SPLAY_EMPTY(ptr)  TREE_EMPTY(ptr)
#define AVL_EMPTY(ptr)    TREE_EMPTY(ptr)

#ifdef __cplusplus
extern "C" {
#endif

	/* applies to other trees derived from BST also */
	struct tree_root *
	tree_search(struct tree_root *entry,
		    int (*compare) (const void *, const void *),
		    struct tree_root *root);

	struct tree_root *
	tree_min(struct tree_root *root);

	struct tree_root *
	tree_max(struct tree_root *root);

	struct tree_root *
	tree_successor(struct tree_root *root);

	struct tree_root *
	tree_predecessor(struct tree_root *root);

	/* add a new entry regardless of any duplicates */
	void tree_add(struct tree_root *new,
		      int (*compare) (const void *, const void *),
		      struct tree_root **root);

	/* add a unique entry
	   if the entry already exists, return the old one. Otherwise
	   the new entry will be returned. */
	struct tree_root *
	tree_map(struct tree_root *new,
		 int (*compare) (const void *, const void *),
		 struct tree_root **root);

	void tree_del(struct tree_root *entry, struct tree_root **root);

	/* similar to tree_map, but it involves an additional splay
	   operation */
	struct tree_root *
	splay_map(struct tree_root *new,
		  int (*compare) (const void *, const void *),
		  struct tree_root **root);

	/* accelerate splay_map at the expense of invalidating parent
	   pointers */
	struct tree_root *
	splay_map_nparent(struct tree_root *new,
			  int (*compare) (const void *, const void *),
			  struct tree_root **root);

	/* similar to tree_search, but it involves an additional splay
	   operation */
	struct tree_root *
	splay_search(struct tree_root *entry,
		     int (*compare) (const void *, const void *),
		     struct tree_root **root);

	/* accelerate splay_search at the expense of invalidating
	   parent pointers */
	struct tree_root *
	splay_search_nparent(struct tree_root *entry,
			     int (*compare) (const void *, const void *),
			     struct tree_root **root);

	void avl_add(struct avl_root *new,
		     int (*compare) (const void *, const void *),
		     struct avl_root **root);

	struct avl_root *
	avl_map(struct avl_root *new,
		int (*compare) (const void *, const void *),
		struct avl_root **root);

	void avl_del(struct avl_root *entry, struct avl_root **root);

#ifdef __cplusplus
}
#endif

/* retrieve the host struct
 * @ptr:    node pointer
 * @type:   host type
 * @member: node member name */
#define tree_entry(ptr, type, member)					\
	((type *)((char *)(ptr)-(unsigned long)(&((type *)0)->member)))

#define avl_entry(ptr, type, member) tree_entry(ptr, type, member)

#define tree_for_each(pos, root)		\
	for (pos = tree_min(root); pos != NIL;	\
	     pos = tree_successor(pos))

/* traversal in reversed order */
#define tree_for_each_prev(pos, root)		\
	for (pos = tree_max(root); pos != NIL;	\
	     pos = tree_predecessor(pos))

/* @pos is safe for removal */
#define tree_for_each_safe(pos, n, root)			\
	for (pos = tree_min(root), n = tree_successor(pos);	\
	     pos != NIL;					\
	     pos = n, n = n != NIL? tree_successor(n): NIL)

/* traverse the host struct instead of node */
#define tree_for_each_entry(pos, root, member)				\
	for (pos = tree_entry(tree_min(root), typeof(*pos), member);    \
	     &pos->member != NIL;					\
	     pos = tree_entry(tree_successor(&pos->member), typeof(*pos), member))

#define tree_for_each_entry_safe(pos, n, root, member)			\
	for (pos = tree_entry(tree_min(root), typeof(*pos), member),    \
		     n = tree_entry(tree_successor(&pos->member), typeof(*pos), member); \
	     &pos->member != NIL; pos = n,				\
		     n = tree_entry(&n->member != NIL? tree_successor(&n->member): NIL, typeof(*n), member))

#define avl_for_each(pos, root)						\
	for (pos = (struct avl_root *)tree_min((struct tree_root *)root); pos != NIL; \
	     pos = (struct avl_root *)tree_successor((struct tree_root *)pos))

#define avl_for_each_prev(pos, root)					\
	for (pos = (struct avl_root *)tree_max((struct tree_root *)root); pos != NIL; \
	     pos = (struct avl_root *)tree_predecessor((struct tree_root *)pos))

#define avl_for_each_safe(pos, n, root)					\
	for (pos = (struct avl_root *)tree_min((struct tree_root *)root), \
		     n = (struct avl_root *)tree_successor((struct tree_root *)pos); pos != NIL; \
	     pos = n,							\
		     n = n != NIL? (struct avl_root *)tree_successor((struct tree_root *)n): NIL)

#define avl_for_each_entry(pos, root, member)				\
	for (pos = tree_entry(tree_min((struct tree_root *)root), typeof(*pos), member); \
	     &pos->member != NIL;					\
	     pos = tree_entry(tree_successor((struct tree_root *)&pos->member), typeof(*pos), member))

#define avl_for_each_entry_safe(pos, n, root, member)			\
	for (pos = tree_entry(tree_min((struct tree_root *)root), typeof(*pos), member), \
		     n = tree_entry(tree_successor((struct tree_root *)&pos->member), typeof(*pos), member); \
	     &pos->member != NIL;					\
	     pos = n,							\
		     n = tree_entry(&n->member != NIL? tree_successor((struct tree_root *)&n->member): NIL, typeof(*n), member))

/* to avoid conflicts with C++ new operator */
#undef new

#endif  /* __ULIB_TREE_H */

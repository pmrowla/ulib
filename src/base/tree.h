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

#ifndef __ULIB_TREE_H
#define __ULIB_TREE_H

struct tree_root {
	struct tree_root *left, *right;
	struct tree_root *parent;
};

/*
 * avl_root is derived from tree_root
 */
struct avl_root {
	struct avl_root *left, *right;
	struct avl_root *parent;
	int balance:3;		/* balance factor */
};

#define NIL (void *)0

/*
 * Macros for internal use.
 * You don't need to initialize tree entry,
 * entries are initialized automatically
 * when adding or mapping them.
 */
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

#define INIT_AVL_ROOT(ptr) do {					\
		INIT_TREE_ROOT(ptr); (ptr)->balance = 0;	\
	} while (0)

/*
 * Simplified tree empty tests
 */
#define TREE_EMPTY(ptr)   ((ptr) == NIL)

#define SPLAY_EMPTY(ptr)  TREE_EMPTY(ptr)

#define AVL_EMPTY(ptr)    TREE_EMPTY(ptr)


#ifdef __cplusplus
extern "C" {
#endif

/**
 * tree_search - searches tree for entry
 * @entry:	entry to search
 * @compare:	function that compares two entries(see note)
 * @root:	tree root entry pointer
 * Note:	compare function should be wrote as to compare the member
 *		of struct tree_root is embedded in, which is the identifier
 *		in that case, tree_entry should be used to obtain such member
 *		in compare function and then make comparison between them.
 */
	struct tree_root *tree_search(struct tree_root *entry,
				      int (*compare) (const void *, const void *),
				      struct tree_root *root);

/**
 * tree_min - returns the minimum entry
 * @root:	tree root entry pointer
 */
	struct tree_root *tree_min(struct tree_root *root);

/**
 * tree_max - returns the maximum entry
 * @root:	tree root entry pointer
 */
	struct tree_root *tree_max(struct tree_root *root);

/**
 * tree_successor - returns the successor entry
 * @root:	tree root entry pointer
 */
	struct tree_root *tree_successor(struct tree_root *root);

/**
 * tree_predecessor - returns the predecessor entry
 * @root:	tree root entry pointer
 */
	struct tree_root *tree_predecessor(struct tree_root *root);

/**
 * tree_add - adds a new entry
 * @new:	new entry to be added
 * @root:	tree root entry pointer address
 */
	void tree_add(struct tree_root *new,
		      int (*compare) (const void *, const void *),
		      struct tree_root **root);

/**
 * tree_map - adds a new entry and returns the pointer to the entry
 * if a duplicate entry found in the tree, returns a pointer to the
 * duplicate without inserting the new entry.
 * @new:	new entry to be added
 * @compare:	function that compares two entries
 * @root:	tree root entry pointer address
 */
	struct tree_root *tree_map(struct tree_root *new,
				   int (*compare) (const void *, const void *),
				   struct tree_root **root);

/**
 * tree_del - deletes an entry
 * @entry:	entry to be deleted
 * @root:	tree root entry pointer address
 */
	void tree_del(struct tree_root *entry, struct tree_root **root);

/**
 * splay_map - adds a new entry and returns the pointer to the entry
 * if a duplicate entry found in the tree, returns a pointer to the
 * duplicate without inserting the new entry.
 * @new:	new entry to be added
 * @compare:	function that compares two entries
 * @root:	tree root entry pointer address
 */
	struct tree_root *splay_map(struct tree_root *new,
				    int (*compare) (const void *, const void *),
				    struct tree_root **root);

/**
 * splay_map_nparent - adds a new entry and returns the pointer to the entry
 * if a duplicate entry found in the tree, returns a pointer to the
 * duplicate without inserting the new entry.
 * @new:	new entry to be added
 * @compare:	function that compares two entries
 * @root:	tree root entry pointer address
 */
	struct tree_root *splay_map_nparent(struct tree_root *new,
					    int (*compare) (const void *, const void *),
					    struct tree_root **root);

/**
 * splay_search - splays tree for entry, returns NIL if entry not found, a pointer
 * to the found entry otherwise
 * @entry:	entry to search
 * @compare:	function that compares two entries(see note)
 * @root:	tree root entry pointer
 * Note:	compare function should be wrote as to compare the member
 *		of struct tree_root is embedded in, which is the identifier
 *		in that case, tree_entry should be used to obtain such member
 *		in compare function and then make comparison between them.
 */
	struct tree_root *splay_search(struct tree_root *entry,
				       int (*compare) (const void *, const void *),
				       struct tree_root **root);

/**
 * splay_search_nparent - splays tree for entry, returns NIL if entry not found, a pointer
 * to the found entry otherwise
 * @entry:	entry to search
 * @compare:	function that compares two entries(see note)
 * @root:	tree root entry pointer
 * Note:	compare function should be wrote as to compare the member
 *		of struct tree_root is embedded in, which is the identifier
 *		in that case, tree_entry should be used to obtain such member
 *		in compare function and then make comparison between them.
 */
	struct tree_root *splay_search_nparent(struct tree_root *entry,
					       int (*compare) (const void *, const void *),
					       struct tree_root **root);

/**
 * avl_add - adds a new entry
 * @new:	new entry to be added
 * @compare:	function that compares two entries
 * @root:	tree root entry pointer address
 * Note:	this function mantains the tree balance
 */
	void avl_add(struct avl_root *new,
		     int (*compare) (const void *, const void *),
		     struct avl_root **root);

/**
 * avl_map - adds a new entry and returns the pointer to the entry
 * if a duplicate entry found in the tree, returns a pointer to the
 * duplicate without inserting the new entry.
 * @new:	new entry to be added
 * @compare:	function that compares two entries
 * @root:	tree root entry pointer address
 * Note:	this function mantains the tree balance
 */
	struct avl_root *avl_map(struct avl_root *new,
				 int (*compare) (const void *, const void *),
				 struct avl_root **root);

/**
 * avl_del - deletes an entry
 * @entry:	the entry to be deleted
 * @compare:	function that compares two entries
 * @root:	tree root entry pointer address
 * Note:	this function matains the tree balance
 */
	void avl_del(struct avl_root *entry, struct avl_root **root);

#ifdef __cplusplus
}
#endif

/**
 * tree_entry - get the struct for this entry
 * @ptr:	the &struct tree_root pointer.
 * @type:	the type of the struct this is embedded in.
 * @member:	the name of the tree_struct within the struct.
 */
#define tree_entry(ptr, type, member)					\
	((type *)((char *)(ptr)-(unsigned long)(&((type *)0)->member)))

/**
 * avl_entry - get the struct for this entry
 * @ptr:	the &struct avl_root pointer.
 * @type:	the type of the struct this is embedded in.
 * @member:	the name of the avl_struct within the struct.
 */
#define avl_entry(ptr, type, member) tree_entry(ptr, type, member)

/**
 * tree_for_each	-	iterate over a tree in ascending order
 * @pos:	the &struct tree_root to use as a loop counter.
 * @root:	the root for your tree.
 */
#define tree_for_each(pos, root)		\
	for (pos = tree_min(root); pos != NIL;	\
	     pos = tree_successor(pos))
/**
 * tree_for_each_prev	-	iterate over a tree in descending order
 * @pos:	the &struct tree_root to use as a loop counter.
 * @root:	the root for your tree.
 */
#define tree_for_each_prev(pos, root)		\
	for (pos = tree_max(root); pos != NIL;	\
	     pos = tree_predecessor(pos))

/**
 * tree_for_each_safe	-	iterate over a tree safe against removal of tree entry
 * @pos:	the &struct tree_root to use as a loop counter.
 * @n:		another &struct tree_root to use as temporary storage
 * @root:	the head for your tree.
 */
#define tree_for_each_safe(pos, n, root)			\
	for (pos = tree_min(root),				\
		     n = tree_successor(pos); pos != NIL;	\
	     pos = n, n = n != NIL? tree_successor(n): NIL)

/**
 * tree_for_each_entry	-	iterate over tree of given type
 * @pos:	the type * to use as a loop counter.
 * @root:	the root for your tree.
 * @member:	the name of the tree_struct within the struct.
 */
#define tree_for_each_entry(pos, root, member)				\
	for (pos = tree_entry(tree_min(root), typeof(*pos), member);	\
	     &pos->member != NIL;					\
	     pos = tree_entry(tree_successor(&pos->member), typeof(*pos), member))

/**
 * tree_for_each_entry_safe - iterate over a tree of given type safe against removal of tree entry
 * @pos:	the type * to use as a loop counter.
 * @n:		another type * to use as temporary storage
 * @root:	the root for your tree.
 * @member:	the name of the tree_struct within the struct.
 */
#define tree_for_each_entry_safe(pos, n, root, member)			\
	for (pos = tree_entry(tree_min(root), typeof(*pos), member),	\
	     n = tree_entry(tree_successor(&pos->member), typeof(*pos), member); \
	     &pos->member != NIL; pos = n,				\
	     n = tree_entry(&n->member != NIL? tree_successor(&n->member): NIL, typeof(*n), member))

/**
 * avl_for_each	-	iterate over an AVL tree in ascending order
 * @pos:	the &struct avl_root to use as a loop counter.
 * @root:	the root for your AVL tree.
 */
#define avl_for_each(pos, root)						\
	for (pos = (struct avl_root *)tree_min((struct tree_root *)root); pos != NIL; \
	     pos = (struct avl_root *)tree_successor((struct tree_root *)pos))
/**
 * avl_for_each_prev	-	iterate over an AVL tree in descending order
 * @pos:	the &struct avl_root to use as a loop counter.
 * @root:	the root for your AVL tree.
 */
#define avl_for_each_prev(pos, root)					\
	for (pos = (struct avl_root *)tree_max((struct tree_root *)root); pos != NIL; \
	     pos = (struct avl_root *)tree_predecessor((struct tree_root *)pos))

/**
 * avl_for_each_safe	-	iterate over an AVL tree safe against removal of tree entry
 * @pos:	the &struct avl_root to use as a loop counter.
 * @n:		another &struct avl_root to use as temporary storage
 * @root:	the root for your AVL tree.
 */
#define avl_for_each_safe(pos, n, root)					\
	for (pos = (struct avl_root *)tree_min((struct tree_root *)root), \
	     n = (struct avl_root *)tree_successor((struct tree_root *)pos); pos != NIL; \
	     pos = n,							\
	     n = n != NIL? (struct avl_root *)tree_successor((struct tree_root *)n): NIL)

/**
 * avl_for_each_entry	-	iterate over tree of given type
 * @pos:	the type * to use as a loop counter.
 * @root:	the root for your AVL tree.
 * @member:	the name of the tree_struct within the struct.
 */
#define avl_for_each_entry(pos, root, member)				\
	for (pos = tree_entry(tree_min((struct tree_root *)root), typeof(*pos), member); \
	     &pos->member != NIL; 					\
	     pos = tree_entry(tree_successor((struct tree_root *)&pos->member), typeof(*pos), member))

/**
 * avl_for_each_entry_safe - iterate over an AVL tree of given type safe against removal of tree entry
 * @pos:	the type * to use as a loop counter.
 * @n:		another type * to use as temporary storage
 * @root:	the root for your tree.
 * @member:	the name of the tree_struct within the struct.
 */
#define avl_for_each_entry_safe(pos, n, root, member)			\
	for (pos = tree_entry(tree_min((struct tree_root *)root), typeof(*pos), member), \
	     n = tree_entry(tree_successor((struct tree_root *)&pos->member), typeof(*pos), member); \
	     &pos->member != NIL;					\
	     pos = n,							\
	     n = tree_entry(&n->member != NIL? tree_successor((struct tree_root *)&n->member): NIL, typeof(*n), member))

#endif  /* __ULIB_TREE_H */

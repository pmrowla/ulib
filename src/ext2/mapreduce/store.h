/* The MIT License

   Copyright (C) 2012 Zilong Tan (eric.zltan@gmail.com)

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

#ifndef __ULIB_STORE_H
#define __ULIB_STORE_H

#include <pthread.h>
#include <assert.h>
#include <string.h>
#include <ulib/regionlock.h>
#include <ulib/chainhash.h>

namespace ulib {

namespace mapreduce {

// store based on chain hash table
template<class _Key, class _Val>
class chain_hash_store : public ulib::chain_hash_map<_Key, _Val>,
	      public ulib::region_lock
{
public:
	typedef typename ulib::chain_hash_map<_Key,_Val>::size_type        size_type;
	typedef typename ulib::chain_hash_map<_Key,_Val>::pointer          pointer;
	typedef typename ulib::chain_hash_map<_Key,_Val>::const_pointer    const_pointer;
	typedef typename ulib::chain_hash_map<_Key,_Val>::reference        reference;
	typedef typename ulib::chain_hash_map<_Key,_Val>::const_reference  const_reference;
	typedef typename ulib::chain_hash_map<_Key,_Val>::iterator         iterator;
	typedef typename ulib::chain_hash_map<_Key,_Val>::const_iterator   const_iterator;

	chain_hash_store(size_t min_bucket, size_t min_lock)
	: ulib::chain_hash_map<_Key,_Val>(min_bucket),
	  ulib::region_lock(min_lock)
	{ assert(min_bucket >= min_lock); }

	chain_hash_store(size_t min_bucket)
	: ulib::chain_hash_map<_Key,_Val>(min_bucket),
	  ulib::region_lock(min_bucket)
	{ }

	// DO NOT copy the elements
	chain_hash_store(const chain_hash_store &other)
	: ulib::chain_hash_map<_Key,_Val>(other),
	  ulib::region_lock(((const ulib::region_lock *)&other)->bucket_count())
	{ }

	void
	lock(const _Key &key)
	{ acquire(key); }

	void
	unlock(const _Key &key)
	{ release(key); }

	// again DO NOT copy the elements
	chain_hash_store &
	operator= (const chain_hash_store &other)
	{
		*(ulib::chain_hash_map<_Key,_Val> *)this =
			*(const ulib::chain_hash_map<_Key,_Val> *)&other;
		*(ulib::region_lock *)this = *(const ulib::region_lock *)&other;
		return *this;
	}

	size_type
	bucket_count() const
	{ return ((ulib::chain_hash_map<_Key,_Val> *)this)->bucket_count(); }
};

}  // namespace mapreduce

}  // namespace ulib

#endif  /* __ULIB_STORE_H */

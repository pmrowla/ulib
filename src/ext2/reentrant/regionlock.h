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

#ifndef _REGION_LOCK_H
#define _REGION_LOCK_H

#include <pthread.h>

namespace ulib {

class region_lock {
public:
	region_lock(size_t max)
	{
		--max;
		max |= max >> 1;
		max |= max >> 2;
		max |= max >> 4;
		max |= max >> 8;
		max |= max >> 16;
		if (sizeof(size_t) == 8)
			max |= max >> 32;
		_mask  = max;
		_locks = new pthread_spinlock_t [max + 1];
		for (size_t i = 0; i <= _mask; ++i)
			pthread_spin_init(&_locks[i], 0);
	}

	region_lock(const region_lock &other)
	{
		_mask  = other.bucket_count() - 1;
		_locks = new pthread_spinlock_t [_mask + 1];
		for (size_t i = 0; i <= _mask; ++i)
			pthread_spin_init(&_locks[i], 0);
	}

	virtual
	~region_lock()
	{
		for (size_t i = 0; i <= _mask; ++i)
			pthread_spin_destroy(_locks + i);
		delete [] _locks;
	}

	region_lock &
	operator= (const region_lock &other)
	{
		if (bucket_count() != other.bucket_count()) {
			for (size_t i = 0; i <= _mask; ++i)
				pthread_spin_destroy(_locks + i);
			delete [] _locks;
			_mask  = other.bucket_count() - 1;
			_locks = new pthread_spinlock_t [_mask + 1];
			for (size_t i = 0; i <= _mask; ++i)
				pthread_spin_init(&_locks[i], 0);
		}
		return *this;
	}

	void
	acquire(size_t h) const
	{ pthread_spin_lock(_locks + (h & _mask)); }

	void
	release(size_t h) const
	{ pthread_spin_unlock(_locks + (h & _mask)); }

	size_t
	bucket_count() const
	{ return _mask + 1; }

private:
	size_t _mask;
	pthread_spinlock_t *_locks;
};

}  // namespace ulib

#endif  /* _REGION_LOCK_H */

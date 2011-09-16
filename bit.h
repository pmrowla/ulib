/*
 * Routines manipulating bits.
 *
 * Copyright (C) 2010  Zi-long Tan (tzlloch@gmail.com)
 *
 * This file is part of ULIB.
 * 
 * ULIB is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * ULIB is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef __ULIB_BIT_H
#define __ULIB_BIT_H

#include <stdint.h>
#include "bit.h"

#define BITS_PER_BYTE       8
#define BITS_PER_LONG       ((int)((sizeof(long) * BITS_PER_BYTE)))

#define DIV_ROUND_UP(n,d)   (((n) + (d) - 1) / (d))
#define BITS_TO_LONGS(nr)   DIV_ROUND_UP(nr, BITS_PER_BYTE * sizeof(long))
#define BIT_WORD(nr)        ((nr) / BITS_PER_LONG)
#define BIT_MASK(nr)        (1UL << ((nr) % BITS_PER_LONG))
#define ALIGN_MASK(x, mask) (((x) + (mask)) & ~(mask))
#define ALIGN(x, a)         ALIGN_MASK(x, (typeof(x))(a) - 1)
#define ROR64(x, r)         ((x) >> (r) | (x) << (64 - (r)))

#endif  /* __ULIB_BIT_H */

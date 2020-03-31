/* Copyright (C) 2010-2012 Free Software Foundation, Inc.
   This file is part of the GNU C Library.
   Contributed by Maxim Kuvyrkov <maxim@codesourcery.com>, 2010.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library.  If not, see
   <http://www.gnu.org/licenses/>.  */

#ifndef _KVX_BITS_ATOMIC_H
#define _KVX_BITS_ATOMIC_H

#include <stdint.h>

typedef int8_t atomic8_t;
typedef uint8_t uatomic8_t;
typedef int_fast8_t atomic_fast8_t;
typedef uint_fast8_t uatomic_fast8_t;

typedef int16_t atomic16_t;
typedef uint16_t uatomic16_t;
typedef int_fast16_t atomic_fast16_t;
typedef uint_fast16_t uatomic_fast16_t;

typedef int32_t atomic32_t;
typedef uint32_t uatomic32_t;
typedef int_fast32_t atomic_fast32_t;
typedef uint_fast32_t uatomic_fast32_t;

typedef int64_t atomic64_t;
typedef uint64_t uatomic64_t;
typedef int_fast64_t atomic_fast64_t;
typedef uint_fast64_t uatomic_fast64_t;

typedef intptr_t atomicptr_t;
typedef uintptr_t uatomicptr_t;
typedef intmax_t atomic_max_t;
typedef uintmax_t uatomic_max_t;


#ifndef atomic_full_barrier
# define atomic_full_barrier() do { atomic_read_barrier();		\
					atomic_write_barrier(); } while(0)
#endif

#ifndef atomic_read_barrier
# define atomic_read_barrier() __builtin_kvx_dinval()
#endif

#ifndef atomic_write_barrier
# define atomic_write_barrier() __builtin_kvx_fence()
#endif

/*
 * Atomic compare and exchange.  Compare OLD with MEM, if identical,
 * store NEW in MEM.  Return the initial value in MEM.  Success is
 * indicated by comparing RETURN with OLD.
 */
#define __cmpxchg(ptr, old, newval, op_suffix)				\
({									\
	__typeof((ptr)) __cxc__ptr = (ptr);					\
	register unsigned long __cxc__rn __asm__("r62") = (unsigned long) (newval);	\
	register unsigned long __cxc__ro __asm__("r63") = (unsigned long) (old);	\
	do {								\
		__asm__ __volatile__ (					\
			"acswap" #op_suffix " 0[%[rPtr]], $r62r63\n"	\
			: "+r" (__cxc__rn), "+r" (__cxc__ro)			\
			: [rPtr] "r" (__cxc__ptr)				\
			: "memory");					\
		/* Success */						\
		if (__cxc__rn) {						\
			__cxc__ro = (unsigned long) (old);			\
			break;						\
		}							\
		/* We failed, read value  */				\
		__cxc__ro = (unsigned long) *(__cxc__ptr);			\
		if (__cxc__ro != (unsigned long) (old))			\
			break;						\
		/* __cxc__rn has been cloberred by cmpxch result */		\
		__cxc__rn = (unsigned long) (newval);				\
	} while (1);							\
	(__cxc__ro);								\
})

#define cmpxchg(ptr, o, n)						\
({									\
	unsigned long __cmpxchg__ret;						\
	switch (sizeof(*(ptr))) {					\
	case 4:								\
		__cmpxchg__ret = __cmpxchg((ptr), (o), (n), w);			\
		break;							\
	case 8:								\
		__cmpxchg__ret = __cmpxchg((ptr), (o), (n), d);			\
		break;							\
	}								\
	(__typeof(*(ptr))) (__cmpxchg__ret);					\
})

#define atomic_compare_and_exchange_val_acq(mem, newval, oldval)	\
	cmpxchg((mem), (oldval), (newval))


#define atomic_exchange_acq(mem, newval)				\
({									\
	unsigned long __aea__ret, __aea__old;					\
	volatile __typeof((mem)) __aea__m = (mem);				\
	do {								\
		__aea__old = *__aea__m;						\
		__aea__ret = atomic_compare_and_exchange_val_acq((mem),	\
						(newval), (__aea__old));\
	} while (__aea__old != __aea__ret);					\
	(__aea__old);							\
})

#endif

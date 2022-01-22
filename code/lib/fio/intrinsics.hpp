#pragma once

#include "compiler.hpp"

#if defined(_MSC_VER)
# include <intrin.h>
#elif defined(__x86_64__) || defined(__i386__)
# include <x86intrin.h>
#endif

namespace fio
{
	namespace nat
	{
#if defined(_M_X64) || defined(_M_AMD64) || defined(__x86_64__) || (defined(_MSC_VER) && defined(_M_IX86)) || defined(__i386__)

		fio_inline
		unsigned int bsr32(unsigned int x)
		{
			fio_assert(x != 0);

# if defined(_MSC_VER)
			unsigned long i;
			_BitScanReverse(&i, x);
			return i;
# else
			return static_cast<unsigned int>(__bsrd(static_cast<int>(x)));
# endif
		}

		fio_inline
		unsigned int udiv32(unsigned int n, unsigned int m, unsigned char s)
		{
			fio_assert(s < 64);

			// pray that the assembly is good :pray:
			const unsigned long long prod = n * static_cast<unsigned long long>(m);
			return static_cast<unsigned int>(prod >> s);
		}

#endif

#if defined(_M_X64) || defined(_M_AMD64) || defined(__x86_64__)

		fio_inline
		unsigned int bsr64(unsigned long long x)
		{
			fio_assert(x != 0);

# if defined(_MSC_VER)
			unsigned long i;
			_BitScanReverse64(&i, x);
			return i;
# else
			return static_cast<unsigned int>(__bsrq(static_cast<long long>(x)));
# endif
		}

		fio_inline
		unsigned long long udiv64(unsigned long long n, unsigned long long m, unsigned char s)
		{
			fio_assert(s >= 64);
			fio_assert(s < 128);

# if defined(_MSC_VER)
			return __umulh(n, m) >> (s - 64);
# elif __SIZEOF_INT128__ == 16
			// pray that the assembly is good :pray:
			const unsigned __int128 prod = n * static_cast<unsigned __int128>(m);
			return static_cast<unsigned long long>(prod >> s);
# else
#  error Missing implementation!
# endif
		}

		fio_inline
		unsigned long long umul128hi(unsigned long long a, unsigned long long b)
		{
# if defined(_MSC_VER)
			return __umulh(a, b);
# elif __SIZEOF_INT128__ == 16
			// pray that the assembly is good :pray:
			const unsigned __int128 prod = a * static_cast<unsigned __int128>(b);
			return static_cast<unsigned long long>(prod >> 64);
# else
#  error Missing implementation!
# endif
		}

		fio_inline
		unsigned long long umul128(unsigned long long a, unsigned long long b, unsigned long long * hi)
		{
# if defined(_MSC_VER)
			return _umul128(a, b, hi);
# elif __SIZEOF_INT128__ == 16
			// pray that the assembly is good :pray:
			const unsigned __int128 prod = a * static_cast<unsigned __int128>(b);
			*hi = static_cast<unsigned long long>(prod >> 64);
			return static_cast<unsigned long long>(prod & 0xffffffffffffffff);
# else
#  error Missing implementation!
# endif
		}

		fio_inline
		unsigned long long ushl128(unsigned long long lo, unsigned long long hi, unsigned char c)
		{
			fio_assert(c < 64);

# if defined(_MSC_VER)
			return __shiftleft128(lo, hi, c);
# elif __SIZEOF_INT128__ == 16
			// pray that the assembly is good :pray:
			return static_cast<unsigned long long>((((static_cast<unsigned __int128>(hi) << 64) | lo) << c) >> 64);
# else
#  error Missing implementation!
# endif
		}

		fio_inline
		unsigned long long ushr128(unsigned long long lo, unsigned long long hi, unsigned char c)
		{
			fio_assert(c < 64);

# if defined(_MSC_VER)
			return __shiftright128(lo, hi, c);
# elif __SIZEOF_INT128__ == 16
			// pray that the assembly is good :pray:
			return static_cast<unsigned long long>((((static_cast<unsigned __int128>(hi) << 64) | lo) >> c) & 0xffffffffffffffff);
# else
#  error Missing implementation!
# endif
		}

#endif
	}
}

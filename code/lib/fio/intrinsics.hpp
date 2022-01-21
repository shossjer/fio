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
#if defined(_M_X64) || defined(_M_AMD64)

		fio_inline
		unsigned int bsr64(unsigned long long x)
		{
			fio_assert(x != 0);

			unsigned long i;
			_BitScanReverse64(&i, x);

			return i;
		}

		fio_inline
		unsigned long long umul128hi(unsigned long long a, unsigned long long b)
		{
			return __umulh(a, b);
		}

		fio_inline
		unsigned long long umul128(unsigned long long a, unsigned long long b, unsigned long long * hi)
		{
			return _umul128(a, b, hi);
		}

		fio_inline
		unsigned long long ushl128(unsigned long long lo, unsigned long long hi, unsigned char c)
		{
			fio_assert(c < 64);

			return __shiftleft128(lo, hi, c);
		}

		fio_inline
		unsigned long long ushr128(unsigned long long lo, unsigned long long hi, unsigned char c)
		{
			fio_assert(c < 64);

			return __shiftright128(lo, hi, c);
		}

#elif defined(__x86_64__)

		fio_inline
		unsigned int bsr64(unsigned long long x)
		{
			fio_assert(x != 0);

			return static_cast<unsigned int>(__bsrq(static_cast<long long>(x)));
		}

#endif

#if __SIZEOF_INT128__ == 16

		// pray that the compiler generates the assembly we want :pray:

		fio_inline
		unsigned long long umul128hi(unsigned long long a, unsigned long long b)
		{
			const unsigned __int128 prod = a * static_cast<unsigned __int128>(b);
			return static_cast<unsigned long long>(prod >> 64);
		}

		fio_inline
		unsigned long long umul128(unsigned long long a, unsigned long long b, unsigned long long * hi)
		{
			const unsigned __int128 prod = a * static_cast<unsigned __int128>(b);
			*hi = static_cast<unsigned long long>(prod >> 64);
			return static_cast<unsigned long long>(prod & 0xffffffffffffffff);
		}

		fio_inline
		unsigned long long ushl128(unsigned long long lo, unsigned long long hi, unsigned char c)
		{
			fio_assert(c < 64);

			return static_cast<unsigned long long>((((static_cast<unsigned __int128>(hi) << 64) | lo) << c) >> 64);
		}

		fio_inline
		unsigned long long ushr128(unsigned long long lo, unsigned long long hi, unsigned char c)
		{
			fio_assert(c < 64);

			return static_cast<unsigned long long>((((static_cast<unsigned __int128>(hi) << 64) | lo) >> c) & 0xffffffffffffffff);
		}

#endif
	}
}

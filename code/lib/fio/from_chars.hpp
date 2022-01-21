#pragma once

#include "fio/compiler.hpp"
#include "fio/stdint.hpp"

#include "fio/intrinsics.hpp"
#include "fio/mem.hpp"
#include "fio/stdhacks.hpp"

namespace fio
{
	namespace detail
	{
		fio_inline constexpr usize umax(uint8) { return 0xffu; }
		fio_inline constexpr usize umax(uint16) { return 0xffffu; }
		fio_inline constexpr usize umax(uint32) { return 0xffffffffu; }
#if defined(_M_X64) || defined(_M_AMD64) || defined(__x86_64__)
		fio_inline constexpr usize umax(uint64) { return 0xffffffffffffffffu; }
#endif

		fio_inline constexpr usize smax(sint8) { return 0x7fu; }
		fio_inline constexpr usize smax(sint16) { return 0x7fffu; }
		fio_inline constexpr usize smax(sint32) { return 0x7fffffffu; }
#if defined(_M_X64) || defined(_M_AMD64) || defined(__x86_64__)
		fio_inline constexpr usize smax(sint64) { return 0x7fffffffffffffffu; }
#endif

		fio_inline constexpr int ulen(uint8) { return 3; }
		fio_inline constexpr int ulen(uint16) { return 5; }
		fio_inline constexpr int ulen(uint32) { return 10; }
#if defined(_M_X64) || defined(_M_AMD64) || defined(__x86_64__)
		fio_inline constexpr int ulen(uint64) { return 20; }
#endif

		fio_inline constexpr int slen(sint8) { return 3; }
		fio_inline constexpr int slen(sint16) { return 5; }
		fio_inline constexpr int slen(sint32) { return 10; }
#if defined(_M_X64) || defined(_M_AMD64) || defined(__x86_64__)
		fio_inline constexpr int slen(sint64) { return 19; }
#endif

		template <typename T>
		fio_inline const char * from_chars_unsigned(const char * begin, const char * end, T & value)
		{
			const char * const error = begin;
			if (!fio_expect(begin != end))
				return error; // not a number

			const usize mval = umax(value);

			usize uval = static_cast<usize>(*begin) - '0';
			if (!fio_expect(!(uval >= 10)))
				return error; // not a number

			begin++;

			if (begin != end)
			{
				const char * const last = begin + (ulen(value) - 1); // first digit already read
				const char * const end_or_last = end < last ? end : last;

				do
				{
					const usize digit = static_cast<usize>(*begin) - '0';
					if (digit >= 10)
					{
						value = static_cast<T>(uval);

						return begin;
					}

					uval = uval * 10 + digit;
					begin++;
				}
				while (begin != end_or_last);

				if (uval > mval)
					return error; // overflow

				if (begin != end)
				{
					const usize trail = static_cast<usize>(*begin) - '0';
					if (!(trail >= 10))
						return error; // overflow
				}
			}

			value = static_cast<T>(uval);

			return begin;
		}

		template <typename T>
		fio_inline const char * from_chars_signed(const char * begin, const char * end, T & value)
		{
			const char * const error = begin;
			if (!fio_expect(begin != end))
				return error; // not a number

			usize mval = smax(value);

			const bool is_negative = *begin == '-';
			if (is_negative)
			{
				begin++;
				mval++;
			}
			if (!fio_expect(begin != end))
				return error; // not a number

			usize uval = static_cast<usize>(*begin) - '0';
			if (!fio_expect(!(uval >= 10)))
				return error; // not a number

			begin++;

			if (begin != end)
			{
				const char * const last = begin + (slen(value) - 1); // first digit already read
				const char * const end_or_last = end < last ? end : last;

				do
				{
					const usize digit = static_cast<usize>(*begin) - '0';
					if (digit >= 10)
					{
						if (is_negative)
						{
							uval = 0 - uval;
						}

						value = static_cast<T>(uval);

						return begin;
					}

					uval = uval * 10 + digit;
					begin++;
				}
				while (begin != end_or_last);

				if (uval > mval)
					return error; // overflow

				if (begin != end)
				{
					const usize trail = static_cast<usize>(*begin) - '0';
					if (!(trail >= 10))
						return error; // overflow
				}
			}

			if (is_negative)
			{
				uval = 0 - uval;
			}

			value = static_cast<T>(uval);

			return begin;
		}

#if defined(_M_X64) || defined(_M_AMD64) || defined(__x86_64__)

		fio_inline const char * from_chars_unsigned(const char * begin, const char * end, uint64 & value)
		{
			const char * const error = begin;
			if (!fio_expect(begin != end))
				return error; // not a number

			usize uval = static_cast<usize>(*begin) - '0';
			if (!fio_expect(!(uval >= 10)))
				return error; // not a number

			begin++;

			if (begin != end)
			{
				const char * const before_last = begin + (ulen(value) - 2); // first digit already read
				const char * const end_or_before_last = end < before_last ? end : before_last;

				do
				{
					// todo msvc inserts a superfluous move
					const usize digit = static_cast<usize>(*begin) - '0';
					if (digit >= 10)
					{
						value = static_cast<uint64>(uval);

						return begin;
					}

					uval = uval * 10 + digit;
					begin++;
				}
				while (begin != end_or_before_last);

				if (begin != end)
				{
					const usize digit = static_cast<usize>(*begin) - '0';
					if (digit >= 10)
					{
						value = static_cast<uint64>(uval);

						return begin;
					}

#if defined(__GNUC__)
					if (__builtin_umull_overflow(uval, 10, &uval))
						return error; // overflow

					if (__builtin_uaddl_overflow(uval, digit, &uval))
						return error; // overflow
#elif defined(_MSC_VER)
					usize overflow;
					uval = _umul128(uval, 10, &overflow);
					if (overflow != 0) // todo msvc does not branch on CF/OF
						return error; // overflow

					if (_addcarry_u64(0, uval, digit, &uval) != 0)
						return error; // overflow
#endif

					begin++;

					if (begin != end)
					{
						const usize trail = static_cast<usize>(*begin) - '0';
						if (!(trail >= 10))
							return error; // overflow
					}
				}
			}

			value = static_cast<uint64>(uval);

			return begin;
		}

#else

# error Missing implementation!
		// todo check for overflows of 32 bit integers, signed and unsigned
		// todo can we use mmx?

#endif
	}

	fio_inline const char * from_chars(const char * begin, const char * end, unsigned char & value)
	{
		static_assert(sizeof(unsigned char) == sizeof(uint8), "Expected unsigned char to be 8 bits");

		return detail::from_chars_unsigned(begin, end, reinterpret_cast<uint8 &>(value));
	}

	fio_inline const char * from_chars(const char * begin, const char * end, signed char & value)
	{
		static_assert(sizeof(signed char) == sizeof(sint8), "Expected signed char to be 8 bits");

		return detail::from_chars_signed(begin, end, reinterpret_cast<sint8 &>(value));
	}

	fio_inline const char * from_chars(const char * begin, const char * end, unsigned short & value)
	{
		static_assert(sizeof(unsigned short) == sizeof(uint16), "Expected unsigned short to be 16 bits");

		return detail::from_chars_unsigned(begin, end, reinterpret_cast<uint16 &>(value));
	}

	fio_inline const char * from_chars(const char * begin, const char * end, signed short & value)
	{
		static_assert(sizeof(signed short) == sizeof(sint16), "Expected signed short to be 16 bits");

		return detail::from_chars_signed(begin, end, reinterpret_cast<sint16 &>(value));
	}

	fio_inline const char * from_chars(const char * begin, const char * end, unsigned int & value)
	{
		static_assert(sizeof(unsigned int) == sizeof(uint32), "Expected unsigned int to be 32 bits");

		return detail::from_chars_unsigned(begin, end, reinterpret_cast<uint32 &>(value));
	}

	fio_inline const char * from_chars(const char * begin, const char * end, signed int & value)
	{
		static_assert(sizeof(signed int) == sizeof(sint32), "Expected signed int to be 32 bits");

		return detail::from_chars_signed(begin, end, reinterpret_cast<sint32 &>(value));
	}

#if defined(_M_X64) || defined(_M_AMD64) || defined(__x86_64__)

	fio_inline const char * from_chars(const char * begin, const char * end, unsigned long long & value)
	{
		static_assert(sizeof(unsigned long long) == sizeof(uint64), "Expected unsigned long long to be 64 bits");

		return detail::from_chars_unsigned(begin, end, reinterpret_cast<uint64 &>(value));
	}

	fio_inline const char * from_chars(const char * begin, const char * end, signed long long & value)
	{
		static_assert(sizeof(signed long long) == sizeof(sint64), "Expected signed long long to be 64 bits");

		return detail::from_chars_signed(begin, end, reinterpret_cast<sint64 &>(value));
	}

#endif

#if defined(__LP64__)

	fio_inline const char * from_chars(const char * begin, const char * end, unsigned long & value)
	{
		static_assert(sizeof(unsigned long) == sizeof(uint64), "Expected unsigned long to be 64 bits");

		return detail::from_chars_unsigned(begin, end, reinterpret_cast<uint64 &>(value));
	}

	fio_inline const char * from_chars(const char * begin, const char * end, signed long & value)
	{
		static_assert(sizeof(signed long) == sizeof(sint64), "Expected signed long to be 64 bits");

		return detail::from_chars_signed(begin, end, reinterpret_cast<sint64 &>(value));
	}

#else

	fio_inline const char * from_chars(const char * begin, const char * end, unsigned long & value)
	{
		static_assert(sizeof(unsigned long) == sizeof(uint32), "Expected unsigned long to be 32 bits");

		return detail::from_chars_unsigned(begin, end, reinterpret_cast<uint32 &>(value));
	}

	fio_inline const char * from_chars(const char * begin, const char * end, signed long & value)
	{
		static_assert(sizeof(signed long) == sizeof(sint32), "Expected signed long to be 32 bits");

		return detail::from_chars_signed(begin, end, reinterpret_cast<sint32 &>(value));
	}

#endif

	namespace detail
	{
		fio_target("sse4.1") fio_inline
		void extract_integer_8(const char * end, fio::uint32 & val)
		{
			const __m128i line = _mm_loadl_epi64(reinterpret_cast<const __m128i *>(end - 8));
			// note we use _mm_loadl_epi64 instead of _mm_loadu_si64
			// since it is more portable between compilers, even though
			// the former is part of SSE2 while the latter only needs SSE

			const __m128i digits = _mm_sub_epi8(line, _mm_set1_epi8('0'));

			const __m128i digits_abcd = _mm_shuffle_epi8(digits, _mm_set_epi8(-1, -1, -1, 3, -1, -1, -1, 2, -1, -1, -1, 1, -1, -1, -1, 0));
			const __m128i digits_efgh = _mm_shuffle_epi8(digits, _mm_set_epi8(-1, -1, -1, 7, -1, -1, -1, 6, -1, -1, -1, 5, -1, -1, -1, 4));

			// todo can it be done faster?
			const __m128i digits_abcd_mul = _mm_mullo_epi32(digits_abcd, _mm_set_epi32(10000, 100000, 1000000, 10000000));
			const __m128i digits_efgh_mul = _mm_mullo_epi32(digits_efgh, _mm_set_epi32(1, 10, 100, 1000));

			const __m128i digits_add1 = _mm_add_epi32(digits_abcd_mul, digits_efgh_mul);
			const __m128i digits_add2 = _mm_add_epi32(digits_add1, _mm_srli_si128(digits_add1, 8));
			const __m128i digits_add3 = _mm_add_epi32(digits_add2, _mm_srli_si128(digits_add2, 4));

			val = static_cast<unsigned int>(_mm_cvtsi128_si32(digits_add3));
		}

		fio_target("ssse3") fio_inline
		void extract_integer_16(const char * end, fio::uint64 & val)
		{
			const __m128i line = _mm_loadu_si128(reinterpret_cast<const __m128i *>(end - 16));

			const __m128i digits = _mm_sub_epi8(line, _mm_set1_epi8('0'));

			// _mm_maddubs_epi16 // ssse3
			//       arg a  p| o| n| m| l| k| j| i| h| g| f| e| d| c| b| a
			//       arg b  1|10| 1|10| 1|10| 1|10| 1|10| 1|10| 1|10| 1|10
			// (8 16-bits)    op|   mn|   kl|   ij|   gh|   ef|   cd|   ab
			const __m128i pair = _mm_maddubs_epi16(digits, _mm_set1_epi16(0x010a));
			// _mm_madd_epi16
			//       arg a    op|   mn|   kl|   ij|   gh|   ef|   cd|   ab
			//       arg b     1|  100|    1|  100|    1|  100|    1|  100
			// (4 32-bits)        mnop|       ijkl|       efgh|       abcd
			const __m128i quad = _mm_madd_epi16(pair, _mm_set1_epi32(0x00010064));

			// _mm_mul_epu32
			//       arg a        mnop|       ijkl|       efgh|       abcd
			//       arg b            |      10000|           |  244140625 // 5**12
			// (2 64-bits)                ijkl0000|                  abcd*
			const __m128i digits_abcdijkl = _mm_mul_epu32(quad, _mm_set_epi32(0, 10000, 0, 244140625));

			const __m128i digits_abcd = _mm_slli_epi64(digits_abcdijkl, 12);
			const __m128i digits_ijkl = _mm_srli_si128(digits_abcdijkl, 8);

			// _mm_srli_epi64 imm8=32
			//       arg a        mnop|       ijkl|       efgh|       abcd
			// _mm_mul_epu32
			//       arg b            |          0|           |  100000000
			// (2 64-bits)                       0|           efgh00000000
			const __m128i digits_efgh = _mm_mul_epu32(_mm_srli_epi64(quad, 32), _mm_set_epi32(0, 0, 0, 100000000));

			const __m128i digits_mnop = _mm_srli_si128(quad, 12);

			// _mm_add_epi32
			//       arg a                       0|                   mnop
			//       arg b                       0|               ijkl0000
			// _mm_add_epi32
			//       arg b                       0|           efgh00000000
			// _mm_add_epi32
			//       arg b                        |       abcd000000000000
			// (2 64-bits)                        |       abcdefghijklmnop
			const __m128i sum = _mm_add_epi64(_mm_add_epi64(_mm_add_epi64(digits_mnop, digits_ijkl), digits_efgh), digits_abcd);

			val = static_cast<unsigned long long>(_mm_cvtsi128_si64(sum));
		}

		fio_target("ssse3") fio_inline
		void extract_integer_32(const char * end, fio::uint64 & valhi, fio::uint64 & vallo)
		{
			const __m128i line1 = _mm_loadu_si128(reinterpret_cast<const __m128i *>(end - 32));
			const __m128i line2 = _mm_loadu_si128(reinterpret_cast<const __m128i *>(end - 16));

			const __m128i digits1 = _mm_sub_epi8(line1, _mm_set1_epi8('0'));
			const __m128i digits2 = _mm_sub_epi8(line2, _mm_set1_epi8('0'));

			// _mm_maddubs_epi16 // ssse3
			//       arg a  p| o| n| m| l| k| j| i| h| g| f| e| d| c| b| a
			//       arg b  1|10| 1|10| 1|10| 1|10| 1|10| 1|10| 1|10| 1|10
			// (8 16-bits)    op|   mn|   kl|   ij|   gh|   ef|   cd|   ab
			const __m128i digits11 = _mm_maddubs_epi16(digits1, _mm_set1_epi16(0x010a));
			// _mm_madd_epi16
			//       arg a    op|   mn|   kl|   ij|   gh|   ef|   cd|   ab
			//       arg b     1|  100|    1|  100|    1|  100|    1|  100
			// (4 32-bits)        mnop|       ijkl|       efgh|       abcd
			const __m128i digits1111 = _mm_madd_epi16(digits11, _mm_set1_epi32(0x00010064));

			// _mm_maddubs_epi16 // ssse3
			//       arg a  F| E| D| C| B| A| z| y| x| w| v| u| t| s| r| q
			//       arg b  1|10| 1|10| 1|10| 1|10| 1|10| 1|10| 1|10| 1|10
			// (8 16-bits)    EF|   CD|   AB|   yz|   wx|   uv|   st|   qr
			const __m128i digits22 = _mm_maddubs_epi16(digits2, _mm_set1_epi16(0x010a));
			// _mm_madd_epi16
			//       arg a    EF|   CD|   AB|   yz|   wx|   uv|   st|   qr
			//       arg b     1|  100|    1|  100|    1|  100|    1|  100
			// (4 32-bits)        CDEF|       yzAB|       uvwx|       qrst
			const __m128i digits2222 = _mm_madd_epi16(digits22, _mm_set1_epi32(0x00010064));

			// _mm_unpacklo_epi64
			//       arg a        mnop|       ijkl|       efgh|       abcd
			//       arg b        CDEF|       yzAB|       uvwx|       qrst
			// (4 32-bits)        uvwx|       qrst|       efgh|       abcd
			const __m128i unpacklo = _mm_unpacklo_epi64(digits1111, digits2222);
			// _mm_unpackhi_epi64
			//       arg a        mnop|       ijkl|       efgh|       abcd
			//       arg b        CDEF|       yzAB|       uvwx|       qrst
			// (4 32-bits)        CDEF|       yzAB|       mnop|       ijkl
			const __m128i unpackhi = _mm_unpackhi_epi64(digits1111, digits2222);

			// _mm_mul_epu32
			//       arg a        uvwx|       qrst|       efgh|       abcd
			//       arg b            |  244140625|           |  244140625 // 5**12
			// _mm_slli_epi64 imm8=12
			// (2 64-bits)        qrst000000000000|       abcd000000000000
			const __m128i digits_1000000000000 = _mm_slli_epi64(_mm_mul_epu32(unpacklo, _mm_set_epi32(0, 244140625, 0, 244140625)), 12);

			// _mm_srli_epi64 imm8=32
			//       arg a        uvwx|       qrst|       efgh|       abcd
			// _mm_mul_epu32
			//       arg b            |  100000000|           |  100000000
			// (2 64-bits)            uvwx00000000|           efgh00000000
			const __m128i digits_100000000 = _mm_mul_epu32(_mm_srli_epi64(unpacklo, 32), _mm_set_epi32(0, 100000000, 0, 100000000));

			// _mm_mul_epu32
			//       arg a        CDEF|       yzAB|       mnop|       ijkl
			//       arg b            |      10000|           |      10000
			// (2 64-bits)                yzAB0000|               ijkl0000
			const __m128i digits_10000 = _mm_mul_epu32(unpackhi, _mm_set_epi32(0, 10000, 0, 10000));

			// _mm_srli_epi64 imm8=32
			//       arg a        CDEF|       yzAB|       mnop|       ijkl
			// (2 64-bits)                    CDEF|                   mnop
			const __m128i digits_1 = _mm_srli_epi64(unpackhi, 32);

			// _mm_add_epi32
			//       arg a                    CDEF|                   mnop
			//       arg b                yzAB0000|               ijkl0000
			// _mm_add_epi32
			//       arg b            uvwx00000000|           efgh00000000
			// _mm_add_epi32
			//       arg b        qrst000000000000|       abcd000000000000
			// (2 64-bits)        qrstuvwxyzABCDEF|       abcdefghijklmnop
			const __m128i sum = _mm_add_epi64(_mm_add_epi64(_mm_add_epi64(digits_1, digits_10000), digits_100000000), digits_1000000000000);

			valhi = static_cast<unsigned long long>(_mm_cvtsi128_si64(sum));
			vallo = static_cast<unsigned long long>(_mm_cvtsi128_si64(_mm_srli_si128(sum, 8)));
		}

		fio_target("ssse3") fio_inline
		void extract_integer_40(const char * end, fio::uint64 & valhi, fio::uint32 & valmi, fio::uint64 & vallo)
		{
			extract_integer_8(end - 16, valmi);

			// todo do not duplicate all this
			const __m128i line1 = _mm_loadu_si128(reinterpret_cast<const __m128i *>(end - 40));
			const __m128i line2 = _mm_loadu_si128(reinterpret_cast<const __m128i *>(end - 16));

			const __m128i digits1 = _mm_sub_epi8(line1, _mm_set1_epi8('0'));
			const __m128i digits2 = _mm_sub_epi8(line2, _mm_set1_epi8('0'));

			// _mm_maddubs_epi16 // ssse3
			//       arg a  p| o| n| m| l| k| j| i| h| g| f| e| d| c| b| a
			//       arg b  1|10| 1|10| 1|10| 1|10| 1|10| 1|10| 1|10| 1|10
			// (8 16-bits)    op|   mn|   kl|   ij|   gh|   ef|   cd|   ab
			const __m128i digits11 = _mm_maddubs_epi16(digits1, _mm_set1_epi16(0x010a));
			// _mm_madd_epi16
			//       arg a    op|   mn|   kl|   ij|   gh|   ef|   cd|   ab
			//       arg b     1|  100|    1|  100|    1|  100|    1|  100
			// (4 32-bits)        mnop|       ijkl|       efgh|       abcd
			const __m128i digits1111 = _mm_madd_epi16(digits11, _mm_set1_epi32(0x00010064));

			// _mm_maddubs_epi16 // ssse3
			//       arg a  F| E| D| C| B| A| z| y| x| w| v| u| t| s| r| q
			//       arg b  1|10| 1|10| 1|10| 1|10| 1|10| 1|10| 1|10| 1|10
			// (8 16-bits)    EF|   CD|   AB|   yz|   wx|   uv|   st|   qr
			const __m128i digits22 = _mm_maddubs_epi16(digits2, _mm_set1_epi16(0x010a));
			// _mm_madd_epi16
			//       arg a    EF|   CD|   AB|   yz|   wx|   uv|   st|   qr
			//       arg b     1|  100|    1|  100|    1|  100|    1|  100
			// (4 32-bits)        CDEF|       yzAB|       uvwx|       qrst
			const __m128i digits2222 = _mm_madd_epi16(digits22, _mm_set1_epi32(0x00010064));

			// _mm_unpacklo_epi64
			//       arg a        mnop|       ijkl|       efgh|       abcd
			//       arg b        CDEF|       yzAB|       uvwx|       qrst
			// (4 32-bits)        uvwx|       qrst|       efgh|       abcd
			const __m128i unpacklo = _mm_unpacklo_epi64(digits1111, digits2222);
			// _mm_unpackhi_epi64
			//       arg a        mnop|       ijkl|       efgh|       abcd
			//       arg b        CDEF|       yzAB|       uvwx|       qrst
			// (4 32-bits)        CDEF|       yzAB|       mnop|       ijkl
			const __m128i unpackhi = _mm_unpackhi_epi64(digits1111, digits2222);

			// _mm_mul_epu32
			//       arg a        uvwx|       qrst|       efgh|       abcd
			//       arg b            |  244140625|           |  244140625 // 5**12
			// _mm_slli_epi64 imm8=12
			// (2 64-bits)        qrst000000000000|       abcd000000000000
			const __m128i digits_1000000000000 = _mm_slli_epi64(_mm_mul_epu32(unpacklo, _mm_set_epi32(0, 244140625, 0, 244140625)), 12);

			// _mm_srli_epi64 imm8=32
			//       arg a        uvwx|       qrst|       efgh|       abcd
			// _mm_mul_epu32
			//       arg b            |  100000000|           |  100000000
			// (2 64-bits)            uvwx00000000|           efgh00000000
			const __m128i digits_100000000 = _mm_mul_epu32(_mm_srli_epi64(unpacklo, 32), _mm_set_epi32(0, 100000000, 0, 100000000));

			// _mm_mul_epu32
			//       arg a        CDEF|       yzAB|       mnop|       ijkl
			//       arg b            |      10000|           |      10000
			// (2 64-bits)                yzAB0000|               ijkl0000
			const __m128i digits_10000 = _mm_mul_epu32(unpackhi, _mm_set_epi32(0, 10000, 0, 10000));

			// _mm_srli_epi64 imm8=32
			//       arg a        CDEF|       yzAB|       mnop|       ijkl
			// (2 64-bits)                    CDEF|                   mnop
			const __m128i digits_1 = _mm_srli_epi64(unpackhi, 32);

			// _mm_add_epi32
			//       arg a                    CDEF|                   mnop
			//       arg b                yzAB0000|               ijkl0000
			// _mm_add_epi32
			//       arg b            uvwx00000000|           efgh00000000
			// _mm_add_epi32
			//       arg b        qrst000000000000|       abcd000000000000
			// (2 64-bits)        qrstuvwxyzABCDEF|       abcdefghijklmnop
			const __m128i sum = _mm_add_epi64(_mm_add_epi64(_mm_add_epi64(digits_1, digits_10000), digits_100000000), digits_1000000000000);

			valhi = static_cast<unsigned long long>(_mm_cvtsi128_si64(sum));
			vallo = static_cast<unsigned long long>(_mm_cvtsi128_si64(_mm_srli_si128(sum, 8)));
		}

		inline
		fio::uint32 extract_integer_bits_16(const char * end)
		{
			fio::uint64 val;
			extract_integer_16(end, val);

			const unsigned int index = fio::nat::bsr64(val);

			const unsigned int mag = 127 + index - 1; // the one is added back again as the 25th bit of the mantissa

			const unsigned long long bits = (mag << 24) + (val >> (index - 24));

			const unsigned long long rounded = bits + 1; // note may overflow into exponent
			return static_cast<fio::uint32>(rounded >> 1);
		}

		inline
		fio::uint32 extract_integer_bits_32(const char * end)
		{
			fio::uint64 valx;
			fio::uint64 valy;
			extract_integer_32(end, valy, valx);

			unsigned long long yhi;
			unsigned long long ylo = fio::nat::umul128(valy, 10000000000000000, &yhi);

			unsigned long long sumlo;
			unsigned char carry = _addcarry_u64(0, ylo, valx, &sumlo);
			unsigned long long sumhi;
			carry = _addcarry_u64(carry, yhi, 0, &sumhi);

			if (sumhi != 0)
			{
				const unsigned int index = fio::nat::bsr64(sumhi);

				const unsigned int mag = 191 + index;

				const unsigned long long bits = fio::nat::ushl128(fio::nat::ushr128(sumlo, sumhi, static_cast<unsigned char>(index)), mag, 24);

				const unsigned long long rounded = bits + 1; // note may overflow into exponent
				return static_cast<fio::uint32>(rounded >> 1);
			}
			else
			{
				const unsigned int index = fio::nat::bsr64(sumlo);

				const unsigned int mag = 127 + index - 1; // the one is added back again as the 25th bit of the mantissa

				const unsigned long long bits = (mag << 24) + (sumlo >> (index - 24));

				const unsigned long long rounded = bits + 1; // note may overflow into exponent
				return static_cast<fio::uint32>(rounded >> 1);
			}
		}

		inline
		fio::uint32 extract_integer_bits_40(const char * end)
		{
			fio::uint64 valx;
			fio::uint32 valy;
			fio::uint64 valz;
			extract_integer_40(end, valz, valy, valx);

			unsigned long long zhi;
			unsigned long long zlo = fio::nat::umul128(valz, 59604644775390625, &zhi); // 5**24
			unsigned long long yhi;
			unsigned long long ylo = fio::nat::umul128(valy, 10000000000000000, &yhi);
			unsigned long long xlo = valx;

			if (zhi >= (1ull << (64 - 24)))
				return 2139095040; // overflow

			unsigned long long hihi = fio::nat::ushl128(zlo, zhi, 24);
			unsigned long long hilo = zlo << 24;
			unsigned long long mihi = yhi;
			unsigned long long milo = ylo;
			unsigned long long lolo = xlo;

			unsigned long long lo;
			unsigned char carry = _addcarry_u64(0, lolo, milo, &lo);
			unsigned long long hi;
			carry = _addcarry_u64(carry, mihi, 0, &hi);
			carry = _addcarry_u64(carry, lo, hilo, &lo); // note carry-in is guaranteed to be 0
			carry = _addcarry_u64(carry, hi, hihi, &hi);
			if (carry != 0)
				return 2139095040; // overflow

			const unsigned int index = fio::nat::bsr64(hi);

			const unsigned int mag = 191 + index - 1; // the one is added back again as the 25th bit of the mantissa

			const unsigned long long bits = (mag << 24) + (hi >> (index - 24));

			const unsigned long long rounded = bits + 1; // note may overflow into exponent
			return static_cast<fio::uint32>(rounded >> 1);
		}

		inline
		fio::uint64 extract_decimal_bits_24(const char * end)
		{
			fio::uint64 valx;
			fio::uint64 valy;
			extract_integer_32(end, valy, valx);

			// 24: yyyyyyyyxxxxxxxxxxxxxxxx // (5**24)
			// (yyyyyyyy * (10**16) + xxxxxxxxxxxxxxxx) // (5**24)
			// (yyyyyyyy * (2**16) * (5**16) + xxxxxxxxxxxxxxxx) // (5**24)
			// (yyyyyyyy * (2**16) + xxxxxxxxxxxxxxxx // (5**16)) // (5**8)
			//  |43--------------|

			const fio::uint64 x_div_16 = fio::nat::umul128hi(valx, 0x39a5652fb1137857) >> 35; // 5**16
			const fio::uint64 sum = (valy << 16) + x_div_16;
			const fio::uint64 sum_div_8 = fio::nat::umul128hi(sum, 0xabcc77118461cefd) >> 18; // 5**8
			return sum_div_8;
		}

		fio_inline
		void multiply_integer_2(fio::uint64 hi, fio::uint64 lo, const unsigned long long(&denominators)[3], unsigned long long(&results)[7])
		{
			//     x1x0
			//*    y1y0
			//----------
			//     x0y0
			//   x1y0
			//   x0y1
			// x1y1
			//----------
			//   r2r1r0
			// s2s1s0

			unsigned long long x0y0hi;
			unsigned long long x0y0lo = fio::nat::umul128(lo, denominators[0], &x0y0hi);
			unsigned long long x1y0hi;
			unsigned long long x1y0lo = fio::nat::umul128(hi, denominators[0], &x1y0hi);
			unsigned long long x0y1hi;
			unsigned long long x0y1lo = fio::nat::umul128(lo, denominators[1], &x0y1hi);
			unsigned long long x1y1hi;
			unsigned long long x1y1lo = fio::nat::umul128(hi, denominators[1], &x1y1hi);

			unsigned char carry = 0;

			unsigned long long r0 = x0y0lo;
			unsigned long long r1;
			carry = _addcarry_u64(carry, x0y0hi, x1y0lo, &r1);
			unsigned long long r2;
			carry = _addcarry_u64(carry, x1y0hi, 0, &r2);
			if (!fio_expect(carry == 0))
			{
				carry = 0;
			}

			unsigned long long s0 = x0y1lo;
			unsigned long long s1;
			carry = _addcarry_u64(carry, x0y1hi, x1y1lo, &s1);
			unsigned long long s2;
			carry = _addcarry_u64(carry, x1y1hi, 0, &s2);
			if (!fio_expect(carry == 0))
			{
				carry = 0;
			}

			results[0] = r0;
			carry = _addcarry_u64(carry, r1, s0, results + 1);
			carry = _addcarry_u64(carry, r2, s1, results + 2);
			carry = _addcarry_u64(carry, 0, s2, results + 3);
		}

		fio_inline
		void multiply_integer_3(fio::uint64 hi, fio::uint64 mi, fio::uint64 lo, const unsigned long long(&denominators)[3], unsigned long long(&results)[7])
		{
			//       x2x1x0
			//*      y2y1y0
			//--------------
			//         x0y0
			//       x1y0
			//     x2y0
			//       x0y1
			//     x1y1
			//   x2y1
			//     x0y2
			//   x1y2
			// x2y2
			//--------------
			//     r3r2r1r0
			//   s3s2s1s0
			// t3t2t1t0

			////// t3 will always be zero... right?

			unsigned long long x0y0hi;
			unsigned long long x0y0lo = fio::nat::umul128(lo, denominators[0], &x0y0hi);
			unsigned long long x1y0hi;
			unsigned long long x1y0lo = fio::nat::umul128(mi, denominators[0], &x1y0hi);
			unsigned long long x2y0hi;
			unsigned long long x2y0lo = fio::nat::umul128(hi, denominators[0], &x2y0hi);
			unsigned long long x0y1hi;
			unsigned long long x0y1lo = fio::nat::umul128(lo, denominators[1], &x0y1hi);
			unsigned long long x1y1hi;
			unsigned long long x1y1lo = fio::nat::umul128(mi, denominators[1], &x1y1hi);
			unsigned long long x2y1hi;
			unsigned long long x2y1lo = fio::nat::umul128(hi, denominators[1], &x2y1hi);
			unsigned long long x0y2hi;
			unsigned long long x0y2lo = fio::nat::umul128(lo, denominators[2], &x0y2hi);
			unsigned long long x1y2hi;
			unsigned long long x1y2lo = fio::nat::umul128(mi, denominators[2], &x1y2hi);
			unsigned long long x2y2hi;
			unsigned long long x2y2lo = fio::nat::umul128(hi, denominators[2], &x2y2hi);

			unsigned char carry = 0;

			unsigned long long r0 = x0y0lo;
			unsigned long long r1;
			carry = _addcarry_u64(carry, x0y0hi, x1y0lo, &r1);
			unsigned long long r2;
			carry = _addcarry_u64(carry, x1y0hi, x2y0lo, &r2);
			unsigned long long r3;
			carry = _addcarry_u64(carry, x2y0hi, 0, &r3);
			if (!fio_expect(carry == 0))
			{
				carry = 0;
			}

			unsigned long long s0 = x0y1lo;
			unsigned long long s1;
			carry = _addcarry_u64(carry, x0y1hi, x1y1lo, &s1);
			unsigned long long s2;
			carry = _addcarry_u64(carry, x1y1hi, x2y1lo, &s2);
			unsigned long long s3;
			carry = _addcarry_u64(carry, x2y1hi, 0, &s3);
			if (!fio_expect(carry == 0))
			{
				carry = 0;
			}

			unsigned long long t0 = x0y2lo;
			unsigned long long t1;
			carry = _addcarry_u64(carry, x0y2hi, x1y2lo, &t1);
			unsigned long long t2;
			carry = _addcarry_u64(carry, x1y2hi, x2y2lo, &t2);
			unsigned long long t3;
			carry = _addcarry_u64(carry, x2y2hi, 0, &t3);
			if (!fio_expect(carry == 0))
			{
				carry = 0;
			}

			results[0] = r0;
			carry = _addcarry_u64(carry, r1, s0, results + 1);
			carry = _addcarry_u64(carry, r2, s1, results + 2);
			carry = _addcarry_u64(carry, r3, s2, results + 3);
			carry = _addcarry_u64(carry, 0, s3, results + 4);
			// fio_assume(carry == 0); // since t3 must be zero this must hold??????????
			if (!fio_expect(carry == 0))
			{
				carry = 0;
			}
			carry = _addcarry_u64(carry, results[2], t0, results + 2);
			carry = _addcarry_u64(carry, results[3], t1, results + 3);
			carry = _addcarry_u64(carry, results[4], t2, results + 4);
			carry = _addcarry_u64(carry, 0, t3, results + 5);
		}

		inline
		fio::uint32 float_bits(const char * first, const char * dot, const char * last, fio::ssize exp)
		{
			alignas(16) char buffer[128 + 1 + 112]; // 1 + 112 extra because of dot-shifting non-integers

			const auto n_integers = dot - first + exp;
			if (n_integers > 0)
			{
				if (n_integers >= 40)
				{
					return 2139095040; // overflow
				}
				else if (n_integers > 32)
				{
					_mm_store_si128(reinterpret_cast<__m128i *>(buffer + 0), _mm_set1_epi8('0'));
					_mm_store_si128(reinterpret_cast<__m128i *>(buffer + 16), _mm_set1_epi8('0'));
					_mm_store_si128(reinterpret_cast<__m128i *>(buffer + 32), _mm_set1_epi8('0'));

					const auto may_copy_dot = dot - first > 0;

					const fio::usize size = static_cast<fio::usize>(n_integers + may_copy_dot) < static_cast<fio::usize>(last - first) ? static_cast<fio::usize>(n_integers + may_copy_dot) : static_cast<fio::usize>(last - first);
					fio::memcpy(first, buffer + (40 - n_integers), size);

					if (may_copy_dot)
					{
						const fio::usize offset = static_cast<fio::usize>(n_integers) < static_cast<fio::usize>(dot - first) ? static_cast<fio::usize>(n_integers) : static_cast<fio::usize>(dot - first);
						_mm_storeu_si128(reinterpret_cast<__m128i *>(buffer + (40 - n_integers) + offset + 0), _mm_loadu_si128(reinterpret_cast<const __m128i *>(buffer + (40 - n_integers) + offset + 0 + 1)));
						_mm_storeu_si128(reinterpret_cast<__m128i *>(buffer + (40 - n_integers) + offset + 16), _mm_loadu_si128(reinterpret_cast<const __m128i *>(buffer + (40 - n_integers) + offset + 16 + 1)));
						_mm_storeu_si128(reinterpret_cast<__m128i *>(buffer + (40 - n_integers) + offset + 32), _mm_loadu_si128(reinterpret_cast<const __m128i *>(buffer + (40 - n_integers) + offset + 32 + 1)));
					}

					return extract_integer_bits_40(buffer + 40);
				}
				else if (n_integers > 16)
				{
					_mm_store_si128(reinterpret_cast<__m128i *>(buffer + 0), _mm_set1_epi8('0'));
					_mm_store_si128(reinterpret_cast<__m128i *>(buffer + 16), _mm_set1_epi8('0'));
					_mm_store_si128(reinterpret_cast<__m128i *>(buffer + 32), _mm_set1_epi8('0'));

					const auto may_copy_dot = dot - first > 0;

					const fio::usize size = static_cast<fio::usize>(n_integers + may_copy_dot) < static_cast<fio::usize>(last - first) ? static_cast<fio::usize>(n_integers + may_copy_dot) : static_cast<fio::usize>(last - first);
					fio::memcpy(first, buffer + (40 - n_integers), size);

					if (may_copy_dot)
					{
						const fio::usize offset = static_cast<fio::usize>(n_integers) < static_cast<fio::usize>(dot - first) ? static_cast<fio::usize>(n_integers) : static_cast<fio::usize>(dot - first);
						_mm_storeu_si128(reinterpret_cast<__m128i *>(buffer + (40 - n_integers) + offset + 0), _mm_loadu_si128(reinterpret_cast<const __m128i *>(buffer + (40 - n_integers) + offset + 0 + 1)));
						_mm_storeu_si128(reinterpret_cast<__m128i *>(buffer + (40 - n_integers) + offset + 16), _mm_loadu_si128(reinterpret_cast<const __m128i *>(buffer + (40 - n_integers) + offset + 16 + 1)));
						_mm_storeu_si128(reinterpret_cast<__m128i *>(buffer + (40 - n_integers) + offset + 32), _mm_loadu_si128(reinterpret_cast<const __m128i *>(buffer + (40 - n_integers) + offset + 32 + 1)));
					}

					return extract_integer_bits_32(buffer + 40);
				}
				else if (n_integers > 8)
				{
					_mm_store_si128(reinterpret_cast<__m128i *>(buffer + 0), _mm_set1_epi8('0')); // ???
					_mm_store_si128(reinterpret_cast<__m128i *>(buffer + 16), _mm_set1_epi8('0'));
					_mm_store_si128(reinterpret_cast<__m128i *>(buffer + 32), _mm_set1_epi8('0'));

					const auto may_copy_dot = dot - first > 0;

					const fio::usize size = static_cast<fio::usize>(n_integers + may_copy_dot) < static_cast<fio::usize>(last - first) ? static_cast<fio::usize>(n_integers + may_copy_dot) : static_cast<fio::usize>(last - first);
					fio::memcpy(first, buffer + (40 - n_integers), size);

					if (may_copy_dot)
					{
						const fio::usize offset = static_cast<fio::usize>(n_integers) < static_cast<fio::usize>(dot - first) ? static_cast<fio::usize>(n_integers) : static_cast<fio::usize>(dot - first);
						_mm_storeu_si128(reinterpret_cast<__m128i *>(buffer + (40 - n_integers) + offset + 0), _mm_loadu_si128(reinterpret_cast<const __m128i *>(buffer + (40 - n_integers) + offset + 0 + 1)));
						_mm_storeu_si128(reinterpret_cast<__m128i *>(buffer + (40 - n_integers) + offset + 16), _mm_loadu_si128(reinterpret_cast<const __m128i *>(buffer + (40 - n_integers) + offset + 16 + 1)));
						_mm_storeu_si128(reinterpret_cast<__m128i *>(buffer + (40 - n_integers) + offset + 32), _mm_loadu_si128(reinterpret_cast<const __m128i *>(buffer + (40 - n_integers) + offset + 32 + 1))); // ???
					}

					return extract_integer_bits_16(buffer + 40);
				}
				else
				{
					_mm_store_si128(reinterpret_cast<__m128i *>(buffer + 0), _mm_set1_epi8('0')); // ???
					_mm_store_si128(reinterpret_cast<__m128i *>(buffer + 16), _mm_set1_epi8('0')); // ???
					_mm_store_si128(reinterpret_cast<__m128i *>(buffer + 32), _mm_set1_epi8('0'));
					_mm_store_si128(reinterpret_cast<__m128i *>(buffer + 48), _mm_set1_epi8('0'));
					_mm_store_si128(reinterpret_cast<__m128i *>(buffer + 64), _mm_set1_epi8('0'));
					buffer[64] = '0';

					const auto may_copy_dot = dot - first > 0;

					// we need at most 25 digits (the case when the integer part is one bit, i.e. the number 1)
					const fio::usize size = static_cast<fio::usize>(25 + may_copy_dot) < static_cast<fio::usize>(last - first) ? static_cast<fio::usize>(25 + may_copy_dot) : static_cast<fio::usize>(last - first);
					fio::memcpy(first, buffer + (40 - n_integers), size);

					if (may_copy_dot)
					{
						const fio::usize offset = static_cast<fio::usize>(25) < static_cast<fio::usize>(dot - first) ? static_cast<fio::usize>(25) : static_cast<fio::usize>(dot - first);
						_mm_storeu_si128(reinterpret_cast<__m128i *>(buffer + (40 - n_integers) + offset + 0), _mm_loadu_si128(reinterpret_cast<const __m128i *>(buffer + (40 - n_integers) + offset + 0 + 1)));
						_mm_storeu_si128(reinterpret_cast<__m128i *>(buffer + (40 - n_integers) + offset + 16), _mm_loadu_si128(reinterpret_cast<const __m128i *>(buffer + (40 - n_integers) + offset + 16 + 1)));
						_mm_storeu_si128(reinterpret_cast<__m128i *>(buffer + (40 - n_integers) + offset + 32), _mm_loadu_si128(reinterpret_cast<const __m128i *>(buffer + (40 - n_integers) + offset + 32 + 1)));
					}

					fio::uint32 intval;
					extract_integer_8(buffer + 40, intval);

					fio::uint64 bits = intval;

					const unsigned int index = fio::nat::bsr64(bits);

					const unsigned int mag = 127 + index - 1; // the one is added back again as the 25th bit of the mantissa

					const int more = 24 - static_cast<int>(index);
					if (more > 0)
					{
						_mm_storeu_si128(reinterpret_cast<__m128i *>(buffer + 40 - 16), _mm_set1_epi8('0')); // todo necessary to zero (at least 8 digits) since the decimal is actually read as 32 digits

						const fio::uint64 more_bits = extract_decimal_bits_24(buffer + 64);

						bits = (mag << 24) + ((bits << more) | (more_bits >> index));

						const unsigned long long rounded = bits + 1; // note may overflow into exponent
						return static_cast<unsigned int>(rounded >> 1);
					}
					else
					{
						bits = (mag << 24) + (bits >> (index - 24));

						const unsigned long long rounded = bits + 1; // note may overflow into exponent
						return static_cast<unsigned int>(rounded >> 1);
					}
				}
			}
			else
			{
				const auto n_zeroes = -n_integers - (dot < first);
				if (n_zeroes < 46)
				{
					_mm_store_si128(reinterpret_cast<__m128i *>(buffer + 0), _mm_set1_epi8('0'));
					_mm_store_si128(reinterpret_cast<__m128i *>(buffer + 16), _mm_set1_epi8('0'));
					_mm_store_si128(reinterpret_cast<__m128i *>(buffer + 32), _mm_set1_epi8('0'));
					_mm_store_si128(reinterpret_cast<__m128i *>(buffer + 48), _mm_set1_epi8('0'));
					_mm_store_si128(reinterpret_cast<__m128i *>(buffer + 64), _mm_set1_epi8('0'));
					_mm_store_si128(reinterpret_cast<__m128i *>(buffer + 80), _mm_set1_epi8('0'));
					_mm_store_si128(reinterpret_cast<__m128i *>(buffer + 96), _mm_set1_epi8('0'));
					_mm_store_si128(reinterpret_cast<__m128i *>(buffer + 112), _mm_set1_epi8('0'));
					buffer[128] = '0'; // needed because of dot-shifting

					static const fio::uint8 required_digits[46] = {
						28, 30, 32, 35, 37, 39, 42, 44, 46, 49, 51, 53, 56, 58, 60, 63, 65, 67, 70, 72, 74, 77, 79, 81, 84, 86, 88, 91, 93, 95, 97, 100, 102, 104, 107, 109, 111, 113, 112, 111, 110, 109, 108, 107, 106, 105,
					};

					const auto may_copy_dot = dot - first > 0;

					const fio::usize size = static_cast<fio::usize>(required_digits[n_zeroes] + may_copy_dot) < static_cast<fio::usize>(last - first) ? static_cast<fio::usize>(required_digits[n_zeroes] + may_copy_dot) : static_cast<fio::usize>(last - first);
					fio::memcpy(first, buffer + (128 - required_digits[n_zeroes]), size);

					if (may_copy_dot)
					{
						const fio::usize offset = static_cast<fio::usize>(required_digits[n_zeroes]) < static_cast<fio::usize>(dot - first) ? static_cast<fio::usize>(required_digits[n_zeroes]) : static_cast<fio::usize>(dot - first);
						if (!fio_expect((128 - required_digits[n_zeroes]) + offset + 0 >= 16))
							return 0; // panic
						if (!fio_expect((128 - required_digits[n_zeroes]) + offset + 96 + 1 < sizeof buffer - 16))
							return 0; // panic

						_mm_storeu_si128(reinterpret_cast<__m128i *>(buffer + (128 - required_digits[n_zeroes]) + offset + 0), _mm_loadu_si128(reinterpret_cast<const __m128i *>(buffer + (128 - required_digits[n_zeroes]) + offset + 0 + 1)));
						_mm_storeu_si128(reinterpret_cast<__m128i *>(buffer + (128 - required_digits[n_zeroes]) + offset + 16), _mm_loadu_si128(reinterpret_cast<const __m128i *>(buffer + (128 - required_digits[n_zeroes]) + offset + 16 + 1)));
						_mm_storeu_si128(reinterpret_cast<__m128i *>(buffer + (128 - required_digits[n_zeroes]) + offset + 32), _mm_loadu_si128(reinterpret_cast<const __m128i *>(buffer + (128 - required_digits[n_zeroes]) + offset + 32 + 1)));
						_mm_storeu_si128(reinterpret_cast<__m128i *>(buffer + (128 - required_digits[n_zeroes]) + offset + 48), _mm_loadu_si128(reinterpret_cast<const __m128i *>(buffer + (128 - required_digits[n_zeroes]) + offset + 48 + 1)));
						_mm_storeu_si128(reinterpret_cast<__m128i *>(buffer + (128 - required_digits[n_zeroes]) + offset + 64), _mm_loadu_si128(reinterpret_cast<const __m128i *>(buffer + (128 - required_digits[n_zeroes]) + offset + 64 + 1)));
						_mm_storeu_si128(reinterpret_cast<__m128i *>(buffer + (128 - required_digits[n_zeroes]) + offset + 96), _mm_loadu_si128(reinterpret_cast<const __m128i *>(buffer + (128 - required_digits[n_zeroes]) + offset + 96 + 1)));
					}

					fio::uint64 valg;
					fio::uint64 valf;
					fio::uint64 vale;
					fio::uint64 vald;
					fio::uint64 valc;
					fio::uint64 valb;
					fio::uint64 vala;
					fio::uint64 valz; // at most 9
					extract_integer_32(buffer + 32, valz, vala);
					extract_integer_32(buffer + 64, valb, valc);
					extract_integer_32(buffer + 96, vald, vale);
					extract_integer_32(buffer + 128, valf, valg);

					static const unsigned long long denominators[46][8][3] = {
						{ {16225927682921337, 0, 0}, {39614081257132169, 0, 0}, {1}, {1}, {1}, {1}, {1}, {1}, },
						{ {16225927682921337, 0, 0}, {5192296858534827629, 0, 0}, {1}, {1}, {1}, {1}, {1}, {1}, },
						{ {16225927682921337, 0, 0}, {16481947188333068751u, 36, 0}, {1}, {1}, {1}, {1}, {1}, {1}, },
						{ {16225927682921337, 0, 0}, {7591182125049451957, 14, 0}, {1152921504607, 0, 0}, {1}, {1}, {1}, {1}, {1}, },
						{ {16225927682921337, 0, 0}, {7591182125049451957, 14, 0}, {604462909807315, 0, 0}, {1}, {1}, {1}, {1}, {1}, },
						{ {16225927682921337, 0, 0}, {7591182125049451957, 14, 0}, {39614081257132169, 0, 0}, {1}, {1}, {1}, {1}, {1}, },
						{ {16225927682921337, 0, 0}, {7591182125049451957, 14, 0}, {14783955820913345207u, 1, 0}, {1}, {1}, {1}, {1}, {1}, },
						{ {16225927682921337, 0, 0}, {7591182125049451957, 14, 0}, {545673798139537739, 59, 0}, {1}, {1}, {1}, {1}, {1}, },
						{ {16225927682921337, 0, 0}, {7591182125049451957, 14, 0}, {9241489220749011347u, 30948, 0}, {1}, {1}, {1}, {1}, {1}, },
						{ {16225927682921337, 0, 0}, {7591182125049451957, 14, 0}, {5979391860423864507, 236118, 0}, {1934281311383407, 0, 0}, {1}, {1}, {1}, {1}, },
						{ {16225927682921337, 0, 0}, {7591182125049451957, 14, 0}, {5979391860423864507, 236118, 0}, {253530120045645881, 0, 0}, {1}, {1}, {1}, {1}, },
						{ {16225927682921337, 0, 0}, {7591182125049451957, 14, 0}, {5979391860423864507, 236118, 0}, {14783955820913345207u, 1, 0}, {1}, {1}, {1}, {1}, },
						{ {16225927682921337, 0, 0}, {7591182125049451957, 14, 0}, {5979391860423864507, 236118, 0}, {16503551413014162057u, 188, 0}, {1}, {1}, {1}, {1}, },
						{ {16225927682921337, 0, 0}, {7591182125049451957, 14, 0}, {5979391860423864507, 236118, 0}, {7494647606406928093, 198070, 0}, {1}, {1}, {1}, {1}, },
						{ {16225927682921337, 0, 0}, {7591182125049451957, 14, 0}, {5979391860423864507, 236118, 0}, {2699442461655512651, 12980742, 0}, {1}, {1}, {1}, {1}, },
						{ {16225927682921337, 0, 0}, {7591182125049451957, 14, 0}, {5979391860423864507, 236118, 0}, {8670538443036954087, 10889035741, 0}, {1}, {1}, {1}, {1}, },
						{ {16225927682921337, 0, 0}, {7591182125049451957, 14, 0}, {5979391860423864507, 236118, 0}, {9843675500044451025u, 7737125245, 0}, {9762294514781471889u, 11, 0}, {1}, {1}, {1}, },
						{ {16225927682921337, 0, 0}, {7591182125049451957, 14, 0}, {5979391860423864507, 236118, 0}, {9843675500044451025u, 7737125245, 0}, {16503551413014162057u, 188, 0}, {1}, {1}, {1}, },
						{ {16225927682921337, 0, 0}, {7591182125049451957, 14, 0}, {5979391860423864507, 236118, 0}, {9843675500044451025u, 7737125245, 0}, {5536128266792618279, 633825, 0}, {1}, {1}, {1}, },
						{ {16225927682921337, 0, 0}, {7591182125049451957, 14, 0}, {5979391860423864507, 236118, 0}, {9843675500044451025u, 7737125245, 0}, {8727421805997189671, 166153499, 0}, {1}, {1}, {1}, },
						{ {16225927682921337, 0, 0}, {7591182125049451957, 14, 0}, {5979391860423864507, 236118, 0}, {9843675500044451025u, 7737125245, 0}, {8670538443036954087, 10889035741, 0}, {1}, {1}, {1}, },
						{ {16225927682921337, 0, 0}, {7591182125049451957, 14, 0}, {5979391860423864507, 236118, 0}, {9843675500044451025u, 7737125245, 0}, {2642288987520351985, 9134385233318, 0}, {1}, {1}, {1}, },
						{ {16225927682921337, 0, 0}, {7591182125049451957, 14, 0}, {5979391860423864507, 236118, 0}, {9843675500044451025u, 7737125245, 0}, {15408495767769702249u, 598631070650737, 0}, {1}, {1}, {1}, },
						{ {16225927682921337, 0, 0}, {7591182125049451957, 14, 0}, {5979391860423864507, 236118, 0}, {9843675500044451025u, 7737125245, 0}, {1564089289045153947, 4056481920730334, 0}, {5536128266792618279, 633825, 0}, {1}, {1}, },
						{ {16225927682921337, 0, 0}, {7591182125049451957, 14, 0}, {5979391860423864507, 236118, 0}, {9843675500044451025u, 7737125245, 0}, {1564089289045153947, 4056481920730334, 0}, {2895828445369772503, 265845599, 0}, {1}, {1}, },
						{ {16225927682921337, 0, 0}, {7591182125049451957, 14, 0}, {5979391860423864507, 236118, 0}, {9843675500044451025u, 7737125245, 0}, {1564089289045153947, 4056481920730334, 0}, {7529911443791671953, 69689828745, 0}, {1}, {1}, },
						{ {16225927682921337, 0, 0}, {7591182125049451957, 14, 0}, {5979391860423864507, 236118, 0}, {9843675500044451025u, 7737125245, 0}, {1564089289045153947, 4056481920730334, 0}, {1321144493760175993, 4567192616659, 0}, {1}, {1}, },
						{ {16225927682921337, 0, 0}, {7591182125049451957, 14, 0}, {5979391860423864507, 236118, 0}, {9843675500044451025u, 7737125245, 0}, {1564089289045153947, 4056481920730334, 0}, {2691303730436425989, 3831238852164722, 0}, {1}, {1}, },
						{ {16225927682921337, 0, 0}, {7591182125049451957, 14, 0}, {5979391860423864507, 236118, 0}, {9843675500044451025u, 7737125245, 0}, {1564089289045153947, 4056481920730334, 0}, {1971277250102393653, 502168138830934461, 0}, {1}, {1}, },
						{ {16225927682921337, 0, 0}, {7591182125049451957, 14, 0}, {5979391860423864507, 236118, 0}, {9843675500044451025u, 7737125245, 0}, {1564089289045153947, 4056481920730334, 0}, {10140024425764638827u, 16455045573212060421u, 0}, {1}, {1}, },
						{ {16225927682921337, 0, 0}, {7591182125049451957, 14, 0}, {5979391860423864507, 236118, 0}, {9843675500044451025u, 7737125245, 0}, {1564089289045153947, 4056481920730334, 0}, {3511393333235066575, 11121167568117138797u, 3}, {12988327758750611785u, 34844914372, 0}, {1}, },
						{ {16225927682921337, 0, 0}, {7591182125049451957, 14, 0}, {5979391860423864507, 236118, 0}, {9843675500044451025u, 7737125245, 0}, {1564089289045153947, 4056481920730334, 0}, {3511393333235066575, 11121167568117138797u, 3}, {1076627130581305705, 29230032746618, 0}, {1}, },
						{ {16225927682921337, 0, 0}, {7591182125049451957, 14, 0}, {5979391860423864507, 236118, 0}, {9843675500044451025u, 7737125245, 0}, {1564089289045153947, 4056481920730334, 0}, {3511393333235066575, 11121167568117138797u, 3}, {2691303730436425989, 3831238852164722, 0}, {1}, },
						{ {16225927682921337, 0, 0}, {7591182125049451957, 14, 0}, {5979391860423864507, 236118, 0}, {9843675500044451025u, 7737125245, 0}, {1564089289045153947, 4056481920730334, 0}, {3511393333235066575, 11121167568117138797u, 3}, {1971277250102393653, 502168138830934461, 0}, {1}, },
						{ {16225927682921337, 0, 0}, {7591182125049451957, 14, 0}, {5979391860423864507, 236118, 0}, {9843675500044451025u, 7737125245, 0}, {1564089289045153947, 4056481920730334, 0}, {3511393333235066575, 11121167568117138797u, 3}, {15422499392788156965u, 7710398526309305619, 11}, {1}, },
						{ {16225927682921337, 0, 0}, {7591182125049451957, 14, 0}, {5979391860423864507, 236118, 0}, {9843675500044451025u, 7737125245, 0}, {1564089289045153947, 4056481920730334, 0}, {3511393333235066575, 11121167568117138797u, 3}, {865119391821669287, 2865761711822312790, 2993}, {1}, },
						{ {16225927682921337, 0, 0}, {7591182125049451957, 14, 0}, {5979391860423864507, 236118, 0}, {9843675500044451025u, 7737125245, 0}, {1564089289045153947, 4056481920730334, 0}, {3511393333235066575, 11121167568117138797u, 3}, {5193155008627850229, 7917911339171543649, 196159}, {1}, },
						{ {16225927682921337, 0, 0}, {7591182125049451957, 14, 0}, {5979391860423864507, 236118, 0}, {9843675500044451025u, 7737125245, 0}, {1564089289045153947, 4056481920730334, 0}, {3511393333235066575, 11121167568117138797u, 3}, {16611413540376147735u, 5470823367985906411, 944473}, {2691303730436425989, 3831238852164722, 0}, },
						{ {16225927682921337, 0, 0}, {7591182125049451957, 14, 0}, {5979391860423864507, 236118, 0}, {9843675500044451025u, 7737125245, 0}, {1564089289045153947, 4056481920730334, 0}, {3511393333235066575, 11121167568117138797u, 3}, {1496253268323035203, 408217133286861182, 803469}, {1}, },
						{ {16225927682921337, 0, 0}, {7591182125049451957, 14, 0}, {5979391860423864507, 236118, 0}, {9843675500044451025u, 7737125245, 0}, {1564089289045153947, 4056481920730334, 0}, {3511393333235066575, 11121167568117138797u, 3}, {9597435353935534609u, 4713740301749103199, 200867}, {1}, },
						{ {16225927682921337, 0, 0}, {7591182125049451957, 14, 0}, {5979391860423864507, 236118, 0}, {9843675500044451025u, 7737125245, 0}, {1564089289045153947, 4056481920730334, 0}, {3511393333235066575, 11121167568117138797u, 3}, {17340580483737799491u, 7506746565359719755, 25108}, {1}, },
						{ {16225927682921337, 0, 0}, {7591182125049451957, 14, 0}, {5979391860423864507, 236118, 0}, {9843675500044451025u, 7737125245, 0}, {1564089289045153947, 4056481920730334, 0}, {3511393333235066575, 11121167568117138797u, 3}, {9085101588108306793u, 10161715357524740777u, 3138}, {1}, },
						{ {16225927682921337, 0, 0}, {7591182125049451957, 14, 0}, {5979391860423864507, 236118, 0}, {9843675500044451025u, 7737125245, 0}, {1564089289045153947, 4056481920730334, 0}, {3511393333235066575, 11121167568117138797u, 3}, {10944112390718391959u, 2940950219058990250, 196}, {1}, },
						{ {16225927682921337, 0, 0}, {7591182125049451957, 14, 0}, {5979391860423864507, 236118, 0}, {9843675500044451025u, 7737125245, 0}, {1564089289045153947, 4056481920730334, 0}, {3511393333235066575, 11121167568117138797u, 3}, {5979700067267186899, 9590990814237149589u, 24}, {1}, },
						{ {16225927682921337, 0, 0}, {7591182125049451957, 14, 0}, {5979391860423864507, 236118, 0}, {9843675500044451025u, 7737125245, 0}, {1564089289045153947, 4056481920730334, 0}, {3511393333235066575, 11121167568117138797u, 3}, {12276677554476868123u, 1198873851779643698, 3}, {1}, },
						{ {16225927682921337, 0, 0}, {7591182125049451957, 14, 0}, {5979391860423864507, 236118, 0}, {9843675500044451025u, 7737125245, 0}, {1564089289045153947, 4056481920730334, 0}, {3511393333235066575, 11121167568117138797u, 3}, {10759939715039024913u, 1766847064778384329, 0}, {1}, },
					};

					static const unsigned char skips[46][8][2] = {
						{ {1, 27}, {1, 19}, },
						{ {1, 27}, {1, 33}, },
						{ {1, 27}, {1, 47}, },
						{ {1, 27}, {1, 41}, {0, 54},  },
						{ {1, 27}, {1, 41}, {1, 6}, },
						{ {1, 27}, {1, 41}, {1, 19}, },
						{ {1, 27}, {1, 41}, {1, 38}, },
						{ {1, 27}, {1, 41}, {1, 50}, },
						{ {1, 27}, {1, 41}, {2, 2}, },
						{ {1, 27}, {1, 41}, {1, 55}, {1, 10}, },
						{ {1, 27}, {1, 41}, {1, 55}, {1, 24}, },
						{ {1, 27}, {1, 41}, {1, 55}, {1, 38}, },
						{ {1, 27}, {1, 41}, {1, 55}, {1, 54}, },
						{ {1, 27}, {1, 41}, {1, 55}, {2, 7}, },
						{ {1, 27}, {1, 41}, {1, 55}, {2, 20}, },
						{ {1, 27}, {1, 41}, {1, 55}, {2, 39}, },
						{ {1, 27}, {1, 41}, {1, 55}, {2, 6}, {1, 43}, },
						{ {1, 27}, {1, 41}, {1, 55}, {2, 6}, {1, 54}, },
						{ {1, 27}, {1, 41}, {1, 55}, {2, 6}, {2, 11}, },
						{ {1, 27}, {1, 41}, {1, 55}, {2, 6}, {2, 26}, },
						{ {1, 27}, {1, 41}, {1, 55}, {2, 6}, {2, 39}, },
						{ {1, 27}, {1, 41}, {1, 55}, {2, 6}, {2, 58}, },
						{ {1, 27}, {1, 41}, {1, 55}, {2, 6}, {3, 7}, },
						{ {1, 27}, {1, 41}, {1, 55}, {2, 6}, {2, 25}, {2, 11}, },
						{ {1, 27}, {1, 41}, {1, 55}, {2, 6}, {2, 25}, {2, 29}, },
						{ {1, 27}, {1, 41}, {1, 55}, {2, 6}, {2, 25}, {2, 44}, },
						{ {1, 27}, {1, 41}, {1, 55}, {2, 6}, {2, 25}, {2, 57}, },
						{ {1, 27}, {1, 41}, {1, 55}, {2, 6}, {2, 25}, {3, 12}, },
						{ {1, 27}, {1, 41}, {1, 55}, {2, 6}, {2, 25}, {3, 26}, },
						{ {1, 27}, {1, 41}, {1, 55}, {2, 6}, {2, 25}, {3, 38}, },
						{ {1, 27}, {1, 41}, {1, 55}, {2, 6}, {2, 25}, {2, 39}, {2, 43}, },
						{ {1, 27}, {1, 41}, {1, 55}, {2, 6}, {2, 25}, {2, 39}, {2, 62}, },
						{ {1, 27}, {1, 41}, {1, 55}, {2, 6}, {2, 25}, {2, 39}, {3, 12}, },
						{ {1, 27}, {1, 41}, {1, 55}, {2, 6}, {2, 25}, {2, 39}, {3, 26}, },
						{ {1, 27}, {1, 41}, {1, 55}, {2, 6}, {2, 25}, {2, 39}, {3, 44}, },
						{ {1, 27}, {1, 41}, {1, 55}, {2, 6}, {2, 25}, {2, 39}, {3, 59}, },
						{ {1, 27}, {1, 41}, {1, 55}, {2, 6}, {2, 25}, {2, 39}, {4, 8}, },
						{ {1, 27}, {1, 41}, {1, 55}, {2, 6}, {2, 25}, {2, 39}, {2, 57}, {3, 12} },
						{ {1, 27}, {1, 41}, {1, 55}, {2, 6}, {2, 25}, {2, 39}, {4, 17}, },
						{ {1, 27}, {1, 41}, {1, 55}, {2, 6}, {2, 25}, {2, 39}, {4, 15}, },
						{ {1, 27}, {1, 41}, {1, 55}, {2, 6}, {2, 25}, {2, 39}, {4, 12}, },
						{ {1, 27}, {1, 41}, {1, 55}, {2, 6}, {2, 25}, {2, 39}, {4, 9}, },
						{ {1, 27}, {1, 41}, {1, 55}, {2, 6}, {2, 25}, {2, 39}, {4, 5}, },
						{ {1, 27}, {1, 41}, {1, 55}, {2, 6}, {2, 25}, {2, 39}, {4, 2}, },
						{ {1, 27}, {1, 41}, {1, 55}, {2, 6}, {2, 25}, {2, 39}, {3, 63}, },
						{ {1, 27}, {1, 41}, {1, 55}, {2, 6}, {2, 25}, {2, 39}, {3, 58}, },
					};

					// (z * (10**112) + aaaaaaaaaaaaaaaa * (10**96) + bbbbbbbbbbbbbbbb * (10**80) + cccccccccccccccc * (10**64) + dddddddddddddddd * (10**48) + eeeeeeeeeeeeeeee * (10**32) + ffffffffffffffff * (10**16) + ggggggggggggggg) // (5**150)
					// (z * (2**112) + (aaaaaaaaaaaaaaaa * (2**96) + (bbbbbbbbbbbbbbbb * (2**80) + (cccccccccccccccc * (2**64) + (dddddddddddddddd * (2**48) + (eeeeeeeeeeeeeeee * (2**32) + (ffffffffffffffff * (2**16) + (ggggggggggggggg) // (5**16)) // (5**16)) // (5**16)) // (5**16)) // (5**16)) // (5**16)) // (5**16)) // (5**38)
					//                                                                                                                                                                        |70----------------------|   |16 all ones---------------|
					//                                                                                                                                          |86----------------------|   |32 all ones---------------------------------------------------------|
					//                                                                                                            |102---------------------|   |48 all ones--------
					//                                                                              |118---------------------|   |64 all ones--------
					//                                                |134---------------------|   |80 all ones --------
					//                  |150---------------------|   |96 all ones--------
					//  |116-------|   |112 all ones--------

					// needed to increase tmps[6] because shifting may access tmps[4+2]
					unsigned long long tmps[7] = {}; // actually important to zero tmps[3], see 0b0'00110101'00000000000000000000000

					unsigned long long g0 = fio::nat::umul128hi(valg, 16225927682921337) >> 27; // divide by 5**16

					multiply_integer_2(fio::nat::ushl128(valf, 0, 16), (valf << 16) + g0, denominators[n_zeroes][1], tmps);
					unsigned long long f0 = fio::nat::ushr128(tmps[1], tmps[1 + 1], skips[n_zeroes][1][1]);
					if (!fio_expect(tmps[1 + 2] == 0))
						return static_cast<unsigned int>(-1);

					multiply_integer_2(fio::nat::ushl128(vale, 0, 32), (vale << 32) + f0, denominators[n_zeroes][2], tmps);
					unsigned long long e0 = fio::nat::ushr128(tmps[skips[n_zeroes][2][0]], tmps[skips[n_zeroes][2][0] + 1], skips[n_zeroes][2][1]);
					if (!fio_expect(tmps[skips[n_zeroes][2][0] + 2] == 0))
						return static_cast<unsigned int>(-1);

					multiply_integer_2(fio::nat::ushl128(vald, 0, 48), (vald << 48) + e0, denominators[n_zeroes][3], tmps);
					unsigned long long d0 = fio::nat::ushr128(tmps[skips[n_zeroes][3][0]], tmps[skips[n_zeroes][3][0] + 1], skips[n_zeroes][3][1]);
					if (!fio_expect(tmps[skips[n_zeroes][3][0] + 2] == 0))
						return static_cast<unsigned int>(-1);

					multiply_integer_2(valc, d0, denominators[n_zeroes][4], tmps);
					unsigned long long c0 = fio::nat::ushr128(tmps[skips[n_zeroes][4][0]], tmps[skips[n_zeroes][4][0] + 1], skips[n_zeroes][4][1]);
					unsigned long long c1 = tmps[skips[n_zeroes][4][0] + 1] >> skips[n_zeroes][4][1];
					if (!fio_expect(tmps[skips[n_zeroes][4][0] + 2] == 0))
						return static_cast<unsigned int>(-1);

					multiply_integer_3(fio::nat::ushl128(valb, 0, 16), (valb << 16) + c1, c0, denominators[n_zeroes][5], tmps);
					unsigned long long b0 = fio::nat::ushr128(tmps[skips[n_zeroes][5][0]], tmps[skips[n_zeroes][5][0] + 1], skips[n_zeroes][5][1]);
					unsigned long long b1 = fio::nat::ushr128(tmps[skips[n_zeroes][5][0] + 1], tmps[skips[n_zeroes][5][0] + 2], skips[n_zeroes][5][1]);

					multiply_integer_3(fio::nat::ushl128(vala, 0, 32), (vala << 32) + b1, b0, denominators[n_zeroes][6], tmps);
					unsigned long long a0 = fio::nat::ushr128(tmps[skips[n_zeroes][6][0]], tmps[skips[n_zeroes][6][0] + 1], skips[n_zeroes][6][1]);
					unsigned long long a1 = fio::nat::ushr128(tmps[skips[n_zeroes][6][0] + 1], tmps[skips[n_zeroes][6][0] + 2], skips[n_zeroes][6][1]);

					tmps[4] = 0;
					tmps[5] = 0;

					multiply_integer_2((valz << 48) + a1, a0, denominators[n_zeroes][7], tmps);
					unsigned long long z0 = fio::nat::ushr128(tmps[skips[n_zeroes][7][0]], tmps[skips[n_zeroes][7][0] + 1], skips[n_zeroes][7][1]);

					unsigned long long bits = z0;

					if (bits == 0) // underflow
						return 0;

					const unsigned int index = fio::nat::bsr64(bits);

					if (index >= 24)
					{
						const unsigned int mag_base = 150 - (static_cast<unsigned int>(n_zeroes) + required_digits[n_zeroes]);
						const unsigned int mag = mag_base + (index - 24);

						bits = (mag << 24) + (bits >> (index - 24));

						const unsigned long long rounded = bits + 1; // note may overflow into exponent
						return static_cast<unsigned int>(rounded >> 1);
					}
					else // probably subnormal (but could overflow to become normal)
					{
						const fio::uint64 rounded = bits + 1;
						return static_cast<unsigned int>(rounded >> 1);
					}
				}
				else // underflow
				{
					return 0;
				}
			}
		}

		fio_inline
		const char * read_exponent(const char * beg, const char * end, fio::ssize & value)
		{
			// note the exponent is limited to 16 digits because that is
			// already a very generous limit

			fio::ssize nsize = beg - end;
			if (nsize < 0)
			{
				fio::usize val = static_cast<unsigned int>(*(end + nsize) - '0');
				if (val > 9)
					return nullptr; // error no digits

				nsize++;
				if (nsize < 0)
				{
					do
					{
						const fio::usize digit = static_cast<unsigned int>(*(end + nsize) - '0');
						if (digit > 9)
							break;

						val = val * 10 + digit;

						nsize++;
					}
					while (nsize < 0);

					if (end + nsize > beg + 16)
						return nullptr; // error too many digits
				}

				value = static_cast<fio::ssize>(val);

				return end + nsize;
			}
			else
			{
				return nullptr; // error no digits
			}
		}

		fio_inline
		const char * float_parse(const char * begin, const char * end, const char *& first, const char *& dot, const char *& last, fio::ssize & exp)
		{
			bool have_digits = false;

			// todo vectorize this mess

			// skip zeroes
			if (*begin == '0')
			{
				have_digits = true;

				do
				{
					begin++;

					if (begin == end)
					{
						goto zero;
					}
				}
				while (*begin == '0');
			}

			if (*begin == '.')
			{
				dot = begin;

				begin++;

				if (begin == end)
				{
					if (have_digits)
					{
						goto zero;
					}
				}

				if (*begin == '0')
				{
					// skip more zeroes
					do
					{
						begin++;

						if (begin == end)
						{
							goto zero;
						}
					}
					while (*begin == '0');
				}

				first = begin;
				exp = 0;

				if (*begin >= '0' && *begin <= '9')
				{
					// skip to end
					do
					{
						begin++;

						if (begin == end)
						{
							last = begin;

							return begin;
						}
					}
					while (*begin >= '0' && *begin <= '9');
				}

				last = begin;
			}
			else if (*begin >= '0' && *begin <= '9')
			{
				first = begin;
				exp = 0;

				// todo change to skip digits
				do
				{
					begin++;

					if (begin == end)
					{
						dot = begin;
						last = begin;

						return begin;
					}
				}
				while (*begin >= '0' && *begin <= '9');

				dot = begin;

				if (*begin == '.')
				{
					// skip to end
					do
					{
						begin++;

						if (begin == end)
						{
							last = begin;

							return begin;
						}
					}
					while (*begin >= '0' && *begin <= '9');
				}

				last = begin;
			}
			else if (have_digits) // but they are all zeroes
			{
				first = begin;
				dot = begin;
				last = begin;
			}
			else
			{
				return nullptr; // error no digits
			}

			if (*begin == 'E' || *begin == 'e')
			{
				begin++;
				if (begin == end)
					return nullptr; // error bad exponent

				const bool is_negative = *begin == '-';
				if (is_negative || *begin == '+')
				{
					begin++;
				}

				begin = read_exponent(begin, end, exp);
				if (begin == nullptr)
					return nullptr; // error bad exponent

				if (is_negative)
				{
					exp = -exp;
				}
			}

			if (first == last)
			{
			zero:
				first = nullptr;
				dot = nullptr;
				last = nullptr; // actually unnecessary
				exp = -64; // arbitrary large and negative to bypass the division algorithm (at least -46)
			}

			return begin;
		}
	}

	fio_inline
	const char * from_chars(const char * begin, const char * end, float & value)
	{
		if (begin == end)
			return nullptr; // error

		const bool is_negative = *begin == '-';
		if (is_negative)
		{
			begin++;

			if (begin == end)
				return nullptr; // error
		}

		// 0 = zero   x = non-zero   z = maybe zero   . = dot   : = maybe dot
		//
		//    first            first   last         dot      last
		//    v                v       v            v        v
		// 000xz:           000xz.zzzzz           00.000xzzzz
		//      ^                ^                      ^
		//      dot=last         dot                    first

		const char * first;
		const char * dot;
		const char * last;
		fio::ssize exp;
		end = detail::float_parse(begin, end, first, dot, last, exp);

		if (end != nullptr)
		{
			fio::uint32 bits = detail::float_bits(first, dot, last, exp);
			if (is_negative)
			{
				bits |= 0b1'00000000'00000000000000000000000;
			}

			value = fio::bit_cast<float>(bits);
		}

		return end;
	}
}

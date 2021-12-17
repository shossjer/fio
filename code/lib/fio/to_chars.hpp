#pragma once

#include "fio/compiler.hpp"
#include "fio/stdint.hpp"

#if defined(_MSC_VER)
# include <intrin.h>
#elif defined(__GNUC__)
# if defined(_M_X64) || defined(_M_AMD64) || defined(__x86_64__) || (defined(_MSC_VER) && defined(_M_IX86)) || defined(__i386__)
#  include <x86intrin.h>
# endif
#endif

namespace fio
{
#if defined(_M_X64) || defined(_M_AMD64)
	fio_inline unsigned long long mulhi(unsigned long long a, unsigned long long b)
	{
		return __umulh(a, b);
	}
#elif __SIZEOF_INT128__ == 16
	fio_inline unsigned long long mulhi(unsigned long long a, unsigned long long b)
	{
		// apparently this is the best way to get the high part :shrug: kind
		// of silly not to have an intrinsic for it
		//
		// https://stackoverflow.com/a/50958815
		const unsigned __int128 prod = a * static_cast<unsigned __int128>(b);
		return prod >> 64;
	}
#endif
}

namespace fio
{
	namespace detail
	{
		fio_target("ssse3") fio_inline void integer_digits(__m128i y4321x4321, __m128i & digit1, __m128i & digit10, __m128i & digit100, __m128i & digit1000)
		{
			const __m128i div10w = _mm_set1_epi16(0x199a);
			const __m128i div100w = _mm_set1_epi16(0x147b);
			const __m128i div1000w = _mm_set1_epi16(0x20c5);
			const __m128i mod10w = _mm_set1_epi16(0x4ccd);
			const __m128i table_index = _mm_set_epi8(-1, -1, -1, -1, -1, -1, 11, 6, 1, 12, 8, 3, 14, 9, 4, 0);

			// _mm_mulhi_epi16 (/10)
			//       arg a      |     |     |     |m nop|i jkl|e fgh|a bcd
			//       arg b  199a| 199a| 199a| 199a| 199a| 199a| 199a| 199a
			// (8 16-bits)      |     |     |     |  mno|  ijk|  efg|  abc
			const __m128i y4321x4321_div10 = _mm_mulhi_epi16(y4321x4321, div10w);

			// _mm_mulhi_epi16 (/100)
			//       arg a      |     |     |     |m nop|i jkl|e fgh|a bcd
			//       arg b  147b| 147b| 147b| 147b| 147b| 147b| 147b| 147b
			// _mm_srli_epi16 imm8=3
			// (8 16-bits)      |     |     |     |   mn|   ij|   ef|   ab
			const __m128i y4321x4321_div100 = _mm_srli_epi16(_mm_mulhi_epi16(y4321x4321, div100w), 3);

			// _mm_mulhi_epi16 (/1000)
			//       arg a      |     |     |     |m nop|i jkl|e fgh|a bcd
			//       arg b  20c5| 20c5| 20c5| 20c5| 20c5| 20c5| 20c5| 20c5
			// _mm_srli_epi16 imm8=7
			// (8 16-bits)      |     |     |     |    m|    i|    e|    a
			const __m128i y4321x4321_div1000 = _mm_srli_epi16(_mm_mulhi_epi16(y4321x4321, div1000w), 7);


			// _mm_mullo_epi16 (%10)
			//       arg a      |     |     |     |m nop|i jkl|e fgh|a bcd
			//       arg b  4ccd| 4ccd| 4ccd| 4ccd| 4ccd| 4ccd| 4ccd| 4ccd
			// _mm_srli_epi16 imm8=12
			// (8 16-bits)      |     |     |     |   p*|   l*|   h*|   d* // 4-bit indices into table 4ccd
			digit1 = _mm_srli_epi16(_mm_mullo_epi16(y4321x4321, mod10w), 12);

			// _mm_mullo_epi16 (%10)
			//       arg a      |     |     |     |  mno|  ijk|  efg|  abc
			//       arg b  4ccd| 4ccd| 4ccd| 4ccd| 4ccd| 4ccd| 4ccd| 4ccd
			// _mm_srli_epi16 imm8=12
			// (8 16-bits)      |     |     |     |   o*|   k*|   g*|   c* // 4-bit indices into table 4ccd
			digit10 = _mm_srli_epi16(_mm_mullo_epi16(y4321x4321_div10, mod10w), 12);

			// _mm_mullo_epi16 (%10)
			//       arg a      |     |     |     |   mn|   ij|   ef|   ab
			//       arg b  4ccd| 4ccd| 4ccd| 4ccd| 4ccd| 4ccd| 4ccd| 4ccd
			// _mm_srli_epi16 imm8=12
			// (8 16-bits)      |     |     |     |   n*|   j*|   f*|   b* // 4-bit indices into table 4ccd
			digit100 = _mm_srli_epi16(_mm_mullo_epi16(y4321x4321_div100, mod10w), 12);

			// _mm_suffle_epi8 // ssse3
			//       arg b      |     |     |     |    m|    i|    e|    a
			// (8 16-bits)      |     |     |     |   m*|   i*|   e*|   a* // 4-bit indices into table 4ccd
			digit1000 = _mm_shuffle_epi8(table_index, y4321x4321_div1000);
		}

		fio_target("ssse3") fio_inline void packlo_digits(__m128i digit1, __m128i digit10, __m128i digit100, __m128i digit1000, __m128i & chrs)
		{
			const __m128i table_4ccd = _mm_set_epi8(-1, '3', '6', '6', '9', '2', '2', '5', -1, '8', '1', '1', '4', '7', '7', '0');

			// _mm_unpacklo_epi16
			//       arg a      |     |     |     |   m*|   i*|   e*|   a*
			//       arg b      |     |     |     |   n*|   j*|   f*|   b*
			// (8 16-bits)    n*|   m*|   j*|   i*|   f*|   e*|   b*|   a*
			const __m128i hipart = _mm_unpacklo_epi16(digit1000, digit100);

			// _mm_unpacklo_epi16
			//       arg a      |     |     |     |   o*|   k*|   g*|   c*
			//       arg b      |     |     |     |   p*|   l*|   h*|   d*
			// (8 16-bits)    p*|   o*|   l*|   k*|   h*|   g*|   d*|   c*
			const __m128i lopart = _mm_unpacklo_epi16(digit10, digit1);

			// _mm_unpacklo_epi32
			//       arg a    n*|   m*|   j*|   i*|   f*|   e*|   b*|   a*
			//       arg b    p*|   o*|   l*|   k*|   h*|   g*|   d*|   c*
			// (8 16-bits)    h*|   g*|   f*|   e*|   d*|   c*|   b*|   a*
			const __m128i part21 = _mm_unpacklo_epi32(hipart, lopart);

			// _mm_unpackhi_epi32
			//       arg a    n*|   m*|   j*|   i*|   f*|   e*|   b*|   a*
			//       arg b    p*|   o*|   l*|   k*|   h*|   g*|   d*|   c*
			// (8 16-bits)    p*|   o*|   n*|   m*|   l*|   k*|   j*|   i*
			const __m128i part43 = _mm_unpackhi_epi32(hipart, lopart);

			// _mm_packs_epi16
			//       arg a    h*|   g*|   f*|   e*|   d*|   c*|   b*|   a*
			//       arg b    p*|   o*|   n*|   m*|   l*|   k*|   j*|   i*
			// (16 8-bits) p*|o*|n*|m*|l*|k*|j*|i*|h*|g*|f*|e*|d*|c*|b*|a*
			const __m128i packed = _mm_packs_epi16(part21, part43);

			// _mm_shuffle_epi8 table 4ccd // ssse3
			//       arg b p*|o*|n*|m*|l*|k*|j*|i*|h*|g*|f*|e*|d*|c*|b*|a*
			// (16 8-bits) p#|o#|n#|m#|l#|k#|j#|i#|h#|g#|f#|e#|d#|c#|b#|a# // character digits
			chrs = _mm_shuffle_epi8(table_4ccd, packed);
		}

		fio_target("ssse3") fio_inline void packhi_digits(__m128i digit1, __m128i digit10, __m128i digit100, __m128i digit1000, __m128i & chrs)
		{
			const __m128i table_4ccd = _mm_set_epi8(-1, '3', '6', '6', '9', '2', '2', '5', -1, '8', '1', '1', '4', '7', '7', '0');

			// _mm_unpackhi_epi16
			//       arg a    m*|   i*|   e*|   a*|     |     |     |
			//       arg b    n*|   j*|   f*|   b*|     |     |     |
			// (8 16-bits)    n*|   m*|   j*|   i*|   f*|   e*|   b*|   a*
			const __m128i hipart = _mm_unpackhi_epi16(digit1000, digit100);

			// _mm_unpacklo_epi16
			//       arg a    o*|   k*|   g*|   c*|     |     |     |
			//       arg b    p*|   l*|   h*|   d*|     |     |     |
			// (8 16-bits)    p*|   o*|   l*|   k*|   h*|   g*|   d*|   c*
			const __m128i lopart = _mm_unpackhi_epi16(digit10, digit1);

			// _mm_unpacklo_epi32
			//       arg a    n*|   m*|   j*|   i*|   f*|   e*|   b*|   a*
			//       arg b    p*|   o*|   l*|   k*|   h*|   g*|   d*|   c*
			// (8 16-bits)    h*|   g*|   f*|   e*|   d*|   c*|   b*|   a*
			const __m128i part21 = _mm_unpacklo_epi32(hipart, lopart);

			// _mm_unpackhi_epi32
			//       arg a    n*|   m*|   j*|   i*|   f*|   e*|   b*|   a*
			//       arg b    p*|   o*|   l*|   k*|   h*|   g*|   d*|   c*
			// (8 16-bits)    p*|   o*|   n*|   m*|   l*|   k*|   j*|   i*
			const __m128i part43 = _mm_unpackhi_epi32(hipart, lopart);

			// _mm_packs_epi16
			//       arg a    h*|   g*|   f*|   e*|   d*|   c*|   b*|   a*
			//       arg b    p*|   o*|   n*|   m*|   l*|   k*|   j*|   i*
			// (16 8-bits) p*|o*|n*|m*|l*|k*|j*|i*|h*|g*|f*|e*|d*|c*|b*|a*
			const __m128i packed = _mm_packs_epi16(part21, part43);

			// _mm_shuffle_epi8 table 4ccd // ssse3
			//       arg b p*|o*|n*|m*|l*|k*|j*|i*|h*|g*|f*|e*|d*|c*|b*|a*
			// (16 8-bits) p#|o#|n#|m#|l#|k#|j#|i#|h#|g#|f#|e#|d#|c#|b#|a# // character digits
			chrs = _mm_shuffle_epi8(table_4ccd, packed);
		}

		inline char * to_chars(uint8 value, char * buffer)
		{
			//   255
			//   abc
			// x 111 1
			unsigned int val = value;

#if defined(_MSC_VER)
			unsigned long bit;
			_BitScanReverse(&bit, value | 1);
#else
			const int bit = __builtin_clz(value | 1);
#endif

			unsigned int x1;
			int digits;
			switch (bit)
			{
			case 0:
			case 1:
			case 2:
			digits_1: // 1 digit
				x1 = val * 1000;
				digits = 1;
				break;
			case 3:
				if (val < 10u) goto digits_1; fio_fallthrough;
			case 4:
			case 5:
			digits_2: // 2 digits
				x1 = val * 100;
				digits = 2;
				break;
			case 6:
				if (val < 100u) goto digits_2; fio_fallthrough;
			case 7:
				x1 = val * 10;
				digits = 3;
				break;
			default:
				fio_unreachable();
			}

			const __m128i x___1 = _mm_set_epi16(0, 0, 0, 0, 0, 0, 0, static_cast<short>(x1));

			__m128i xdigit1;
			__m128i xdigit10;
			__m128i xdigit100;
			__m128i xdigit1000; // unused
			detail::integer_digits(x___1, xdigit1, xdigit10, xdigit100, xdigit1000);

			__m128i xchrs;
			detail::packlo_digits(xdigit1, xdigit10, xdigit100, xdigit1000, xchrs);

			_mm_storeu_si128(reinterpret_cast<__m128i *>(buffer + 0), xchrs);

			return buffer + digits;
		}

		inline char * to_chars(uint16 value, char * buffer)
		{
			//   65 535
			//   ab cde
			// x 11 112 222
			unsigned int val = value;

#if defined(_MSC_VER)
			unsigned long bit;
			_BitScanReverse(&bit, value | 1);
#else
			const int bit = __builtin_clz(value | 1);
#endif

			unsigned int x1;
			unsigned int x2;
			int digits;
			switch (bit)
			{
			case 0:
			case 1:
			case 2:
			digits_1: // 1 digit
				x1 = val * 1000;
				x2 = 0;
				digits = 1;
				break;
			case 3:
				if (val < 10u) goto digits_1; fio_fallthrough;
			case 4:
			case 5:
			digits_2: // 2 digits
				x1 = val * 100;
				x2 = 0;
				digits = 2;
				break;
			case 6:
				if (val < 100u) goto digits_2; fio_fallthrough;
			case 7:
			case 8:
			digits_3: // 3 digits
				x1 = val * 10;
				x2 = 0;
				digits = 3;
				break;
			case 9:
				if (val < 1000u) goto digits_3; fio_fallthrough;
			case 10:
			case 11:
			case 12:
			digits_4: // 4 digits
				x1 = val;
				x2 = 0;
				digits = 4;
				break;
			case 13:
				if (val < 10000u) goto digits_4; fio_fallthrough;
			case 14:
			case 15:
				x1 = val / 10;
				val -= x1 * 10;
				x2 = val * 1000;
				digits = 5;
				break;
			default:
				fio_unreachable();
			}

			const __m128i y____x__21 = _mm_set_epi16(0, 0, 0, 0, 0, 0, static_cast<short>(x2), static_cast<short>(x1));

			__m128i yxdigit1;
			__m128i yxdigit10;
			__m128i yxdigit100;
			__m128i yxdigit1000;
			detail::integer_digits(y____x__21, yxdigit1, yxdigit10, yxdigit100, yxdigit1000);

			__m128i xchrs;
			detail::packlo_digits(yxdigit1, yxdigit10, yxdigit100, yxdigit1000, xchrs);

			_mm_storeu_si128(reinterpret_cast<__m128i *>(buffer + 0), xchrs);

			return buffer + digits;
		}

		inline char * to_chars(uint32 value, char * buffer)
		{
			//   4 294 967 295
			//   a bcd efg hij
			// x 1 111 222 233 33
			unsigned int val = static_cast<unsigned int>(value);

#if defined(_MSC_VER)
			unsigned long bit;
			_BitScanReverse(&bit, value | 1);
#else
			const int bit = __builtin_clz(value | 1);
#endif

			unsigned int x1;
			unsigned int x2;
			unsigned int x3;
			int digits;
			switch (bit)
			{
			case 0:
			case 1:
			case 2:
			digits_1: // 1 digit
				x1 = val * 1000;
				x2 = 0;
				x3 = 0;
				digits = 1;
				break;
			case 3:
				if (val < 10u) goto digits_1; fio_fallthrough;
			case 4:
			case 5:
			digits_2: // 2 digits
				x1 = val * 100;
				x2 = 0;
				x3 = 0;
				digits = 2;
				break;
			case 6:
				if (val < 100u) goto digits_2; fio_fallthrough;
			case 7:
			case 8:
			digits_3: // 3 digits
				x1 = val * 10;
				x2 = 0;
				x3 = 0;
				digits = 3;
				break;
			case 9:
				if (val < 1000u) goto digits_3; fio_fallthrough;
			case 10:
			case 11:
			case 12:
			digits_4: // 4 digits
				x1 = val;
				x2 = 0;
				x3 = 0;
				digits = 4;
				break;
			case 13:
				if (val < 10000u) goto digits_4; fio_fallthrough;
			case 14:
			case 15:
			digits_5: // 5 digits
				x1 = val / 10;
				val -= x1 * 10;
				x2 = val * 1000;
				x3 = 0;
				digits = 5;
				break;
			case 16:
				if (val < 100000u) goto digits_5; fio_fallthrough;
			case 17:
			case 18:
			digits_6: // 6 digits
				x1 = val / 100;
				val -= x1 * 100;
				x2 = val * 100;
				x3 = 0;
				digits = 6;
				break;
			case 19:
				if (val < 1000000u) goto digits_6; fio_fallthrough;
			case 20:
			case 21:
			case 22:
			digits_7: // 7 digits
				x1 = val / 1000;
				val -= x1 * 1000;
				x2 = val * 10;
				x3 = 0;
				digits = 7;
				break;
			case 23:
				if (val < 10000000u) goto digits_7; fio_fallthrough;
			case 24:
			case 25:
			digits_8: // 8 digits
				x1 = val / 10000;
				val -= x1 * 10000;
				x2 = val;
				x3 = 0;
				digits = 8;
				break;
			case 26:
				if (val < 100000000u) goto digits_8; fio_fallthrough;
			case 27:
			case 28:
			digits_9: // 9 digits
				x1 = val / 100000;
				val -= x1 * 100000;
				x2 = val / 10;
				val -= x2 * 10;
				x3 = val * 1000;
				digits = 9;
				break;
			case 29:
				if (val < 1000000000u) goto digits_9; fio_fallthrough;
			case 30:
			case 31:
				// 10 digits
				x1 = val / 1000000;
				val -= x1 * 1000000;
				x2 = val / 100;
				val -= x2 * 100;
				x3 = val * 100;
				digits = 10;
				break;
			default:
				fio_unreachable();
			}

			const __m128i y____x_321 = _mm_set_epi16(0, 0, 0, 0, 0, static_cast<short>(x3), static_cast<short>(x2), static_cast<short>(x1));

			__m128i yxdigit1;
			__m128i yxdigit10;
			__m128i yxdigit100;
			__m128i yxdigit1000;
			detail::integer_digits(y____x_321, yxdigit1, yxdigit10, yxdigit100, yxdigit1000);

			__m128i xchrs;
			detail::packlo_digits(yxdigit1, yxdigit10, yxdigit100, yxdigit1000, xchrs);

			_mm_storeu_si128(reinterpret_cast<__m128i *>(buffer + 0), xchrs);

			return buffer + digits;
		}

		inline char * to_chars(uint64 value, char * buffer)
		{
			//   18 446 744 073 709 551 615
			//   ab cde fgh ijk lmn opq rst
			// x 11 112 222 333 344 44
			// y                      1 111
			unsigned long long val = static_cast<unsigned long long>(value);

#if defined(_MSC_VER)
			unsigned long bit;
			_BitScanReverse64(&bit, value | 1);
#else
			const int bit = __builtin_clzll(value | 1);
#endif

			unsigned long long x1;
			unsigned long long x2;
			unsigned long long x3;
			unsigned long long x4;
			unsigned long long y1;
			int digits;
			switch (bit)
			{
			case 0:
			case 1:
			case 2:
			digits_1: // 1 digit
				x1 = val * 1000;
				x2 = 0;
				x3 = 0;
				x4 = 0;
				y1 = 0;
				digits = 1;
				break;
			case 3:
				if (val < 10u) goto digits_1; fio_fallthrough;
			case 4:
			case 5:
			digits_2: // 2 digits
				x1 = val * 100;
				x2 = 0;
				x3 = 0;
				x4 = 0;
				y1 = 0;
				digits = 2;
				break;
			case 6:
				if (val < 100u) goto digits_2; fio_fallthrough;
			case 7:
			case 8:
			digits_3: // 3 digits
				x1 = val * 10;
				x2 = 0;
				x3 = 0;
				x4 = 0;
				y1 = 0;
				digits = 3;
				break;
			case 9:
				if (val < 1000u) goto digits_3; fio_fallthrough;
			case 10:
			case 11:
			case 12:
			digits_4: // 4 digits
				x1 = val;
				x2 = 0;
				x3 = 0;
				x4 = 0;
				y1 = 0;
				digits = 4;
				break;
			case 13:
				if (val < 10000u) goto digits_4; fio_fallthrough;
			case 14:
			case 15:
			digits_5: // 5 digits
				val *= 1000;
				digits = 5;
				goto setup_2;
			case 16:
				if (val < 100000u) goto digits_5; fio_fallthrough;
			case 17:
			case 18:
			digits_6: // 6 digits
				val *= 100;
				digits = 6;
				goto setup_2;
			case 19:
				if (val < 1000000u) goto digits_6; fio_fallthrough;
			case 20:
			case 21:
			case 22:
			digits_7: // 7 digits
				val *= 10;
				digits = 7;
				goto setup_2;
			case 23:
				if (val < 10000000u) goto digits_7; fio_fallthrough;
			case 24:
			case 25:
			digits_8: // 8 digits
				digits = 8;
			setup_2:
				{
					// val = ab cde fgh
					const unsigned long long tx1 = val / 10000u; //     a bcd
					x1 = tx1;
					x2 = val - tx1 * 10000;
					x3 = 0;
					x4 = 0;
					y1 = 0;
				}
				break;
			case 26:
				if (val < 100000000u) goto digits_8; fio_fallthrough;
			case 27:
			case 28:
			digits_9: // 9 digits
				val *= 1000;
				digits = 9;
				goto setup_3;
			case 29:
				if (val < 1000000000u) goto digits_9; fio_fallthrough;
			case 30:
			case 31:
			case 32:
			digits_10: // 10 digits
				val *= 100;
				digits = 10;
				goto setup_3;
			case 33:
				if (val < 10000000000u) goto digits_10; fio_fallthrough;
			case 34:
			case 35:
			digits_11: // 11 digits
				val *= 10;
				digits = 11;
				goto setup_3;
			case 36:
				if (val < 100000000000u) goto digits_11; fio_fallthrough;
			case 37:
			case 38:
			digits_12: // 12 digits
				digits = 12;
			setup_3:
				{
					// val = abc def ghi jkl
					const unsigned long long tx1 = val / 100000000u; //     a bcd
					const unsigned long long tx2 = val / 10000u; //    ab cde fgh
					x1 = tx1;
					x2 = tx2 - tx1 * 10000;
					x3 = val - tx2 * 10000;
					x4 = 0;
					y1 = 0;
				}
				break;
			case 39:
				if (val < 1000000000000u) goto digits_12; fio_fallthrough;
			case 40:
			case 41:
			case 42:
			digits_13: // 13 digits
				val *= 1000;
				digits = 13;
				goto setup_4;
			case 43:
				if (val < 10000000000000u) goto digits_13; fio_fallthrough;
			case 44:
			case 45:
			digits_14: // 14 digits
				val *= 100;
				digits = 14;
				goto setup_4;
			case 46:
				if (val < 100000000000000u) goto digits_14; fio_fallthrough;
			case 47:
			case 48:
			digits_15: // 15 digits
				val *= 10;
				digits = 15;
				goto setup_4;
			case 49:
				if (val < 1000000000000000u) goto digits_15; fio_fallthrough;
			case 50:
			case 51:
			case 52:
			digits_16: // 16 digits
				digits = 16;
			setup_4:
				{
					// note msvc does not generate magic numbers for division constants
					// larger than 32 bits, in case other compilers also have problems we
					// replace all divisions by these magical numbers (that was
					// shamelessly stolen from clangs output)

					// val = a bcd efg hij klm nop
					const unsigned long long tx1 = mulhi(val, 0x232F33025BD42233) >> 37; // val / 1000000000000 = a bcd
					const unsigned long long tx2 = mulhi(val, 0xABCC77118461CEFD) >> 26; // val / 100000000 = ab cde fgh
					const unsigned long long tx3 = mulhi(val, 0x346DC5D63886594B) >> 11; // val / 10000 = abc def ghi jkl
					x1 = tx1;
					x2 = tx2 - tx1 * 10000;
					x3 = tx3 - tx2 * 10000;
					x4 = val - tx3 * 10000;
					y1 = 0;
				}
				break;
			case 53:
				if (val < 10000000000000000u) goto digits_16; fio_fallthrough;
			case 54:
			case 55:
			digits_17: // 17 digits
				val *= 100;
				digits = 17;
				goto setup_5x;
			case 56:
				if (val < 100000000000000000u) goto digits_17; fio_fallthrough;
			case 57:
			case 58:
			digits_18: // 18 digits
				val *= 10;
				digits = 18;
				goto setup_5x;
			case 59:
				if (val < 1000000000000000000u) goto digits_18; fio_fallthrough;
			case 60:
			case 61:
			case 62:
			digits_19: // 19 digits
				digits = 19;
			setup_5x:
				{
					// note msvc does not generate magic numbers for division constants
					// larger than 32 bits, in case other compilers also have problems we
					// replace all divisions by these magical numbers (that was
					// shamelessly stolen from clangs output)

					// todo
					// val = ab cde fgh ijk lmn opq rs
					const unsigned long long tx1 = val / 1000000000000000ull; // val / 1000000000000000 = a bcd
					const unsigned long long tx2 = mulhi(val, 0xAFEBFF0BCB24AAFF) >> 36; // val / 100000000000 = ab cde fgh
					const unsigned long long tx3 = mulhi(val, 0xD6BF94D5E57A42BD) >> 23; // val / 10000000 = abc def ghi jkl
					const unsigned long long tx4 = val / 1000ull; // val / 1000 = a bcd efg hij klm nop
					x1 = tx1;
					x2 = tx2 - tx1 * 10000;
					x3 = tx3 - tx2 * 10000;
					x4 = tx4 - tx3 * 10000;
					y1 = (val - tx4 * 1000) * 10;
				}
				break;
			case 63:
				if (val < 10000000000000000000u) goto digits_19;
				digits = 20;
				{
					// note msvc does not generate magic numbers for division constants
					// larger than 32 bits, in case other compilers also have problems we
					// replace all divisions by these magical numbers (that was
					// shamelessly stolen from clangs output)

					// val = ab cde fgh ijk lmn opq rst
					const unsigned long long tx1 = mulhi(val, 0x39A5652FB1137857) >> 51; // val / 10000000000000000 = a bcd
					const unsigned long long tx2 = mulhi(val, 0x232F33025BD42233) >> 37; // val / 1000000000000 = ab cde fgh
					const unsigned long long tx3 = mulhi(val, 0xABCC77118461CEFD) >> 26; // val / 100000000 = abc def ghi jkl
					const unsigned long long tx4 = mulhi(val, 0x346DC5D63886594B) >> 11; // val / 10000 = a bcd efg hij klm nop
					x1 = tx1;
					x2 = tx2 - tx1 * 10000;
					x3 = tx3 - tx2 * 10000;
					x4 = tx4 - tx3 * 10000;
					y1 = val - tx4 * 10000;
				}
				break;
			default:
				fio_unreachable();
			}

			const __m128i y___1x4321 = _mm_set_epi16(0, 0, 0, static_cast<short>(y1), static_cast<short>(x4), static_cast<short>(x3), static_cast<short>(x2), static_cast<short>(x1));

			__m128i yxdigit1;
			__m128i yxdigit10;
			__m128i yxdigit100;
			__m128i yxdigit1000;
			detail::integer_digits(y___1x4321, yxdigit1, yxdigit10, yxdigit100, yxdigit1000);

			__m128i xchrs;
			__m128i ychrs;
			detail::packlo_digits(yxdigit1, yxdigit10, yxdigit100, yxdigit1000, xchrs);
			detail::packhi_digits(yxdigit1, yxdigit10, yxdigit100, yxdigit1000, ychrs);

			_mm_storeu_si128(reinterpret_cast<__m128i *>(buffer + 0), xchrs);
			_mm_storeu_si128(reinterpret_cast<__m128i *>(buffer + 16), ychrs);

			return buffer + digits;
		}
	}

	inline char * to_chars(bool value, char * buffer) = delete;

	fio_inline char * to_chars(unsigned char value, char * buffer)
	{
		return detail::to_chars(static_cast<uint8>(value), buffer);
	}

	fio_inline char * to_chars(signed char value, char * buffer)
	{
		unsigned char uvalue;

		if (value < 0)
		{
			uvalue = static_cast<unsigned char>(-value);

			buffer[0] = '-';
			buffer++;
		}
		else
		{
			uvalue = static_cast<unsigned char>(value);
		}

		return to_chars(uvalue, buffer);
	}

	fio_inline char * to_chars(unsigned short value, char * buffer)
	{
		return detail::to_chars(static_cast<uint16>(value), buffer);
	}

	fio_inline char * to_chars(short value, char * buffer)
	{
		unsigned short uvalue;

		if (value < 0)
		{
			uvalue = static_cast<unsigned short>(-value);

			buffer[0] = '-';
			buffer++;
		}
		else
		{
			uvalue = static_cast<unsigned short>(value);
		}

		return to_chars(uvalue, buffer);
	}

	fio_inline char * to_chars(unsigned int value, char * buffer)
	{
		return detail::to_chars(static_cast<uint32>(value), buffer);
	}

	fio_inline char * to_chars(int value, char * buffer)
	{
		unsigned int uvalue;

		if (value < 0)
		{
			uvalue = static_cast<unsigned int>(-value);

			buffer[0] = '-';
			buffer++;
		}
		else
		{
			uvalue = static_cast<unsigned int>(value);
		}

		return to_chars(uvalue, buffer);
	}

	fio_inline char * to_chars(unsigned long long value, char * buffer)
	{
		return detail::to_chars(static_cast<uint64>(value), buffer);
	}

	fio_inline char * to_chars(long long value, char * buffer)
	{
		unsigned long long uvalue;

		if (value < 0)
		{
			uvalue = static_cast<unsigned long long>(-value);

			buffer[0] = '-';
			buffer++;
		}
		else
		{
			uvalue = static_cast<unsigned long long>(value);
		}

		return to_chars(uvalue, buffer);
	}

	fio_inline char * to_chars(unsigned long value, char * buffer)
	{
#if defined(__LP64__)
		return detail::to_chars(static_cast<uint64>(value), buffer);
#else
		return detail::to_chars(static_cast<uint32>(value), buffer);
#endif
	}

	fio_inline char * to_chars(long value, char * buffer)
	{
		unsigned long uvalue;

		if (value < 0)
		{
			uvalue = static_cast<unsigned long>(-value);

			buffer[0] = '-';
			buffer++;
		}
		else
		{
			uvalue = static_cast<unsigned long>(value);
		}

		return to_chars(uvalue, buffer);
	}
}

#pragma once

#include "fio/compiler.hpp"
#include "fio/stdint.hpp"

#include "fio/intrinsics.hpp"

namespace fio
{
	namespace detail
	{
		fio_target("sse2") fio_inline
		usize integer_chunks(uint8 value, __m128i & chunks)
		{
			//   255
			//   abc
			// x 111 1
			unsigned int val = value;

			const unsigned int bit = nat::bsr32(value | 1);

			unsigned int x1;
			usize digits;
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
				// 3 digits
				x1 = val * 10;
				digits = 3;
				break;
			default:
				fio_unreachable();
			}

			chunks = _mm_set_epi16(0, 0, 0, 0, 0, 0, 0, static_cast<short>(x1));

			return digits;
		}

		fio_target("sse2") fio_inline
		usize integer_chunks(uint16 value, __m128i & chunks)
		{
			//   65 535
			//   ab cde
			// x 11 112 222
			unsigned int val = value;

			const unsigned int bit = fio::nat::bsr32(value | 1);

			unsigned int x1;
			unsigned int x2;
			usize digits;
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
				// 5 digits
			{
				// val = a bcde
				const unsigned int tx1 = (val * 0xcccd) >> 19; // val / 10 = abcd
				x1 = tx1;
				x2 = val * 1000 - tx1 * 10000; // e000
				digits = 5;
				break;
			}
			default:
				fio_unreachable();
			}

			chunks = _mm_set_epi16(0, 0, 0, 0, 0, 0, static_cast<short>(x2), static_cast<short>(x1));

			return digits;
		}

		fio_target("sse2") fio_inline
		usize integer_chunks(uint32 value, __m128i & chunks)
		{
			//   4 294 967 295
			//   a bcd efg hij
			// x 1 111 222 233 33
			unsigned int val = value;

			const unsigned int bit = fio::nat::bsr32(value | 1);

			unsigned int x1;
			unsigned int x2;
			unsigned int x3;
			usize digits;
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
			{
				// val = a bcde
				const unsigned int tx1 = nat::udiv32(val, 0xcccd, 19); // val / 10 = abcd
				x1 = tx1;
				x2 = val * 1000 - tx1 * 10000; // e000
				x3 = 0;
				digits = 5;
				break;
			}
			case 16:
				if (val < 100000u) goto digits_5; fio_fallthrough;
			case 17:
			case 18:
			digits_6: // 6 digits
			{
				// val = ab cdef
				const unsigned int tx1 = nat::udiv32(val, 0xa3d71, 26); // val / 100 = abcd
				x1 = tx1;
				x2 = val * 100 - tx1 * 10000; // ef00
				x3 = 0;
				digits = 6;
				break;
			}
			case 19:
				if (val < 1000000u) goto digits_6; fio_fallthrough;
			case 20:
			case 21:
			case 22:
			digits_7: // 7 digits
			{
				// val = abc defg
				const unsigned int tx1 = nat::udiv32(val, 0x83126f, 33); // val / 1000 = abcd
				x1 = tx1;
				x2 = val * 10 - tx1 * 1000; // efg0
				x3 = 0;
				digits = 7;
				break;
			}
			case 23:
				if (val < 10000000u) goto digits_7; fio_fallthrough;
			case 24:
			case 25:
			digits_8: // 8 digits
			{
				// val = abcd efgh
				const unsigned int tx1 = nat::udiv32(val, 0x68db8bb, 40); // val / 10000 = abcd
				x1 = tx1;
				x2 = val - tx1 * 10000; // efgh
				x3 = 0;
				digits = 8;
				break;
			}
			case 26:
				if (val < 100000000u) goto digits_8; fio_fallthrough;
			case 27:
			case 28:
			digits_9: // 9 digits
			{
				// val = a bcde fghi
				const unsigned int tx1 = nat::udiv32(val, 0x14f8b589, 45); // val / 100000 = abcd
				const unsigned int tx2 = nat::udiv32(val, 0xccccccd, 31); // val / 10 = abcd efgh
				x1 = tx1;
				x2 = tx2 - tx1 * 10000; // efgh
				x3 = val * 1000 - tx2 * 10000; // i000 // note fine to ignore high bits
				digits = 9;
				break;
			}
			case 29:
				if (val < 1000000000u) goto digits_9; fio_fallthrough;
			case 30:
			case 31:
				// 10 digits
			{
				// val = ab cdef ghij
				const unsigned int tx1 = nat::udiv32(val, 0x431bde83, 50); // val / 1000000 = abcd
				const unsigned int tx2 = nat::udiv32(val, 0x51eb851f, 37); // val / 100 = abcd efgh
				x1 = tx1;
				x2 = tx2 - tx1 * 10000; // efgh
				x3 = val * 100 - tx2 * 10000; // ij00 // note fine to ignore high bits
				digits = 10;
				break;
			}
			default:
				fio_unreachable();
			}

			chunks = _mm_set_epi16(0, 0, 0, 0, 0, static_cast<short>(x3), static_cast<short>(x2), static_cast<short>(x1));

			return digits;
		}

#if defined(_M_X64) || defined(_M_AMD64) || defined(__x86_64__)

		fio_target("sse2") fio_inline
		usize integer_chunks(uint64 value, __m128i & chunks)
		{
			//   18 446 744 073 709 551 615
			//   ab cde fgh ijk lmn opq rst
			// x 11 112 222 333 344 44
			// y                      1 111
			unsigned long long val = value;

			const unsigned int bit = fio::nat::bsr64(value | 1);

			unsigned long long x1;
			unsigned long long x2;
			unsigned long long x3;
			unsigned long long x4;
			unsigned long long y1;
			usize digits;
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
			{
				// val = a bcde
				const unsigned long long tx1 = (val * 0xcccd) >> 19; // val / 10 = abcd
				x1 = tx1;
				x2 = val * 1000 - tx1 * 10000; // e000
				x3 = 0;
				x4 = 0;
				y1 = 0;
				digits = 5;
				break;
			}
			case 16:
				if (val < 100000u) goto digits_5; fio_fallthrough;
			case 17:
			case 18:
			digits_6: // 6 digits
			{
				// val = ab cdef
				const unsigned long long tx1 = (val * 0xa3d71) >> 26; // val / 100 = abcd
				x1 = tx1;
				x2 = val * 100 - tx1 * 10000; // ef00
				x3 = 0;
				x4 = 0;
				y1 = 0;
				digits = 6;
				break;
			}
			case 19:
				if (val < 1000000u) goto digits_6; fio_fallthrough;
			case 20:
			case 21:
			case 22:
			digits_7: // 7 digits
			{
				// val = abc defg
				const unsigned long long tx1 = (val * 0x83126f) >> 33; // val / 1000 = abcd
				x1 = tx1;
				x2 = val * 10 - tx1 * 1000; // efg0
				x3 = 0;
				x4 = 0;
				y1 = 0;
				digits = 7;
				break;
			}
			case 23:
				if (val < 10000000u) goto digits_7; fio_fallthrough;
			case 24:
			case 25:
			digits_8: // 8 digits
			{
				// val = abcd efgh
				const unsigned long long tx1 = (val * 0x68db8bb) >> 40; // val / 10000 = abcd
				x1 = tx1;
				x2 = val - tx1 * 10000; // efgh
				x3 = 0;
				x4 = 0;
				y1 = 0;
				digits = 8;
				break;
			}
			case 26:
				if (val < 100000000u) goto digits_8; fio_fallthrough;
			case 27:
			case 28:
			digits_9: // 9 digits
			{
				// val = a bcde fghi
				const unsigned long long tx1 = (val * 0x14f8b589) >> 45; // val / 100000 = abcd
				const unsigned long long tx2 = (val * 0xccccccd) >> 31; // val / 10 = abcd efgh
				x1 = tx1;
				x2 = tx2 - tx1 * 10000; // efgh
				x3 = val * 1000 - tx2 * 10000; // i000
				x4 = 0;
				y1 = 0;
				digits = 9;
				break;
			}
			case 29:
				if (val < 1000000000u) goto digits_9; fio_fallthrough;
			case 30:
			case 31:
			case 32:
			digits_10: // 10 digits
			{
				// val = ab cdef ghij
				const unsigned long long tx1 = nat::udiv64(val, 0x8637bd05af6d, 67); // val / 1000000 = abcd
				const unsigned long long tx2 = nat::udiv64(val, 0xa3d70a3d70a3d71, 66); // val / 100 = abcd efgh
				x1 = tx1;
				x2 = tx2 - tx1 * 10000; // efgh
				x3 = val * 100 - tx2 * 10000; // ij00
				x4 = 0;
				y1 = 0;
				digits = 10;
				break;
			}
			case 33:
				if (val < 10000000000u) goto digits_10; fio_fallthrough;
			case 34:
			case 35:
			digits_11: // 11 digits
			{
				// val = abc defg hijk
				const unsigned long long tx1 = nat::udiv64(val, 0x1ad7f29abcb, 64); // val / 10000000 = abcd
				const unsigned long long tx2 = nat::udiv64(val, 0x10624dd2f1a9fbf, 66); // val / 1000 = abcd efgh
				x1 = tx1;
				x2 = tx2 - tx1 * 10000; // efgh
				x3 = val * 10 - tx2 * 10000; // ijk0
				x4 = 0;
				y1 = 0;
				digits = 11;
				break;
			}
			case 36:
				if (val < 100000000000u) goto digits_11; fio_fallthrough;
			case 37:
			case 38:
			digits_12: // 12 digits
			{
				// val = abcd efgh ijkl
				const unsigned long long tx1 = nat::udiv64(val, 0xabcc771185, 66); // val / 100000000 = abcd
				const unsigned long long tx2 = nat::udiv64(val, 0x1a36e2eb1c432d, 66); // val / 10000 = abcd efgh
				x1 = tx1;
				x2 = tx2 - tx1 * 10000; // efgh
				x3 = val - tx2 * 10000; // ijkl
				x4 = 0;
				y1 = 0;
				digits = 12;
				break;
			}
			case 39:
				if (val < 1000000000000u) goto digits_12; fio_fallthrough;
			case 40:
			case 41:
			case 42:
			digits_13: // 13 digits
			{
				// val = a bcde fghi jklm
				const unsigned long long tx1 = nat::udiv64(val, 0x225c17d04db, 71); // val / 1000000000 = abcd
				const unsigned long long tx2 = nat::udiv64(val, 0x53e2d6238da3d, 67); // val / 100000 = abcd efgh
				const unsigned long long tx3 = nat::udiv64(val, 0x6666666666666667, 66); // val / 10 = abcd efgh ijkl
				x1 = tx1;
				x2 = tx2 - tx1 * 10000; // efgh
				x3 = tx3 - tx2 * 10000; // ijkl
				x4 = val * 1000 - tx3 * 10000; // m000
				y1 = 0;
				digits = 13;
				break;
			}
			case 43:
				if (val < 10000000000000u) goto digits_13; fio_fallthrough;
			case 44:
			case 45:
			digits_14: // 14 digits
			{
				// val = ab cdef ghij klmn
				const unsigned long long tx1 = nat::udiv64(val, 0xdbe6fecebdf, 77); // val / 10000000000 = abcd
				const unsigned long long tx2 = nat::udiv64(val, 0x8637bd05af6d, 67); // val / 1000000 = abcd efgh
				const unsigned long long tx3 = nat::udiv64(val, 0xa3d70a3d70a3d71, 66); // val / 100 = abcd efgh ijkl
				x1 = tx1;
				x2 = tx2 - tx1 * 10000; // efgh
				x3 = tx3 - tx2 * 10000; // ijkl
				x4 = val * 100 - tx3 * 10000; // mn00
				y1 = 0;
				digits = 14;
				break;
			}
			case 46:
				if (val < 100000000000000u) goto digits_14; fio_fallthrough;
			case 47:
			case 48:
			digits_15: // 15 digits
			{
				// val = abc defg hijk lmno
				const unsigned long long tx1 = nat::udiv64(val, 0x2bfaffc2f2c93, 86); // val / 100000000000 = abcd
				const unsigned long long tx2 = nat::udiv64(val, 0x6b5fca6af2bd3, 74); // val / 10000000 = abcd efgh
				const unsigned long long tx3 = nat::udiv64(val, 0x10624dd2f1a9fbf, 66); // val / 1000 = abcd efgh ijkl
				x1 = tx1;
				x2 = tx2 - tx1 * 10000; // efgh
				x3 = tx3 - tx2 * 10000; // ijkl
				x4 = val * 10 - tx3 * 10000; // mno0
				y1 = 0;
				digits = 15;
				break;
			}
			case 49:
				if (val < 1000000000000000u) goto digits_15; fio_fallthrough;
			case 50:
			case 51:
			case 52:
			digits_16: // 16 digits
			{
				// val = abcd efgh ijkl mnop
				const unsigned long long tx1 = nat::udiv64(val, 0x232f33025bd423, 93); // val / 1000000000000 = abcd
				const unsigned long long tx2 = nat::udiv64(val, 0xabcc77118461d, 78); // val / 100000000 = abcd efgh
				const unsigned long long tx3 = nat::udiv64(val, 0x1a36e2eb1c432d, 66); // val / 10000 = abcd efgh ijkl
				x1 = tx1;
				x2 = tx2 - tx1 * 10000; // efgh
				x3 = tx3 - tx2 * 10000; // ijkl
				x4 = val - tx3 * 10000; // mnop
				y1 = 0;
				digits = 16;
				break;
			}
			case 53:
				if (val < 10000000000000000u) goto digits_16; fio_fallthrough;
			case 54:
			case 55:
			digits_17: // 17 digits
			{
				// val = a bcde fghi jklm nopq
				const unsigned long long tx1 = nat::udiv64(val, 0x1c25c268497681d, 100); // val / 10000000000000 = abcd
				const unsigned long long tx2 = nat::udiv64(val, 0x225c17d04dad297, 87); // val / 1000000000 = abcd efgh
				const unsigned long long tx3 = nat::udiv64(val, 0x14f8b588e368f09, 73); // val / 100000 = abcd efgh ijkl
				const unsigned long long tx4 = nat::udiv64(val, 0x6666666666666667, 66); // val / 10 = abcd efgh ijkl mnop
				x1 = tx1;
				x2 = tx2 - tx1 * 10000; // efgh
				x3 = tx3 - tx2 * 10000; // ijkl
				x4 = tx4 - tx3 * 10000; // mnop
				y1 = val * 1000 - tx4 * 10000; // q000 // note fine to ignore high bits
				digits = 17;
				break;
			}
			case 56:
				if (val < 100000000000000000u) goto digits_17; fio_fallthrough;
			case 57:
			case 58:
			digits_18: // 18 digits
			{
				// val = ab cdef ghij klmn opqr
				const unsigned long long tx1 = nat::udiv64(val, 0xb424dc35095cd81, 106); // val / 100000000000000 = abcd
				const unsigned long long tx2 = nat::udiv64(val, 0x36f9bfb3af7b757, 91); // val / 10000000000 = abcd efgh
				const unsigned long long tx3 = nat::udiv64(val, 0x10c6f7a0b5ed8d37, 80); // val / 1000000 = abcd efgh ijkl
				const unsigned long long tx4 = nat::udiv64(val, 0xa3d70a3d70a3d71, 66); // val / 100 = abcd efgh ijkl mnop
				x1 = tx1;
				x2 = tx2 - tx1 * 10000; // efgh
				x3 = tx3 - tx2 * 10000; // ijkl
				x4 = tx4 - tx3 * 10000; // mnop
				y1 = val * 100 - tx4 * 10000; // qr00 // note fine to ignore high bits
				digits = 18;
				break;
			}
			case 59:
				if (val < 1000000000000000000u) goto digits_18; fio_fallthrough;
			case 60:
			case 61:
			case 62:
			digits_19: // 19 digits
			{
				// val = abc defg hijk lmno pqrs
				const unsigned long long tx1 = nat::udiv64(val, 0x480ebe7b9d58566d, 112); // val / 1000000000000000 = abcd
				const unsigned long long tx2 = nat::udiv64(val, 0xafebff0bcb24ab, 92); // val / 100000000000 = abcd efgh
				const unsigned long long tx3 = nat::udiv64(val, 0xd6bf94d5e57a42bd, 87); // val / 10000000 = abcd efgh ijkl
				const unsigned long long tx4 = nat::udiv64(val, 0x20c49ba5e353f7cf, 71); // val / 1000 = abcd efgh ijkl mnop
				x1 = tx1;
				x2 = tx2 - tx1 * 10000; // efgh
				x3 = tx3 - tx2 * 10000; // ijkl
				x4 = tx4 - tx3 * 10000; // mnop
				y1 = val * 10 - tx4 * 10000; // qrs0 // note fine to ignore high bits
				digits = 19;
				break;
			}
			case 63:
				if (val < 10000000000000000000u) goto digits_19;
				// digits 20
			{
				// val = abcd efgh ijkl mnop qrst
				const unsigned long long tx1 = nat::udiv64(val, 0x39a5652fb1137857, 115); // val / 10000000000000000 = abcd
				const unsigned long long tx2 = nat::udiv64(val, 0x232f33025bd42233, 101); // val / 1000000000000 = abcd efgh
				const unsigned long long tx3 = nat::udiv64(val, 0xabcc77118461cefd, 90); // val / 100000000 = abcd efgh ijkl
				const unsigned long long tx4 = nat::udiv64(val, 0x346dc5d63886594b, 75); // val / 10000 = abcd efgh ijkl mnop
				x1 = tx1;
				x2 = tx2 - tx1 * 10000; // efgh
				x3 = tx3 - tx2 * 10000; // ijkl
				x4 = tx4 - tx3 * 10000; // mnop
				y1 = val - tx4 * 10000; // qrst // note fine to ignore high bits
				digits = 20;
				break;
			}
			default:
				fio_unreachable();
			}

			chunks = _mm_set_epi16(0, 0, 0, static_cast<short>(y1), static_cast<short>(x4), static_cast<short>(x3), static_cast<short>(x2), static_cast<short>(x1));

			return digits;
		}

#endif

		fio_target("ssse3") fio_inline
		void integer_digits(__m128i y4321x4321, __m128i & digit1, __m128i & digit10, __m128i & digit100, __m128i & digit1000)
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

		fio_target("ssse3") fio_inline
		void packlo_digits(__m128i digit1, __m128i digit10, __m128i digit100, __m128i digit1000, __m128i & chrs)
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

		fio_target("ssse3") fio_inline
		void packhi_digits(__m128i digit1, __m128i digit10, __m128i digit100, __m128i digit1000, __m128i & chrs)
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

		fio_inline
		char * to_chars(uint8 value, char * buffer)
		{
			__m128i x___1;
			const usize digits = detail::integer_chunks(value, x___1);

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

		fio_inline
		char * to_chars(uint16 value, char * buffer)
		{
			__m128i y____x__21;
			const usize digits = detail::integer_chunks(value, y____x__21);

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

		fio_inline
		char * to_chars(uint32 value, char * buffer)
		{
			__m128i y____x_321;
			const usize digits = detail::integer_chunks(value, y____x_321);

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

		fio_inline
		char * to_chars(uint64 value, char * buffer)
		{
			__m128i y___1x4321;
			const usize digits = detail::integer_chunks(value, y___1x4321);

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

#if defined(_MSC_VER)

	namespace detail
	{
		fio_inline
		wchar_t * to_chars(uint8 value, wchar_t * buffer)
		{
			__m128i x___1;
			const usize digits = detail::integer_chunks(value, x___1);

			__m128i xdigit1;
			__m128i xdigit10;
			__m128i xdigit100;
			__m128i xdigit1000; // unused
			detail::integer_digits(x___1, xdigit1, xdigit10, xdigit100, xdigit1000);

			__m128i xchrs;
			detail::packlo_digits(xdigit1, xdigit10, xdigit100, xdigit1000, xchrs);

			const __m128i zero = _mm_setzero_si128();
			_mm_storeu_si128(reinterpret_cast<__m128i *>(buffer + 0), _mm_unpacklo_epi8(xchrs, zero));

			return buffer + digits;
		}

		fio_inline
		wchar_t * to_chars(uint16 value, wchar_t * buffer)
		{
			__m128i y____x__21;
			const usize digits = detail::integer_chunks(value, y____x__21);

			__m128i yxdigit1;
			__m128i yxdigit10;
			__m128i yxdigit100;
			__m128i yxdigit1000;
			detail::integer_digits(y____x__21, yxdigit1, yxdigit10, yxdigit100, yxdigit1000);

			__m128i xchrs;
			detail::packlo_digits(yxdigit1, yxdigit10, yxdigit100, yxdigit1000, xchrs);

			const __m128i zero = _mm_setzero_si128();
			_mm_storeu_si128(reinterpret_cast<__m128i *>(buffer + 0), _mm_unpacklo_epi8(xchrs, zero));

			return buffer + digits;
		}

		fio_inline
		wchar_t * to_chars(uint32 value, wchar_t * buffer)
		{
			__m128i y____x_321;
			const usize digits = detail::integer_chunks(value, y____x_321);

			__m128i yxdigit1;
			__m128i yxdigit10;
			__m128i yxdigit100;
			__m128i yxdigit1000;
			detail::integer_digits(y____x_321, yxdigit1, yxdigit10, yxdigit100, yxdigit1000);

			__m128i xchrs;
			detail::packlo_digits(yxdigit1, yxdigit10, yxdigit100, yxdigit1000, xchrs);

			const __m128i zero = _mm_setzero_si128();
			_mm_storeu_si128(reinterpret_cast<__m128i *>(buffer + 0), _mm_unpacklo_epi8(xchrs, zero));
			_mm_storeu_si128(reinterpret_cast<__m128i *>(buffer + 16 / 2), _mm_unpackhi_epi8(xchrs, zero));

			return buffer + digits;
		}

		fio_inline
		wchar_t * to_chars(uint64 value, wchar_t * buffer)
		{
			__m128i y___1x4321;
			const usize digits = detail::integer_chunks(value, y___1x4321);

			__m128i yxdigit1;
			__m128i yxdigit10;
			__m128i yxdigit100;
			__m128i yxdigit1000;
			detail::integer_digits(y___1x4321, yxdigit1, yxdigit10, yxdigit100, yxdigit1000);

			__m128i xchrs;
			__m128i ychrs;
			detail::packlo_digits(yxdigit1, yxdigit10, yxdigit100, yxdigit1000, xchrs);
			detail::packhi_digits(yxdigit1, yxdigit10, yxdigit100, yxdigit1000, ychrs);

			const __m128i zero = _mm_setzero_si128();
			_mm_storeu_si128(reinterpret_cast<__m128i *>(buffer + 0), _mm_unpacklo_epi8(xchrs, zero));
			_mm_storeu_si128(reinterpret_cast<__m128i *>(buffer + 16 / 2), _mm_unpackhi_epi8(xchrs, zero));
			_mm_storeu_si128(reinterpret_cast<__m128i *>(buffer + 32 / 2), _mm_unpacklo_epi8(ychrs, zero));

			return buffer + digits;
		}
	}

	inline wchar_t * to_chars(bool value, wchar_t * buffer) = delete;

	fio_inline wchar_t * to_chars(unsigned char value, wchar_t * buffer)
	{
		return detail::to_chars(static_cast<uint8>(value), buffer);
	}

	fio_inline wchar_t * to_chars(signed char value, wchar_t * buffer)
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

	fio_inline wchar_t * to_chars(unsigned short value, wchar_t * buffer)
	{
		return detail::to_chars(static_cast<uint16>(value), buffer);
	}

	fio_inline wchar_t * to_chars(short value, wchar_t * buffer)
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

	fio_inline wchar_t * to_chars(unsigned int value, wchar_t * buffer)
	{
		return detail::to_chars(static_cast<uint32>(value), buffer);
	}

	fio_inline wchar_t * to_chars(int value, wchar_t * buffer)
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

	fio_inline wchar_t * to_chars(unsigned long long value, wchar_t * buffer)
	{
		return detail::to_chars(static_cast<uint64>(value), buffer);
	}

	fio_inline wchar_t * to_chars(long long value, wchar_t * buffer)
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

	fio_inline wchar_t * to_chars(unsigned long value, wchar_t * buffer)
	{
#if defined(__LP64__)
		return detail::to_chars(static_cast<uint64>(value), buffer);
#else
		return detail::to_chars(static_cast<uint32>(value), buffer);
#endif
	}

	fio_inline wchar_t * to_chars(long value, wchar_t * buffer)
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

#endif
}

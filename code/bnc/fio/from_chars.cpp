#include <catch2/catch.hpp>

#include "catchhacks.hpp"

#include "fio/from_chars.hpp"
#include "fio/mem.hpp"

#include <cstdio>
#if (__cplusplus >= 201703L) || (defined(_MSVC_LANG) && _MSVC_LANG >= 201703L)
# include <charconv>
#endif

#if HAVE_EASTDC
# include <EAStdC/EASprintf.h>
#endif

#if HAVE_FMT
# include <fmt/core.h>
#endif

TEST_CASE("from_chars sint8", "[.][dump]")
{
	BENCHMARK_DUMP("plot/from_chars_sint8.dump", lin_style, 1, 4, 1, "#digits")
	{
		BENCHMARK_GROUP("sscanf (std)")(Catch::Benchmark::Groupometer meter)
		{
			char buffer[1 + 3 + 1] = {'-', '1', '1', '1'};
			buffer[1 + meter.size()] = '\0';

			meter.measure([&](int)
			{
				static_assert(sizeof(signed char) == sizeof(fio::sint8), "");

				signed char val;
				std::sscanf(buffer + 0, "%hhd", &val);
				return val;
			});
		};

#if (__cplusplus >= 201703L) || (defined(_MSVC_LANG) && _MSVC_LANG >= 201703L)
		BENCHMARK_GROUP("from\\_chars (std)")(Catch::Benchmark::Groupometer meter)
		{
			char buffer[1 + 3 + 1] = {'-', '1', '1', '1'};
			buffer[1 + meter.size()] = '\0';

			meter.measure([&](int)
			{
				fio::sint8 val;
				std::from_chars(buffer + 0, buffer + 1 + meter.size(), val);
				return val;
			});
		};
#endif

#if defined(_MSC_VER)
		BENCHMARK_GROUP("\\_atoi64 (win32)")(Catch::Benchmark::Groupometer meter)
		{
			char buffer[1 + 3 + 1] = {'-', '1', '1', '1'};
			buffer[1 + meter.size()] = '\0';

			meter.measure([&](int)
			{
				return static_cast<fio::sint8>(::_atoi64(buffer + 0));
			});
		};
#endif

#if HAVE_EASTDC
		BENCHMARK_GROUP("Sscanf (eastdc)")(Catch::Benchmark::Groupometer meter)
		{
			char buffer[1 + 5 + 1] = {'-', '1', '1', '1'};
			buffer[1 + meter.size()] = '\0';

			meter.measure([&](int)
			{
				fio::sint8 val;
				EA::StdC::Sscanf(buffer + 0, "%I8d", &val);
				return val;
			});
		};
#endif

		BENCHMARK_GROUP("from\\_chars")(Catch::Benchmark::Groupometer meter)
		{
			char buffer[1 + 5 + 1] = {'-', '1', '1', '1'};
			buffer[1 + meter.size()] = '\0';

			meter.measure([&](int)
			{
				fio::sint8 val;
				fio::from_chars(buffer + 0, buffer + 1 + meter.size(), val);
				return val;
			});
		};
	}
}

TEST_CASE("from_chars uint8", "[.][dump]")
{
	BENCHMARK_DUMP("plot/from_chars_uint8.dump", lin_style, 1, 4, 1, "#digits")
	{
		BENCHMARK_GROUP("sscanf (std)")(Catch::Benchmark::Groupometer meter)
		{
			char buffer[3 + 1] = {'1', '1', '1'};
			buffer[meter.size()] = '\0';

			meter.measure([&](int)
			{
				static_assert(sizeof(unsigned char) == sizeof(fio::uint8), "");

				unsigned char val;
				std::sscanf(buffer + 0, "%hhu", &val);
				return val;
			});
		};

#if (__cplusplus >= 201703L) || (defined(_MSVC_LANG) && _MSVC_LANG >= 201703L)
		BENCHMARK_GROUP("from\\_chars (std)")(Catch::Benchmark::Groupometer meter)
		{
			char buffer[3 + 1] = {'1', '1', '1'};
			buffer[meter.size()] = '\0';

			meter.measure([&](int)
			{
				fio::uint8 val;
				std::from_chars(buffer + 0, buffer + meter.size(), val);
				return val;
			});
		};
#endif

#if defined(_MSC_VER)
		BENCHMARK_GROUP("\\_atoi64 (win32)")(Catch::Benchmark::Groupometer meter)
		{
			char buffer[3 + 1] = {'1', '1', '1'};
			buffer[meter.size()] = '\0';

			meter.measure([&](int)
			{
				return static_cast<fio::uint8>(::_atoi64(buffer + 0));
			});
		};
#endif

#if HAVE_EASTDC
		BENCHMARK_GROUP("Sscanf (eastdc)")(Catch::Benchmark::Groupometer meter)
		{
			char buffer[3 + 1] = {'1', '1', '1'};
			buffer[meter.size()] = '\0';

			meter.measure([&](int)
			{
				fio::uint8 val;
				EA::StdC::Sscanf(buffer + 0, "%I8u", &val);
				return val;
			});
		};
#endif

		BENCHMARK_GROUP("from\\_chars")(Catch::Benchmark::Groupometer meter)
		{
			char buffer[3 + 1] = {'1', '1', '1'};
			buffer[meter.size()] = '\0';

			meter.measure([&](int)
			{
				fio::uint8 val;
				fio::from_chars(buffer + 0, buffer + meter.size(), val);
				return val;
			});
		};
	}
}

TEST_CASE("from_chars sint16", "[.][dump]")
{
	BENCHMARK_DUMP("plot/from_chars_sint16.dump", lin_style, 1, 6, 1, "#digits")
	{
		BENCHMARK_GROUP("sscanf (std)")(Catch::Benchmark::Groupometer meter)
		{
			char buffer[1 + 5 + 1] = {'-', '1', '1', '1', '1', '1'};
			buffer[1 + meter.size()] = '\0';

			meter.measure([&](int)
			{
				static_assert(sizeof(signed short) == sizeof(fio::sint16), "");

				signed short val;
				std::sscanf(buffer + 0, "%hd", &val);
				return val;
			});
		};

#if (__cplusplus >= 201703L) || (defined(_MSVC_LANG) && _MSVC_LANG >= 201703L)
		BENCHMARK_GROUP("from\\_chars (std)")(Catch::Benchmark::Groupometer meter)
		{
			char buffer[1 + 5 + 1] = {'-', '1', '1', '1', '1', '1'};
			buffer[1 + meter.size()] = '\0';

			meter.measure([&](int)
			{
				fio::sint16 val;
				std::from_chars(buffer + 0, buffer + 1 + meter.size(), val);
				return val;
			});
		};
#endif

#if defined(_MSC_VER)
		BENCHMARK_GROUP("\\_atoi64 (win32)")(Catch::Benchmark::Groupometer meter)
		{
			char buffer[1 + 5 + 1] = {'-', '1', '1', '1', '1', '1'};
			buffer[1 + meter.size()] = '\0';

			meter.measure([&](int)
			{
				return static_cast<fio::sint16>(::_atoi64(buffer + 0));
			});
		};
#endif

#if HAVE_EASTDC
		BENCHMARK_GROUP("Sscanf (eastdc)")(Catch::Benchmark::Groupometer meter)
		{
			char buffer[1 + 5 + 1] = {'-', '1', '1', '1', '1', '1'};
			buffer[1 + meter.size()] = '\0';

			meter.measure([&](int)
			{
				fio::sint16 val;
				EA::StdC::Sscanf(buffer + 0, "%I16d", &val);
				return val;
			});
		};
#endif

		BENCHMARK_GROUP("from\\_chars")(Catch::Benchmark::Groupometer meter)
		{
			char buffer[1 + 5 + 1] = {'-', '1', '1', '1', '1', '1'};
			buffer[1 + meter.size()] = '\0';

			meter.measure([&](int)
			{
				fio::sint16 val;
				fio::from_chars(buffer + 0, buffer + 1 + meter.size(), val);
				return val;
			});
		};
	}
}

TEST_CASE("from_chars uint16", "[.][dump]")
{
	BENCHMARK_DUMP("plot/from_chars_uint16.dump", lin_style, 1, 6, 1, "#digits")
	{
		BENCHMARK_GROUP("sscanf (std)")(Catch::Benchmark::Groupometer meter)
		{
			char buffer[5 + 1] = {'1', '1', '1', '1', '1'};
			buffer[meter.size()] = '\0';

			meter.measure([&](int)
			{
				static_assert(sizeof(unsigned short) == sizeof(fio::uint16), "");

				unsigned short val;
				std::sscanf(buffer + 0, "%hu", &val);
				return val;
			});
		};

#if (__cplusplus >= 201703L) || (defined(_MSVC_LANG) && _MSVC_LANG >= 201703L)
		BENCHMARK_GROUP("from\\_chars (std)")(Catch::Benchmark::Groupometer meter)
		{
			char buffer[5 + 1] = {'1', '1', '1', '1', '1'};
			buffer[meter.size()] = '\0';

			meter.measure([&](int)
			{
				fio::uint16 val;
				std::from_chars(buffer + 0, buffer + meter.size(), val);
				return val;
			});
		};
#endif

#if defined(_MSC_VER)
		BENCHMARK_GROUP("\\_atoi64 (win32)")(Catch::Benchmark::Groupometer meter)
		{
			char buffer[5 + 1] = {'1', '1', '1', '1', '1'};
			buffer[meter.size()] = '\0';

			meter.measure([&](int)
			{
				return static_cast<fio::uint16>(::_atoi64(buffer + 0));
			});
		};
#endif

#if HAVE_EASTDC
		BENCHMARK_GROUP("Sscanf (eastdc)")(Catch::Benchmark::Groupometer meter)
		{
			char buffer[5 + 1] = {'1', '1', '1', '1', '1'};
			buffer[meter.size()] = '\0';

			meter.measure([&](int)
			{
				fio::uint16 val;
				EA::StdC::Sscanf(buffer + 0, "%I16u", &val);
				return val;
			});
		};
#endif

		BENCHMARK_GROUP("from\\_chars")(Catch::Benchmark::Groupometer meter)
		{
			char buffer[5 + 1] = {'1', '1', '1', '1', '1'};
			buffer[meter.size()] = '\0';

			meter.measure([&](int)
			{
				fio::uint16 val;
				fio::from_chars(buffer + 0, buffer + meter.size(), val);
				return val;
			});
		};
	}
}

TEST_CASE("from_chars sint32", "[.][dump]")
{
	BENCHMARK_DUMP("plot/from_chars_sint32.dump", lin_style, 1, 11, 1, "#digits")
	{
		BENCHMARK_GROUP("sscanf (std)")(Catch::Benchmark::Groupometer meter)
		{
			char buffer[1 + 10 + 1] = {'-', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1'};
			buffer[1 + meter.size()] = '\0';

			meter.measure([&](int)
			{
				static_assert(sizeof(signed int) == sizeof(fio::sint32), "");

				signed int val;
				std::sscanf(buffer + 0, "%d", &val);
				return val;
			});
		};

#if (__cplusplus >= 201703L) || (defined(_MSVC_LANG) && _MSVC_LANG >= 201703L)
		BENCHMARK_GROUP("from\\_chars (std)")(Catch::Benchmark::Groupometer meter)
		{
			char buffer[1 + 10 + 1] = {'-', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1'};
			buffer[1 + meter.size()] = '\0';

			meter.measure([&](int)
			{
				fio::sint32 val;
				std::from_chars(buffer + 0, buffer + 1 + meter.size(), val);
				return val;
			});
		};
#endif

#if defined(_MSC_VER)
		BENCHMARK_GROUP("\\_atoi64 (win32)")(Catch::Benchmark::Groupometer meter)
		{
			char buffer[1 + 10 + 1] = {'-', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1'};
			buffer[1 + meter.size()] = '\0';

			meter.measure([&](int)
			{
				return static_cast<fio::sint32>(::_atoi64(buffer + 0));
			});
		};
#endif

#if HAVE_EASTDC
		BENCHMARK_GROUP("Sscanf (eastdc)")(Catch::Benchmark::Groupometer meter)
		{
			char buffer[1 + 10 + 1] = {'-', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1'};
			buffer[1 + meter.size()] = '\0';

			meter.measure([&](int)
			{
				fio::sint32 val;
				EA::StdC::Sscanf(buffer + 0, "%I32d", &val);
				return val;
			});
		};
#endif

		BENCHMARK_GROUP("from\\_chars")(Catch::Benchmark::Groupometer meter)
		{
			char buffer[1 + 10 + 1] = {'-', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1'};
			buffer[1 + meter.size()] = '\0';

			meter.measure([&](int)
			{
				fio::sint32 val;
				fio::from_chars(buffer + 0, buffer + 1 + meter.size(), val);
				return val;
			});
		};
	}
}

TEST_CASE("from_chars uint32", "[.][dump]")
{
	BENCHMARK_DUMP("plot/from_chars_uint32.dump", lin_style, 1, 11, 1, "#digits")
	{
		BENCHMARK_GROUP("sscanf (std)")(Catch::Benchmark::Groupometer meter)
		{
			char buffer[10 + 1] = {'1', '1', '1', '1', '1', '1', '1', '1', '1', '1'};
			buffer[meter.size()] = '\0';

			meter.measure([&](int)
			{
				static_assert(sizeof(unsigned int) == sizeof(fio::uint32), "");

				unsigned int val;
				std::sscanf(buffer + 0, "%u", &val);
				return val;
			});
		};

#if (__cplusplus >= 201703L) || (defined(_MSVC_LANG) && _MSVC_LANG >= 201703L)
		BENCHMARK_GROUP("from\\_chars (std)")(Catch::Benchmark::Groupometer meter)
		{
			char buffer[10 + 1] = {'1', '1', '1', '1', '1', '1', '1', '1', '1', '1'};
			buffer[meter.size()] = '\0';

			meter.measure([&](int)
			{
				fio::uint32 val;
				std::from_chars(buffer + 0, buffer + meter.size(), val);
				return val;
			});
		};
#endif

#if defined(_MSC_VER)
		BENCHMARK_GROUP("\\_atoi64 (win32)")(Catch::Benchmark::Groupometer meter)
		{
			char buffer[10 + 1] = {'1', '1', '1', '1', '1', '1', '1', '1', '1', '1'};
			buffer[meter.size()] = '\0';

			meter.measure([&](int)
			{
				return static_cast<fio::uint32>(::_atoi64(buffer + 0));
			});
		};
#endif

#if HAVE_EASTDC
		BENCHMARK_GROUP("Sscanf (eastdc)")(Catch::Benchmark::Groupometer meter)
		{
			char buffer[10 + 1] = {'1', '1', '1', '1', '1', '1', '1', '1', '1', '1'};
			buffer[meter.size()] = '\0';

			meter.measure([&](int)
			{
				fio::uint32 val;
				EA::StdC::Sscanf(buffer + 0, "%I32u", &val);
				return val;
			});
		};
#endif

		BENCHMARK_GROUP("from\\_chars")(Catch::Benchmark::Groupometer meter)
		{
			char buffer[10 + 1] = {'1', '1', '1', '1', '1', '1', '1', '1', '1', '1'};
			buffer[meter.size()] = '\0';

			meter.measure([&](int)
			{
				fio::uint32 val;
				fio::from_chars(buffer + 0, buffer + meter.size(), val);
				return val;
			});
		};
	}
}

TEST_CASE("from_chars sint64", "[.][dump]")
{
	BENCHMARK_DUMP("plot/from_chars_sint64.dump", lin_style, 1, 20, 1, "#digits")
	{
		BENCHMARK_GROUP("sscanf (std)")(Catch::Benchmark::Groupometer meter)
		{
			char buffer[1 + 19 + 1] = {'-', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1'};
			buffer[1 + meter.size()] = '\0';

			meter.measure([&](int)
			{
				static_assert(sizeof(signed long long) == sizeof(fio::sint64), "");

				signed long long val;
				std::sscanf(buffer + 0, "%lld", &val);
				return val;
			});
		};

#if (__cplusplus >= 201703L) || (defined(_MSVC_LANG) && _MSVC_LANG >= 201703L)
		BENCHMARK_GROUP("from\\_chars (std)")(Catch::Benchmark::Groupometer meter)
		{
			char buffer[1 + 19 + 1] = {'-', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1'};
			buffer[1 + meter.size()] = '\0';

			meter.measure([&](int)
			{
				fio::sint64 val;
				std::from_chars(buffer + 0, buffer + 1 + meter.size(), val);
				return val;
			});
		};
#endif

#if defined(_MSC_VER)
		BENCHMARK_GROUP("\\_atoi64 (win32)")(Catch::Benchmark::Groupometer meter)
		{
			char buffer[1 + 19 + 1] = {'-', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1'};
			buffer[1 + meter.size()] = '\0';

			meter.measure([&](int)
			{
				return static_cast<fio::sint64>(::_atoi64(buffer + 0));
			});
		};
#endif

#if HAVE_EASTDC
		BENCHMARK_GROUP("Sscanf (eastdc)")(Catch::Benchmark::Groupometer meter)
		{
			char buffer[1 + 19 + 1] = {'-', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1'};
			buffer[1 + meter.size()] = '\0';

			meter.measure([&](int)
			{
				fio::sint64 val;
				EA::StdC::Sscanf(buffer + 0, "%I64d", &val);
				return val;
			});
		};
#endif

		BENCHMARK_GROUP("from\\_chars")(Catch::Benchmark::Groupometer meter)
		{
			char buffer[1 + 19 + 1] = {'-', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1'};
			buffer[1 + meter.size()] = '\0';

			meter.measure([&](int)
			{
				fio::sint64 val;
				fio::from_chars(buffer + 0, buffer + 1 + meter.size(), val);
				return val;
			});
		};
	}
}

TEST_CASE("from_chars uint64", "[.][dump]")
{
	BENCHMARK_DUMP("plot/from_chars_uint64.dump", lin_style, 1, 21, 1, "#digits")
	{
		BENCHMARK_GROUP("sscanf (std)")(Catch::Benchmark::Groupometer meter)
		{
			char buffer[20 + 1] = {'1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1'};
			buffer[meter.size()] = '\0';

			meter.measure([&](int)
			{
				static_assert(sizeof(unsigned long long) == sizeof(fio::uint64), "");

				unsigned long long val;
				std::sscanf(buffer + 0, "%llu", &val);
				return val;
			});
		};

#if (__cplusplus >= 201703L) || (defined(_MSVC_LANG) && _MSVC_LANG >= 201703L)
		BENCHMARK_GROUP("from\\_chars (std)")(Catch::Benchmark::Groupometer meter)
		{
			char buffer[20 + 1] = {'1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1'};
			buffer[meter.size()] = '\0';

			meter.measure([&](int)
			{
				fio::uint64 val;
				std::from_chars(buffer + 0, buffer + meter.size(), val);
				return val;
			});
		};
#endif

#if HAVE_EASTDC
		BENCHMARK_GROUP("Sscanf (eastdc)")(Catch::Benchmark::Groupometer meter)
		{
			char buffer[20 + 1] = {'1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1'};
			buffer[meter.size()] = '\0';

			meter.measure([&](int)
			{
				fio::uint64 val;
				EA::StdC::Sscanf(buffer + 0, "%I64u", &val);
				return val;
			});
		};
#endif

		BENCHMARK_GROUP("from\\_chars")(Catch::Benchmark::Groupometer meter)
		{
			char buffer[20 + 1] = {'1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1'};
			buffer[meter.size()] = '\0';

			meter.measure([&](int)
			{
				fio::uint64 val;
				fio::from_chars(buffer + 0, buffer + meter.size(), val);
				return val;
			});
		};
	}
}

namespace
{
	namespace detail
	{
		fio_target("sse4.1")
		void extract_integer_8(const char * end, fio::uint32 & val)
		{
			const __m128i line = _mm_loadu_si64(end - 8);

			const __m128i digits = _mm_sub_epi8(line, _mm_set1_epi8('0'));

			const __m128i digits_abcd = _mm_shuffle_epi8(digits, _mm_set_epi8(-1, -1, -1, 3, -1, -1, -1, 2, -1, -1, -1, 1, -1, -1, -1, 0));
			const __m128i digits_efgh = _mm_shuffle_epi8(digits, _mm_set_epi8(-1, -1, -1, 7, -1, -1, -1, 6, -1, -1, -1, 5, -1, -1, -1, 4));

			// todo can it be done faster?
			const __m128i digits_abcd_mul = _mm_mullo_epi32(digits_abcd, _mm_set_epi32(10000, 100000, 1000000, 10000000));
			const __m128i digits_efgh_mul = _mm_mullo_epi32(digits_efgh, _mm_set_epi32(1, 10, 100, 1000));

			const __m128i digits_add1 = _mm_add_epi32(digits_abcd_mul, digits_efgh_mul);
			const __m128i digits_add2 = _mm_add_epi32(digits_add1, _mm_srli_si128(digits_add1, 8));
			const __m128i digits_add3 = _mm_add_epi32(digits_add2, _mm_srli_si128(digits_add2, 4));

			val = _mm_cvtsi128_si32(digits_add3);
		}

		fio_target("ssse3")
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

			val = _mm_cvtsi128_si64x(sum);
		}

		fio_target("ssse3")
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

			valhi = _mm_cvtsi128_si64x(sum);
			vallo = _mm_cvtsi128_si64x(_mm_srli_si128(sum, 8));
		}

		fio_target("ssse3")
		void extract_integer_40(const char * end, fio::uint64 & valhi, fio::uint32 & valmi, fio::uint64 & vallo)
		{
			extract_integer_8(end - 16, valmi);

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

			valhi = _mm_cvtsi128_si64x(sum);
			vallo = _mm_cvtsi128_si64x(_mm_srli_si128(sum, 8));
		}

		fio::uint32 extract_integer_bits_8(const char * first, fio::usize count)
		{
			fio::uint32 val;
			extract_integer_8(first + count, val); // end, out

			return val;
		}

		fio::uint32 extract_integer_bits_16(const char * first, fio::usize count)
		{
			fio::uint64 val;
			extract_integer_16(first + count, val); // end, out

			unsigned long index;
			_BitScanReverse64(&index, val);

			const unsigned int exp = 127 + index - 1; // the one is added back again as the 25th bit of the mantissa

			const unsigned long long bits = (exp << 24) + (val >> (index - 24));

			const unsigned long long rounded = bits + 1; // note may overflow into exponent
			return static_cast<fio::uint32>(rounded >> 1);
		}

		fio::uint32 extract_integer_bits_32(const char * first, fio::usize count)
		{
			fio::uint64 valx;
			fio::uint64 valy;
			extract_integer_32(first + count, valy, valx); // end, out

			unsigned long long yhi;
			unsigned long long ylo = _umul128(valy, 10000000000000000, &yhi);

			unsigned long long sumlo;
			unsigned char carry = _addcarry_u64(0, ylo, valx, &sumlo);
			unsigned long long sumhi;
			carry = _addcarry_u64(carry, yhi, 0, &sumhi);

			if (sumhi != 0)
			{
				unsigned long index; // at mmost 106-64=42
				_BitScanReverse64(&index, sumhi);

				const unsigned int exp = 191 + index;

				const unsigned long long bits = __shiftleft128(__shiftright128(sumlo, sumhi, static_cast<unsigned char>(index)), exp, 24);

				const unsigned long long rounded = bits + 1; // note may overflow into exponent
				return static_cast<fio::uint32>(rounded >> 1);
			}
			else
			{
				unsigned long index;
				_BitScanReverse64(&index, sumlo);

				const unsigned int exp = 127 + index - 1; // the one is added back again as the 25th bit of the mantissa

				const unsigned long long bits = (exp << 24) + (sumlo >> (index - 24));

				const unsigned long long rounded = bits + 1; // note may overflow into exponent
				return static_cast<fio::uint32>(rounded >> 1);
			}
		}

		fio::uint32 extract_integer_bits_40(const char * first, fio::usize count)
		{
			fio::uint64 valx;
			fio::uint32 valy;
			fio::uint64 valz;
			extract_integer_40(first + count, valz, valy, valx); // end, out

			unsigned long long zhi;
			unsigned long long zlo = _umul128(valz, 59604644775390625, &zhi); // 5**24
			unsigned long long yhi;
			unsigned long long ylo = _umul128(valy, 10000000000000000, &yhi);
			unsigned long long xlo = valx;

			if (zhi >= (1ull << (64 - 24)))
				return fio::uint32(-1); // overflow

			unsigned long long hihi = __shiftleft128(zlo, zhi, 24);
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
				return fio::uint32(-1); // overflow

			unsigned long index; // at least 26
			_BitScanReverse64(&index, hi);

			const unsigned int exp = 191 + index - 1; // the one is added back again as the 25th bit of the mantissa

			const unsigned long long bits = (exp << 24) + (hi >> (index - 24));

			const unsigned long long rounded = bits + 1; // note may overflow into exponent
			return static_cast<fio::uint32>(rounded >> 1);
		}

		fio::uint64 extract_decimal_bits_24(const char * first, fio::usize count)
		{
			fio_unused(count);

			fio::uint64 valx;
			fio::uint64 valy;
			extract_integer_32(first + 24, valy, valx); // end, out, out

			// 24: yyyyyyyyxxxxxxxxxxxxxxxx // (5**24)
			// (yyyyyyyy * (10**16) + xxxxxxxxxxxxxxxx) // (5**24)
			// (yyyyyyyy * (2**16) * (5**16) + xxxxxxxxxxxxxxxx) // (5**24)
			// (yyyyyyyy * (2**16) + xxxxxxxxxxxxxxxx // (5**16)) // (5**8)
			//  |43--------------|

			const fio::uint64 x_div_16 = __umulh(valx, 0x39a5652fb1137857) >> 35; // 5**16
			const fio::uint64 sum = (valy << 16) + x_div_16;
			const fio::uint64 sum_div_8 = __umulh(sum, 0xabcc77118461cefd) >> 18; // 5**8
			return sum_div_8 >> (24 - count);
		}

		fio_inline
		void multiply_integer_2(fio::uint64 hi, fio::uint64 lo, const unsigned long long (& denominators)[3], unsigned long long (& results)[7])
		{
			//     x1x0
			//     y1y0
			//----------
			//     x0y0
			//   x1y0
			//   x0y1
			// x1y1
			//----------
			//   r2r1r0
			// s2s1s0

			unsigned long long x0y0hi;
			unsigned long long x0y0lo = _umul128(lo, denominators[0], &x0y0hi);
			unsigned long long x1y0hi;
			unsigned long long x1y0lo = _umul128(hi, denominators[0], &x1y0hi);
			unsigned long long x0y1hi;
			unsigned long long x0y1lo = _umul128(lo, denominators[1], &x0y1hi);
			unsigned long long x1y1hi;
			unsigned long long x1y1lo = _umul128(hi, denominators[1], &x1y1hi);

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
		void multiply_integer_3(fio::uint64 hi, fio::uint64 mi, fio::uint64 lo, const unsigned long long (& denominators)[3], unsigned long long (& results)[7])
		{
			//       x2x1x0
			//       y2y1y0
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
			unsigned long long x0y0lo = _umul128(lo, denominators[0], &x0y0hi);
			unsigned long long x1y0hi;
			unsigned long long x1y0lo = _umul128(mi, denominators[0], &x1y0hi);
			unsigned long long x2y0hi;
			unsigned long long x2y0lo = _umul128(hi, denominators[0], &x2y0hi);
			unsigned long long x0y1hi;
			unsigned long long x0y1lo = _umul128(lo, denominators[1], &x0y1hi);
			unsigned long long x1y1hi;
			unsigned long long x1y1lo = _umul128(mi, denominators[1], &x1y1hi);
			unsigned long long x2y1hi;
			unsigned long long x2y1lo = _umul128(hi, denominators[1], &x2y1hi);
			unsigned long long x0y2hi;
			unsigned long long x0y2lo = _umul128(lo, denominators[2], &x0y2hi);
			unsigned long long x1y2hi;
			unsigned long long x1y2lo = _umul128(mi, denominators[2], &x1y2hi);
			unsigned long long x2y2hi;
			unsigned long long x2y2lo = _umul128(hi, denominators[2], &x2y2hi);

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
			//__assume(carry == 0); // since t3 must be zero this must hold??????????
			if (!fio_expect(carry == 0))
			{
				carry = 0;
			}
			carry = _addcarry_u64(carry, results[2], t0, results + 2);
			carry = _addcarry_u64(carry, results[3], t1, results + 3);
			carry = _addcarry_u64(carry, results[4], t2, results + 4);
			carry = _addcarry_u64(carry, 0, t3, results + 5);
		}

		fio::uint32 float_bits(const char * first, const char * dot, const char * last)
		{
			constexpr const int offset = 32;
			alignas(16) char buffer[128];

			const auto n_integers = dot - first;
			if (n_integers > 0)
			{
				if (n_integers >= 40)
				{
					return 0; // todo
				}
				else if (n_integers > 32)
				{
					_mm_store_si128(reinterpret_cast<__m128i *>(buffer + 16), _mm_set1_epi8('0')); // todo 8 suffice

					fio::memcpy(first, buffer + offset, n_integers);

					return extract_integer_bits_40(buffer + offset, n_integers); // beg, n
				}
				else if (n_integers > 16)
				{
					_mm_store_si128(reinterpret_cast<__m128i *>(buffer + 16), _mm_set1_epi8('0'));

					fio::memcpy(first, buffer + offset, n_integers);

					return extract_integer_bits_32(buffer + offset, n_integers); // beg, n
				}
				else if (n_integers > 8)
				{
					_mm_store_si128(reinterpret_cast<__m128i *>(buffer + 16), _mm_set1_epi8('0')); // todo 8 suffice

					fio::memcpy(first, buffer + offset, n_integers);

					return extract_integer_bits_16(buffer + offset, n_integers); // beg, n
				}
				else
				{
					// todo fewer?
					_mm_store_si128(reinterpret_cast<__m128i *>(buffer + 0), _mm_set1_epi8('0'));
					_mm_store_si128(reinterpret_cast<__m128i *>(buffer + 16), _mm_set1_epi8('0'));

					fio::memcpy(first, buffer + offset, n_integers);

					fio::uint64 bits = extract_integer_bits_8(buffer + offset, n_integers); // beg, n

					unsigned long index;
					_BitScanReverse64(&index, bits);

					const unsigned int exp = 127 + index - 1; // the one is added back again as the 25th bit of the mantissa

					const int more = 24 - index;
					if (more > 0)
					{
						const unsigned int available = more; // todo assume there is always the correct amount available
						fio::memcpy(dot + 1, buffer + 8, available);

						const fio::uint64 more_bits = extract_decimal_bits_24(buffer + 8, more); // beg, n

						bits = (exp << 24) + ((bits << more) | more_bits);
					}
					else
					{
						bits = (exp << 24) + (bits >> (index - 24));
					}

					const unsigned long long rounded = bits + 1; // note may overflow into exponent
					return static_cast<unsigned int>(rounded >> 1);
				}
			}
			else
			{
				const auto n_zeroes = -n_integers - 1;
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

					static const fio::uint8 required_digits[46] = {
						28, 30, 32, 35, 37, 39, 42, 44, 46, 49, 51, 53, 56, 58, 60, 63, 65, 67, 70, 72, 74, 77, 79, 81, 84, 86, 88, 91, 93, 95, 97, 100, 102, 104, 107, 109, 111, 113, 112, 111, 110, 109, 108, 107, 106, 105,
					};

					const fio::usize available = static_cast<fio::usize>(last - first);
					const fio::usize count = available < required_digits[n_zeroes] ? available : required_digits[n_zeroes];
					fio::memcpy(first, buffer + 128 - required_digits[n_zeroes], count);

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
						{ {16225927682921337, 0, 0}, {16481947188333068751, 36, 0}, {1}, {1}, {1}, {1}, {1}, {1}, },
						{ {16225927682921337, 0, 0}, {7591182125049451957, 14, 0}, {1152921504607, 0, 0}, {1}, {1}, {1}, {1}, {1}, },
						{ {16225927682921337, 0, 0}, {7591182125049451957, 14, 0}, {604462909807315, 0, 0}, {1}, {1}, {1}, {1}, {1}, },
						{ {16225927682921337, 0, 0}, {7591182125049451957, 14, 0}, {39614081257132169, 0, 0}, {1}, {1}, {1}, {1}, {1}, },
						{ {16225927682921337, 0, 0}, {7591182125049451957, 14, 0}, {14783955820913345207, 1, 0}, {1}, {1}, {1}, {1}, {1}, },
						{ {16225927682921337, 0, 0}, {7591182125049451957, 14, 0}, {545673798139537739, 59, 0}, {1}, {1}, {1}, {1}, {1}, },
						{ {16225927682921337, 0, 0}, {7591182125049451957, 14, 0}, {9241489220749011347, 30948, 0}, {1}, {1}, {1}, {1}, {1}, },
						{ {16225927682921337, 0, 0}, {7591182125049451957, 14, 0}, {5979391860423864507, 236118, 0}, {1934281311383407, 0, 0}, {1}, {1}, {1}, {1}, },
						{ {16225927682921337, 0, 0}, {7591182125049451957, 14, 0}, {5979391860423864507, 236118, 0}, {253530120045645881, 0, 0}, {1}, {1}, {1}, {1}, },
						{ {16225927682921337, 0, 0}, {7591182125049451957, 14, 0}, {5979391860423864507, 236118, 0}, {14783955820913345207, 1, 0}, {1}, {1}, {1}, {1}, },
						{ {16225927682921337, 0, 0}, {7591182125049451957, 14, 0}, {5979391860423864507, 236118, 0}, {16503551413014162057, 188, 0}, {1}, {1}, {1}, {1}, },
						{ {16225927682921337, 0, 0}, {7591182125049451957, 14, 0}, {5979391860423864507, 236118, 0}, {7494647606406928093, 198070, 0}, {1}, {1}, {1}, {1}, },
						{ {16225927682921337, 0, 0}, {7591182125049451957, 14, 0}, {5979391860423864507, 236118, 0}, {2699442461655512651, 12980742, 0}, {1}, {1}, {1}, {1}, },
						{ {16225927682921337, 0, 0}, {7591182125049451957, 14, 0}, {5979391860423864507, 236118, 0}, {8670538443036954087, 10889035741, 0}, {1}, {1}, {1}, {1}, },
						{ {16225927682921337, 0, 0}, {7591182125049451957, 14, 0}, {5979391860423864507, 236118, 0}, {9843675500044451025, 7737125245, 0}, {9762294514781471889, 11, 0}, {1}, {1}, {1}, },
						{ {16225927682921337, 0, 0}, {7591182125049451957, 14, 0}, {5979391860423864507, 236118, 0}, {9843675500044451025, 7737125245, 0}, {16503551413014162057, 188, 0}, {1}, {1}, {1}, },
						{ {16225927682921337, 0, 0}, {7591182125049451957, 14, 0}, {5979391860423864507, 236118, 0}, {9843675500044451025, 7737125245, 0}, {5536128266792618279, 633825, 0}, {1}, {1}, {1}, },
						{ {16225927682921337, 0, 0}, {7591182125049451957, 14, 0}, {5979391860423864507, 236118, 0}, {9843675500044451025, 7737125245, 0}, {8727421805997189671, 166153499, 0}, {1}, {1}, {1}, },
						{ {16225927682921337, 0, 0}, {7591182125049451957, 14, 0}, {5979391860423864507, 236118, 0}, {9843675500044451025, 7737125245, 0}, {8670538443036954087, 10889035741, 0}, {1}, {1}, {1}, },
						{ {16225927682921337, 0, 0}, {7591182125049451957, 14, 0}, {5979391860423864507, 236118, 0}, {9843675500044451025, 7737125245, 0}, {2642288987520351985, 9134385233318, 0}, {1}, {1}, {1}, },
						{ {16225927682921337, 0, 0}, {7591182125049451957, 14, 0}, {5979391860423864507, 236118, 0}, {9843675500044451025, 7737125245, 0}, {15408495767769702249, 598631070650737, 0}, {1}, {1}, {1}, },
						{ {16225927682921337, 0, 0}, {7591182125049451957, 14, 0}, {5979391860423864507, 236118, 0}, {9843675500044451025, 7737125245, 0}, {1564089289045153947, 4056481920730334, 0}, {5536128266792618279, 633825, 0}, {1}, {1}, },
						{ {16225927682921337, 0, 0}, {7591182125049451957, 14, 0}, {5979391860423864507, 236118, 0}, {9843675500044451025, 7737125245, 0}, {1564089289045153947, 4056481920730334, 0}, {2895828445369772503, 265845599, 0}, {1}, {1}, },
						{ {16225927682921337, 0, 0}, {7591182125049451957, 14, 0}, {5979391860423864507, 236118, 0}, {9843675500044451025, 7737125245, 0}, {1564089289045153947, 4056481920730334, 0}, {7529911443791671953, 69689828745, 0}, {1}, {1}, },
						{ {16225927682921337, 0, 0}, {7591182125049451957, 14, 0}, {5979391860423864507, 236118, 0}, {9843675500044451025, 7737125245, 0}, {1564089289045153947, 4056481920730334, 0}, {1321144493760175993, 4567192616659, 0}, {1}, {1}, },
						{ {16225927682921337, 0, 0}, {7591182125049451957, 14, 0}, {5979391860423864507, 236118, 0}, {9843675500044451025, 7737125245, 0}, {1564089289045153947, 4056481920730334, 0}, {2691303730436425989, 3831238852164722, 0}, {1}, {1}, },
						{ {16225927682921337, 0, 0}, {7591182125049451957, 14, 0}, {5979391860423864507, 236118, 0}, {9843675500044451025, 7737125245, 0}, {1564089289045153947, 4056481920730334, 0}, {1971277250102393653, 502168138830934461, 0}, {1}, {1}, },
						{ {16225927682921337, 0, 0}, {7591182125049451957, 14, 0}, {5979391860423864507, 236118, 0}, {9843675500044451025, 7737125245, 0}, {1564089289045153947, 4056481920730334, 0}, {10140024425764638827, 16455045573212060421, 0}, {1}, {1}, },
						{ {16225927682921337, 0, 0}, {7591182125049451957, 14, 0}, {5979391860423864507, 236118, 0}, {9843675500044451025, 7737125245, 0}, {1564089289045153947, 4056481920730334, 0}, {3511393333235066575, 11121167568117138797, 3}, {12988327758750611785, 34844914372, 0}, {1}, },
						{ {16225927682921337, 0, 0}, {7591182125049451957, 14, 0}, {5979391860423864507, 236118, 0}, {9843675500044451025, 7737125245, 0}, {1564089289045153947, 4056481920730334, 0}, {3511393333235066575, 11121167568117138797, 3}, {1076627130581305705, 29230032746618, 0}, {1}, },
						{ {16225927682921337, 0, 0}, {7591182125049451957, 14, 0}, {5979391860423864507, 236118, 0}, {9843675500044451025, 7737125245, 0}, {1564089289045153947, 4056481920730334, 0}, {3511393333235066575, 11121167568117138797, 3}, {2691303730436425989, 3831238852164722, 0}, {1}, },
						{ {16225927682921337, 0, 0}, {7591182125049451957, 14, 0}, {5979391860423864507, 236118, 0}, {9843675500044451025, 7737125245, 0}, {1564089289045153947, 4056481920730334, 0}, {3511393333235066575, 11121167568117138797, 3}, {1971277250102393653, 502168138830934461, 0}, {1}, },
						{ {16225927682921337, 0, 0}, {7591182125049451957, 14, 0}, {5979391860423864507, 236118, 0}, {9843675500044451025, 7737125245, 0}, {1564089289045153947, 4056481920730334, 0}, {3511393333235066575, 11121167568117138797, 3}, {15422499392788156965, 7710398526309305619, 11}, {1}, },
						{ {16225927682921337, 0, 0}, {7591182125049451957, 14, 0}, {5979391860423864507, 236118, 0}, {9843675500044451025, 7737125245, 0}, {1564089289045153947, 4056481920730334, 0}, {3511393333235066575, 11121167568117138797, 3}, {865119391821669287, 2865761711822312790, 2993}, {1}, },
						{ {16225927682921337, 0, 0}, {7591182125049451957, 14, 0}, {5979391860423864507, 236118, 0}, {9843675500044451025, 7737125245, 0}, {1564089289045153947, 4056481920730334, 0}, {3511393333235066575, 11121167568117138797, 3}, {5193155008627850229, 7917911339171543649, 196159}, {1}, },
						{ {16225927682921337, 0, 0}, {7591182125049451957, 14, 0}, {5979391860423864507, 236118, 0}, {9843675500044451025, 7737125245, 0}, {1564089289045153947, 4056481920730334, 0}, {3511393333235066575, 11121167568117138797, 3}, {16611413540376147735, 5470823367985906411, 944473}, {2691303730436425989, 3831238852164722, 0}, },
						{ {16225927682921337, 0, 0}, {7591182125049451957, 14, 0}, {5979391860423864507, 236118, 0}, {9843675500044451025, 7737125245, 0}, {1564089289045153947, 4056481920730334, 0}, {3511393333235066575, 11121167568117138797, 3}, {1496253268323035203, 408217133286861182, 803469}, {1}, },
						{ {16225927682921337, 0, 0}, {7591182125049451957, 14, 0}, {5979391860423864507, 236118, 0}, {9843675500044451025, 7737125245, 0}, {1564089289045153947, 4056481920730334, 0}, {3511393333235066575, 11121167568117138797, 3}, {9597435353935534609, 4713740301749103199, 200867}, {1}, },
						{ {16225927682921337, 0, 0}, {7591182125049451957, 14, 0}, {5979391860423864507, 236118, 0}, {9843675500044451025, 7737125245, 0}, {1564089289045153947, 4056481920730334, 0}, {3511393333235066575, 11121167568117138797, 3}, {17340580483737799491, 7506746565359719755, 25108}, {1}, },
						{ {16225927682921337, 0, 0}, {7591182125049451957, 14, 0}, {5979391860423864507, 236118, 0}, {9843675500044451025, 7737125245, 0}, {1564089289045153947, 4056481920730334, 0}, {3511393333235066575, 11121167568117138797, 3}, {9085101588108306793, 10161715357524740777, 3138}, {1}, },
						{ {16225927682921337, 0, 0}, {7591182125049451957, 14, 0}, {5979391860423864507, 236118, 0}, {9843675500044451025, 7737125245, 0}, {1564089289045153947, 4056481920730334, 0}, {3511393333235066575, 11121167568117138797, 3}, {10944112390718391959, 2940950219058990250, 196}, {1}, },
						{ {16225927682921337, 0, 0}, {7591182125049451957, 14, 0}, {5979391860423864507, 236118, 0}, {9843675500044451025, 7737125245, 0}, {1564089289045153947, 4056481920730334, 0}, {3511393333235066575, 11121167568117138797, 3}, {5979700067267186899, 9590990814237149589, 24}, {1}, },
						{ {16225927682921337, 0, 0}, {7591182125049451957, 14, 0}, {5979391860423864507, 236118, 0}, {9843675500044451025, 7737125245, 0}, {1564089289045153947, 4056481920730334, 0}, {3511393333235066575, 11121167568117138797, 3}, {12276677554476868123, 1198873851779643698, 3}, {1}, },
						{ {16225927682921337, 0, 0}, {7591182125049451957, 14, 0}, {5979391860423864507, 236118, 0}, {9843675500044451025, 7737125245, 0}, {1564089289045153947, 4056481920730334, 0}, {3511393333235066575, 11121167568117138797, 3}, {10759939715039024913, 1766847064778384329, 0}, {1}, },
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

					unsigned long long g0 = __umulh(valg, 16225927682921337) >> 27; // divide by 5**16

					multiply_integer_2(__shiftleft128(valf, 0, 16), (valf << 16) + g0, denominators[n_zeroes][1], tmps);
					unsigned long long f0 = __shiftright128(tmps[1], tmps[1 + 1], skips[n_zeroes][1][1]);
					if (!fio_expect(tmps[1 + 2] == 0))
						return static_cast<unsigned int>(-1);

					multiply_integer_2(__shiftleft128(vale, 0, 32), (vale << 32) + f0, denominators[n_zeroes][2], tmps);
					unsigned long long e0 = __shiftright128(tmps[skips[n_zeroes][2][0]], tmps[skips[n_zeroes][2][0] + 1], skips[n_zeroes][2][1]);
					if (!fio_expect(tmps[skips[n_zeroes][2][0] + 2] == 0))
						return static_cast<unsigned int>(-1);

					multiply_integer_2(__shiftleft128(vald, 0, 48), (vald << 48) + e0, denominators[n_zeroes][3], tmps);
					unsigned long long d0 = __shiftright128(tmps[skips[n_zeroes][3][0]], tmps[skips[n_zeroes][3][0] + 1], skips[n_zeroes][3][1]);
					if (!fio_expect(tmps[skips[n_zeroes][3][0] + 2] == 0))
						return static_cast<unsigned int>(-1);

					multiply_integer_2(valc, d0, denominators[n_zeroes][4], tmps);
					unsigned long long c0 = __shiftright128(tmps[skips[n_zeroes][4][0]], tmps[skips[n_zeroes][4][0] + 1], skips[n_zeroes][4][1]);
					unsigned long long c1 = tmps[skips[n_zeroes][4][0] + 1] >> skips[n_zeroes][4][1];
					if (!fio_expect(tmps[skips[n_zeroes][4][0] + 2] == 0))
						return static_cast<unsigned int>(-1);

					multiply_integer_3(__shiftleft128(valb, 0, 16), (valb << 16) + c1, c0, denominators[n_zeroes][5], tmps);
					unsigned long long b0 = __shiftright128(tmps[skips[n_zeroes][5][0]], tmps[skips[n_zeroes][5][0] + 1], skips[n_zeroes][5][1]);
					unsigned long long b1 = __shiftright128(tmps[skips[n_zeroes][5][0] + 1], tmps[skips[n_zeroes][5][0] + 2], skips[n_zeroes][5][1]);

					multiply_integer_3(__shiftleft128(vala, 0, 32), (vala << 32) + b1, b0, denominators[n_zeroes][6], tmps);
					unsigned long long a0 = __shiftright128(tmps[skips[n_zeroes][6][0]], tmps[skips[n_zeroes][6][0] + 1], skips[n_zeroes][6][1]);
					unsigned long long a1 = __shiftright128(tmps[skips[n_zeroes][6][0] + 1], tmps[skips[n_zeroes][6][0] + 2], skips[n_zeroes][6][1]);

					tmps[4] = 0;
					tmps[5] = 0;

					multiply_integer_2((valz << 48) + a1, a0, denominators[n_zeroes][7], tmps);
					unsigned long long z0 = __shiftright128(tmps[skips[n_zeroes][7][0]], tmps[skips[n_zeroes][7][0] + 1], skips[n_zeroes][7][1]);

					unsigned long long bits = z0;

					if (bits == 0) // underflow
						return 0;

					unsigned long index;
					_BitScanReverse64(&index, bits);

					if (index >= 24)
					{
						const unsigned int exp_base = 150 - (static_cast<unsigned int>(n_zeroes) + required_digits[n_zeroes]);
						const unsigned int exp = exp_base + (index - 24);

						bits = (exp << 24) + (bits >> (index - 24));

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

		// skip zeroes
		if (*begin == '0')
		{
			do
			{
				begin++;

				if (begin == end)
					return nullptr; // todo value = 0
			}
			while (*begin == '0');
		}

		const char * last;
		const char * dot = begin;
		if (*begin == '.')
		{
			// skip more zeroes
			do
			{
				begin++;

				if (begin == end)
					break;
			}
			while (*begin == '0');

			last = begin;
		}
		else
		{
			// todo change to skip digits
			do
			{
				dot++;

				if (dot == end)
					break;
			}
			while (*dot >= '0' && *dot <= '9');

			last = dot;
		}

		if (last != end)
		{
			// skip to end
			do
			{
				last++;

				if (last == end)
					break;
			}
			while (*last >= '0' && *last <= '9');
		}

		// todo exponent

		fio::uint32 bits = detail::float_bits(begin, dot, last);
		if (is_negative)
		{
			bits |= 0b1'00000000'00000000000000000000000;
		}

		value = *reinterpret_cast<const float *>(&bits);

		return last;
	}
}

#include <iostream>
#include <fstream>
#include <bitset>

TEST_CASE("from_chars float32", "[.][dump]")
{
	char digits[][1 + 2 + 150 + 1] = {
		"00.000000000000000000000000000000000000000000000700649232162408535461864791644958065640130970938257885878534141944895541342930300743319094181060791015625",
		"00.000000000000000000000000000000000000011754944208872107242095900834087248423144721207851846153345402941318314539442813071445925743319094181060791015625",
		"00.00000000000000000000000000000000000002350988841774421448419180166817449684628944241570369230669080588263662907888562614289185148663818836212158203125",
		"00.0000000000000000000000000000000000000470197768354884289683836033363489936925788848314073846133816117652732581577712522857837029732763767242431640625",
		"00.000000000000000000000000000000000000094039553670976857936767206672697987385157769662814769226763223530546516315542504571567405946552753448486328125",
		"00.00000000000000000000000000000000000018807910734195371587353441334539597477031553932562953845352644706109303263108500914313481189310550689697265625",
		"00.0000000000000000000000000000000000003761582146839074317470688266907919495406310786512590769070528941221860652621700182862696237862110137939453125",
		"00.000000000000000000000000000000000000752316429367814863494137653381583899081262157302518153814105788244372130524340036572539247572422027587890625",
		"00.00000000000000000000000000000000000150463285873562972698827530676316779816252431460503630762821157648874426104868007314507849514484405517578125",
		"00.0000000000000000000000000000000000030092657174712594539765506135263355963250486292100726152564231529774885220973601462901569902896881103515625",
		"00.000000000000000000000000000000000006018531434942518907953101227052671192650097258420145230512846305954977044194720292580313980579376220703125",
		"00.00000000000000000000000000000000001203706286988503781590620245410534238530019451684029046102569261190995408838944058516062796115875244140625",
		"00.0000000000000000000000000000000000240741257397700756318124049082106847706003890336805809220513852238199081767788811703212559223175048828125",
		"00.000000000000000000000000000000000048148251479540151263624809816421369541200778067361161844102770447639816353557762340642511844635009765625",
		"00.00000000000000000000000000000000009629650295908030252724961963284273908240155613472232368820554089527963270711552468128502368927001953125",
		"00.0000000000000000000000000000000001925930059181606050544992392656854781648031122694446473764110817905592654142310493625700473785400390625",
		"00.000000000000000000000000000000000385186011836321210108998478531370956329606224538889294752822163581118530828462098725140094757080078125",
		"00.00000000000000000000000000000000077037202367264242021799695706274191265921244907777858950564432716223706165692419745028018951416015625",
		"00.0000000000000000000000000000000015407440473452848404359939141254838253184248981555571790112886543244741233138483949005603790283203125",
		"00.000000000000000000000000000000003081488094690569680871987828250967650636849796311114358022577308648948246627696789801120758056640625",
		"00.00000000000000000000000000000000616297618938113936174397565650193530127369959262222871604515461729789649325539357960224151611328125",
		"00.0000000000000000000000000000000123259523787622787234879513130038706025473991852444574320903092345957929865107871592044830322265625",
		"00.000000000000000000000000000000024651904757524557446975902626007741205094798370488914864180618469191585973021574318408966064453125",
		"00.00000000000000000000000000000004930380951504911489395180525201548241018959674097782972836123693838317194604314863681793212890625",
		"00.0000000000000000000000000000000986076190300982297879036105040309648203791934819556594567224738767663438920862972736358642578125",
		"00.000000000000000000000000000000197215238060196459575807221008061929640758386963911318913444947753532687784172594547271728515625",
		"00.00000000000000000000000000000039443047612039291915161444201612385928151677392782263782688989550706537556834518909454345703125",
		"00.0000000000000000000000000000007888609522407858383032288840322477185630335478556452756537797910141307511366903781890869140625",
		"00.000000000000000000000000000001577721904481571676606457768064495437126067095711290551307559582028261502273380756378173828125",
		"00.00000000000000000000000000000315544380896314335321291553612899087425213419142258110261511916405652300454676151275634765625",
		"00.0000000000000000000000000000063108876179262867064258310722579817485042683828451622052302383281130460090935230255126953125",
		"00.000000000000000000000000000012621775235852573412851662144515963497008536765690324410460476656226092018187046051025390625",
		"00.00000000000000000000000000002524355047170514682570332428903192699401707353138064882092095331245218403637409210205078125",
		"00.0000000000000000000000000000504871009434102936514066485780638539880341470627612976418419066249043680727481842041015625",
		"00.000000000000000000000000000100974201886820587302813297156127707976068294125522595283683813249808736145496368408203125",
		"00.00000000000000000000000000020194840377364117460562659431225541595213658825104519056736762649961747229099273681640625",
		"00.0000000000000000000000000004038968075472823492112531886245108319042731765020903811347352529992349445819854736328125",
		"00.000000000000000000000000000807793615094564698422506377249021663808546353004180762269470505998469889163970947265625",
		"00.00000000000000000000000000161558723018912939684501275449804332761709270600836152453894101199693977832794189453125",
		"00.0000000000000000000000000032311744603782587936900255089960866552341854120167230490778820239938795566558837890625",
		"00.000000000000000000000000006462348920756517587380051017992173310468370824033446098155764047987759113311767578125",
		"00.00000000000000000000000001292469784151303517476010203598434662093674164806689219631152809597551822662353515625",
		"00.0000000000000000000000000258493956830260703495202040719686932418734832961337843926230561919510364532470703125",
		"00.000000000000000000000000051698791366052140699040408143937386483746966592267568785246112383902072906494140625",
		"00.00000000000000000000000010339758273210428139808081628787477296749393318453513757049222476780414581298828125",
		"00.0000000000000000000000002067951654642085627961616325757495459349878663690702751409844495356082916259765625",
		"00.000000000000000000000000413590330928417125592323265151499091869975732738140550281968899071216583251953125",
		"00.00000000000000000000000082718066185683425118464653030299818373995146547628110056393779814243316650390625",
		"00.0000000000000000000000016543613237136685023692930606059963674799029309525622011278755962848663330078125",
		"00.000000000000000000000003308722647427337004738586121211992734959805861905124402255751192569732666015625",
		"00.00000000000000000000000661744529485467400947717224242398546991961172381024880451150238513946533203125",
		"00.0000000000000000000000132348905897093480189543444848479709398392234476204976090230047702789306640625",
		"00.000000000000000000000026469781179418696037908688969695941879678446895240995218046009540557861328125",
		"00.00000000000000000000005293956235883739207581737793939188375935689379048199043609201908111572265625",
		"00.0000000000000000000001058791247176747841516347558787837675187137875809639808721840381622314453125",
		"00.000000000000000000000211758249435349568303269511757567535037427575161927961744368076324462890625",
		"00.00000000000000000000042351649887069913660653902351513507007485515032385592348873615264892578125",
		"00.0000000000000000000008470329977413982732130780470302701401497103006477118469774723052978515625",
		"00.000000000000000000001694065995482796546426156094060540280299420601295423693954944610595703125",
		"00.00000000000000000000338813199096559309285231218812108056059884120259084738790988922119140625",
		"00.0000000000000000000067762639819311861857046243762421611211976824051816947758197784423828125",
		"00.000000000000000000013552527963862372371409248752484322242395364810363389551639556884765625",
		"00.00000000000000000002710505592772474474281849750496864448479072962072677910327911376953125",
		"00.0000000000000000000542101118554494894856369950099372889695814592414535582065582275390625",
		"00.000000000000000000108420223710898978971273990019874577939162918482907116413116455078125",
		"00.00000000000000000021684044742179795794254798003974915587832583696581423282623291015625",
		"00.0000000000000000004336808948435959158850959600794983117566516739316284656524658203125",
		"00.000000000000000000867361789687191831770191920158996623513303347863256931304931640625",
		"00.00000000000000000173472357937438366354038384031799324702660669572651386260986328125",
		"00.0000000000000000034694471587487673270807676806359864940532133914530277252197265625",
		"00.000000000000000006938894317497534654161535361271972988106426782906055450439453125",
		"00.00000000000000001387778863499506930832307072254394597621285356581211090087890625",
		"00.0000000000000000277555772699901386166461414450878919524257071316242218017578125",
		"00.000000000000000055511154539980277233292282890175783904851414263248443603515625",
		"00.00000000000000011102230907996055446658456578035156780970282852649688720703125",
		"00.0000000000000002220446181599211089331691315607031356194056570529937744140625",
		"00.000000000000000444089236319842217866338263121406271238811314105987548828125",
		"00.00000000000000088817847263968443573267652624281254247762262821197509765625",
		"00.0000000000000017763569452793688714653530524856250849552452564239501953125",
		"00.000000000000003552713890558737742930706104971250169910490512847900390625",
		"00.00000000000000710542778111747548586141220994250033982098102569580078125",
		"00.0000000000000142108555622349509717228244198850006796419620513916015625",
		"00.000000000000028421711124469901943445648839770001359283924102783203125",
		"00.00000000000005684342224893980388689129767954000271856784820556640625",
		"00.0000000000001136868444978796077737825953590800054371356964111328125",
		"00.000000000000227373688995759215547565190718160010874271392822265625",
		"00.00000000000045474737799151843109513038143632002174854278564453125",
		"00.0000000000009094947559830368621902607628726400434970855712890625",
		"00.000000000001818989511966073724380521525745280086994171142578125",
		"00.00000000000363797902393214744876104305149056017398834228515625",
		"00.0000000000072759580478642948975220861029811203479766845703125",
		"00.000000000014551916095728589795044172205962240695953369140625",
		"00.00000000002910383219145717959008834441192448139190673828125",
		"00.0000000000582076643829143591801766888238489627838134765625",
		"00.000000000116415328765828718360353377647697925567626953125",
		"00.00000000023283065753165743672070675529539585113525390625",
		"00.0000000004656613150633148734414135105907917022705078125",
		"00.000000000931322630126629746882827021181583404541015625",
		"00.00000000186264526025325949376565404236316680908203125",
		"00.0000000037252905205065189875313080847263336181640625",
		"00.000000007450581041013037975062616169452667236328125",
		"00.00000001490116208202607595012523233890533447265625",
		"00.0000000298023241640521519002504646778106689453125",
		"00.000000059604648328104303800500929355621337890625",
		"00.00000011920929665620860760100185871124267578125",
		"00.0000002384185933124172152020037174224853515625",
		"00.000000476837186624834430404007434844970703125",
		"00.00000095367437324966886080801486968994140625",
		"00.0000019073487464993377216160297393798828125",
		"00.000003814697492998675443232059478759765625",
		"00.00000762939498599735088646411895751953125",
		"00.0000152587899719947017729282379150390625",
		"00.000030517579943989403545856475830078125",
		"00.00006103515988797880709171295166015625",
		"00.0001220703197759576141834259033203125",
		"00.000244140639551915228366851806640625",
		"00.00048828127910383045673370361328125",
		"00.0009765625582076609134674072265625",
		"00.001953125116415321826934814453125",
		"00.00390625023283064365386962890625",
		"00.0078125004656612873077392578125",
		"00.015625000931322574615478515625",
		"00.03125000186264514923095703125",
		"00.0625000037252902984619140625",
		"00.125000007450580596923828125",
		"00.25000001490116119384765625",
		"00.5000000298023223876953125",
		"01.000000059604644775390625",
		"02.00000011920928955078125",
		"04.0000002384185791015625",
		"08.000000476837158203125",
		"016.00000095367431640625",
		"032.0000019073486328125",
		"064.000003814697265625",
		"0128.00000762939453125",
		"0256.0000152587890625",
		"0512.000030517578125",
		"01024.00006103515625",
		"02048.0001220703125",
		"04096.000244140625",
		"08192.00048828125",
		"016384.0009765625",
		"032768.001953125",
		"065536.00390625",
		"0131072.0078125",
		"0262144.015625",
		"0524288.03125",
		"01048576.0625",
		"02097152.125",
		"04194304.25",
		"08388608.5",
		"016777217.",
		"033554434.",
		"067108868.",
		"0134217736.",
		"0268435472.",
		"0536870944.",
		"01073741888.",
		"02147483776.",
		"04294967552.",
		"08589935104.",
		"017179870208.",
		"034359740416.",
		"068719480832.",
		"0137438961664.",
		"0274877923328.",
		"0549755846656.",
		"01099511693312.",
		"02199023386624.",
		"04398046773248.",
		"08796093546496.",
		"017592187092992.",
		"035184374185984.",
		"070368748371968.",
		"0140737496743936.",
		"0281474993487872.",
		"0562949986975744.",
		"01125899973951488.",
		"02251799947902976.",
		"04503599895805952.",
		"09007199791611904.",
		"018014399583223808.",
		"036028799166447616.",
		"072057598332895232.",
		"0144115196665790464.",
		"0288230393331580928.",
		"0576460786663161856.",
		"01152921573326323712.",
		"02305843146652647424.",
		"04611686293305294848.",
		"09223372586610589696.",
		"018446745173221179392.",
		"036893490346442358784.",
		"073786980692884717568.",
		"0147573961385769435136.",
		"0295147922771538870272.",
		"0590295845543077740544.",
		"01180591691086155481088.",
		"02361183382172310962176.",
		"04722366764344621924352.",
		"09444733528689243848704.",
		"018889467057378487697408.",
		"037778934114756975394816.",
		"075557868229513950789632.",
		"0151115736459027901579264.",
		"0302231472918055803158528.",
		"0604462945836111606317056.",
		"01208925891672223212634112.",
		"02417851783344446425268224.",
		"04835703566688892850536448.",
		"09671407133377785701072896.",
		"019342814266755571402145792.",
		"038685628533511142804291584.",
		"077371257067022285608583168.",
		"0154742514134044571217166336.",
		"0309485028268089142434332672.",
		"0618970056536178284868665344.",
		"01237940113072356569737330688.",
		"02475880226144713139474661376.",
		"04951760452289426278949322752.",
		"09903520904578852557898645504.",
		"019807041809157705115797291008.",
		"039614083618315410231594582016.",
		"079228167236630820463189164032.",
		"0158456334473261640926378328064.",
		"0316912668946523281852756656128.",
		"0633825337893046563705513312256.",
		"01267650675786093127411026624512.",
		"02535301351572186254822053249024.",
		"05070602703144372509644106498048.",
		"010141205406288745019288212996096.",
		"020282410812577490038576425992192.",
		"040564821625154980077152851984384.",
		"081129643250309960154305703968768.",
		"0162259286500619920308611407937536.",
		"0324518573001239840617222815875072.",
		"0649037146002479681234445631750144.",
		"01298074292004959362468891263500288.",
		"02596148584009918724937782527000576.",
		"05192297168019837449875565054001152.",
		"010384594336039674899751130108002304.",
		"020769188672079349799502260216004608.",
		"041538377344158699599004520432009216.",
		"083076754688317399198009040864018432.",
		"0166153509376634798396018081728036864.",
		"0332307018753269596792036163456073728.",
		"0664614037506539193584072326912147456.",
		"01329228075013078387168144653824294912.",
		"02658456150026156774336289307648589824.",
		"05316912300052313548672578615297179648.",
		"010633824600104627097345157230594359296.",
		"021267649200209254194690314461188718592.",
		"042535298400418508389380628922377437184.",
		"085070596800837016778761257844754874368.",
		"0170141193601674033557522515689509748736.",
	};

	signed char steps[][1 + 2 + 150 + 1] = {
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 4, 0, 1, 2, 9, 8, 4, 6, 4, 3, 2, 4, 8, 1, 7, 0, 7, 0, 9, 2, 3, 7, 2, 9, 5, 8, 3, 2, 8, 9, 9, 1, 6, 1, 3, 1, 2, 8, 0, 2, 6, 1, 9, 4, 1, 8, 7, 6, 5, 1, 5, 7, 7, 1, 7, 5, 7, 0, 6, 8, 2, 8, 3, 8, 8, 9, 7, 9, 1, 0, 8, 2, 6, 8, 5, 8, 6, 0, 6, 0, 1, 4, 8, 6, 6, 3, 8, 1, 8, 8, 3, 6, 2, 1, 2, 1, 5, 8, 2, 0, 3, 1, 2, 5, },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 4, 0, 1, 2, 9, 8, 4, 6, 4, 3, 2, 4, 8, 1, 7, 0, 7, 0, 9, 2, 3, 7, 2, 9, 5, 8, 3, 2, 8, 9, 9, 1, 6, 1, 3, 1, 2, 8, 0, 2, 6, 1, 9, 4, 1, 8, 7, 6, 5, 1, 5, 7, 7, 1, 7, 5, 7, 0, 6, 8, 2, 8, 3, 8, 8, 9, 7, 9, 1, 0, 8, 2, 6, 8, 5, 8, 6, 0, 6, 0, 1, 4, 8, 6, 6, 3, 8, 1, 8, 8, 3, 6, 2, 1, 2, 1, 5, 8, 2, 0, 3, 1, 2, 5, },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 8, 0, 2, 5, 9, 6, 9, 2, 8, 6, 4, 9, 6, 3, 4, 1, 4, 1, 8, 4, 7, 4, 5, 9, 1, 6, 6, 5, 7, 9, 8, 3, 2, 2, 6, 2, 5, 6, 0, 5, 2, 3, 8, 8, 3, 7, 5, 3, 0, 3, 1, 5, 4, 3, 5, 1, 4, 1, 3, 6, 5, 6, 7, 7, 7, 9, 5, 8, 2, 1, 6, 5, 3, 7, 1, 7, 2, 1, 2, 0, 2, 9, 7, 3, 2, 7, 6, 3, 7, 6, 7, 2, 4, 2, 4, 3, 1, 6, 4, 0, 6, 2, 5, },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5, 6, 0, 5, 1, 9, 3, 8, 5, 7, 2, 9, 9, 2, 6, 8, 2, 8, 3, 6, 9, 4, 9, 1, 8, 3, 3, 3, 1, 5, 9, 6, 6, 4, 5, 2, 5, 1, 2, 1, 0, 4, 7, 7, 6, 7, 5, 0, 6, 0, 6, 3, 0, 8, 7, 0, 2, 8, 2, 7, 3, 1, 3, 5, 5, 5, 9, 1, 6, 4, 3, 3, 0, 7, 4, 3, 4, 4, 2, 4, 0, 5, 9, 4, 6, 5, 5, 2, 7, 5, 3, 4, 4, 8, 4, 8, 6, 3, 2, 8, 1, 2, 5, },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 2, 1, 0, 3, 8, 7, 7, 1, 4, 5, 9, 8, 5, 3, 6, 5, 6, 7, 3, 8, 9, 8, 3, 6, 6, 6, 6, 3, 1, 9, 3, 2, 9, 0, 5, 0, 2, 4, 2, 0, 9, 5, 5, 3, 5, 0, 1, 2, 1, 2, 6, 1, 7, 4, 0, 5, 6, 5, 4, 6, 2, 7, 1, 1, 1, 8, 3, 2, 8, 6, 6, 1, 4, 8, 6, 8, 8, 4, 8, 1, 1, 8, 9, 3, 1, 0, 5, 5, 0, 6, 8, 9, 6, 9, 7, 2, 6, 5, 6, 2, 5, },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 4, 2, 0, 7, 7, 5, 4, 2, 9, 1, 9, 7, 0, 7, 3, 1, 3, 4, 7, 7, 9, 6, 7, 3, 3, 3, 2, 6, 3, 8, 6, 5, 8, 1, 0, 0, 4, 8, 4, 1, 9, 1, 0, 7, 0, 0, 2, 4, 2, 5, 2, 3, 4, 8, 1, 1, 3, 0, 9, 2, 5, 4, 2, 2, 3, 6, 6, 5, 7, 3, 2, 2, 9, 7, 3, 7, 6, 9, 6, 2, 3, 7, 8, 6, 2, 1, 1, 0, 1, 3, 7, 9, 3, 9, 4, 5, 3, 1, 2, 5, },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 4, 8, 4, 1, 5, 5, 0, 8, 5, 8, 3, 9, 4, 1, 4, 6, 2, 6, 9, 5, 5, 9, 3, 4, 6, 6, 6, 5, 2, 7, 7, 3, 1, 6, 2, 0, 0, 9, 6, 8, 3, 8, 2, 1, 4, 0, 0, 4, 8, 5, 0, 4, 6, 9, 6, 2, 2, 6, 1, 8, 5, 0, 8, 4, 4, 7, 3, 3, 1, 4, 6, 4, 5, 9, 4, 7, 5, 3, 9, 2, 4, 7, 5, 7, 2, 4, 2, 2, 0, 2, 7, 5, 8, 7, 8, 9, 0, 6, 2, 5, },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8, 9, 6, 8, 3, 1, 0, 1, 7, 1, 6, 7, 8, 8, 2, 9, 2, 5, 3, 9, 1, 1, 8, 6, 9, 3, 3, 3, 0, 5, 5, 4, 6, 3, 2, 4, 0, 1, 9, 3, 6, 7, 6, 4, 2, 8, 0, 0, 9, 7, 0, 0, 9, 3, 9, 2, 4, 5, 2, 3, 7, 0, 1, 6, 8, 9, 4, 6, 6, 2, 9, 2, 9, 1, 8, 9, 5, 0, 7, 8, 4, 9, 5, 1, 4, 4, 8, 4, 4, 0, 5, 5, 1, 7, 5, 7, 8, 1, 2, 5, },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 7, 9, 3, 6, 6, 2, 0, 3, 4, 3, 3, 5, 7, 6, 5, 8, 5, 0, 7, 8, 2, 3, 7, 3, 8, 6, 6, 6, 1, 1, 0, 9, 2, 6, 4, 8, 0, 3, 8, 7, 3, 5, 2, 8, 5, 6, 0, 1, 9, 4, 0, 1, 8, 7, 8, 4, 9, 0, 4, 7, 4, 0, 3, 3, 7, 8, 9, 3, 2, 5, 8, 5, 8, 3, 7, 9, 0, 1, 5, 6, 9, 9, 0, 2, 8, 9, 6, 8, 8, 1, 1, 0, 3, 5, 1, 5, 6, 2, 5, },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 5, 8, 7, 3, 2, 4, 0, 6, 8, 6, 7, 1, 5, 3, 1, 7, 0, 1, 5, 6, 4, 7, 4, 7, 7, 3, 3, 2, 2, 2, 1, 8, 5, 2, 9, 6, 0, 7, 7, 4, 7, 0, 5, 7, 1, 2, 0, 3, 8, 8, 0, 3, 7, 5, 6, 9, 8, 0, 9, 4, 8, 0, 6, 7, 5, 7, 8, 6, 5, 1, 7, 1, 6, 7, 5, 8, 0, 3, 1, 3, 9, 8, 0, 5, 7, 9, 3, 7, 6, 2, 2, 0, 7, 0, 3, 1, 2, 5, },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 1, 7, 4, 6, 4, 8, 1, 3, 7, 3, 4, 3, 0, 6, 3, 4, 0, 3, 1, 2, 9, 4, 9, 5, 4, 6, 6, 4, 4, 4, 3, 7, 0, 5, 9, 2, 1, 5, 4, 9, 4, 1, 1, 4, 2, 4, 0, 7, 7, 6, 0, 7, 5, 1, 3, 9, 6, 1, 8, 9, 6, 1, 3, 5, 1, 5, 7, 3, 0, 3, 4, 3, 3, 5, 1, 6, 0, 6, 2, 7, 9, 6, 1, 1, 5, 8, 7, 5, 2, 4, 4, 1, 4, 0, 6, 2, 5, },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 4, 3, 4, 9, 2, 9, 6, 2, 7, 4, 6, 8, 6, 1, 2, 6, 8, 0, 6, 2, 5, 8, 9, 9, 0, 9, 3, 2, 8, 8, 8, 7, 4, 1, 1, 8, 4, 3, 0, 9, 8, 8, 2, 2, 8, 4, 8, 1, 5, 5, 2, 1, 5, 0, 2, 7, 9, 2, 3, 7, 9, 2, 2, 7, 0, 3, 1, 4, 6, 0, 6, 8, 6, 7, 0, 3, 2, 1, 2, 5, 5, 9, 2, 2, 3, 1, 7, 5, 0, 4, 8, 8, 2, 8, 1, 2, 5, },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 8, 6, 9, 8, 5, 9, 2, 5, 4, 9, 3, 7, 2, 2, 5, 3, 6, 1, 2, 5, 1, 7, 9, 8, 1, 8, 6, 5, 7, 7, 7, 4, 8, 2, 3, 6, 8, 6, 1, 9, 7, 6, 4, 5, 6, 9, 6, 3, 1, 0, 4, 3, 0, 0, 5, 5, 8, 4, 7, 5, 8, 4, 5, 4, 0, 6, 2, 9, 2, 1, 3, 7, 3, 4, 0, 6, 4, 2, 5, 1, 1, 8, 4, 4, 6, 3, 5, 0, 0, 9, 7, 6, 5, 6, 2, 5, },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5, 7, 3, 9, 7, 1, 8, 5, 0, 9, 8, 7, 4, 4, 5, 0, 7, 2, 2, 5, 0, 3, 5, 9, 6, 3, 7, 3, 1, 5, 5, 4, 9, 6, 4, 7, 3, 7, 2, 3, 9, 5, 2, 9, 1, 3, 9, 2, 6, 2, 0, 8, 6, 0, 1, 1, 1, 6, 9, 5, 1, 6, 9, 0, 8, 1, 2, 5, 8, 4, 2, 7, 4, 6, 8, 1, 2, 8, 5, 0, 2, 3, 6, 8, 9, 2, 7, 0, 0, 1, 9, 5, 3, 1, 2, 5, },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 4, 7, 9, 4, 3, 7, 0, 1, 9, 7, 4, 8, 9, 0, 1, 4, 4, 5, 0, 0, 7, 1, 9, 2, 7, 4, 6, 3, 1, 0, 9, 9, 2, 9, 4, 7, 4, 4, 7, 9, 0, 5, 8, 2, 7, 8, 5, 2, 4, 1, 7, 2, 0, 2, 2, 3, 3, 9, 0, 3, 3, 8, 1, 6, 2, 5, 1, 6, 8, 5, 4, 9, 3, 6, 2, 5, 7, 0, 0, 4, 7, 3, 7, 8, 5, 4, 0, 0, 3, 9, 0, 6, 2, 5, },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 9, 5, 8, 8, 7, 4, 0, 3, 9, 4, 9, 7, 8, 0, 2, 8, 9, 0, 0, 1, 4, 3, 8, 5, 4, 9, 2, 6, 2, 1, 9, 8, 5, 8, 9, 4, 8, 9, 5, 8, 1, 1, 6, 5, 5, 7, 0, 4, 8, 3, 4, 4, 0, 4, 4, 6, 7, 8, 0, 6, 7, 6, 3, 2, 5, 0, 3, 3, 7, 0, 9, 8, 7, 2, 5, 1, 4, 0, 0, 9, 4, 7, 5, 7, 0, 8, 0, 0, 7, 8, 1, 2, 5, },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 5, 9, 1, 7, 7, 4, 8, 0, 7, 8, 9, 9, 5, 6, 0, 5, 7, 8, 0, 0, 2, 8, 7, 7, 0, 9, 8, 5, 2, 4, 3, 9, 7, 1, 7, 8, 9, 7, 9, 1, 6, 2, 3, 3, 1, 1, 4, 0, 9, 6, 6, 8, 8, 0, 8, 9, 3, 5, 6, 1, 3, 5, 2, 6, 5, 0, 0, 6, 7, 4, 1, 9, 7, 4, 5, 0, 2, 8, 0, 1, 8, 9, 5, 1, 4, 1, 6, 0, 1, 5, 6, 2, 5, },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 1, 8, 3, 5, 4, 9, 6, 1, 5, 7, 9, 9, 1, 2, 1, 1, 5, 6, 0, 0, 5, 7, 5, 4, 1, 9, 7, 0, 4, 8, 7, 9, 4, 3, 5, 7, 9, 5, 8, 3, 2, 4, 6, 6, 2, 2, 8, 1, 9, 3, 3, 7, 6, 1, 7, 8, 7, 1, 2, 2, 7, 0, 5, 3, 0, 0, 1, 3, 4, 8, 3, 9, 4, 9, 0, 0, 5, 6, 0, 3, 7, 9, 0, 2, 8, 3, 2, 0, 3, 1, 2, 5, },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 8, 3, 6, 7, 0, 9, 9, 2, 3, 1, 5, 9, 8, 2, 4, 2, 3, 1, 2, 0, 1, 1, 5, 0, 8, 3, 9, 4, 0, 9, 7, 5, 8, 8, 7, 1, 5, 9, 1, 6, 6, 4, 9, 3, 2, 4, 5, 6, 3, 8, 6, 7, 5, 2, 3, 5, 7, 4, 2, 4, 5, 4, 1, 0, 6, 0, 0, 2, 6, 9, 6, 7, 8, 9, 8, 0, 1, 1, 2, 0, 7, 5, 8, 0, 5, 6, 6, 4, 0, 6, 2, 5, },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 6, 7, 3, 4, 1, 9, 8, 4, 6, 3, 1, 9, 6, 4, 8, 4, 6, 2, 4, 0, 2, 3, 0, 1, 6, 7, 8, 8, 1, 9, 5, 1, 7, 7, 4, 3, 1, 8, 3, 3, 2, 9, 8, 6, 4, 9, 1, 2, 7, 7, 3, 5, 0, 4, 7, 1, 4, 8, 4, 9, 0, 8, 2, 1, 2, 0, 0, 5, 3, 9, 3, 5, 7, 9, 6, 0, 2, 2, 4, 1, 5, 1, 6, 1, 1, 3, 2, 8, 1, 2, 5, },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 3, 4, 6, 8, 3, 9, 6, 9, 2, 6, 3, 9, 2, 9, 6, 9, 2, 4, 8, 0, 4, 6, 0, 3, 3, 5, 7, 6, 3, 9, 0, 3, 5, 4, 8, 6, 3, 6, 6, 6, 5, 9, 7, 2, 9, 8, 2, 5, 5, 4, 7, 0, 0, 9, 4, 2, 9, 6, 9, 8, 1, 6, 4, 2, 4, 0, 1, 0, 7, 8, 7, 1, 5, 9, 2, 0, 4, 4, 8, 3, 0, 3, 2, 2, 2, 6, 5, 6, 2, 5, },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 4, 6, 9, 3, 6, 7, 9, 3, 8, 5, 2, 7, 8, 5, 9, 3, 8, 4, 9, 6, 0, 9, 2, 0, 6, 7, 1, 5, 2, 7, 8, 0, 7, 0, 9, 7, 2, 7, 3, 3, 3, 1, 9, 4, 5, 9, 6, 5, 1, 0, 9, 4, 0, 1, 8, 8, 5, 9, 3, 9, 6, 3, 2, 8, 4, 8, 0, 2, 1, 5, 7, 4, 3, 1, 8, 4, 0, 8, 9, 6, 6, 0, 6, 4, 4, 5, 3, 1, 2, 5, },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 9, 3, 8, 7, 3, 5, 8, 7, 7, 0, 5, 5, 7, 1, 8, 7, 6, 9, 9, 2, 1, 8, 4, 1, 3, 4, 3, 0, 5, 5, 6, 1, 4, 1, 9, 4, 5, 4, 6, 6, 6, 3, 8, 9, 1, 9, 3, 0, 2, 1, 8, 8, 0, 3, 7, 7, 1, 8, 7, 9, 2, 6, 5, 6, 9, 6, 0, 4, 3, 1, 4, 8, 6, 3, 6, 8, 1, 7, 9, 3, 2, 1, 2, 8, 9, 0, 6, 2, 5, },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5, 8, 7, 7, 4, 7, 1, 7, 5, 4, 1, 1, 1, 4, 3, 7, 5, 3, 9, 8, 4, 3, 6, 8, 2, 6, 8, 6, 1, 1, 1, 2, 2, 8, 3, 8, 9, 0, 9, 3, 3, 2, 7, 7, 8, 3, 8, 6, 0, 4, 3, 7, 6, 0, 7, 5, 4, 3, 7, 5, 8, 5, 3, 1, 3, 9, 2, 0, 8, 6, 2, 9, 7, 2, 7, 3, 6, 3, 5, 8, 6, 4, 2, 5, 7, 8, 1, 2, 5, },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 7, 5, 4, 9, 4, 3, 5, 0, 8, 2, 2, 2, 8, 7, 5, 0, 7, 9, 6, 8, 7, 3, 6, 5, 3, 7, 2, 2, 2, 2, 4, 5, 6, 7, 7, 8, 1, 8, 6, 6, 5, 5, 5, 6, 7, 7, 2, 0, 8, 7, 5, 2, 1, 5, 0, 8, 7, 5, 1, 7, 0, 6, 2, 7, 8, 4, 1, 7, 2, 5, 9, 4, 5, 4, 7, 2, 7, 1, 7, 2, 8, 5, 1, 5, 6, 2, 5, },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 3, 5, 0, 9, 8, 8, 7, 0, 1, 6, 4, 4, 5, 7, 5, 0, 1, 5, 9, 3, 7, 4, 7, 3, 0, 7, 4, 4, 4, 4, 4, 9, 1, 3, 5, 5, 6, 3, 7, 3, 3, 1, 1, 1, 3, 5, 4, 4, 1, 7, 5, 0, 4, 3, 0, 1, 7, 5, 0, 3, 4, 1, 2, 5, 5, 6, 8, 3, 4, 5, 1, 8, 9, 0, 9, 4, 5, 4, 3, 4, 5, 7, 0, 3, 1, 2, 5, },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 7, 0, 1, 9, 7, 7, 4, 0, 3, 2, 8, 9, 1, 5, 0, 0, 3, 1, 8, 7, 4, 9, 4, 6, 1, 4, 8, 8, 8, 8, 9, 8, 2, 7, 1, 1, 2, 7, 4, 6, 6, 2, 2, 2, 7, 0, 8, 8, 3, 5, 0, 0, 8, 6, 0, 3, 5, 0, 0, 6, 8, 2, 5, 1, 1, 3, 6, 6, 9, 0, 3, 7, 8, 1, 8, 9, 0, 8, 6, 9, 1, 4, 0, 6, 2, 5, },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 4, 0, 3, 9, 5, 4, 8, 0, 6, 5, 7, 8, 3, 0, 0, 0, 6, 3, 7, 4, 9, 8, 9, 2, 2, 9, 7, 7, 7, 7, 9, 6, 5, 4, 2, 2, 5, 4, 9, 3, 2, 4, 4, 5, 4, 1, 7, 6, 7, 0, 0, 1, 7, 2, 0, 7, 0, 0, 1, 3, 6, 5, 0, 2, 2, 7, 3, 3, 8, 0, 7, 5, 6, 3, 7, 8, 1, 7, 3, 8, 2, 8, 1, 2, 5, },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 8, 8, 0, 7, 9, 0, 9, 6, 1, 3, 1, 5, 6, 6, 0, 0, 1, 2, 7, 4, 9, 9, 7, 8, 4, 5, 9, 5, 5, 5, 5, 9, 3, 0, 8, 4, 5, 0, 9, 8, 6, 4, 8, 9, 0, 8, 3, 5, 3, 4, 0, 0, 3, 4, 4, 1, 4, 0, 0, 2, 7, 3, 0, 0, 4, 5, 4, 6, 7, 6, 1, 5, 1, 2, 7, 5, 6, 3, 4, 7, 6, 5, 6, 2, 5, },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 7, 6, 1, 5, 8, 1, 9, 2, 2, 6, 3, 1, 3, 2, 0, 0, 2, 5, 4, 9, 9, 9, 5, 6, 9, 1, 9, 1, 1, 1, 1, 8, 6, 1, 6, 9, 0, 1, 9, 7, 2, 9, 7, 8, 1, 6, 7, 0, 6, 8, 0, 0, 6, 8, 8, 2, 8, 0, 0, 5, 4, 6, 0, 0, 9, 0, 9, 3, 5, 2, 3, 0, 2, 5, 5, 1, 2, 6, 9, 5, 3, 1, 2, 5, },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 5, 2, 3, 1, 6, 3, 8, 4, 5, 2, 6, 2, 6, 4, 0, 0, 5, 0, 9, 9, 9, 9, 1, 3, 8, 3, 8, 2, 2, 2, 3, 7, 2, 3, 3, 8, 0, 3, 9, 4, 5, 9, 5, 6, 3, 3, 4, 1, 3, 6, 0, 1, 3, 7, 6, 5, 6, 0, 1, 0, 9, 2, 0, 1, 8, 1, 8, 7, 0, 4, 6, 0, 5, 1, 0, 2, 5, 3, 9, 0, 6, 2, 5, },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 5, 0, 4, 6, 3, 2, 7, 6, 9, 0, 5, 2, 5, 2, 8, 0, 1, 0, 1, 9, 9, 9, 8, 2, 7, 6, 7, 6, 4, 4, 4, 7, 4, 4, 6, 7, 6, 0, 7, 8, 9, 1, 9, 1, 2, 6, 6, 8, 2, 7, 2, 0, 2, 7, 5, 3, 1, 2, 0, 2, 1, 8, 4, 0, 3, 6, 3, 7, 4, 0, 9, 2, 1, 0, 2, 0, 5, 0, 7, 8, 1, 2, 5, },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 9, 2, 6, 5, 5, 3, 8, 1, 0, 5, 0, 5, 6, 0, 2, 0, 3, 9, 9, 9, 6, 5, 5, 3, 5, 2, 8, 8, 9, 4, 8, 9, 3, 5, 2, 1, 5, 7, 8, 3, 8, 2, 5, 3, 3, 6, 5, 4, 4, 0, 5, 5, 0, 6, 2, 4, 0, 4, 3, 6, 8, 0, 7, 2, 7, 4, 8, 1, 8, 4, 2, 0, 4, 1, 0, 1, 5, 6, 2, 5, },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 0, 1, 8, 5, 3, 1, 0, 7, 6, 2, 1, 0, 1, 1, 2, 0, 4, 0, 7, 9, 9, 9, 3, 1, 0, 7, 0, 5, 7, 7, 8, 9, 7, 8, 7, 0, 4, 3, 1, 5, 6, 7, 6, 5, 0, 6, 7, 3, 0, 8, 8, 1, 1, 0, 1, 2, 4, 8, 0, 8, 7, 3, 6, 1, 4, 5, 4, 9, 6, 3, 6, 8, 4, 0, 8, 2, 0, 3, 1, 2, 5, },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 0, 3, 7, 0, 6, 2, 1, 5, 2, 4, 2, 0, 2, 2, 4, 0, 8, 1, 5, 9, 9, 8, 6, 2, 1, 4, 1, 1, 5, 5, 7, 9, 5, 7, 4, 0, 8, 6, 3, 1, 3, 5, 3, 0, 1, 3, 4, 6, 1, 7, 6, 2, 2, 0, 2, 4, 9, 6, 1, 7, 4, 7, 2, 2, 9, 0, 9, 9, 2, 7, 3, 6, 8, 1, 6, 4, 0, 6, 2, 5, },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 4, 0, 7, 4, 1, 2, 4, 3, 0, 4, 8, 4, 0, 4, 4, 8, 1, 6, 3, 1, 9, 9, 7, 2, 4, 2, 8, 2, 3, 1, 1, 5, 9, 1, 4, 8, 1, 7, 2, 6, 2, 7, 0, 6, 0, 2, 6, 9, 2, 3, 5, 2, 4, 4, 0, 4, 9, 9, 2, 3, 4, 9, 4, 4, 5, 8, 1, 9, 8, 5, 4, 7, 3, 6, 3, 2, 8, 1, 2, 5, },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 8, 1, 4, 8, 2, 4, 8, 6, 0, 9, 6, 8, 0, 8, 9, 6, 3, 2, 6, 3, 9, 9, 4, 4, 8, 5, 6, 4, 6, 2, 3, 1, 8, 2, 9, 6, 3, 4, 5, 2, 5, 4, 1, 2, 0, 5, 3, 8, 4, 7, 0, 4, 8, 8, 0, 9, 9, 8, 4, 6, 9, 8, 8, 9, 1, 6, 3, 9, 7, 0, 9, 4, 7, 2, 6, 5, 6, 2, 5, },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 6, 2, 9, 6, 4, 9, 7, 2, 1, 9, 3, 6, 1, 7, 9, 2, 6, 5, 2, 7, 9, 8, 8, 9, 7, 1, 2, 9, 2, 4, 6, 3, 6, 5, 9, 2, 6, 9, 0, 5, 0, 8, 2, 4, 1, 0, 7, 6, 9, 4, 0, 9, 7, 6, 1, 9, 9, 6, 9, 3, 9, 7, 7, 8, 3, 2, 7, 9, 4, 1, 8, 9, 4, 5, 3, 1, 2, 5, },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 9, 2, 5, 9, 2, 9, 9, 4, 4, 3, 8, 7, 2, 3, 5, 8, 5, 3, 0, 5, 5, 9, 7, 7, 9, 4, 2, 5, 8, 4, 9, 2, 7, 3, 1, 8, 5, 3, 8, 1, 0, 1, 6, 4, 8, 2, 1, 5, 3, 8, 8, 1, 9, 5, 2, 3, 9, 9, 3, 8, 7, 9, 5, 5, 6, 6, 5, 5, 8, 8, 3, 7, 8, 9, 0, 6, 2, 5, },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 8, 5, 1, 8, 5, 9, 8, 8, 8, 7, 7, 4, 4, 7, 1, 7, 0, 6, 1, 1, 1, 9, 5, 5, 8, 8, 5, 1, 6, 9, 8, 5, 4, 6, 3, 7, 0, 7, 6, 2, 0, 3, 2, 9, 6, 4, 3, 0, 7, 7, 6, 3, 9, 0, 4, 7, 9, 8, 7, 7, 5, 9, 1, 1, 3, 3, 1, 1, 7, 6, 7, 5, 7, 8, 1, 2, 5, },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 7, 0, 3, 7, 1, 9, 7, 7, 7, 5, 4, 8, 9, 4, 3, 4, 1, 2, 2, 2, 3, 9, 1, 1, 7, 7, 0, 3, 3, 9, 7, 0, 9, 2, 7, 4, 1, 5, 2, 4, 0, 6, 5, 9, 2, 8, 6, 1, 5, 5, 2, 7, 8, 0, 9, 5, 9, 7, 5, 5, 1, 8, 2, 2, 6, 6, 2, 3, 5, 3, 5, 1, 5, 6, 2, 5, },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 5, 4, 0, 7, 4, 3, 9, 5, 5, 5, 0, 9, 7, 8, 8, 6, 8, 2, 4, 4, 4, 7, 8, 2, 3, 5, 4, 0, 6, 7, 9, 4, 1, 8, 5, 4, 8, 3, 0, 4, 8, 1, 3, 1, 8, 5, 7, 2, 3, 1, 0, 5, 5, 6, 1, 9, 1, 9, 5, 1, 0, 3, 6, 4, 5, 3, 2, 4, 7, 0, 7, 0, 3, 1, 2, 5, },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 8, 1, 4, 8, 7, 9, 1, 1, 0, 1, 9, 5, 7, 7, 3, 6, 4, 8, 8, 9, 5, 6, 4, 7, 0, 8, 1, 3, 5, 8, 8, 3, 7, 0, 9, 6, 6, 0, 9, 6, 2, 6, 3, 7, 1, 4, 4, 6, 2, 1, 1, 1, 2, 3, 8, 3, 9, 0, 2, 0, 7, 2, 9, 0, 6, 4, 9, 4, 1, 4, 0, 6, 2, 5, },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 1, 6, 2, 9, 7, 5, 8, 2, 2, 0, 3, 9, 1, 5, 4, 7, 2, 9, 7, 7, 9, 1, 2, 9, 4, 1, 6, 2, 7, 1, 7, 6, 7, 4, 1, 9, 3, 2, 1, 9, 2, 5, 2, 7, 4, 2, 8, 9, 2, 4, 2, 2, 2, 4, 7, 6, 7, 8, 0, 4, 1, 4, 5, 8, 1, 2, 9, 8, 8, 2, 8, 1, 2, 5, },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 3, 2, 5, 9, 5, 1, 6, 4, 4, 0, 7, 8, 3, 0, 9, 4, 5, 9, 5, 5, 8, 2, 5, 8, 8, 3, 2, 5, 4, 3, 5, 3, 4, 8, 3, 8, 6, 4, 3, 8, 5, 0, 5, 4, 8, 5, 7, 8, 4, 8, 4, 4, 4, 9, 5, 3, 5, 6, 0, 8, 2, 9, 1, 6, 2, 5, 9, 7, 6, 5, 6, 2, 5, },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 4, 6, 5, 1, 9, 0, 3, 2, 8, 8, 1, 5, 6, 6, 1, 8, 9, 1, 9, 1, 1, 6, 5, 1, 7, 6, 6, 5, 0, 8, 7, 0, 6, 9, 6, 7, 7, 2, 8, 7, 7, 0, 1, 0, 9, 7, 1, 5, 6, 9, 6, 8, 8, 9, 9, 0, 7, 1, 2, 1, 6, 5, 8, 3, 2, 5, 1, 9, 5, 3, 1, 2, 5, },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 9, 3, 0, 3, 8, 0, 6, 5, 7, 6, 3, 1, 3, 2, 3, 7, 8, 3, 8, 2, 3, 3, 0, 3, 5, 3, 3, 0, 1, 7, 4, 1, 3, 9, 3, 5, 4, 5, 7, 5, 4, 0, 2, 1, 9, 4, 3, 1, 3, 9, 3, 7, 7, 9, 8, 1, 4, 2, 4, 3, 3, 1, 6, 6, 5, 0, 3, 9, 0, 6, 2, 5, },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 8, 6, 0, 7, 6, 1, 3, 1, 5, 2, 6, 2, 6, 4, 7, 5, 6, 7, 6, 4, 6, 6, 0, 7, 0, 6, 6, 0, 3, 4, 8, 2, 7, 8, 7, 0, 9, 1, 5, 0, 8, 0, 4, 3, 8, 8, 6, 2, 7, 8, 7, 5, 5, 9, 6, 2, 8, 4, 8, 6, 6, 3, 3, 3, 0, 0, 7, 8, 1, 2, 5, },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 9, 7, 2, 1, 5, 2, 2, 6, 3, 0, 5, 2, 5, 2, 9, 5, 1, 3, 5, 2, 9, 3, 2, 1, 4, 1, 3, 2, 0, 6, 9, 6, 5, 5, 7, 4, 1, 8, 3, 0, 1, 6, 0, 8, 7, 7, 7, 2, 5, 5, 7, 5, 1, 1, 9, 2, 5, 6, 9, 7, 3, 2, 6, 6, 6, 0, 1, 5, 6, 2, 5, },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 9, 4, 4, 3, 0, 4, 5, 2, 6, 1, 0, 5, 0, 5, 9, 0, 2, 7, 0, 5, 8, 6, 4, 2, 8, 2, 6, 4, 1, 3, 9, 3, 1, 1, 4, 8, 3, 6, 6, 0, 3, 2, 1, 7, 5, 5, 4, 5, 1, 1, 5, 0, 2, 3, 8, 5, 1, 3, 9, 4, 6, 5, 3, 3, 2, 0, 3, 1, 2, 5, },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 8, 8, 8, 6, 0, 9, 0, 5, 2, 2, 1, 0, 1, 1, 8, 0, 5, 4, 1, 1, 7, 2, 8, 5, 6, 5, 2, 8, 2, 7, 8, 6, 2, 2, 9, 6, 7, 3, 2, 0, 6, 4, 3, 5, 1, 0, 9, 0, 2, 3, 0, 0, 4, 7, 7, 0, 2, 7, 8, 9, 3, 0, 6, 6, 4, 0, 6, 2, 5, },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 5, 7, 7, 7, 2, 1, 8, 1, 0, 4, 4, 2, 0, 2, 3, 6, 1, 0, 8, 2, 3, 4, 5, 7, 1, 3, 0, 5, 6, 5, 5, 7, 2, 4, 5, 9, 3, 4, 6, 4, 1, 2, 8, 7, 0, 2, 1, 8, 0, 4, 6, 0, 0, 9, 5, 4, 0, 5, 5, 7, 8, 6, 1, 3, 2, 8, 1, 2, 5, },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 1, 5, 5, 4, 4, 3, 6, 2, 0, 8, 8, 4, 0, 4, 7, 2, 2, 1, 6, 4, 6, 9, 1, 4, 2, 6, 1, 1, 3, 1, 1, 4, 4, 9, 1, 8, 6, 9, 2, 8, 2, 5, 7, 4, 0, 4, 3, 6, 0, 9, 2, 0, 1, 9, 0, 8, 1, 1, 1, 5, 7, 2, 2, 6, 5, 6, 2, 5, },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 3, 1, 0, 8, 8, 7, 2, 4, 1, 7, 6, 8, 0, 9, 4, 4, 4, 3, 2, 9, 3, 8, 2, 8, 5, 2, 2, 2, 6, 2, 2, 8, 9, 8, 3, 7, 3, 8, 5, 6, 5, 1, 4, 8, 0, 8, 7, 2, 1, 8, 4, 0, 3, 8, 1, 6, 2, 2, 3, 1, 4, 4, 5, 3, 1, 2, 5, },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 6, 2, 1, 7, 7, 4, 4, 8, 3, 5, 3, 6, 1, 8, 8, 8, 8, 6, 5, 8, 7, 6, 5, 7, 0, 4, 4, 5, 2, 4, 5, 7, 9, 6, 7, 4, 7, 7, 1, 3, 0, 2, 9, 6, 1, 7, 4, 4, 3, 6, 8, 0, 7, 6, 3, 2, 4, 4, 6, 2, 8, 9, 0, 6, 2, 5, },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 5, 2, 4, 3, 5, 4, 8, 9, 6, 7, 0, 7, 2, 3, 7, 7, 7, 7, 3, 1, 7, 5, 3, 1, 4, 0, 8, 9, 0, 4, 9, 1, 5, 9, 3, 4, 9, 5, 4, 2, 6, 0, 5, 9, 2, 3, 4, 8, 8, 7, 3, 6, 1, 5, 2, 6, 4, 8, 9, 2, 5, 7, 8, 1, 2, 5, },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5, 0, 4, 8, 7, 0, 9, 7, 9, 3, 4, 1, 4, 4, 7, 5, 5, 5, 4, 6, 3, 5, 0, 6, 2, 8, 1, 7, 8, 0, 9, 8, 3, 1, 8, 6, 9, 9, 0, 8, 5, 2, 1, 1, 8, 4, 6, 9, 7, 7, 4, 7, 2, 3, 0, 5, 2, 9, 7, 8, 5, 1, 5, 6, 2, 5, },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 9, 7, 4, 1, 9, 5, 8, 6, 8, 2, 8, 9, 5, 1, 1, 0, 9, 2, 7, 0, 1, 2, 5, 6, 3, 5, 6, 1, 9, 6, 6, 3, 7, 3, 9, 8, 1, 7, 0, 4, 2, 3, 6, 9, 3, 9, 5, 4, 9, 4, 4, 6, 1, 0, 5, 9, 5, 7, 0, 3, 1, 2, 5, },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 1, 9, 4, 8, 3, 9, 1, 7, 3, 6, 5, 7, 9, 0, 2, 2, 1, 8, 5, 4, 0, 2, 5, 1, 2, 7, 1, 2, 3, 9, 3, 2, 7, 4, 7, 9, 6, 3, 4, 0, 8, 4, 7, 3, 8, 7, 9, 0, 9, 8, 8, 9, 2, 2, 1, 1, 9, 1, 4, 0, 6, 2, 5, },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 0, 3, 8, 9, 6, 7, 8, 3, 4, 7, 3, 1, 5, 8, 0, 4, 4, 3, 7, 0, 8, 0, 5, 0, 2, 5, 4, 2, 4, 7, 8, 6, 5, 4, 9, 5, 9, 2, 6, 8, 1, 6, 9, 4, 7, 7, 5, 8, 1, 9, 7, 7, 8, 4, 4, 2, 3, 8, 2, 8, 1, 2, 5, },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8, 0, 7, 7, 9, 3, 5, 6, 6, 9, 4, 6, 3, 1, 6, 0, 8, 8, 7, 4, 1, 6, 1, 0, 0, 5, 0, 8, 4, 9, 5, 7, 3, 0, 9, 9, 1, 8, 5, 3, 6, 3, 3, 8, 9, 5, 5, 1, 6, 3, 9, 5, 5, 6, 8, 8, 4, 7, 6, 5, 6, 2, 5, },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 6, 1, 5, 5, 8, 7, 1, 3, 3, 8, 9, 2, 6, 3, 2, 1, 7, 7, 4, 8, 3, 2, 2, 0, 1, 0, 1, 6, 9, 9, 1, 4, 6, 1, 9, 8, 3, 7, 0, 7, 2, 6, 7, 7, 9, 1, 0, 3, 2, 7, 9, 1, 1, 3, 7, 6, 9, 5, 3, 1, 2, 5, },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 2, 3, 1, 1, 7, 4, 2, 6, 7, 7, 8, 5, 2, 6, 4, 3, 5, 4, 9, 6, 6, 4, 4, 0, 2, 0, 3, 3, 9, 8, 2, 9, 2, 3, 9, 6, 7, 4, 1, 4, 5, 3, 5, 5, 8, 2, 0, 6, 5, 5, 8, 2, 2, 7, 5, 3, 9, 0, 6, 2, 5, },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 4, 6, 2, 3, 4, 8, 5, 3, 5, 5, 7, 0, 5, 2, 8, 7, 0, 9, 9, 3, 2, 8, 8, 0, 4, 0, 6, 7, 9, 6, 5, 8, 4, 7, 9, 3, 4, 8, 2, 9, 0, 7, 1, 1, 6, 4, 1, 3, 1, 1, 6, 4, 5, 5, 0, 7, 8, 1, 2, 5, },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 9, 2, 4, 6, 9, 7, 0, 7, 1, 1, 4, 1, 0, 5, 7, 4, 1, 9, 8, 6, 5, 7, 6, 0, 8, 1, 3, 5, 9, 3, 1, 6, 9, 5, 8, 6, 9, 6, 5, 8, 1, 4, 2, 3, 2, 8, 2, 6, 2, 3, 2, 9, 1, 0, 1, 5, 6, 2, 5, },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 5, 8, 4, 9, 3, 9, 4, 1, 4, 2, 2, 8, 2, 1, 1, 4, 8, 3, 9, 7, 3, 1, 5, 2, 1, 6, 2, 7, 1, 8, 6, 3, 3, 9, 1, 7, 3, 9, 3, 1, 6, 2, 8, 4, 6, 5, 6, 5, 2, 4, 6, 5, 8, 2, 0, 3, 1, 2, 5, },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5, 1, 6, 9, 8, 7, 8, 8, 2, 8, 4, 5, 6, 4, 2, 2, 9, 6, 7, 9, 4, 6, 3, 0, 4, 3, 2, 5, 4, 3, 7, 2, 6, 7, 8, 3, 4, 7, 8, 6, 3, 2, 5, 6, 9, 3, 1, 3, 0, 4, 9, 3, 1, 6, 4, 0, 6, 2, 5, },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 3, 3, 9, 7, 5, 7, 6, 5, 6, 9, 1, 2, 8, 4, 5, 9, 3, 5, 8, 9, 2, 6, 0, 8, 6, 5, 0, 8, 7, 4, 5, 3, 5, 6, 6, 9, 5, 7, 2, 6, 5, 1, 3, 8, 6, 2, 6, 0, 9, 8, 6, 3, 2, 8, 1, 2, 5, },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 6, 7, 9, 5, 1, 5, 3, 1, 3, 8, 2, 5, 6, 9, 1, 8, 7, 1, 7, 8, 5, 2, 1, 7, 3, 0, 1, 7, 4, 9, 0, 7, 1, 3, 3, 9, 1, 4, 5, 3, 0, 2, 7, 7, 2, 5, 2, 1, 9, 7, 2, 6, 5, 6, 2, 5, },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 1, 3, 5, 9, 0, 3, 0, 6, 2, 7, 6, 5, 1, 3, 8, 3, 7, 4, 3, 5, 7, 0, 4, 3, 4, 6, 0, 3, 4, 9, 8, 1, 4, 2, 6, 7, 8, 2, 9, 0, 6, 0, 5, 5, 4, 5, 0, 4, 3, 9, 4, 5, 3, 1, 2, 5, },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8, 2, 7, 1, 8, 0, 6, 1, 2, 5, 5, 3, 0, 2, 7, 6, 7, 4, 8, 7, 1, 4, 0, 8, 6, 9, 2, 0, 6, 9, 9, 6, 2, 8, 5, 3, 5, 6, 5, 8, 1, 2, 1, 1, 0, 9, 0, 0, 8, 7, 8, 9, 0, 6, 2, 5, },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 6, 5, 4, 3, 6, 1, 2, 2, 5, 1, 0, 6, 0, 5, 5, 3, 4, 9, 7, 4, 2, 8, 1, 7, 3, 8, 4, 1, 3, 9, 9, 2, 5, 7, 0, 7, 1, 3, 1, 6, 2, 4, 2, 2, 1, 8, 0, 1, 7, 5, 7, 8, 1, 2, 5, },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 3, 0, 8, 7, 2, 2, 4, 5, 0, 2, 1, 2, 1, 1, 0, 6, 9, 9, 4, 8, 5, 6, 3, 4, 7, 6, 8, 2, 7, 9, 8, 5, 1, 4, 1, 4, 2, 6, 3, 2, 4, 8, 4, 4, 3, 6, 0, 3, 5, 1, 5, 6, 2, 5, },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 6, 1, 7, 4, 4, 4, 9, 0, 0, 4, 2, 4, 2, 2, 1, 3, 9, 8, 9, 7, 1, 2, 6, 9, 5, 3, 6, 5, 5, 9, 7, 0, 2, 8, 2, 8, 5, 2, 6, 4, 9, 6, 8, 8, 7, 2, 0, 7, 0, 3, 1, 2, 5, },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 3, 2, 3, 4, 8, 8, 9, 8, 0, 0, 8, 4, 8, 4, 4, 2, 7, 9, 7, 9, 4, 2, 5, 3, 9, 0, 7, 3, 1, 1, 9, 4, 0, 5, 6, 5, 7, 0, 5, 2, 9, 9, 3, 7, 7, 4, 4, 1, 4, 0, 6, 2, 5, },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 6, 4, 6, 9, 7, 7, 9, 6, 0, 1, 6, 9, 6, 8, 8, 5, 5, 9, 5, 8, 8, 5, 0, 7, 8, 1, 4, 6, 2, 3, 8, 8, 1, 1, 3, 1, 4, 1, 0, 5, 9, 8, 7, 5, 4, 8, 8, 2, 8, 1, 2, 5, },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5, 2, 9, 3, 9, 5, 5, 9, 2, 0, 3, 3, 9, 3, 7, 7, 1, 1, 9, 1, 7, 7, 0, 1, 5, 6, 2, 9, 2, 4, 7, 7, 6, 2, 2, 6, 2, 8, 2, 1, 1, 9, 7, 5, 0, 9, 7, 6, 5, 6, 2, 5, },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 5, 8, 7, 9, 1, 1, 8, 4, 0, 6, 7, 8, 7, 5, 4, 2, 3, 8, 3, 5, 4, 0, 3, 1, 2, 5, 8, 4, 9, 5, 5, 2, 4, 5, 2, 5, 6, 4, 2, 3, 9, 5, 0, 1, 9, 5, 3, 1, 2, 5, },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 1, 1, 7, 5, 8, 2, 3, 6, 8, 1, 3, 5, 7, 5, 0, 8, 4, 7, 6, 7, 0, 8, 0, 6, 2, 5, 1, 6, 9, 9, 1, 0, 4, 9, 0, 5, 1, 2, 8, 4, 7, 9, 0, 0, 3, 9, 0, 6, 2, 5, },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 2, 3, 5, 1, 6, 4, 7, 3, 6, 2, 7, 1, 5, 0, 1, 6, 9, 5, 3, 4, 1, 6, 1, 2, 5, 0, 3, 3, 9, 8, 2, 0, 9, 8, 1, 0, 2, 5, 6, 9, 5, 8, 0, 0, 7, 8, 1, 2, 5, },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8, 4, 7, 0, 3, 2, 9, 4, 7, 2, 5, 4, 3, 0, 0, 3, 3, 9, 0, 6, 8, 3, 2, 2, 5, 0, 0, 6, 7, 9, 6, 4, 1, 9, 6, 2, 0, 5, 1, 3, 9, 1, 6, 0, 1, 5, 6, 2, 5, },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 6, 9, 4, 0, 6, 5, 8, 9, 4, 5, 0, 8, 6, 0, 0, 6, 7, 8, 1, 3, 6, 6, 4, 5, 0, 0, 1, 3, 5, 9, 2, 8, 3, 9, 2, 4, 1, 0, 2, 7, 8, 3, 2, 0, 3, 1, 2, 5, },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 3, 8, 8, 1, 3, 1, 7, 8, 9, 0, 1, 7, 2, 0, 1, 3, 5, 6, 2, 7, 3, 2, 9, 0, 0, 0, 2, 7, 1, 8, 5, 6, 7, 8, 4, 8, 2, 0, 5, 5, 6, 6, 4, 0, 6, 2, 5, },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 7, 7, 6, 2, 6, 3, 5, 7, 8, 0, 3, 4, 4, 0, 2, 7, 1, 2, 5, 4, 6, 5, 8, 0, 0, 0, 5, 4, 3, 7, 1, 3, 5, 6, 9, 6, 4, 1, 1, 1, 3, 2, 8, 1, 2, 5, },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 3, 5, 5, 2, 5, 2, 7, 1, 5, 6, 0, 6, 8, 8, 0, 5, 4, 2, 5, 0, 9, 3, 1, 6, 0, 0, 1, 0, 8, 7, 4, 2, 7, 1, 3, 9, 2, 8, 2, 2, 2, 6, 5, 6, 2, 5, },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 7, 1, 0, 5, 0, 5, 4, 3, 1, 2, 1, 3, 7, 6, 1, 0, 8, 5, 0, 1, 8, 6, 3, 2, 0, 0, 2, 1, 7, 4, 8, 5, 4, 2, 7, 8, 5, 6, 4, 4, 5, 3, 1, 2, 5, },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5, 4, 2, 1, 0, 1, 0, 8, 6, 2, 4, 2, 7, 5, 2, 2, 1, 7, 0, 0, 3, 7, 2, 6, 4, 0, 0, 4, 3, 4, 9, 7, 0, 8, 5, 5, 7, 1, 2, 8, 9, 0, 6, 2, 5, },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 8, 4, 2, 0, 2, 1, 7, 2, 4, 8, 5, 5, 0, 4, 4, 3, 4, 0, 0, 7, 4, 5, 2, 8, 0, 0, 8, 6, 9, 9, 4, 1, 7, 1, 1, 4, 2, 5, 7, 8, 1, 2, 5, },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 1, 6, 8, 4, 0, 4, 3, 4, 4, 9, 7, 1, 0, 0, 8, 8, 6, 8, 0, 1, 4, 9, 0, 5, 6, 0, 1, 7, 3, 9, 8, 8, 3, 4, 2, 2, 8, 5, 1, 5, 6, 2, 5, },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 3, 3, 6, 8, 0, 8, 6, 8, 9, 9, 4, 2, 0, 1, 7, 7, 3, 6, 0, 2, 9, 8, 1, 1, 2, 0, 3, 4, 7, 9, 7, 6, 6, 8, 4, 5, 7, 0, 3, 1, 2, 5, },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8, 6, 7, 3, 6, 1, 7, 3, 7, 9, 8, 8, 4, 0, 3, 5, 4, 7, 2, 0, 5, 9, 6, 2, 2, 4, 0, 6, 9, 5, 9, 5, 3, 3, 6, 9, 1, 4, 0, 6, 2, 5, },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 7, 3, 4, 7, 2, 3, 4, 7, 5, 9, 7, 6, 8, 0, 7, 0, 9, 4, 4, 1, 1, 9, 2, 4, 4, 8, 1, 3, 9, 1, 9, 0, 6, 7, 3, 8, 2, 8, 1, 2, 5, },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 4, 6, 9, 4, 4, 6, 9, 5, 1, 9, 5, 3, 6, 1, 4, 1, 8, 8, 8, 2, 3, 8, 4, 8, 9, 6, 2, 7, 8, 3, 8, 1, 3, 4, 7, 6, 5, 6, 2, 5, },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 9, 3, 8, 8, 9, 3, 9, 0, 3, 9, 0, 7, 2, 2, 8, 3, 7, 7, 6, 4, 7, 6, 9, 7, 9, 2, 5, 5, 6, 7, 6, 2, 6, 9, 5, 3, 1, 2, 5, },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 3, 8, 7, 7, 7, 8, 7, 8, 0, 7, 8, 1, 4, 4, 5, 6, 7, 5, 5, 2, 9, 5, 3, 9, 5, 8, 5, 1, 1, 3, 5, 2, 5, 3, 9, 0, 6, 2, 5, },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 7, 7, 5, 5, 5, 7, 5, 6, 1, 5, 6, 2, 8, 9, 1, 3, 5, 1, 0, 5, 9, 0, 7, 9, 1, 7, 0, 2, 2, 7, 0, 5, 0, 7, 8, 1, 2, 5, },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5, 5, 5, 1, 1, 1, 5, 1, 2, 3, 1, 2, 5, 7, 8, 2, 7, 0, 2, 1, 1, 8, 1, 5, 8, 3, 4, 0, 4, 5, 4, 1, 0, 1, 5, 6, 2, 5, },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 2, 2, 3, 0, 2, 4, 6, 2, 5, 1, 5, 6, 5, 4, 0, 4, 2, 3, 6, 3, 1, 6, 6, 8, 0, 9, 0, 8, 2, 0, 3, 1, 2, 5, },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 0, 4, 4, 6, 0, 4, 9, 2, 5, 0, 3, 1, 3, 0, 8, 0, 8, 4, 7, 2, 6, 3, 3, 3, 6, 1, 8, 1, 6, 4, 0, 6, 2, 5, },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 4, 4, 0, 8, 9, 2, 0, 9, 8, 5, 0, 0, 6, 2, 6, 1, 6, 1, 6, 9, 4, 5, 2, 6, 6, 7, 2, 3, 6, 3, 2, 8, 1, 2, 5, },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8, 8, 8, 1, 7, 8, 4, 1, 9, 7, 0, 0, 1, 2, 5, 2, 3, 2, 3, 3, 8, 9, 0, 5, 3, 3, 4, 4, 7, 2, 6, 5, 6, 2, 5, },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 7, 7, 6, 3, 5, 6, 8, 3, 9, 4, 0, 0, 2, 5, 0, 4, 6, 4, 6, 7, 7, 8, 1, 0, 6, 6, 8, 9, 4, 5, 3, 1, 2, 5, },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 5, 5, 2, 7, 1, 3, 6, 7, 8, 8, 0, 0, 5, 0, 0, 9, 2, 9, 3, 5, 5, 6, 2, 1, 3, 3, 7, 8, 9, 0, 6, 2, 5, },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 1, 0, 5, 4, 2, 7, 3, 5, 7, 6, 0, 1, 0, 0, 1, 8, 5, 8, 7, 1, 1, 2, 4, 2, 6, 7, 5, 7, 8, 1, 2, 5, },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 4, 2, 1, 0, 8, 5, 4, 7, 1, 5, 2, 0, 2, 0, 0, 3, 7, 1, 7, 4, 2, 2, 4, 8, 5, 3, 5, 1, 5, 6, 2, 5, },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 8, 4, 2, 1, 7, 0, 9, 4, 3, 0, 4, 0, 4, 0, 0, 7, 4, 3, 4, 8, 4, 4, 9, 7, 0, 7, 0, 3, 1, 2, 5, },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5, 6, 8, 4, 3, 4, 1, 8, 8, 6, 0, 8, 0, 8, 0, 1, 4, 8, 6, 9, 6, 8, 9, 9, 4, 1, 4, 0, 6, 2, 5, },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 3, 6, 8, 6, 8, 3, 7, 7, 2, 1, 6, 1, 6, 0, 2, 9, 7, 3, 9, 3, 7, 9, 8, 8, 2, 8, 1, 2, 5, },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 7, 3, 7, 3, 6, 7, 5, 4, 4, 3, 2, 3, 2, 0, 5, 9, 4, 7, 8, 7, 5, 9, 7, 6, 5, 6, 2, 5, },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 5, 4, 7, 4, 7, 3, 5, 0, 8, 8, 6, 4, 6, 4, 1, 1, 8, 9, 5, 7, 5, 1, 9, 5, 3, 1, 2, 5, },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 0, 9, 4, 9, 4, 7, 0, 1, 7, 7, 2, 9, 2, 8, 2, 3, 7, 9, 1, 5, 0, 3, 9, 0, 6, 2, 5, },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 8, 1, 8, 9, 8, 9, 4, 0, 3, 5, 4, 5, 8, 5, 6, 4, 7, 5, 8, 3, 0, 0, 7, 8, 1, 2, 5, },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 6, 3, 7, 9, 7, 8, 8, 0, 7, 0, 9, 1, 7, 1, 2, 9, 5, 1, 6, 6, 0, 1, 5, 6, 2, 5, },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 2, 7, 5, 9, 5, 7, 6, 1, 4, 1, 8, 3, 4, 2, 5, 9, 0, 3, 3, 2, 0, 3, 1, 2, 5, },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 4, 5, 5, 1, 9, 1, 5, 2, 2, 8, 3, 6, 6, 8, 5, 1, 8, 0, 6, 6, 4, 0, 6, 2, 5, },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 9, 1, 0, 3, 8, 3, 0, 4, 5, 6, 7, 3, 3, 7, 0, 3, 6, 1, 3, 2, 8, 1, 2, 5, },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5, 8, 2, 0, 7, 6, 6, 0, 9, 1, 3, 4, 6, 7, 4, 0, 7, 2, 2, 6, 5, 6, 2, 5, },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 6, 4, 1, 5, 3, 2, 1, 8, 2, 6, 9, 3, 4, 8, 1, 4, 4, 5, 3, 1, 2, 5, },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 3, 2, 8, 3, 0, 6, 4, 3, 6, 5, 3, 8, 6, 9, 6, 2, 8, 9, 0, 6, 2, 5, },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 6, 5, 6, 6, 1, 2, 8, 7, 3, 0, 7, 7, 3, 9, 2, 5, 7, 8, 1, 2, 5, },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 3, 1, 3, 2, 2, 5, 7, 4, 6, 1, 5, 4, 7, 8, 5, 1, 5, 6, 2, 5, },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 8, 6, 2, 6, 4, 5, 1, 4, 9, 2, 3, 0, 9, 5, 7, 0, 3, 1, 2, 5, },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 7, 2, 5, 2, 9, 0, 2, 9, 8, 4, 6, 1, 9, 1, 4, 0, 6, 2, 5, },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 4, 5, 0, 5, 8, 0, 5, 9, 6, 9, 2, 3, 8, 2, 8, 1, 2, 5, },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 4, 9, 0, 1, 1, 6, 1, 1, 9, 3, 8, 4, 7, 6, 5, 6, 2, 5, },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 9, 8, 0, 2, 3, 2, 2, 3, 8, 7, 6, 9, 5, 3, 1, 2, 5, },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5, 9, 6, 0, 4, 6, 4, 4, 7, 7, 5, 3, 9, 0, 6, 2, 5, },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 9, 2, 0, 9, 2, 8, 9, 5, 5, 0, 7, 8, 1, 2, 5, },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 3, 8, 4, 1, 8, 5, 7, 9, 1, 0, 1, 5, 6, 2, 5, },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 7, 6, 8, 3, 7, 1, 5, 8, 2, 0, 3, 1, 2, 5, },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 5, 3, 6, 7, 4, 3, 1, 6, 4, 0, 6, 2, 5, },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 9, 0, 7, 3, 4, 8, 6, 3, 2, 8, 1, 2, 5, },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 8, 1, 4, 6, 9, 7, 2, 6, 5, 6, 2, 5, },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 6, 2, 9, 3, 9, 4, 5, 3, 1, 2, 5, },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 5, 2, 5, 8, 7, 8, 9, 0, 6, 2, 5, },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 5, 1, 7, 5, 7, 8, 1, 2, 5, },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 1, 0, 3, 5, 1, 5, 6, 2, 5, },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 2, 0, 7, 0, 3, 1, 2, 5, },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 4, 4, 1, 4, 0, 6, 2, 5, },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 8, 8, 2, 8, 1, 2, 5, },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 7, 6, 5, 6, 2, 5, },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 9, 5, 3, 1, 2, 5, },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 9, 0, 6, 2, 5, },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 8, 1, 2, 5, },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 5, 6, 2, 5, },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 1, 2, 5, },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 2, 5, },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 5, },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 5, },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 5, },
		{ 0, 0, 0, 0, 0, 0, 0, 1, },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 2, },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 4, },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 8, },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 1, 6, },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 3, 2, },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 6, 4, },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 8, },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 2, 5, 6, },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 5, 1, 2, },
		{ 0, 0, 0, 0, 0, 0, 0, 1, 0, 2, 4, },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 4, 8, },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 4, 0, 9, 6, },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 8, 1, 9, 2, },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 1, 6, 3, 8, 4, },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 3, 2, 7, 6, 8, },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 6, 5, 5, 3, 6, },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 1, 3, 1, 0, 7, 2, },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 2, 6, 2, 1, 4, 4, },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 5, 2, 4, 2, 8, 8, },
		{ 0, 0, 0, 0, 0, 0, 0, 1, 0, 4, 8, 5, 7, 6, },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 9, 7, 1, 5, 2, },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 4, 1, 9, 4, 3, 0, 4, },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 8, 3, 8, 8, 6, 0, 8, },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 1, 6, 7, 7, 7, 2, 1, 6, },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 3, 3, 5, 5, 4, 4, 3, 2, },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 6, 7, 1, 0, 8, 8, 6, 4, },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 1, 3, 4, 2, 1, 7, 7, 2, 8, },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 2, 6, 8, 4, 3, 5, 4, 5, 6, },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 5, 3, 6, 8, 7, 0, 9, 1, 2, },
		{ 0, 0, 0, 0, 0, 0, 0, 1, 0, 7, 3, 7, 4, 1, 8, 2, 4, },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 2, 1, 4, 7, 4, 8, 3, 6, 4, 8, },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 4, 2, 9, 4, 9, 6, 7, 2, 9, 6, },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 8, 5, 8, 9, 9, 3, 4, 5, 9, 2, },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 1, 7, 1, 7, 9, 8, 6, 9, 1, 8, 4, },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 3, 4, 3, 5, 9, 7, 3, 8, 3, 6, 8, },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 6, 8, 7, 1, 9, 4, 7, 6, 7, 3, 6, },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 1, 3, 7, 4, 3, 8, 9, 5, 3, 4, 7, 2, },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 2, 7, 4, 8, 7, 7, 9, 0, 6, 9, 4, 4, },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 5, 4, 9, 7, 5, 5, 8, 1, 3, 8, 8, 8, },
		{ 0, 0, 0, 0, 0, 0, 0, 1, 0, 9, 9, 5, 1, 1, 6, 2, 7, 7, 7, 6, },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 2, 1, 9, 9, 0, 2, 3, 2, 5, 5, 5, 5, 2, },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 4, 3, 9, 8, 0, 4, 6, 5, 1, 1, 1, 0, 4, },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 8, 7, 9, 6, 0, 9, 3, 0, 2, 2, 2, 0, 8, },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 1, 7, 5, 9, 2, 1, 8, 6, 0, 4, 4, 4, 1, 6, },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 3, 5, 1, 8, 4, 3, 7, 2, 0, 8, 8, 8, 3, 2, },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 7, 0, 3, 6, 8, 7, 4, 4, 1, 7, 7, 6, 6, 4, },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 1, 4, 0, 7, 3, 7, 4, 8, 8, 3, 5, 5, 3, 2, 8, },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 2, 8, 1, 4, 7, 4, 9, 7, 6, 7, 1, 0, 6, 5, 6, },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 5, 6, 2, 9, 4, 9, 9, 5, 3, 4, 2, 1, 3, 1, 2, },
		{ 0, 0, 0, 0, 0, 0, 0, 1, 1, 2, 5, 8, 9, 9, 9, 0, 6, 8, 4, 2, 6, 2, 4, },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 5, 1, 7, 9, 9, 8, 1, 3, 6, 8, 5, 2, 4, 8, },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 4, 5, 0, 3, 5, 9, 9, 6, 2, 7, 3, 7, 0, 4, 9, 6, },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 9, 0, 0, 7, 1, 9, 9, 2, 5, 4, 7, 4, 0, 9, 9, 2, },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 1, 8, 0, 1, 4, 3, 9, 8, 5, 0, 9, 4, 8, 1, 9, 8, 4, },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 3, 6, 0, 2, 8, 7, 9, 7, 0, 1, 8, 9, 6, 3, 9, 6, 8, },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 7, 2, 0, 5, 7, 5, 9, 4, 0, 3, 7, 9, 2, 7, 9, 3, 6, },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 1, 4, 4, 1, 1, 5, 1, 8, 8, 0, 7, 5, 8, 5, 5, 8, 7, 2, },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 2, 8, 8, 2, 3, 0, 3, 7, 6, 1, 5, 1, 7, 1, 1, 7, 4, 4, },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 5, 7, 6, 4, 6, 0, 7, 5, 2, 3, 0, 3, 4, 2, 3, 4, 8, 8, },
		{ 0, 0, 0, 0, 0, 0, 0, 1, 1, 5, 2, 9, 2, 1, 5, 0, 4, 6, 0, 6, 8, 4, 6, 9, 7, 6, },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 2, 3, 0, 5, 8, 4, 3, 0, 0, 9, 2, 1, 3, 6, 9, 3, 9, 5, 2, },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 4, 6, 1, 1, 6, 8, 6, 0, 1, 8, 4, 2, 7, 3, 8, 7, 9, 0, 4, },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 9, 2, 2, 3, 3, 7, 2, 0, 3, 6, 8, 5, 4, 7, 7, 5, 8, 0, 8, },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 1, 8, 4, 4, 6, 7, 4, 4, 0, 7, 3, 7, 0, 9, 5, 5, 1, 6, 1, 6, },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 3, 6, 8, 9, 3, 4, 8, 8, 1, 4, 7, 4, 1, 9, 1, 0, 3, 2, 3, 2, },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 7, 3, 7, 8, 6, 9, 7, 6, 2, 9, 4, 8, 3, 8, 2, 0, 6, 4, 6, 4, },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 1, 4, 7, 5, 7, 3, 9, 5, 2, 5, 8, 9, 6, 7, 6, 4, 1, 2, 9, 2, 8, },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 2, 9, 5, 1, 4, 7, 9, 0, 5, 1, 7, 9, 3, 5, 2, 8, 2, 5, 8, 5, 6, },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 5, 9, 0, 2, 9, 5, 8, 1, 0, 3, 5, 8, 7, 0, 5, 6, 5, 1, 7, 1, 2, },
		{ 0, 0, 0, 0, 0, 0, 0, 1, 1, 8, 0, 5, 9, 1, 6, 2, 0, 7, 1, 7, 4, 1, 1, 3, 0, 3, 4, 2, 4, },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 2, 3, 6, 1, 1, 8, 3, 2, 4, 1, 4, 3, 4, 8, 2, 2, 6, 0, 6, 8, 4, 8, },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 4, 7, 2, 2, 3, 6, 6, 4, 8, 2, 8, 6, 9, 6, 4, 5, 2, 1, 3, 6, 9, 6, },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 9, 4, 4, 4, 7, 3, 2, 9, 6, 5, 7, 3, 9, 2, 9, 0, 4, 2, 7, 3, 9, 2, },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 1, 8, 8, 8, 9, 4, 6, 5, 9, 3, 1, 4, 7, 8, 5, 8, 0, 8, 5, 4, 7, 8, 4, },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 3, 7, 7, 7, 8, 9, 3, 1, 8, 6, 2, 9, 5, 7, 1, 6, 1, 7, 0, 9, 5, 6, 8, },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 7, 5, 5, 5, 7, 8, 6, 3, 7, 2, 5, 9, 1, 4, 3, 2, 3, 4, 1, 9, 1, 3, 6, },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 1, 5, 1, 1, 1, 5, 7, 2, 7, 4, 5, 1, 8, 2, 8, 6, 4, 6, 8, 3, 8, 2, 7, 2, },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 2, 2, 3, 1, 4, 5, 4, 9, 0, 3, 6, 5, 7, 2, 9, 3, 6, 7, 6, 5, 4, 4, },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 6, 0, 4, 4, 6, 2, 9, 0, 9, 8, 0, 7, 3, 1, 4, 5, 8, 7, 3, 5, 3, 0, 8, 8, },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 0, 8, 9, 2, 5, 8, 1, 9, 6, 1, 4, 6, 2, 9, 1, 7, 4, 7, 0, 6, 1, 7, 6, },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 2, 4, 1, 7, 8, 5, 1, 6, 3, 9, 2, 2, 9, 2, 5, 8, 3, 4, 9, 4, 1, 2, 3, 5, 2, },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 4, 8, 3, 5, 7, 0, 3, 2, 7, 8, 4, 5, 8, 5, 1, 6, 6, 9, 8, 8, 2, 4, 7, 0, 4, },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 9, 6, 7, 1, 4, 0, 6, 5, 5, 6, 9, 1, 7, 0, 3, 3, 3, 9, 7, 6, 4, 9, 4, 0, 8, },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 1, 9, 3, 4, 2, 8, 1, 3, 1, 1, 3, 8, 3, 4, 0, 6, 6, 7, 9, 5, 2, 9, 8, 8, 1, 6, },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 3, 8, 6, 8, 5, 6, 2, 6, 2, 2, 7, 6, 6, 8, 1, 3, 3, 5, 9, 0, 5, 9, 7, 6, 3, 2, },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 7, 7, 3, 7, 1, 2, 5, 2, 4, 5, 5, 3, 3, 6, 2, 6, 7, 1, 8, 1, 1, 9, 5, 2, 6, 4, },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 1, 5, 4, 7, 4, 2, 5, 0, 4, 9, 1, 0, 6, 7, 2, 5, 3, 4, 3, 6, 2, 3, 9, 0, 5, 2, 8, },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 9, 4, 8, 5, 0, 0, 9, 8, 2, 1, 3, 4, 5, 0, 6, 8, 7, 2, 4, 7, 8, 1, 0, 5, 6, },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 6, 1, 8, 9, 7, 0, 0, 1, 9, 6, 4, 2, 6, 9, 0, 1, 3, 7, 4, 4, 9, 5, 6, 2, 1, 1, 2, },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 3, 7, 9, 4, 0, 0, 3, 9, 2, 8, 5, 3, 8, 0, 2, 7, 4, 8, 9, 9, 1, 2, 4, 2, 2, 4, },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 2, 4, 7, 5, 8, 8, 0, 0, 7, 8, 5, 7, 0, 7, 6, 0, 5, 4, 9, 7, 9, 8, 2, 4, 8, 4, 4, 8, },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 4, 9, 5, 1, 7, 6, 0, 1, 5, 7, 1, 4, 1, 5, 2, 1, 0, 9, 9, 5, 9, 6, 4, 9, 6, 8, 9, 6, },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 0, 3, 5, 2, 0, 3, 1, 4, 2, 8, 3, 0, 4, 2, 1, 9, 9, 1, 9, 2, 9, 9, 3, 7, 9, 2, },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 1, 9, 8, 0, 7, 0, 4, 0, 6, 2, 8, 5, 6, 6, 0, 8, 4, 3, 9, 8, 3, 8, 5, 9, 8, 7, 5, 8, 4, },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 3, 9, 6, 1, 4, 0, 8, 1, 2, 5, 7, 1, 3, 2, 1, 6, 8, 7, 9, 6, 7, 7, 1, 9, 7, 5, 1, 6, 8, },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 7, 9, 2, 2, 8, 1, 6, 2, 5, 1, 4, 2, 6, 4, 3, 3, 7, 5, 9, 3, 5, 4, 3, 9, 5, 0, 3, 3, 6, },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 1, 5, 8, 4, 5, 6, 3, 2, 5, 0, 2, 8, 5, 2, 8, 6, 7, 5, 1, 8, 7, 0, 8, 7, 9, 0, 0, 6, 7, 2, },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 3, 1, 6, 9, 1, 2, 6, 5, 0, 0, 5, 7, 0, 5, 7, 3, 5, 0, 3, 7, 4, 1, 7, 5, 8, 0, 1, 3, 4, 4, },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 6, 3, 3, 8, 2, 5, 3, 0, 0, 1, 1, 4, 1, 1, 4, 7, 0, 0, 7, 4, 8, 3, 5, 1, 6, 0, 2, 6, 8, 8, },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 6, 7, 6, 5, 0, 6, 0, 0, 2, 2, 8, 2, 2, 9, 4, 0, 1, 4, 9, 6, 7, 0, 3, 2, 0, 5, 3, 7, 6, },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 2, 5, 3, 5, 3, 0, 1, 2, 0, 0, 4, 5, 6, 4, 5, 8, 8, 0, 2, 9, 9, 3, 4, 0, 6, 4, 1, 0, 7, 5, 2, },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 5, 0, 7, 0, 6, 0, 2, 4, 0, 0, 9, 1, 2, 9, 1, 7, 6, 0, 5, 9, 8, 6, 8, 1, 2, 8, 2, 1, 5, 0, 4, },
		{ 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 4, 1, 2, 0, 4, 8, 0, 1, 8, 2, 5, 8, 3, 5, 2, 1, 1, 9, 7, 3, 6, 2, 5, 6, 4, 3, 0, 0, 8, },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 2, 8, 2, 4, 0, 9, 6, 0, 3, 6, 5, 1, 6, 7, 0, 4, 2, 3, 9, 4, 7, 2, 5, 1, 2, 8, 6, 0, 1, 6, },
	};

	//                                       0.0                                                                                                                                                      > 0b0'00000000'00000000000000000000000 -- 0b0'00000000'11111111111111111111111 <                                       0.000000000000000000000000000000000000011754942807573642917278829910357665133228589927589904276829631184250030649651730385585324256680905818939208984374
	//                                       0.000000000000000000000000000000000000011754942807573642917278829910357665133228589927589904276829631184250030649651730385585324256680905818939208984375 > 0b0'00000001'00000000000000000000000 -- 0b0'01111110'11111111111111111111111 <                                       0.9999999701976776123046874
	//                                       0.9999999701976776123046875                                                                                                                              > 0b0'01111111'00000000000000000000000 -- 0b0'10010110'11111111111111111111111 <                                16777215.4
	//                                16777215.5                                                                                                                                                      > 0b0'10010111'00000000000000000000000 -- 0b0'11111110'11111111111111111111111 < 340282356779733661637539395458142568447
	// 340282356779733661637539395458142568448                                                                                                                                                        > 0b0'11111111'00000000000000000000000
	if (0)
	for (int magnitude = 0b10110100; magnitude < 0b11111111; magnitude++)
	{
		std::cout << "magnitude = " << std::bitset<8>(magnitude) << '\n';

		char * first = digits[magnitude] + 0;
		do
		{
			first++;
		}
		while (*first == '0');

		char * dot = first;
		if (*first == '.')
		{
			do
			{
				first++;
			}
			while (*first == '0');
		}
		else
		{
			do
			{
				dot++;
			}
			while (*dot != '.');
		}

		char * last = first > dot ? first : dot;
		do
		{
			last++;
		}
		while (*last != 0);

		if (*(last - 1) == '.')
		{
			last--;
		}

		for (unsigned int mantissa = 0; mantissa < 0b100000000000000000000000; mantissa++)
		{
			const unsigned int value = (magnitude << 23) | mantissa;

			const char * const begin = first == digits[magnitude] ? digits[magnitude] : digits[magnitude] + 1;
			INFO(std::bitset<32>(value) << " : " << std::string_view(begin, last - begin));

			fio::ssize offset;
			unsigned char carry;

			carry = 1;
			offset = last - dot;
			if (offset != 0)
			{
				offset--;
				do
				{
					char digit = dot[offset] - carry;
					if (digit < '0')
					{
						digit += 10;
					}
					else
					{
						carry = 0;
					}
					dot[offset] = digit;
					if (carry == 0)
						goto done_dec;

					offset--;
				}
				while (offset != 0);
			}
			offset = dot - digits[magnitude];
			if (offset != 0)
			{
				do
				{
					offset--;

					char digit = digits[magnitude][offset] - carry;
					if (digit < '0')
					{
						digit += 10;
					}
					else
					{
						carry = 0;
					}
					digits[magnitude][offset] = digit;
					if (carry == 0)
						goto done_dec;
				}
				while (offset != 0);
			}
		done_dec:

			float fval;
			from_chars(begin, last, fval);
			REQUIRE(*reinterpret_cast<const unsigned int *>(&fval) == value + 0);

			carry = 1;
			offset = last - dot;
			if (offset != 0)
			{
				offset--;
				do
				{
					char digit = dot[offset] + carry;
					if (digit > '9')
					{
						digit -= 10;
					}
					else
					{
						carry = 0;
					}
					dot[offset] = digit;
					if (carry == 0)
						goto done_inc;

					offset--;
				}
				while (offset != 0);
			}
			offset = dot - digits[magnitude];
			if (offset != 0)
			{
				do
				{
					offset--;

					char digit = digits[magnitude][offset] + carry;
					if (digit > '9')
					{
						digit -= 10;
					}
					else
					{
						carry = 0;
					}
					digits[magnitude][offset] = digit;
					if (carry == 0)
						goto done_inc;
				}
				while (offset != 0);
			}
		done_inc:

			float gval;
			from_chars(begin, last, gval);
			REQUIRE(*reinterpret_cast<const unsigned int *>(&gval) == value + 1);

			carry = 0;
			offset = last - dot;
			if (offset != 0)
			{
				const signed char * beg = steps[magnitude] + (dot - digits[magnitude]);

				offset--;
				do
				{
					char digit = dot[offset] + beg[offset] + carry;
					if (digit > '9')
					{
						carry = 1;
						digit -= 10;
					}
					else
					{
						carry = 0;
					}
					dot[offset] = digit;
					offset--;
				}
				while (offset != 0);
			}
			offset = dot - digits[magnitude];
			if (offset != 0)
			{
				do
				{
					offset--;

					char digit = digits[magnitude][offset] + steps[magnitude][offset] + carry;
					if (digit > '9')
					{
						carry = 1;
						digit -= 10;
					}
					else
					{
						carry = 0;
					}
					digits[magnitude][offset] = digit;
				}
				while (offset != 0);
			}

			if (first > dot)
			{
				if (*(first - 1) > '0')
				{
					first--;
				}
			}
			else
			{
				if (digits[magnitude][0] != '0') // need the extra digit (only happens when integer part is nonzero)
				{
					first = digits[magnitude];
				}
			}
		}
	}

	// generate tables
	if (0)
	{
		std::ofstream file("single-precision.txt");
		file << "char digits[][1 + 2 + 150 + 1] = {\n";
		for (unsigned int value = 0b0'00000000'00000000000000000000000; value < 0b0'11111111'00000000000000000000000; value += 0b0'00000001'00000000000000000000000)
		{
			char buffer[300];
			buffer[0] = '0';

			const unsigned int next = value + 1;
			const float value_as_float = *reinterpret_cast<const float *>(&value);
			const float next_as_float = *reinterpret_cast<const float *>(&next);
			const double middle = static_cast<double>(value_as_float) * .5 + static_cast<double>(next_as_float) * .5;
			const int length = std::snprintf(buffer + 1, 300 - 1, "%.200f", middle) + 1; // note null-terminates buffer

			char * last = buffer + length;
			if (*(last - 1) == '0')
			{
				do
				{
					last--;
				}
				while (*(last - 1) == '0');
			}

			file << "\t\"" << std::string_view(buffer, last - buffer) << "\",\n";
		}
		file << "};\n";
		file << "signed char steps[][1 + 2 + 150 + 1] = {\n";
		for (unsigned int value = 0b0'00000000'00000000000000000000000; value < 0b0'11111111'00000000000000000000000; value += 0b0'00000001'00000000000000000000000)
		{
			char buffer_current[300];
			buffer_current[0] = '0';
			char buffer_next[300];
			buffer_next[0] = '0';
			signed char buffer_steps[300];

			const unsigned int next = value + 1;
			const float value_as_float = *reinterpret_cast<const float *>(&value);
			const float next_as_float = *reinterpret_cast<const float *>(&next);
			const int length_current = std::snprintf(buffer_current + 1, 300 - 1, "%.200f", static_cast<double>(value_as_float)) + 1; // note null-terminates buffer
			const int length_next = std::snprintf(buffer_next + 1, 300 - 1, "%.200f", static_cast<double>(next_as_float)) + 1; // note null-terminates buffer
			const int length = length_current < length_next ? length_current : length_next;

			fio::ssize offset = length;
			signed char diff;
			do
			{
				offset--;

				diff = buffer_next[offset] - buffer_current[offset]; // -9 <= diff <= 9
			}
			while (diff == 0);

			offset++;

			signed char * last = buffer_steps + offset;

			signed char borrow = 0;
			signed char carry = 0;
			do
			{
				offset--;

				diff = buffer_next[offset] - buffer_current[offset] - borrow; // -9 <= diff <= 9

				if (diff < 0)
				{
					borrow = 1;
					diff += 10;
				}
				else
				{
					borrow = 0;
				}
				signed char step = diff + carry;
				if (step > 9)
				{
					carry = 1;
					step -= 10;
				}
				else
				{
					carry = 0;
				}
				buffer_steps[offset] = step;
			}
			while (offset > 0);

			file << "\t{ ";

			offset = buffer_steps - last;
			do
			{
				file << int(last[offset]) << ", ";

				offset++;
			}
			while (offset < 0);

			file << "},\n";
		}
		file << "};\n";
	}

	BENCHMARK_DUMP("plot/from_chars_float32.dump", lin_style, 0, 256, 1, "magnitude (exponent + 127)")
	{
		BENCHMARK_GROUP("sscanf (std)")(Catch::Benchmark::Groupometer meter)
		{
			const char * const buffer = digits[meter.size()] + 1;

			meter.measure([&](int)
			{
				float val;
				std::sscanf(buffer, "%f", &val);
				return val;
			});
		};

		BENCHMARK_GROUP("strtof (std)")(Catch::Benchmark::Groupometer meter)
		{
			const char * const buffer = digits[meter.size()] + 1;

			meter.measure([&](int)
			{
				char * end;
				return std::strtof(buffer, &end);
			});
		};

#if (__cplusplus >= 201703L) || (defined(_MSVC_LANG) && _MSVC_LANG >= 201703L)
		BENCHMARK_GROUP("from\\_chars (std)")(Catch::Benchmark::Groupometer meter)
		{
			const char * const buffer = digits[meter.size()] + 1;

			meter.measure([&](int)
			{
				float val;
				std::from_chars(buffer, buffer + 154 - 1 - 1, val);
				return val;
			});
		};
#endif

#if HAVE_EASTDC
		BENCHMARK_GROUP("Sscanf (eastdc)")(Catch::Benchmark::Groupometer meter)
		{
			const char * const buffer = digits[meter.size()] + 1;

			meter.measure([&](int)
			{
				float val;
				EA::StdC::Sscanf(buffer, "%f", &val);
				return val;
			});
		};
#endif

		BENCHMARK_GROUP("from\\_chars")(Catch::Benchmark::Groupometer meter)
		{
			const char * const buffer = digits[meter.size()] + 1;

			meter.measure([&](int)
			{
				float val;
				/*fio::*/from_chars(buffer, buffer + 154 - 1 - 1, val);
				return val;
			});
		};
	}
}

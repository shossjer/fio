#include <catch2/catch.hpp>

#include "catchhacks.hpp"

#include "fio/from_chars.hpp"

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

TEST_CASE("from_chars float32 in-betweens", "[.][dump]")
{
	char buffer[255][200];
	for (unsigned int magnitude = 0b00000000; magnitude < 0b11111111; magnitude++)
	{
		const unsigned int value = magnitude << 23;
		const unsigned int next = value + 1;
		const float value_as_float = fio::bit_cast<float>(value);
		const float next_as_float = fio::bit_cast<float>(next);
		const double middle = static_cast<double>(value_as_float) * .5 + static_cast<double>(next_as_float) * .5;
		const int length = std::snprintf(buffer[magnitude] + 1, 200 - 1, "%.150f", middle);
		REQUIRE(length > 0);
		REQUIRE(length < 200);

		buffer[magnitude][0] = 0; // paranoid

		int size = length;
		if (buffer[magnitude][size] == '0')
		{
			do
			{
				size--;
			}
			while (buffer[magnitude][size] == '0');
		}

		buffer[magnitude][0] = static_cast<char>(static_cast<unsigned char>(size));
	}

	BENCHMARK_DUMP("plot/from_chars_float32_in_betweens.dump", lin_style, 0, 255, 1, "magnitude (exponent + 128)")
	{
		BENCHMARK_GROUP("sscanf (std)")(Catch::Benchmark::Groupometer meter)
		{
			const char * const data = buffer[meter.size()] + 1;

			meter.measure([&](int)
			{
				float val;
				std::sscanf(data, "%f", &val);
				return val;
			});
		};

		BENCHMARK_GROUP("strtof (std)")(Catch::Benchmark::Groupometer meter)
		{
			const char * const data = buffer[meter.size()] + 1;

			meter.measure([&](int)
			{
				char * end;
				return std::strtof(data, &end);
			});
		};

#if ((__cplusplus >= 201703L) || (defined(_MSVC_LANG) && _MSVC_LANG >= 201703L)) &&\
    ((defined(_MSC_VER) && _MSC_VER >= 1924) || (defined(_GLIBCXX_RELEASE) && _GLIBCXX_RELEASE >= 11))
		BENCHMARK_GROUP("from\\_chars (std)")(Catch::Benchmark::Groupometer meter)
		{
			const fio::usize size = buffer[meter.size()][0];
			const char * const begin = buffer[meter.size()] + 1;
			const char * const end = begin + size;

			meter.measure([&](int)
			{
				float val;
				std::from_chars(begin, end, val);
				return val;
			});
		};
#endif

#if HAVE_EASTDC
		BENCHMARK_GROUP("Sscanf (eastdc)")(Catch::Benchmark::Groupometer meter)
		{
			const char * const data = buffer[meter.size()] + 1;

			meter.measure([&](int)
			{
				float val;
				EA::StdC::Sscanf(data, "%f", &val);
				return val;
			});
		};
#endif

		BENCHMARK_GROUP("from\\_chars")(Catch::Benchmark::Groupometer meter)
		{
			const fio::usize size = static_cast<unsigned char>(buffer[meter.size()][0]);
			const char * const begin = buffer[meter.size()] + 1;
			const char * const end = begin + size;

			meter.measure([&](int)
			{
				float val;
				fio::from_chars(begin, end, val);
				return val;
			});
		};
	}
}

#if ((__cplusplus >= 201703L) || (defined(_MSVC_LANG) && _MSVC_LANG >= 201703L)) &&\
    ((defined(_MSC_VER) && _MSC_VER >= 1924) || (defined(_GLIBCXX_RELEASE) && _GLIBCXX_RELEASE >= 11))
TEST_CASE("from_chars float32 shortest", "[.][dump]")
{
	char buffer[255][2][50];
	for (unsigned int magnitude = 0b00000000; magnitude < 0b11111111; magnitude++)
	{
		const unsigned int valuelo = (magnitude << 23) + 0;
		const float valuelo_as_float = fio::bit_cast<float>(valuelo);
		const auto reslo = std::to_chars(buffer[magnitude][0] + 1, buffer[magnitude][0] + 50, valuelo_as_float);
		REQUIRE(reslo.ec == std::errc{});

		buffer[magnitude][0][0] = 0; // paranoid

		fio::usize sizelo = static_cast<fio::usize>(reslo.ptr - buffer[magnitude][0]);
		if (buffer[magnitude][0][sizelo] == '0')
		{
			do
			{
				sizelo--;
			}
			while (buffer[magnitude][0][sizelo] == '0');
		}

		buffer[magnitude][0][0] = static_cast<unsigned char>(sizelo);

		const unsigned int valuehi = (magnitude << 23) + 0b11111111111111111111111;
		const float valuehi_as_float = fio::bit_cast<float>(valuehi);
		const auto reshi = std::to_chars(buffer[magnitude][1] + 1, buffer[magnitude][1] + 50, valuehi_as_float);
		REQUIRE(reshi.ec == std::errc{});

		buffer[magnitude][1][0] = 0; // paranoid

		fio::usize sizehi = static_cast<fio::usize>(reshi.ptr - buffer[magnitude][1]);
		if (buffer[magnitude][1][sizehi] == '0')
		{
			do
			{
				sizehi--;
			}
			while (buffer[magnitude][1][sizehi] == '0');
		}

		buffer[magnitude][1][0] = static_cast<unsigned char>(sizehi);
	}

	BENCHMARK_DUMP("plot/from_chars_float32_shortest.dump", lin_style, 0, 255, 1, "magnitude (exponent + 128)")
	{
		BENCHMARK_GROUP("sscanf (std)")(Catch::Benchmark::Groupometer meter)
		{
			const char * const datalo = buffer[meter.size()][0] + 1;
			const char * const datahi = buffer[meter.size()][1] + 1;

			meter.measure([&](int)
			{
				float vallo;
				std::sscanf(datalo, "%f", &vallo);
				float valhi;
				std::sscanf(datahi, "%f", &valhi);
				return valhi - vallo;
			});
		};

		BENCHMARK_GROUP("strtof (std)")(Catch::Benchmark::Groupometer meter)
		{
			const char * const datalo = buffer[meter.size()][0] + 1;
			const char * const datahi = buffer[meter.size()][1] + 1;

			meter.measure([&](int)
			{
				char * end;
				return std::strtof(datahi, &end) - std::strtof(datalo, &end);
			});
		};

		BENCHMARK_GROUP("from\\_chars (std)")(Catch::Benchmark::Groupometer meter)
		{
			const fio::usize sizelo = buffer[meter.size()][0][0];
			const fio::usize sizehi = buffer[meter.size()][1][0];
			const char * const beginlo = buffer[meter.size()][0] + 1;
			const char * const beginhi = buffer[meter.size()][1] + 1;
			const char * const endlo = beginlo + sizelo;
			const char * const endhi = beginhi + sizehi;

			meter.measure([&](int)
			{
				float vallo;
				std::from_chars(beginlo, endlo, vallo);
				float valhi;
				std::from_chars(beginhi, endhi, valhi);
				return valhi - vallo;
			});
		};

#if HAVE_EASTDC
		BENCHMARK_GROUP("Sscanf (eastdc)")(Catch::Benchmark::Groupometer meter)
		{
			const char * const datalo = buffer[meter.size()][0] + 1;
			const char * const datahi = buffer[meter.size()][1] + 1;

			meter.measure([&](int)
			{
				float vallo;
				EA::StdC::Sscanf(datalo, "%f", &vallo);
				float valhi;
				EA::StdC::Sscanf(datahi, "%f", &valhi);
				return valhi - vallo;
			});
		};
#endif

		BENCHMARK_GROUP("from\\_chars")(Catch::Benchmark::Groupometer meter)
		{
			const fio::usize sizelo = buffer[meter.size()][0][0];
			const fio::usize sizehi = buffer[meter.size()][1][0];
			const char * const beginlo = buffer[meter.size()][0] + 1;
			const char * const beginhi = buffer[meter.size()][1] + 1;
			const char * const endlo = beginlo + sizelo;
			const char * const endhi = beginhi + sizehi;

			meter.measure([&](int)
			{
				float vallo;
				fio::from_chars(beginlo, endlo, vallo);
				float valhi;
				fio::from_chars(beginhi, endhi, valhi);
				return valhi - vallo;
			});
		};
	}
}
#endif

#include <iostream>
#include <fstream>
#include <bitset>

TEST_CASE("from_chars float32 in-betweens test", "[.][test]")
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
#if defined(__clang__)
#elif defined(__GNUC__)
# pragma GCC diagnostic push
# pragma GCC diagnostic ignored "-Wstringop-overflow"
#endif
	for (unsigned int magnitude = 0b00000000; magnitude < 0b11111111; magnitude++)
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
					int digit = dot[offset] - carry;
					if (digit < '0')
					{
						digit += 10;
					}
					else
					{
						carry = 0;
					}
					dot[offset] = static_cast<char>(digit);
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

					int digit = digits[magnitude][offset] - carry;
					if (digit < '0')
					{
						digit += 10;
					}
					else
					{
						carry = 0;
					}
					digits[magnitude][offset] = static_cast<char>(digit);
					if (carry == 0)
						goto done_dec;
				}
				while (offset != 0);
			}
		done_dec:

			float fval = fio::bit_cast<float>(-1);
			fio::from_chars(begin, last, fval);
			REQUIRE(fio::bit_cast<unsigned int>(fval) == value + 0);

			carry = 1;
			offset = last - dot;
			if (offset != 0)
			{
				offset--;
				do
				{
					int digit = dot[offset] + carry;
					if (digit > '9')
					{
						digit -= 10;
					}
					else
					{
						carry = 0;
					}
					dot[offset] = static_cast<char>(digit);
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

					int digit = digits[magnitude][offset] + carry;
					if (digit > '9')
					{
						digit -= 10;
					}
					else
					{
						carry = 0;
					}
					digits[magnitude][offset] = static_cast<char>(digit);
					if (carry == 0)
						goto done_inc;
				}
				while (offset != 0);
			}
		done_inc:

			float gval = fio::bit_cast<float>(-1);
			fio::from_chars(begin, last, gval);
			REQUIRE(fio::bit_cast<unsigned int>(gval) == value + 1);

			carry = 0;
			offset = last - dot;
			if (offset != 0)
			{
				const signed char * beg = steps[magnitude] + (dot - digits[magnitude]);

				offset--;
				do
				{
					int digit = dot[offset] + beg[offset] + carry;
					if (digit > '9')
					{
						carry = 1;
						digit -= 10;
					}
					else
					{
						carry = 0;
					}
					dot[offset] = static_cast<char>(digit);
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

					int digit = digits[magnitude][offset] + steps[magnitude][offset] + carry;
					if (digit > '9')
					{
						carry = 1;
						digit -= 10;
					}
					else
					{
						carry = 0;
					}
					digits[magnitude][offset] = static_cast<char>(digit);
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
#if defined(__clang__)
#elif defined(__GNUC__)
# pragma GCC diagnostic pop
#endif
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
			const float value_as_float = fio::bit_cast<float>(value);
			const float next_as_float = fio::bit_cast<float>(next);
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

			file << "\t\"" << std::string_view(buffer, static_cast<fio::usize>(last - buffer)) << "\",\n";
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
			const float value_as_float = fio::bit_cast<float>(value);
			const float next_as_float = fio::bit_cast<float>(next);
			const int length_current = std::snprintf(buffer_current + 1, 300 - 1, "%.200f", static_cast<double>(value_as_float)) + 1; // note null-terminates buffer
			const int length_next = std::snprintf(buffer_next + 1, 300 - 1, "%.200f", static_cast<double>(next_as_float)) + 1; // note null-terminates buffer
			const int length = length_current < length_next ? length_current : length_next;

			fio::ssize offset = length;
			int diff;
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
				int step = diff + carry;
				if (step > 9)
				{
					carry = 1;
					step -= 10;
				}
				else
				{
					carry = 0;
				}
				buffer_steps[offset] = static_cast<signed char>(step);
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
#if ((__cplusplus >= 201703L) || (defined(_MSVC_LANG) && _MSVC_LANG >= 201703L)) &&\
    ((defined(_MSC_VER) && _MSC_VER >= 1924) || (defined(_GLIBCXX_RELEASE) && _GLIBCXX_RELEASE >= 11))
		file << "char shortest_representations[][1 + 2 + 150 + 1] = {\n";
		for (unsigned int value = 0b0'00000000'00000000000000000000000; value < 0b0'11111111'00000000000000000000000; value += 0b0'00000001'00000000000000000000000)
		{
			char buffer[300];

			const unsigned int valuelo = value + 0;
			const float valuelo_as_float = fio::bit_cast<float>(valuelo);
			const auto reslo = std::to_chars(buffer + 0, buffer + 300, valuelo_as_float);

			file << "\t\"" << std::string_view(buffer, reslo.ptr - buffer) << "\",\n";
		}
		file << '\n';
		for (unsigned int value = 0b0'00000000'00000000000000000000000; value < 0b0'11111111'00000000000000000000000; value += 0b0'00000001'00000000000000000000000)
		{
			char buffer[300];

			const unsigned int valuehi = value + 0b11111111111111111111111;
			const float valuehi_as_float = fio::bit_cast<float>(valuehi);
			const auto reshi = std::to_chars(buffer + 0, buffer + 300, valuehi_as_float);

			file << "\t\"" << std::string_view(buffer, reshi.ptr - buffer) << "\",\n";
		}
		file << "};\n";
#endif
	}
}

#if ((__cplusplus >= 201703L) || (defined(_MSVC_LANG) && _MSVC_LANG >= 201703L)) &&\
    ((defined(_MSC_VER) && _MSC_VER >= 1924) || (defined(_GLIBCXX_RELEASE) && _GLIBCXX_RELEASE >= 11))
TEST_CASE("from_chars float32 shortest test", "[.][test]")
{
	static const char * shortest_representations[] = {
		"0",
		"1.1754944e-38",
		"2.3509887e-38",
		"4.7019774e-38",
		"9.403955e-38",
		"1.880791e-37",
		"3.761582e-37",
		"7.523164e-37",
		"1.5046328e-36",
		"3.0092655e-36",
		"6.018531e-36",
		"1.2037062e-35",
		"2.4074124e-35",
		"4.814825e-35",
		"9.62965e-35",
		"1.92593e-34",
		"3.85186e-34",
		"7.70372e-34",
		"1.540744e-33",
		"3.081488e-33",
		"6.162976e-33",
		"1.2325952e-32",
		"2.4651903e-32",
		"4.9303807e-32",
		"9.8607613e-32",
		"1.9721523e-31",
		"3.9443045e-31",
		"7.888609e-31",
		"1.5777218e-30",
		"3.1554436e-30",
		"6.3108872e-30",
		"1.2621775e-29",
		"2.524355e-29",
		"5.04871e-29",
		"1.009742e-28",
		"2.019484e-28",
		"4.038968e-28",
		"8.077936e-28",
		"1.6155871e-27",
		"3.2311743e-27",
		"6.4623485e-27",
		"1.2924697e-26",
		"2.5849394e-26",
		"5.169879e-26",
		"1.0339758e-25",
		"2.0679515e-25",
		"4.135903e-25",
		"8.271806e-25",
		"1.6543612e-24",
		"3.3087225e-24",
		"6.617445e-24",
		"1.323489e-23",
		"2.646978e-23",
		"5.293956e-23",
		"1.0587912e-22",
		"2.1175824e-22",
		"4.2351647e-22",
		"8.4703295e-22",
		"1.6940659e-21",
		"3.3881318e-21",
		"6.7762636e-21",
		"1.3552527e-20",
		"2.7105054e-20",
		"5.421011e-20",
		"1.0842022e-19",
		"2.1684043e-19",
		"4.3368087e-19",
		"8.6736174e-19",
		"1.7347235e-18",
		"3.469447e-18",
		"6.938894e-18",
		"1.3877788e-17",
		"2.7755576e-17",
		"5.551115e-17",
		"1.110223e-16",
		"2.220446e-16",
		"4.440892e-16",
		"8.881784e-16",
		"1.7763568e-15",
		"3.5527137e-15",
		"7.1054274e-15",
		"1.4210855e-14",
		"2.842171e-14",
		"5.684342e-14",
		"1.1368684e-13",
		"2.2737368e-13",
		"4.5474735e-13",
		"9.094947e-13",
		"1.8189894e-12",
		"3.637979e-12",
		"7.275958e-12",
		"1.4551915e-11",
		"2.910383e-11",
		"5.820766e-11",
		"1.1641532e-10",
		"2.3283064e-10",
		"4.656613e-10",
		"9.313226e-10",
		"1.8626451e-09",
		"3.7252903e-09",
		"7.450581e-09",
		"1.4901161e-08",
		"2.9802322e-08",
		"5.9604645e-08",
		"1.1920929e-07",
		"2.3841858e-07",
		"4.7683716e-07",
		"9.536743e-07",
		"1.9073486e-06",
		"3.8146973e-06",
		"7.6293945e-06",
		"1.5258789e-05",
		"3.0517578e-05",
		"6.1035156e-05",
		"0.00012207031",
		"0.00024414062",
		"0.00048828125",
		"0.0009765625",
		"0.001953125",
		"0.00390625",
		"0.0078125",
		"0.015625",
		"0.03125",
		"0.0625",
		"0.125",
		"0.25",
		"0.5",
		"1",
		"2",
		"4",
		"8",
		"16",
		"32",
		"64",
		"128",
		"256",
		"512",
		"1024",
		"2048",
		"4096",
		"8192",
		"16384",
		"32768",
		"65536",
		"131072",
		"262144",
		"524288",
		"1048576",
		"2097152",
		"4194304",
		"8388608",
		"16777216",
		"33554432",
		"67108864",
		"134217728",
		"268435456",
		"536870912",
		"1073741824",
		"2147483648",
		"4294967296",
		"8589934592",
		"17179869184",
		"34359738368",
		"68719476736",
		"137438953472",
		"274877906944",
		"549755813888",
		"1099511627776",
		"2199023255552",
		"4398046511104",
		"8.796093e+12",
		"1.7592186e+13",
		"3.5184372e+13",
		"7.0368744e+13",
		"1.4073749e+14",
		"2.8147498e+14",
		"5.6294995e+14",
		"1.1258999e+15",
		"2.2517998e+15",
		"4.5035996e+15",
		"9.007199e+15",
		"1.8014399e+16",
		"3.6028797e+16",
		"7.2057594e+16",
		"1.4411519e+17",
		"2.8823038e+17",
		"5.7646075e+17",
		"1.1529215e+18",
		"2.305843e+18",
		"4.611686e+18",
		"9.223372e+18",
		"1.8446744e+19",
		"3.689349e+19",
		"7.378698e+19",
		"1.4757395e+20",
		"2.951479e+20",
		"5.902958e+20",
		"1.1805916e+21",
		"2.3611832e+21",
		"4.7223665e+21",
		"9.444733e+21",
		"1.8889466e+22",
		"3.7778932e+22",
		"7.5557864e+22",
		"1.5111573e+23",
		"3.0223145e+23",
		"6.044629e+23",
		"1.2089258e+24",
		"2.4178516e+24",
		"4.8357033e+24",
		"9.671407e+24",
		"1.9342813e+25",
		"3.8685626e+25",
		"7.7371252e+25",
		"1.5474251e+26",
		"3.0948501e+26",
		"6.1897002e+26",
		"1.2379401e+27",
		"2.4758801e+27",
		"4.9517602e+27",
		"9.9035203e+27",
		"1.9807041e+28",
		"3.9614081e+28",
		"7.9228163e+28",
		"1.5845633e+29",
		"3.1691265e+29",
		"6.338253e+29",
		"1.2676506e+30",
		"2.5353012e+30",
		"5.0706024e+30",
		"1.0141205e+31",
		"2.028241e+31",
		"4.056482e+31",
		"8.112964e+31",
		"1.6225928e+32",
		"3.2451855e+32",
		"6.490371e+32",
		"1.2980742e+33",
		"2.5961484e+33",
		"5.192297e+33",
		"1.0384594e+34",
		"2.0769187e+34",
		"4.1538375e+34",
		"8.307675e+34",
		"1.661535e+35",
		"3.32307e+35",
		"6.64614e+35",
		"1.329228e+36",
		"2.658456e+36",
		"5.316912e+36",
		"1.0633824e+37",
		"2.1267648e+37",
		"4.2535296e+37",
		"8.507059e+37",
		"1.7014118e+38",

		"1.1754942e-38",
		"2.3509886e-38",
		"4.701977e-38",
		"9.403954e-38",
		"1.8807908e-37",
		"3.7615817e-37",
		"7.5231634e-37",
		"1.5046327e-36",
		"3.0092654e-36",
		"6.0185307e-36",
		"1.20370614e-35",
		"2.4074123e-35",
		"4.8148246e-35",
		"9.629649e-35",
		"1.9259298e-34",
		"3.8518597e-34",
		"7.7037193e-34",
		"1.5407439e-33",
		"3.0814877e-33",
		"6.1629755e-33",
		"1.2325951e-32",
		"2.4651902e-32",
		"4.9303804e-32",
		"9.860761e-32",
		"1.9721521e-31",
		"3.9443043e-31",
		"7.8886086e-31",
		"1.5777217e-30",
		"3.1554434e-30",
		"6.310887e-30",
		"1.2621774e-29",
		"2.5243547e-29",
		"5.0487095e-29",
		"1.0097419e-28",
		"2.0194838e-28",
		"4.0389676e-28",
		"8.077935e-28",
		"1.615587e-27",
		"3.231174e-27",
		"6.462348e-27",
		"1.2924696e-26",
		"2.5849393e-26",
		"5.1698785e-26",
		"1.0339757e-25",
		"2.0679514e-25",
		"4.1359028e-25",
		"8.2718056e-25",
		"1.6543611e-24",
		"3.3087223e-24",
		"6.6174445e-24",
		"1.3234889e-23",
		"2.6469778e-23",
		"5.2939556e-23",
		"1.0587911e-22",
		"2.1175822e-22",
		"4.2351645e-22",
		"8.470329e-22",
		"1.6940658e-21",
		"3.3881316e-21",
		"6.776263e-21",
		"1.3552526e-20",
		"2.7105053e-20",
		"5.4210105e-20",
		"1.0842021e-19",
		"2.1684042e-19",
		"4.3368084e-19",
		"8.673617e-19",
		"1.7347234e-18",
		"3.4694467e-18",
		"6.9388935e-18",
		"1.3877787e-17",
		"2.7755574e-17",
		"5.5511148e-17",
		"1.11022296e-16",
		"2.2204459e-16",
		"4.4408918e-16",
		"8.8817837e-16",
		"1.7763567e-15",
		"3.5527135e-15",
		"7.105427e-15",
		"1.4210854e-14",
		"2.8421708e-14",
		"5.6843415e-14",
		"1.1368683e-13",
		"2.2737366e-13",
		"4.5474732e-13",
		"9.0949465e-13",
		"1.8189893e-12",
		"3.6379786e-12",
		"7.275957e-12",
		"1.4551914e-11",
		"2.9103829e-11",
		"5.8207657e-11",
		"1.16415315e-10",
		"2.3283063e-10",
		"4.6566126e-10",
		"9.313225e-10",
		"1.862645e-09",
		"3.72529e-09",
		"7.45058e-09",
		"1.490116e-08",
		"2.980232e-08",
		"5.960464e-08",
		"1.1920928e-07",
		"2.3841856e-07",
		"4.7683713e-07",
		"9.5367426e-07",
		"1.9073485e-06",
		"3.814697e-06",
		"7.629394e-06",
		"1.5258788e-05",
		"3.0517576e-05",
		"6.1035153e-05",
		"0.000122070305",
		"0.00024414061",
		"0.00048828122",
		"0.00097656244",
		"0.0019531249",
		"0.0039062498",
		"0.0078124995",
		"0.015624999",
		"0.031249998",
		"0.062499996",
		"0.12499999",
		"0.24999999",
		"0.49999997",
		"0.99999994",
		"1.9999999",
		"3.9999998",
		"7.9999995",
		"15.999999",
		"31.999998",
		"63.999996",
		"127.99999",
		"255.99998",
		"511.99997",
		"1023.99994",
		"2047.9999",
		"4095.9998",
		"8191.9995",
		"16383.999",
		"32767.998",
		"65535.996",
		"131071.99",
		"262143.98",
		"524287.97",
		"1048575.94",
		"2097151.9",
		"4194303.8",
		"8388607.5",
		"16777215",
		"33554430",
		"67108860",
		"134217720",
		"268435440",
		"536870880",
		"1073741760",
		"2147483520",
		"4294967040",
		"8589934080",
		"17179868160",
		"34359736320",
		"68719472640",
		"137438945280",
		"274877890560",
		"549755781120",
		"1099511562240",
		"2199023124480",
		"4398046248960",
		"8796092497920",
		"1.7592185e+13",
		"3.518437e+13",
		"7.036874e+13",
		"1.4073748e+14",
		"2.8147496e+14",
		"5.6294992e+14",
		"1.12589984e+15",
		"2.2517997e+15",
		"4.5035994e+15",
		"9.0071987e+15",
		"1.8014397e+16",
		"3.6028795e+16",
		"7.205759e+16",
		"1.4411518e+17",
		"2.8823036e+17",
		"5.7646072e+17",
		"1.15292144e+18",
		"2.3058429e+18",
		"4.6116857e+18",
		"9.2233715e+18",
		"1.8446743e+19",
		"3.6893486e+19",
		"7.378697e+19",
		"1.4757394e+20",
		"2.9514789e+20",
		"5.9029578e+20",
		"1.18059155e+21",
		"2.3611831e+21",
		"4.7223662e+21",
		"9.4447324e+21",
		"1.8889465e+22",
		"3.777893e+22",
		"7.555786e+22",
		"1.5111572e+23",
		"3.0223144e+23",
		"6.0446287e+23",
		"1.20892575e+24",
		"2.4178515e+24",
		"4.835703e+24",
		"9.671406e+24",
		"1.9342812e+25",
		"3.8685624e+25",
		"7.737125e+25",
		"1.547425e+26",
		"3.09485e+26",
		"6.1897e+26",
		"1.23794e+27",
		"2.47588e+27",
		"4.95176e+27",
		"9.90352e+27",
		"1.980704e+28",
		"3.961408e+28",
		"7.922816e+28",
		"1.5845632e+29",
		"3.1691263e+29",
		"6.3382526e+29",
		"1.2676505e+30",
		"2.535301e+30",
		"5.070602e+30",
		"1.0141204e+31",
		"2.0282408e+31",
		"4.0564817e+31",
		"8.1129634e+31",
		"1.6225927e+32",
		"3.2451853e+32",
		"6.4903707e+32",
		"1.2980741e+33",
		"2.5961483e+33",
		"5.1922965e+33",
		"1.0384593e+34",
		"2.0769186e+34",
		"4.1538372e+34",
		"8.3076745e+34",
		"1.6615349e+35",
		"3.3230698e+35",
		"6.6461396e+35",
		"1.3292279e+36",
		"2.6584558e+36",
		"5.3169117e+36",
		"1.06338233e+37",
		"2.1267647e+37",
		"4.2535293e+37",
		"8.5070587e+37",
		"1.7014117e+38",
		"3.4028235e+38",
	};

	for (int magnitude = 0b10011101; magnitude < 0b11111111; magnitude++)
	{
		const unsigned int valuelo = (magnitude << 23) + 0;
		const unsigned int valuehi = (magnitude << 23) + 0b11111111111111111111111;

		fio::usize lengthlo = 0;
		do
		{
			lengthlo++;
		}
		while (shortest_representations[magnitude + 0][lengthlo] != 0);

		fio::usize lengthhi = 0;
		do
		{
			lengthhi++;
		}
		while (shortest_representations[magnitude + 255][lengthhi] != 0);

		float floatlo = fio::bit_cast<float>(-1);
		REQUIRE(fio::from_chars(shortest_representations[magnitude + 0], shortest_representations[magnitude + 0] + lengthlo, floatlo));
		REQUIRE(fio::bit_cast<unsigned int>(floatlo) == valuelo);

		float floathi = fio::bit_cast<float>(-1);
		REQUIRE(fio::from_chars(shortest_representations[magnitude + 255], shortest_representations[magnitude + 255] + lengthhi, floathi));
		REQUIRE(fio::bit_cast<unsigned int>(floathi) == valuehi);
	}
}
#endif

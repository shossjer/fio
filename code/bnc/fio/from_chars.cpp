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
	BENCHMARK_DUMP("plot/from_chars_sint8.dump", lin_style, 1, 4, 1)
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
	BENCHMARK_DUMP("plot/from_chars_uint8.dump", lin_style, 1, 4, 1)
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
	BENCHMARK_DUMP("plot/from_chars_sint16.dump", lin_style, 1, 6, 1)
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
	BENCHMARK_DUMP("plot/from_chars_uint16.dump", lin_style, 1, 6, 1)
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
	BENCHMARK_DUMP("plot/from_chars_sint32.dump", lin_style, 1, 11, 1)
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
	BENCHMARK_DUMP("plot/from_chars_uint32.dump", lin_style, 1, 11, 1)
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
	BENCHMARK_DUMP("plot/from_chars_sint64.dump", lin_style, 1, 20, 1)
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
	BENCHMARK_DUMP("plot/from_chars_uint64.dump", lin_style, 1, 21, 1)
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

#include <catch2/catch.hpp>

#include "catchhacks.hpp"

#include "fio/to_chars.hpp"

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

TEST_CASE("to_chars sint8", "[.][dump]")
{
	BENCHMARK_DUMP("plot/to_chars_sint8.dump", lin_style, 0, 8, 1, "highest set bit")
	{
		BENCHMARK_GROUP("sprintf (std)")(Catch::Benchmark::Groupometer meter)
		{
			const fio::uint8 num = static_cast<fio::uint8>(1u << meter.size());

			char buffer[1 + 16];

			meter.measure([&](int n)
			{
				static_assert(sizeof(signed char) == sizeof(fio::sint8), "");

				const signed char val = static_cast<signed char>(num + (n & (num - 1)));
				return std::sprintf(buffer + 0, "%d", val);
			});
		};

#if (__cplusplus >= 201703L) || (defined(_MSVC_LANG) && _MSVC_LANG >= 201703L)
		BENCHMARK_GROUP("to\\_chars (std)")(Catch::Benchmark::Groupometer meter)
		{
			const fio::uint8 num = static_cast<fio::uint8>(1u << meter.size());

			char buffer[1 + 16];

			meter.measure([&](int n)
			{
				const fio::sint8 val = static_cast<fio::sint8>(num + (n & (num - 1)));
				return std::to_chars(buffer, buffer + 16, val);
			});
		};
#endif

#if defined(_MSC_VER)
		BENCHMARK_GROUP("\\_itoa (win32)")(Catch::Benchmark::Groupometer meter)
		{
			const fio::uint8 num = static_cast<fio::uint8>(1u << meter.size());

			char buffer[1 + 16];

			meter.measure([&](int n)
			{
				const fio::sint8 val = static_cast<fio::sint8>(num + (n & (num - 1)));
				return ::_itoa(val, buffer + 0, 10);
			});
		};
#endif

#if HAVE_EASTDC
		BENCHMARK_GROUP("Sprintf (eastdc)")(Catch::Benchmark::Groupometer meter)
		{
			const fio::uint8 num = static_cast<fio::uint8>(1u << meter.size());

			char buffer[1 + 16];

			meter.measure([&](int n)
			{
				const fio::sint8 val = static_cast<fio::sint8>(num + (n & (num - 1)));
				return EA::StdC::Sprintf(buffer + 0, "%I8d", val);
			});
		};
#endif

#if HAVE_FMT
		BENCHMARK_GROUP("format\\_to (fmt)")(Catch::Benchmark::Groupometer meter)
		{
			const fio::uint8 num = static_cast<fio::uint8>(1u << meter.size());

			char buffer[1 + 16];

			meter.measure([&](int n)
			{
				const fio::sint8 val = static_cast<fio::sint8>(num + (n & (num - 1)));
				return fmt::format_to(buffer + 0, "{}", val);
			});
		};
#endif

		BENCHMARK_GROUP("to\\_chars")(Catch::Benchmark::Groupometer meter)
		{
			const fio::uint8 num = static_cast<fio::uint8>(1u << meter.size());

			char buffer[1 + 16];

			meter.measure([&](int n)
			{
				const fio::sint8 val = static_cast<fio::sint8>(num + (n & (num - 1)));
				return fio::to_chars(val, buffer + 0);
			});
		};
	}
}

TEST_CASE("to_chars sint16", "[.][dump]")
{
	BENCHMARK_DUMP("plot/to_chars_sint16.dump", lin_style, 0, 16, 1, "highest set bit")
	{
		BENCHMARK_GROUP("sprintf (std)")(Catch::Benchmark::Groupometer meter)
		{
			const fio::uint16 num = static_cast<fio::uint16>(1u << meter.size());

			char buffer[1 + 16];

			meter.measure([&](int n)
			{
				static_assert(sizeof(short) == sizeof(fio::sint16), "");

				const short val = static_cast<short>(num + (n & (num - 1)));
				return std::sprintf(buffer + 0, "%hd", val);
			});
		};

#if (__cplusplus >= 201703L) || (defined(_MSVC_LANG) && _MSVC_LANG >= 201703L)
		BENCHMARK_GROUP("to\\_chars (std)")(Catch::Benchmark::Groupometer meter)
		{
			const fio::uint16 num = static_cast<fio::uint16>(1u << meter.size());

			char buffer[1 + 16];

			meter.measure([&](int n)
			{
				const fio::sint16 val = static_cast<fio::sint16>(num + (n & (num - 1)));
				return std::to_chars(buffer, buffer + 16, val);
			});
		};
#endif

#if defined(_MSC_VER)
		BENCHMARK_GROUP("\\_itoa (win32)")(Catch::Benchmark::Groupometer meter)
		{
			const fio::uint16 num = static_cast<fio::uint16>(1u << meter.size());

			char buffer[1 + 16];

			meter.measure([&](int n)
			{
				const fio::sint16 val = static_cast<fio::sint16>(num + (n & (num - 1)));
				return ::_itoa(val, buffer + 0, 10);
			});
		};
#endif

#if HAVE_EASTDC
		BENCHMARK_GROUP("Sprintf (eastdc)")(Catch::Benchmark::Groupometer meter)
		{
			const fio::uint16 num = static_cast<fio::uint16>(1u << meter.size());

			char buffer[1 + 16];

			meter.measure([&](int n)
			{
				const fio::sint16 val = static_cast<fio::sint16>(num + (n & (num - 1)));
				return EA::StdC::Sprintf(buffer + 0, "%I16d", val);
			});
		};
#endif

#if HAVE_FMT
		BENCHMARK_GROUP("format\\_to (fmt)")(Catch::Benchmark::Groupometer meter)
		{
			const fio::uint16 num = static_cast<fio::uint16>(1u << meter.size());

			char buffer[1 + 16];

			meter.measure([&](int n)
			{
				const fio::sint16 val = static_cast<fio::sint16>(num + (n & (num - 1)));
				return fmt::format_to(buffer + 0, "{}", val);
			});
		};
#endif

		BENCHMARK_GROUP("to\\_chars")(Catch::Benchmark::Groupometer meter)
		{
			const fio::uint16 num = static_cast<fio::uint16>(1u << meter.size());

			char buffer[1 + 16];

			meter.measure([&](int n)
			{
				const fio::sint16 val = static_cast<fio::sint16>(num + (n & (num - 1)));
				return fio::to_chars(val, buffer + 0);
			});
		};
	}
}

TEST_CASE("to_chars sint32", "[.][dump]")
{
	BENCHMARK_DUMP("plot/to_chars_sint32.dump", lin_style, 0, 32, 1, "highest set bit")
	{
		BENCHMARK_GROUP("sprintf (std)")(Catch::Benchmark::Groupometer meter)
		{
			const fio::uint32 num = static_cast<fio::uint32>(1u << meter.size());

			char buffer[1 + 16];

			meter.measure([&](unsigned int n)
			{
				static_assert(sizeof(int) == sizeof(fio::sint32), "");

				const int val = static_cast<int>(num + (n & (num - 1)));
				return std::sprintf(buffer + 0, "%d", val);
			});
		};

#if (__cplusplus >= 201703L) || (defined(_MSVC_LANG) && _MSVC_LANG >= 201703L)
		BENCHMARK_GROUP("to\\_chars (std)")(Catch::Benchmark::Groupometer meter)
		{
			const fio::uint32 num = static_cast<fio::uint32>(1u << meter.size());

			char buffer[1 + 16];

			meter.measure([&](unsigned int n)
			{
				const fio::sint32 val = static_cast<fio::sint32>(num + (n & (num - 1)));
				return std::to_chars(buffer, buffer + 16, val);
			});
		};
#endif

#if defined(_MSC_VER)
		BENCHMARK_GROUP("\\_itoa (win32)")(Catch::Benchmark::Groupometer meter)
		{
			const fio::uint32 num = static_cast<fio::uint32>(1u << meter.size());

			char buffer[1 + 16];

			meter.measure([&](unsigned int n)
			{
				const fio::sint32 val = static_cast<fio::sint32>(num + (n & (num - 1)));
				return ::_itoa(val, buffer + 0, 10);
			});
		};
#endif

#if HAVE_EASTDC
		BENCHMARK_GROUP("Sprintf (eastdc)")(Catch::Benchmark::Groupometer meter)
		{
			const fio::uint32 num = static_cast<fio::uint32>(1u << meter.size());

			char buffer[1 + 16];

			meter.measure([&](unsigned int n)
			{
				const fio::sint32 val = static_cast<fio::sint32>(num + (n & (num - 1)));
				return EA::StdC::Sprintf(buffer + 0, "%I32d", val);
			});
		};
#endif

#if HAVE_FMT
		BENCHMARK_GROUP("format\\_to (fmt)")(Catch::Benchmark::Groupometer meter)
		{
			const fio::uint32 num = static_cast<fio::uint32>(1u << meter.size());

			char buffer[1 + 16];

			meter.measure([&](unsigned int n)
			{
				const fio::sint32 val = static_cast<fio::sint32>(num + (n & (num - 1)));
				return fmt::format_to(buffer + 0, "{}", val);
			});
		};
#endif

		BENCHMARK_GROUP("to\\_chars")(Catch::Benchmark::Groupometer meter)
		{
			const fio::uint32 num = static_cast<fio::uint32>(1u << meter.size());

			char buffer[1 + 16];

			meter.measure([&](unsigned int n)
			{
				const fio::sint32 val = static_cast<fio::sint32>(num + (n & (num - 1)));
				return fio::to_chars(val, buffer + 0);
			});
		};
	}
}

TEST_CASE("to_chars sint64", "[.][dump]")
{
	BENCHMARK_DUMP("plot/to_chars_sint64.dump", lin_style, 0, 64, 1, "highest set bit")
	{
		BENCHMARK_GROUP("sprintf (std)")(Catch::Benchmark::Groupometer meter)
		{
			const fio::uint64 num = static_cast<fio::uint64>(1ull << meter.size());

			char buffer[1 + 32];

			meter.measure([&](unsigned long long n)
			{
				static_assert(sizeof(long long) == sizeof(fio::sint64), "");

				const long long val = static_cast<long long>(num + (n & (num - 1)));
				return std::sprintf(buffer + 0, "%lld", val);
			});
		};

#if (__cplusplus >= 201703L) || (defined(_MSVC_LANG) && _MSVC_LANG >= 201703L)
		BENCHMARK_GROUP("to\\_chars (std)")(Catch::Benchmark::Groupometer meter)
		{
			const fio::uint64 num = static_cast<fio::uint64>(1ull << meter.size());

			char buffer[1 + 32];

			meter.measure([&](unsigned long long n)
			{
				const fio::sint64 val = static_cast<fio::sint64>(num + (n & (num - 1)));
				return std::to_chars(buffer, buffer + 16, val);
			});
		};
#endif

#if defined(_MSC_VER)
		BENCHMARK_GROUP("\\_i64toa (win32)")(Catch::Benchmark::Groupometer meter)
		{
			const fio::uint64 num = static_cast<fio::uint64>(1ull << meter.size());

			char buffer[1 + 32];

			meter.measure([&](unsigned long long n)
			{
				const fio::sint64 val = static_cast<fio::sint64>(num + (n & (num - 1)));
				return ::_i64toa(val, buffer + 0, 10);
			});
		};
#endif

#if HAVE_EASTDC
		BENCHMARK_GROUP("Sprintf (eastdc)")(Catch::Benchmark::Groupometer meter)
		{
			const fio::uint64 num = static_cast<fio::uint64>(1ull << meter.size());

			char buffer[1 + 32];

			meter.measure([&](unsigned long long n)
			{
				const fio::sint64 val = static_cast<fio::sint64>(num + (n & (num - 1)));
				return EA::StdC::Sprintf(buffer + 0, "%I64d", val);
			});
		};
#endif

#if HAVE_FMT
		BENCHMARK_GROUP("format\\_to (fmt)")(Catch::Benchmark::Groupometer meter)
		{
			const fio::uint64 num = static_cast<fio::uint64>(1ull << meter.size());

			char buffer[1 + 32];

			meter.measure([&](unsigned long long n)
			{
				const fio::sint64 val = static_cast<fio::sint64>(num + (n & (num - 1)));
				return fmt::format_to(buffer + 0, "{}", val);
			});
		};
#endif

		BENCHMARK_GROUP("to\\_chars")(Catch::Benchmark::Groupometer meter)
		{
			const fio::uint64 num = static_cast<fio::uint64>(1ull << meter.size());

			char buffer[1 + 32];

			meter.measure([&](unsigned long long n)
			{
				const fio::sint64 val = static_cast<fio::sint64>(num + (n & (num - 1)));
				return fio::to_chars(val, buffer + 0);
			});
		};
	}
}

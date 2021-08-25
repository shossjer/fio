#include <catch2/catch.hpp>

#include "catchhacks.hpp"

#include "fio/mem.hpp"

#include <vector>

#if HAVE_ASMLIB
# include <asmlib.h>
#endif

namespace
{
	char random_char(unsigned int seed)
	{
		return static_cast<char>((seed * 3284436301u + 1916373577u) % (128 - 1) + 1); // arbitrary primes
	}
}

TEST_CASE("memcpy", "[.][dump]")
{
	BENCHMARK_DUMP("plot/memcpy.dump", log_style, 1, 20)
	{
		BENCHMARK_GROUP("memcpy (std)")(Catch::Benchmark::Groupometer meter)
		{
			std::vector<char> buffer_utf8(meter.size(), random_char(static_cast<unsigned int>(meter.group())));

			std::vector<char> write_buffer(buffer_utf8.size() * static_cast<unsigned int>(meter.runs()));

			meter.measure([&](int n)
			{
				return ::memcpy(write_buffer.data() + static_cast<unsigned int>(n) * meter.size(), buffer_utf8.data(), buffer_utf8.size());
			});
		};

		BENCHMARK_GROUP("strcpy (std)")(Catch::Benchmark::Groupometer meter)
		{
			std::vector<char> buffer_utf8(meter.size(), random_char(static_cast<unsigned int>(meter.group())));
			buffer_utf8.push_back(char{}); // terminating null

			std::vector<char> write_buffer(buffer_utf8.size() * static_cast<unsigned int>(meter.runs()));

			meter.measure([&](int n)
			{
				return ::strcpy(write_buffer.data() + static_cast<unsigned int>(n) * meter.size(), buffer_utf8.data());
			});
		};

#if defined(_MSC_VER)

		BENCHMARK_GROUP("memcpy\\_s (win32)")(Catch::Benchmark::Groupometer meter)
		{
			std::vector<char> buffer_utf8(meter.size(), random_char(static_cast<unsigned int>(meter.group())));

			std::vector<char> write_buffer(buffer_utf8.size() * static_cast<unsigned int>(meter.runs()));

			meter.measure([&](int n)
			{
				return ::memcpy_s(write_buffer.data() + static_cast<unsigned int>(n) * meter.size(), buffer_utf8.size(), buffer_utf8.data(), buffer_utf8.size());
			});
		};

		BENCHMARK_GROUP("strcpy\\_s (win32)")(Catch::Benchmark::Groupometer meter)
		{
			std::vector<char> buffer_utf8(meter.size(), random_char(static_cast<unsigned int>(meter.group())));
			buffer_utf8.push_back(char{}); // terminating null

			std::vector<char> write_buffer(buffer_utf8.size() * static_cast<unsigned int>(meter.runs()));

			meter.measure([&](int n)
			{
				return ::strcpy_s(write_buffer.data() + static_cast<unsigned int>(n) * meter.size(), buffer_utf8.size(), buffer_utf8.data());
			});
		};

#endif

#if HAVE_ASMLIB

		BENCHMARK_GROUP("A\\_memcpy (asmlib)")(Catch::Benchmark::Groupometer meter)
		{
			std::vector<char> buffer_utf8(meter.size(), random_char(static_cast<unsigned int>(meter.group())));

			std::vector<char> write_buffer(buffer_utf8.size() * static_cast<unsigned int>(meter.runs()));

			meter.measure([&](int n)
			{
				return ::A_memcpy(write_buffer.data() + static_cast<unsigned int>(n) * meter.size(), buffer_utf8.data(), buffer_utf8.size());
			});
		};

		BENCHMARK_GROUP("A\\_strcpy (asmlib)")(Catch::Benchmark::Groupometer meter)
		{
			std::vector<char> buffer_utf8(meter.size(), random_char(static_cast<unsigned int>(meter.group())));
			buffer_utf8.push_back(char{}); // terminating null

			std::vector<char> write_buffer(buffer_utf8.size() * static_cast<unsigned int>(meter.runs()));

			meter.measure([&](int n)
			{
				return ::A_strcpy(write_buffer.data() + static_cast<unsigned int>(n) * meter.size(), buffer_utf8.data());
			});
		};

#endif

		BENCHMARK_GROUP("memcpy")(Catch::Benchmark::Groupometer meter)
		{
			std::vector<char> buffer_utf8(meter.size(), random_char(static_cast<unsigned int>(meter.group())));

			std::vector<char> write_buffer(buffer_utf8.size() * static_cast<unsigned int>(meter.runs()));

			meter.measure([&](int n)
			{
				return fio::memcpy(buffer_utf8.data(), write_buffer.data() + static_cast<unsigned int>(n) * meter.size(), buffer_utf8.size());
			});
		};
	}
}

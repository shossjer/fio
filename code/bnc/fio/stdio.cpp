#include <catch2/catch.hpp>

#include "catchhacks.hpp"

#include "fio/stdio.hpp"

#include <cstdio>
#include <iostream>
#include <vector>

#if defined(_MSC_VER)
# include <windows.h>
#else
# include <unistd.h>
#endif

#if HAVE_FMT
# include <fmt/core.h>
#endif

namespace
{
#if defined(_MSC_VER)

	struct ScopedConsoleOutputCP
	{
		UINT prev_;

		~ScopedConsoleOutputCP()
		{
			::SetConsoleOutputCP(prev_);
		}

		explicit ScopedConsoleOutputCP(UINT codepage)
			: prev_(::GetConsoleOutputCP())
		{
			REQUIRE(::SetConsoleOutputCP(codepage));
		}
	};

#endif

	unsigned int random_codepoint(unsigned int prev, unsigned int from, unsigned int to)
	{
		return (prev * 3284436301u + 1916373577u) % (to - from) + from; // arbitrary primes
	}

	char * write_utf8(char * begin, char * end, unsigned int codepoint)
	{
		if (codepoint < 0x80)
		{
			if (end - begin < 1)
				return begin;

			begin[0] = static_cast<char>(codepoint);
			return begin + 1;
		}
		else if (codepoint < 0x800)
		{
			if (end - begin < 2)
				return begin;

			begin[0] = static_cast<char>(codepoint >> 6 | 0xc0);
			begin[1] = static_cast<char>((codepoint & 0x3f) | 0x80);
			return begin + 2;
		}
		else if (codepoint < 0x10000)
		{
			if (end - begin < 3)
				return begin;

			begin[0] = static_cast<char>(codepoint >> 12 | 0xe0);
			begin[1] = static_cast<char>((codepoint >> 6 & 0x3f) | 0x80);
			begin[2] = static_cast<char>((codepoint & 0x3f) | 0x80);
			return begin + 3;
		}
		else if (codepoint < 0x110000)
		{
			if (end - begin < 4)
				return begin;

			begin[0] = static_cast<char>(codepoint >> 18 | 0xf0);
			begin[1] = static_cast<char>((codepoint >> 12 & 0x3f) | 0x80);
			begin[2] = static_cast<char>((codepoint >> 6 & 0x3f) | 0x80);
			begin[3] = static_cast<char>((codepoint & 0x3f) | 0x80);
			return begin + 4;
		}
		else // unexpected
		{
			return begin;
		}
	}

	std::vector<char> random_buffer_utf8(size_t size, unsigned int seed)
	{
		std::vector<char> buffer(size);

		unsigned int codepoint = seed;
		char * begin = buffer.data();
		char * const end = buffer.data() + buffer.size();
		while (true)
		{
			codepoint = random_codepoint(codepoint, 0x4e00, 0x9fb0);
			char * next = write_utf8(begin, end, codepoint);
			if (next == begin)
				break;

			begin = next;
		}
		while (begin != end)
		{
			*begin = '#';
			++begin;
		}

		return buffer;
	}

#if defined(_MSC_VER)

	wchar_t * write_utfw(wchar_t * begin, wchar_t * end, unsigned int codepoint)
	{
		if (codepoint < 0x10000)
		{
			if (end - begin < 1)
				return begin;

			begin[0] = static_cast<wchar_t>(codepoint);
			return begin + 1;
		}
		else if (codepoint < 0x110000)
		{
			if (end - begin < 2)
				return begin;

			const unsigned int split = codepoint - 0x10000;
			begin[0] = static_cast<wchar_t>((split >> 10) | 0xd800);
			begin[1] = static_cast<wchar_t>((split & 0x03ff) | 0xdc00);
			return begin + 2;
		}
		else // unexpected
		{
			return begin;
		}
	}

	std::vector<wchar_t> random_buffer_utfw(size_t size, unsigned int seed)
	{
		std::vector<wchar_t> buffer(size);

		unsigned int codepoint = seed;
		wchar_t * begin = buffer.data();
		wchar_t * const end = buffer.data() + buffer.size();
		while (true)
		{
			codepoint = random_codepoint(codepoint, 0x4e00, 0x9fb0);
			wchar_t * next = write_utfw(begin, end, codepoint);
			if (next == begin)
				break;

			begin = next;
		}
		while (begin != end)
		{
			*begin = L'#';
			++begin;
		}

		return buffer;
	}

#endif
}

TEST_CASE("", "")
{
#if defined(_MSC_VER)
	ScopedConsoleOutputCP cp_utf8(65001);
#endif

	::puts(u8"\u79c1\u306f\u65e5\u672c\u8a9e\u3092\u4e0a\u624b\u3067\u3059\u3002");

#if defined(_MSC_VER)
	HANDLE hOut = ::GetStdHandle(STD_OUTPUT_HANDLE);
	DWORD wrote;

	::WriteConsoleA(hOut, u8"\u79c1\u306f\u65e5\u672c\u8a9e\u3092\u4e0a\u624b\u3067\u3059\u3002\n", 34, &wrote, nullptr);
	CHECK(wrote == 34);
	::WriteConsoleW(hOut, L"\u79c1\u306f\u65e5\u672c\u8a9e\u3092\u4e0a\u624b\u3067\u3059\u3002\n", 12, &wrote, nullptr);
	CHECK(wrote == 12);
	::WriteFile(hOut, u8"\u79c1\u306f\u65e5\u672c\u8a9e\u3092\u4e0a\u624b\u3067\u3059\u3002\n", 34, &wrote, nullptr);
	CHECK(wrote == 34);
	if (::IsValidCodePage(1200))
	{
		ScopedConsoleOutputCP cp_utf16(1200);

		::WriteFile(hOut, L"\u79c1\u306f\u65e5\u672c\u8a9e\u3092\u4e0a\u624b\u3067\u3059\u3002\n", 25, &wrote, nullptr);
		CHECK(wrote == 25);
	}
	else
	{
		::WriteFile(hOut, u8"INVALID\n", 8, &wrote, nullptr);
		CHECK(wrote == 8);
	}
#else
	size_t wrote;

	wrote = static_cast<size_t>(::write(STDOUT_FILENO, u8"\u79c1\u306f\u65e5\u672c\u8a9e\u3092\u4e0a\u624b\u3067\u3059\u3002\n", 34));
	CHECK(wrote == 34);
	wrote = ::fwrite_unlocked(u8"\u79c1\u306f\u65e5\u672c\u8a9e\u3092\u4e0a\u624b\u3067\u3059\u3002\n", sizeof(char), 34, stdout);
	CHECK(wrote == 34);
#endif

#if HAVE_FMT
	fmt::print(u8"\u79c1\u306f\u65e5\u672c\u8a9e\u3092\u4e0a\u624b\u3067\u3059\u3002\n");
#endif
}

TEST_CASE("console_output_utf8", "[.][dump]")
{
	BENCHMARK_DUMP("plot/console_output_utf8.dump", log_style, 1, 16, "#bytes")
	{
		BENCHMARK_GROUP("puts (std)")(Catch::Benchmark::Groupometer meter)
		{
#if defined(_MSC_VER)
			ScopedConsoleOutputCP console_ouput_utf8(65001); // utf8
#endif

			std::vector<char> buffer_utf8 = random_buffer_utf8(meter.size(), static_cast<unsigned int>(meter.group()));
			buffer_utf8.push_back(char{}); // terminating null

			meter.measure([&](int)
			{
				return ::puts(buffer_utf8.data());
			});
		};

		BENCHMARK_GROUP("fwrite (std)")(Catch::Benchmark::Groupometer meter)
		{
#if defined(_MSC_VER)
			ScopedConsoleOutputCP console_ouput_utf8(65001); // utf8
#endif

			std::vector<char> buffer_utf8 = random_buffer_utf8(meter.size(), static_cast<unsigned int>(meter.group()));
			buffer_utf8.push_back(char{'\n'});

			FILE * file = stdout;

			meter.measure([&](int)
			{
				return ::fwrite(buffer_utf8.data(), sizeof(char), buffer_utf8.size(), file);
			});
		};

#if defined(_MSC_VER)

		BENCHMARK_GROUP("WriteConsoleA (win32) with GetStdHandle")(Catch::Benchmark::Groupometer meter)
		{
			ScopedConsoleOutputCP console_ouput_utf8(65001); // utf8

			HANDLE hOut = ::GetStdHandle(STD_OUTPUT_HANDLE);
			REQUIRE(hOut != INVALID_HANDLE_VALUE);

			std::vector<char> buffer_utf8 = random_buffer_utf8(meter.size(), static_cast<unsigned int>(meter.group()));
			buffer_utf8.push_back(char{'\n'});

			meter.measure([&](int)
			{
				return ::WriteConsoleA(hOut, buffer_utf8.data(), static_cast<DWORD>(buffer_utf8.size()), nullptr, nullptr);
			});
		};

		BENCHMARK_GROUP("WriteFile (win32) with GetStdHandle")(Catch::Benchmark::Groupometer meter)
		{
			ScopedConsoleOutputCP console_ouput_utf8(65001); // utf8

			HANDLE hOut = ::GetStdHandle(STD_OUTPUT_HANDLE);
			REQUIRE(hOut != INVALID_HANDLE_VALUE);

			std::vector<char> buffer_utf8 = random_buffer_utf8(meter.size(), static_cast<unsigned int>(meter.group()));
			buffer_utf8.push_back(char{'\n'});

			meter.measure([&](int)
			{
				return ::WriteFile(hOut, buffer_utf8.data(), static_cast<DWORD>(buffer_utf8.size()) * sizeof(char), nullptr, nullptr);
			});
		};

		BENCHMARK_GROUP("WriteFile (win32) with CreateFileW")(Catch::Benchmark::Groupometer meter)
		{
			ScopedConsoleOutputCP console_ouput_utf8(65001); // utf8

			HANDLE hOut = ::CreateFileW(L"CONOUT$", GENERIC_WRITE, FILE_SHARE_WRITE, nullptr, OPEN_EXISTING, 0, nullptr);
			REQUIRE(hOut != INVALID_HANDLE_VALUE);

			std::vector<char> buffer_utf8 = random_buffer_utf8(meter.size(), static_cast<unsigned int>(meter.group()));
			buffer_utf8.push_back(char{'\n'});

			meter.measure([&](int)
			{
				return ::WriteFile(hOut, buffer_utf8.data(), static_cast<DWORD>(buffer_utf8.size()) * sizeof(char), nullptr, nullptr);
			});
		};

#else

		BENCHMARK_GROUP("fwrite\\_unlocked (glibc)")(Catch::Benchmark::Groupometer meter)
		{
			std::vector<char> buffer_utf8 = random_buffer_utf8(meter.size(), static_cast<unsigned int>(meter.group()));
			buffer_utf8.push_back(char{'\n'});

			FILE * file = stdout;

			meter.measure([&](int)
			{
				return ::fwrite_unlocked(buffer_utf8.data(), sizeof(char), buffer_utf8.size(), file);
			});
		};

		BENCHMARK_GROUP("write (posix)")(Catch::Benchmark::Groupometer meter)
		{
			std::vector<char> buffer_utf8 = random_buffer_utf8(meter.size(), static_cast<unsigned int>(meter.group()));
			buffer_utf8.push_back(char{'\n'});

			meter.measure([&](int)
			{
				return ::write(STDOUT_FILENO, buffer_utf8.data(), buffer_utf8.size());
			});
		};

#endif

#if HAVE_FMT
		BENCHMARK_GROUP("print (fmt) with string\\_view")(Catch::Benchmark::Groupometer meter)
		{
# if defined(_MSC_VER)
			ScopedConsoleOutputCP console_ouput_utf8(65001); // utf8
# endif

			std::vector<char> buffer_utf8 = random_buffer_utf8(meter.size(), static_cast<unsigned int>(meter.group()));
			buffer_utf8.push_back(char{'\n'});

			meter.measure([&](int)
			{
				fmt::print("{}", fmt::string_view(buffer_utf8.data(), buffer_utf8.size()));
			});
		};
#endif
	}
}

namespace
{
	struct MyBuffer
	{
		using value_type = char;

		std::vector<char> chars_;
	};

	char * data(MyBuffer & x) { return x.chars_.data(); }
	size_t size(MyBuffer & x) { return x.chars_.size(); }

	void append(MyBuffer & x, const char * begin, const char * end)
	{
		x.chars_.insert(x.chars_.end(), begin, end);
	}
}

TEST_CASE("cout chars", "[.][dump]")
{
	BENCHMARK_DUMP("plot/cout-chars.dump", log_style, 1, 8, "#chars")
	{
		BENCHMARK_GROUP("cout + flush (std)")(Catch::Benchmark::Groupometer meter)
		{
#if defined(_MSC_VER)
			ScopedConsoleOutputCP console_ouput_utf8(65001); // utf8

			REQUIRE(fio::set_stdout_console());
#endif

			std::vector<char> buffer_utf8 = random_buffer_utf8(meter.size(), static_cast<unsigned int>(meter.group()));
			buffer_utf8.push_back(char{'\n'});

			meter.measure([&](int)
			{
				auto & stream = std::cout;
				stream.write(buffer_utf8.data(), static_cast<fio::ssize>(buffer_utf8.size()));
				stream.flush();
			});
		};

		BENCHMARK_GROUP("cout - flush (std)")(Catch::Benchmark::Groupometer meter)
		{
#if defined(_MSC_VER)
			ScopedConsoleOutputCP console_ouput_utf8(65001); // utf8

			REQUIRE(fio::set_stdout_console());
#endif

			std::vector<char> buffer_utf8 = random_buffer_utf8(meter.size(), static_cast<unsigned int>(meter.group()));
			buffer_utf8.push_back(char{'\n'});

			auto & stream = std::cout;

			meter.measure([&](int)
			{
				stream.write(buffer_utf8.data(), static_cast<fio::ssize>(buffer_utf8.size()));
			});

			stream.flush();
		};

		BENCHMARK_GROUP("stdostream + flush")(Catch::Benchmark::Groupometer meter)
		{
#if defined(_MSC_VER)
			ScopedConsoleOutputCP console_ouput_utf8(65001); // utf8

			REQUIRE(fio::set_stdout_console());
#endif

			std::vector<char> buffer_utf8 = random_buffer_utf8(meter.size(), static_cast<unsigned int>(meter.group()));
			buffer_utf8.push_back(char{'\n'});

			meter.measure([&](int)
			{
				auto stream = fio::stdostream<MyBuffer>();
				stream.write(buffer_utf8.data(), buffer_utf8.size());
			});
		};

		BENCHMARK_GROUP("stdostream - flush")(Catch::Benchmark::Groupometer meter)
		{
#if defined(_MSC_VER)
			ScopedConsoleOutputCP console_ouput_utf8(65001); // utf8

			REQUIRE(fio::set_stdout_console());
#endif

			std::vector<char> buffer_utf8 = random_buffer_utf8(meter.size(), static_cast<unsigned int>(meter.group()));
			buffer_utf8.push_back(char{'\n'});

			auto stream = fio::stdostream<MyBuffer>();

			meter.measure([&](int)
			{
				stream.write(buffer_utf8.data(), buffer_utf8.size());
			});
		};
	}
}

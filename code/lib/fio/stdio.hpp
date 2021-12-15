#pragma once

#include "fio/io.hpp"

namespace fio
{
#if defined(_MSC_VER)

	// the old handle will be closed
	bool set_stdout(HANDLE handle);

	// set stdout to console (even if it has been redirected)
	bool set_stdout_console();

#else

	// the old fd will be closed
	bool set_stdout(int fd);

#endif

	fio_inline bool flush_stdout()
	{
		extern io_type io_stdout;
		extern fio_thread write_buffer buffer_stdout;

		return flush(io_stdout, buffer_stdout);
	}

	fio_inline usize write_stdout(const char * data, usize size, bool flush = false)
	{
		extern io_type io_stdout;
		extern fio_thread write_buffer buffer_stdout;

		return write(io_stdout, buffer_stdout, data, size, flush);
	}

	fio_inline const char * write_stdout(const char * begin, const char * end, bool flush = false)
	{
		return begin + write_stdout(begin, static_cast<usize>(end - begin), flush);
	}

#if defined(_MSC_VER)

	fio_inline usize write_stdout(const wchar_t * data, usize size, bool flush = false)
	{
		extern io_type io_stdout;
		extern fio_thread write_buffer buffer_stdout;

		return write(io_stdout, buffer_stdout, data, size, flush);
	}

	fio_inline const wchar_t * write_stdout(const wchar_t * begin, const wchar_t * end, bool flush = false)
	{
		return begin + write_stdout(begin, end - begin, flush);
	}

#endif

	template <typename T>
	fio_inline auto write_stdout(T value, bool flush = false)
		-> decltype(to_chars(value, nullptr), usize())
	{
		extern io_type io_stdout;
		extern fio_thread write_buffer buffer_stdout;

		return write(io_stdout, buffer_stdout, value, flush);
	}

	template <typename T, unsigned long long N>
	fio_inline constexpr T * begin(T (& x)[N]) { return x + 0; }

	template <typename T, unsigned long long N>
	fio_inline constexpr T * end(T (& x)[N]) { return x + N; }

	template <typename T>
	fio_inline constexpr T * to_address(T * x) { return x; }

	template <typename T>
	fio_inline constexpr auto to_address(const T & x) -> decltype(x.operator->()) { return x.operator->(); }

	template <typename Buffer>
	class stdostream
	{
	private:

		static stdostream & this_ref(); // note hack

		static stdostream & is_actually_arithmetic(const signed char *);
		static stdostream & is_actually_arithmetic(const short *);
		static stdostream & is_actually_arithmetic(const int *);
		static stdostream & is_actually_arithmetic(const long *);
		static stdostream & is_actually_arithmetic(const long long *);
		static stdostream & is_actually_arithmetic(const unsigned char *);
		static stdostream & is_actually_arithmetic(const unsigned short *);
		static stdostream & is_actually_arithmetic(const unsigned int *);
		static stdostream & is_actually_arithmetic(const unsigned long *);
		static stdostream & is_actually_arithmetic(const unsigned long long *);
		static stdostream & is_actually_arithmetic(const float *);
		static stdostream & is_actually_arithmetic(const double *);
		static stdostream & is_actually_arithmetic(const long double *);

		template <typename T>
		static stdostream & is_actually_pointer(T *); // note hack

	private:

		Buffer buffer_;

	public:

		~stdostream()
		{
			write_stdout(data(buffer_), size(buffer_), true);
		}

	public:

		operator bool() const { return true; } // todo error state

		template <typename T>
		fio_inline auto write(const T * data, usize size)
			-> decltype(append(buffer_, data + 0, data + size), this_ref())
		{
			append(buffer_, data + 0, data + size);

			return *this;
		}

		template <typename T, unsigned long long N>
		fio_inline auto write(const T (& x)[N])
			-> decltype(append(buffer_, x + 0, x + N - 1), this_ref())
		{
			append(buffer_, x + 0, x + N - 1);

			return *this;
		}

		// disable printing of character pointers (well, all pointers
		// actually), otherwise conversion to bool would be used
		//
		// https://stackoverflow.com/a/28243509
		template <typename T>
		fio_inline auto operator << (const T & x)
			-> decltype(is_actually_pointer(x)) = delete;

		fio_inline stdostream & operator << (bool x)
		{
			const char * const str = "01";

			append(buffer_, str + static_cast<int>(x), str + static_cast<int>(x) + 1);

			return *this;
		}

		template <typename T>
		fio_inline auto write(T x)
			-> decltype(append(buffer_, &x + 0, &x + 1), this_ref())
		{
			append(buffer_, &x + 0, &x + 1);

			return *this;
		}

		template <typename T>
		fio_inline auto operator << (const T & x)
			-> decltype(append(buffer_, begin(x), end(x)), this_ref())
		{
			append(buffer_, begin(x), end(x));

			return *this;
		}

		template <typename T>
		fio_inline auto operator << (const T & x)
			-> decltype(to_chars(x, nullptr), is_actually_arithmetic(&x))
		{
			if (reserve(buffer_, size(buffer_) + 32)) // todo 32 for 64bit numbers, else 16
			{
				reduce(buffer_, to_chars(value, data(buffer_) + size(buffer_)));
			}
			return *this;
		}

	};
}

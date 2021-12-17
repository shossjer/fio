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

	fio_inline usize write_stdout(const char * data, usize size)
	{
		extern io_type io_stdout;

		return io_stdout.write(data, size);
	}

	fio_inline const char * write_stdout(const char * begin, const char * end)
	{
		return begin + write_stdout(begin, static_cast<usize>(end - begin));
	}

#if defined(_MSC_VER)

	fio_inline usize write_stdout(const wchar_t * data, usize size)
	{
		extern io_type io_stdout;

		return io_stdout.write(data, size);
	}

	fio_inline const wchar_t * write_stdout(const wchar_t * begin, const wchar_t * end)
	{
		return begin + write_stdout(begin, end - begin);
	}

#endif


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

	public:

		using char_type = typename Buffer::value_type;

	private:

		Buffer buffer_;

	public:

		~stdostream()
		{
			usize remaining = size(buffer_);
			char_type * end = data(buffer_) + remaining;
			do
			{
				remaining -= write_stdout(end - remaining, remaining);
			}
			while (remaining > 0);
		}

	public:

		operator bool() const { return true; } // todo error state

		Buffer & buffer() { return buffer_; }
		const Buffer & buffer() const { return buffer_; }

		stdostream & flush()
		{
			usize remaining = size(buffer_);
			char_type * end = data(buffer_) + remaining;
			do
			{
				remaining -= write_stdout(end - remaining, remaining);
			}
			while (remaining > 0);

			clear(buffer_);

			return *this;
		}

		template <typename T>
		fio_inline auto write(const T * data, usize size)
			-> decltype(append(buffer_, data + 0, data + size), this_ref())
		{
			append(buffer_, data + 0, data + size);

			return *this;
		}

		template <typename T, unsigned long long N>
		fio_inline auto operator << (const T (& x)[N])
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
			char_type digits[2] = {static_cast<char_type>('0'), static_cast<char_type>('1')};

			append(buffer_, digits + static_cast<int>(x), digits + static_cast<int>(x) + 1);

			return *this;
		}

		template <typename T>
		fio_inline auto operator << (T x)
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
				reduce(buffer_, to_chars(x, data(buffer_) + size(buffer_)));
			}
			return *this;
		}

	};
}

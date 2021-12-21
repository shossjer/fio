#pragma once

#include "fio/io.hpp"

#include "fio/to_chars.hpp"

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

	namespace detail
	{
		template <typename ...Ps>
		fio_inline auto adl_clear(Ps && ...ps)
			-> decltype(clear(static_cast<Ps &&>(ps)...))
		{
			return clear(static_cast<Ps &&>(ps)...);
		}
	}

	template <typename Buffer>
	class stdostream
	{
	public:

		using char_type = typename Buffer::value_type;

		using iostate = ssize;
		static constexpr iostate goodbit = 0;
		static constexpr iostate badbit = static_cast<ssize>(~(usize(-1) >> 1) | ~(usize(-1) >> 1) >> 1);
		static constexpr iostate failbit = static_cast<ssize>(~(usize(-1) >> 1) | ~(usize(-1) >> 1) >> 2);
		static constexpr iostate eofbit = static_cast<ssize>(~(usize(-1) >> 1) | ~(usize(-1) >> 1) >> 3);

	private:

		using pointer_type = char_type *;

		template <typename P>
		static P && declval();

		template <typename P>
		static void is_not_type(int, const P &);
		template <typename P, typename ...Ps>
		static int is_not_type(float, Ps && ...);

		static int is_arithmetic(const signed char *);
		static int is_arithmetic(const unsigned char *);
		static int is_arithmetic(const short *);
		static int is_arithmetic(const unsigned short *);
		static int is_arithmetic(const int *);
		static int is_arithmetic(const unsigned int *);
		static int is_arithmetic(const long *);
		static int is_arithmetic(const unsigned long *);
		static int is_arithmetic(const long long *);
		static int is_arithmetic(const unsigned long long *);
		template <typename P>
		static auto is_arithmetic(int, const P & x) -> decltype(is_arithmetic(&x));

	private:

		iostate state_;
		Buffer buffer_;

	public:

		fio_inline ~stdostream()
		{
			usize remaining = size(buffer_);
			char_type * end = data(buffer_) + remaining;
			do
			{
				remaining -= write_stdout(end - remaining, remaining);
			}
			while (remaining > 0);
		}

		fio_inline stdostream()
			: state_(0)
		{}

		template <typename ...Ps,
		          decltype(is_not_type<stdostream>(0, declval<Ps &&>()...)) = 0>
		fio_inline explicit stdostream(Ps && ...ps)
			: state_(0)
			, buffer_(static_cast<Ps &&>(ps)...)
		{}

	public:

		fio_inline explicit operator bool() const { return state_ >= 0; }

		fio_inline Buffer & buffer() { return buffer_; }
		fio_inline const Buffer & buffer() const { return buffer_; }

		fio_inline void clear(iostate state = goodbit)
		{
			state_ = state;
		}

		fio_inline void setstate(iostate state)
		{
			state_ |= state;
		}

		fio_inline stdostream & flush()
		{
			usize remaining = size(buffer_);
			char_type * end = data(buffer_) + remaining;
			do
			{
				remaining -= write_stdout(end - remaining, remaining);
			}
			while (remaining > 0);

			detail::adl_clear(buffer_);

			return *this;
		}

		fio_inline stdostream & write(const char_type * data, usize size)
		{
			append(buffer_, data + 0, data + size);

			return *this;
		}

		template <unsigned long long N>
		fio_inline stdostream & operator << (const char_type (& x)[N])
		{
			append(buffer_, x + 0, x + N - 1);

			return *this;
		}

		fio_inline stdostream & operator << (bool x)
		{
			// todo boolalpha
			char_type digits[2] = {static_cast<char_type>('0'), static_cast<char_type>('1')};

			append(buffer_, digits + static_cast<int>(x), digits + static_cast<int>(x) + 1);

			return *this;
		}

		fio_inline stdostream & operator << (char_type x)
		{
			append(buffer_, &x + 0, &x + 1);

			return *this;
		}

		template <typename T>
		fio_inline auto operator << (const T & x)
			-> decltype(is_arithmetic(0, x), declval<stdostream &>())
		{
			if (reserve(buffer_, size(buffer_) + 32)) // todo 32 for 64bit numbers, else 16
			{
				reduce(buffer_, to_chars(x, data(buffer_) + size(buffer_)));
			}
			return *this;
		}

	};
}

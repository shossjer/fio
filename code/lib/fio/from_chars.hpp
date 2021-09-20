#pragma once

#include "fio/compiler.hpp"
#include "fio/stdint.hpp"

#if defined(_MSC_VER)
# include <intrin.h>
#endif

namespace fio
{
    namespace detail
    {
        fio_inline constexpr usize umax(uint8) { return 0xffu; }
        fio_inline constexpr usize umax(uint16) { return 0xffffu; }
        fio_inline constexpr usize umax(uint32) { return 0xffffffffu; }
#if defined(_M_X64) || defined(_M_AMD64) || defined(__x86_64__)
        fio_inline constexpr usize umax(uint64) { return 0xffffffffffffffffu; }
#endif

        fio_inline constexpr usize smax(sint8) { return 0x7fu; }
        fio_inline constexpr usize smax(sint16) { return 0x7fffu; }
        fio_inline constexpr usize smax(sint32) { return 0x7fffffffu; }
#if defined(_M_X64) || defined(_M_AMD64) || defined(__x86_64__)
        fio_inline constexpr usize smax(sint64) { return 0x7fffffffffffffffu; }
#endif

        fio_inline constexpr int ulen(uint8) { return 3; }
        fio_inline constexpr int ulen(uint16) { return 5; }
        fio_inline constexpr int ulen(uint32) { return 10; }
#if defined(_M_X64) || defined(_M_AMD64) || defined(__x86_64__)
        fio_inline constexpr int ulen(uint64) { return 20; }
#endif

        fio_inline constexpr int slen(sint8) { return 3; }
        fio_inline constexpr int slen(sint16) { return 5; }
        fio_inline constexpr int slen(sint32) { return 10; }
#if defined(_M_X64) || defined(_M_AMD64) || defined(__x86_64__)
        fio_inline constexpr int slen(sint64) { return 19; }
#endif

        template <typename T>
        fio_inline const char * from_chars_unsigned(const char * begin, const char * end, T & value)
        {
            const char * const error = begin;
            if (!fio_expect(begin != end))
                return error; // not a number

            const usize mval = umax(value);

            usize uval = static_cast<usize>(*begin) - '0';
            if (!fio_expect(!(uval >= 10)))
                return error; // not a number

            begin++;

            if (begin != end)
            {
                const char * const last = begin + (ulen(value) - 1); // first digit already read
                const char * const end_or_last = end < last ? end : last;

                do
                {
                    const usize digit = static_cast<usize>(*begin) - '0';
                    if (digit >= 10)
                    {
                        value = static_cast<T>(uval);

                        return begin;
                    }

                    uval = uval * 10 + digit;
                    begin++;
                }
                while (begin != end_or_last);

                if (uval > mval)
                    return error; // overflow

                if (begin != end)
                {
                    const usize trail = static_cast<usize>(*begin) - '0';
                    if (!(trail >= 10))
                        return error; // overflow
                }
            }

            value = static_cast<T>(uval);

            return begin;
        }

        template <typename T>
        fio_inline const char * from_chars_signed(const char * begin, const char * end, T & value)
        {
            const char * const error = begin;
            if (!fio_expect(begin != end))
                return error; // not a number

            usize mval = smax(value);

            const bool is_negative = *begin == '-';
            if (is_negative)
            {
                begin++;
                mval++;
            }
            if (!fio_expect(begin != end))
                return error; // not a number

            usize uval = static_cast<usize>(*begin) - '0';
            if (!fio_expect(!(uval >= 10)))
                return error; // not a number

            begin++;

            if (begin != end)
            {
                const char * const last = begin + (slen(value) - 1); // first digit already read
                const char * const end_or_last = end < last ? end : last;

                do
                {
                    const usize digit = static_cast<usize>(*begin) - '0';
                    if (digit >= 10)
                    {
                        if (is_negative)
                        {
                            uval = 0 - uval;
                        }

                        value = static_cast<T>(uval);

                        return begin;
                    }

                    uval = uval * 10 + digit;
                    begin++;
                }
                while (begin != end_or_last);

                if (uval > mval)
                    return error; // overflow

                if (begin != end)
                {
                    const usize trail = static_cast<usize>(*begin) - '0';
                    if (!(trail >= 10))
                        return error; // overflow
                }
            }

            if (is_negative)
            {
                uval = 0 - uval;
            }

            value = static_cast<T>(uval);

            return begin;
        }

#if defined(_M_X64) || defined(_M_AMD64) || defined(__x86_64__)

        fio_inline const char * from_chars_unsigned(const char * begin, const char * end, uint64 & value)
        {
            const char * const error = begin;
            if (!fio_expect(begin != end))
                return error; // not a number

            usize uval = static_cast<usize>(*begin) - '0';
            if (!fio_expect(!(uval >= 10)))
                return error; // not a number

            begin++;

            if (begin != end)
            {
                const char * const before_last = begin + (ulen(value) - 2); // first digit already read
                const char * const end_or_before_last = end < before_last ? end : before_last;

                do
                {
                    // todo msvc inserts a superfluous move
                    const usize digit = static_cast<usize>(*begin) - '0';
                    if (digit >= 10)
                    {
                        value = static_cast<uint64>(uval);

                        return begin;
                    }

                    uval = uval * 10 + digit;
                    begin++;
                }
                while (begin != end_or_before_last);

                if (begin != end)
                {
                    const usize digit = static_cast<usize>(*begin) - '0';
                    if (digit >= 10)
                    {
                        value = static_cast<uint64>(uval);

                        return begin;
                    }

#if defined(__GNUC__)
                    if (__builtin_umull_overflow(uval, 10, &uval))
                        return error; // overflow

                    if (__builtin_uaddl_overflow(uval, digit, &uval))
                        return error; // overflow
#elif defined(_MSC_VER)
                    usize overflow;
                    uval = _umul128(uval, 10, &overflow);
                    if (overflow != 0) // todo msvc does not branch on CF/OF
                        return error; // overflow

                    if (_addcarry_u64(0, uval, digit, &uval) != 0)
                        return error; // overflow
#endif

                    begin++;

                    if (begin != end)
                    {
                        const usize trail = static_cast<usize>(*begin) - '0';
                        if (!(trail >= 10))
                            return error; // overflow
                    }
                }
            }

            value = static_cast<uint64>(uval);

            return begin;
        }

#else

# error Missing implementation!
        // todo check for overflows of 32 bit integers, signed and unsigned
        // todo can we use mmx?

#endif
    }

    fio_inline const char * from_chars(const char * begin, const char * end, unsigned char & value)
    {
        static_assert(sizeof(unsigned char) == sizeof(uint8), "Expected unsigned char to be 8 bits");

        return detail::from_chars_unsigned(begin, end, reinterpret_cast<uint8 &>(value));
    }

    fio_inline const char * from_chars(const char * begin, const char * end, signed char & value)
    {
        static_assert(sizeof(signed char) == sizeof(sint8), "Expected signed char to be 8 bits");

        return detail::from_chars_signed(begin, end, reinterpret_cast<sint8 &>(value));
    }

    fio_inline const char * from_chars(const char * begin, const char * end, unsigned short & value)
    {
        static_assert(sizeof(unsigned short) == sizeof(uint16), "Expected unsigned short to be 16 bits");

        return detail::from_chars_unsigned(begin, end, reinterpret_cast<uint16 &>(value));
    }

    fio_inline const char * from_chars(const char * begin, const char * end, signed short & value)
    {
        static_assert(sizeof(signed short) == sizeof(sint16), "Expected signed short to be 16 bits");

        return detail::from_chars_signed(begin, end, reinterpret_cast<sint16 &>(value));
    }

    fio_inline const char * from_chars(const char * begin, const char * end, unsigned int & value)
    {
        static_assert(sizeof(unsigned int) == sizeof(uint32), "Expected unsigned int to be 32 bits");

        return detail::from_chars_unsigned(begin, end, reinterpret_cast<uint32 &>(value));
    }

    fio_inline const char * from_chars(const char * begin, const char * end, signed int & value)
    {
        static_assert(sizeof(signed int) == sizeof(sint32), "Expected signed int to be 32 bits");

        return detail::from_chars_signed(begin, end, reinterpret_cast<sint32 &>(value));
    }

#if defined(_M_X64) || defined(_M_AMD64) || defined(__x86_64__)

    fio_inline const char * from_chars(const char * begin, const char * end, unsigned long long & value)
    {
        static_assert(sizeof(unsigned long long) == sizeof(uint64), "Expected unsigned long long to be 64 bits");

        return detail::from_chars_unsigned(begin, end, reinterpret_cast<uint64 &>(value));
    }

    fio_inline const char * from_chars(const char * begin, const char * end, signed long long & value)
    {
        static_assert(sizeof(signed long long) == sizeof(sint64), "Expected signed long long to be 64 bits");

        return detail::from_chars_signed(begin, end, reinterpret_cast<sint64 &>(value));
    }

#endif

#if defined(__LP64__)

    fio_inline const char * from_chars(const char * begin, const char * end, unsigned long & value)
    {
        static_assert(sizeof(unsigned long) == sizeof(uint64), "Expected unsigned long to be 64 bits");

        return detail::from_chars_unsigned(begin, end, reinterpret_cast<uint64 &>(value));
    }

    fio_inline const char * from_chars(const char * begin, const char * end, signed long & value)
    {
        static_assert(sizeof(signed long) == sizeof(sint64), "Expected signed long to be 64 bits");

        return detail::from_chars_signed(begin, end, reinterpret_cast<sint64 &>(value));
    }

#else

    fio_inline const char * from_chars(const char * begin, const char * end, unsigned long & value)
    {
        static_assert(sizeof(unsigned long) == sizeof(uint32), "Expected unsigned long to be 32 bits");

        return detail::from_chars_unsigned(begin, end, reinterpret_cast<uint32 &>(value));
    }

    fio_inline const char * from_chars(const char * begin, const char * end, signed long & value)
    {
        static_assert(sizeof(signed long) == sizeof(sint32), "Expected signed long to be 32 bits");

        return detail::from_chars_signed(begin, end, reinterpret_cast<sint32 &>(value));
    }

#endif
}

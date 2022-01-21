#pragma once

#include "compiler.hpp"

namespace fio
{
	template <typename U, typename T>
	fio_inline
	U bit_cast(const T & x)
	{
#if __has_builtin(__builtin_bit_cast)
		return __builtin_bit_cast(U, x);
#elif defined(_MSC_VER)
# if _MSC_VER >= 1926
		return __builtin_bit_cast(U, x);
# else
		// msvc is inconsistent in its description about unions for type
		// punning, saying both that it is "unreliable" and that the
		// result "would depend on the internal storage", which one is
		// it?
		//
		// https://docs.microsoft.com/en-us/cpp/c-language/union-declarations
		//
		// the documentation for bit_cast, however, mentions (and
		// discourages) the use of reinterpret_cast as tool for type
		// punning
		//
		// https://docs.microsoft.com/en-us/cpp/standard-library/bit-functions#remarks
		return *reinterpret_cast<const U *>(&x);
# endif
#elif defined(__GNUC__)
		// https://gcc.gnu.org/onlinedocs/gcc/Optimize-Options.html#Type-punning
		union
		{
			T from;
			U to;
		};

		from = x;
		return to;
#else
# error Missing implementation!
#endif
	}
}

#if HAVE_EASTDC

#include "fio/compiler.hpp"

#include <cstddef>

#if defined(_MSC_VER)
# define fio_cdecl __cdecl
#elif defined(__GNUC__)
# define fio_cdecl
#endif

void * fio_cdecl operator new[](size_t size, const char * name, int flags, unsigned debugFlags, const char * file, int line)
{
	fio_unused(name);
	fio_unused(flags);
	fio_unused(debugFlags);
	fio_unused(file);
	fio_unused(line);
	return new char[size];
}

#endif

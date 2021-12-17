#pragma once

#include "fio/mem.hpp"
#include "fio/to_chars.hpp"

#if defined(_MSC_VER)
# include <windows.h>
#else
# include <unistd.h>
#endif

namespace fio
{
	struct io_type
	{
#if defined(_MSC_VER)

		HANDLE handle;

		fio_inline HANDLE exchange(HANDLE value)
		{
			return _InterlockedExchangePointer(&handle, value);
		}

		fio_inline HANDLE load() const
		{
			// note simple reads and writes are atomic
			//
			// https://docs.microsoft.com/en-us/windows/win32/sync/interlocked-variable-access
			return handle;
		}

		fio_inline usize write(const char * data, usize size)
		{
			DWORD wrote;

			LPOVERLAPPED lpOverlapped = nullptr;
			LPDWORD lpNumberOfBytesWritten = &wrote;
			DWORD nNumberOfBytesToWrite = static_cast<DWORD>(size);
			LPCVOID lpBuffer = data;
			HANDLE hFile = load();

			::WriteFile(hFile, lpBuffer, nNumberOfBytesToWrite, lpNumberOfBytesWritten, lpOverlapped);

			return wrote;
		}

		fio_inline usize write(const wchar_t * data, usize size)
		{
			// todo convert to utf8 and writefile
			DWORD wrote;

			LPVOID lpReserved = nullptr;
			LPDWORD lpNumberOfCharsWritten = &wrote;
			DWORD nNumberOfCharsToWrite = static_cast<DWORD>(size);
			const void * lpBuffer = data;
			HANDLE hConsoleOutput = load();

			::WriteConsoleW(hConsoleOutput, lpBuffer, nNumberOfCharsToWrite, lpNumberOfCharsWritten, lpReserved);

			return wrote;
		}

#else

		int fd;

		fio_inline int load()
		{
			return __atomic_load_n(&fd, __ATOMIC_RELAXED);
		}

		fio_inline int exchange(int value)
		{
			return __atomic_exchange_n(&fd, value, __ATOMIC_RELAXED);
		}

		fio_inline usize write(const char * data, usize size)
		{
			int fd_ = load();

			ssize_t wrote = ::write(fd_, data, size);

			return static_cast<usize>(wrote);
		}

#endif
	};
}

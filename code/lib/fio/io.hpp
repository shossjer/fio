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
	struct write_buffer
	{
		static constexpr usize flushlim = 0x0c00; // < 0x8000
		static constexpr usize capacity = 0x1000; // < 0x8000

		short size; // utfw < 0 < utf8
		char data[capacity]; // arbitrary
	};

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

	fio_inline bool flush(io_type & io, write_buffer & buffer)
	{
		if (buffer.size != 0)
		{
#if defined(_MSC_VER)
			if (buffer.size > 0) // utf8
			{
#endif
				const usize wrote = io.write(buffer.data, static_cast<usize>(buffer.size));
				if (!fio_expect(wrote == static_cast<usize>(buffer.size)))
					return 0; // todo memcpy(buffer.data + wrote, buffer.data, buffer.size = (buffer.size - wrote));

				buffer.size = 0;
#if defined(_MSC_VER)
			}
			else // utfw
			{
				const usize wrote = io.write(reinterpret_cast<const wchar_t *>(buffer.data), -buffer.size / sizeof(wchar_t));
				if (!fio_expect(wrote == static_cast<usize>(-buffer.size / sizeof(wchar_t))))
					return 0; // todo memcpy(buffer.data + wrote, buffer.data, -(buffer.size = -(-buffer.size - wrote * sizeof(wchar_t))));

				buffer.size = 0;
			}
#endif
		}

		return true;
	}

	inline usize write(io_type & io, write_buffer & buffer, const char * data, usize size, bool flush = false)
	{
#if defined(_MSC_VER)
		if (buffer.size < 0) // utfw
		{
			const usize wrote = io.write(reinterpret_cast<const wchar_t *>(buffer.data), -buffer.size / sizeof(wchar_t));
			if (!fio_expect(wrote == static_cast<usize>(-buffer.size / sizeof(wchar_t))))
				return 0; // todo memcpy(buffer.data + wrote, buffer.data, -(buffer.size = -(-buffer.size - wrote * sizeof(wchar_t))));

			buffer.size = 0;
		}
#endif

		usize next_size = size * sizeof(char) + static_cast<usize>(buffer.size);
		if (next_size > buffer.capacity)
		{
			if (buffer.size > 0)
			{
				const usize wrote = io.write(buffer.data, static_cast<usize>(buffer.size));
				if (!fio_expect(wrote == static_cast<usize>(buffer.size)))
					return 0; // todo memcpy(buffer.data + wrote, buffer.data, buffer.size = (buffer.size - wrote));

				next_size -= static_cast<usize>(buffer.size);
			}

			if (next_size > buffer.flushlim) // if size * sizeof(char) > flushlim
			{
				return io.write(data, next_size);
			}
		}

		memcpy(data, buffer.data + buffer.size, size * sizeof(char));

		if (next_size > buffer.flushlim || flush)
		{
			const usize wrote = io.write(buffer.data, next_size);
			if (!fio_expect(wrote == next_size))
				return size; // todo memcpy(buffer.data + wrote, buffer.data, buffer.size = (next_size - wrote));

			buffer.size = 0;
		}
		else
		{
			buffer.size = static_cast<short>(next_size);
		}

		return size;
	}

	fio_inline const char * write(io_type & io, write_buffer & buffer, const char * begin, const char * end, bool flush = false)
	{
		return begin + write(io, buffer, begin, static_cast<usize>(end - begin), flush);
	}

#if defined(_MSC_VER)

	inline usize write(io_type & io, write_buffer & buffer, const wchar_t * data, usize size, bool flush = false)
	{
		if (buffer.size > 0) // utf8
		{
			const usize wrote = io.write(buffer.data, buffer.size);
			if (!fio_expect(wrote == static_cast<usize>(buffer.size)))
				return 0; // todo memcpy(buffer.data + wrote, buffer.data, buffer.size = (buffer.size - wrote));

			buffer.size = 0;
		}

		usize next_size = size * sizeof(wchar_t) - buffer.size;
		if (next_size > buffer.capacity)
		{
			if (buffer.size < 0)
			{
				const usize wrote = io.write(reinterpret_cast<const wchar_t *>(buffer.data), -buffer.size / sizeof(wchar_t));
				if (!fio_expect(wrote == static_cast<usize>(-buffer.size / sizeof(wchar_t))))
					return 0; // todo memcpy(buffer.data + wrote, buffer.data, -(buffer.size = -(-buffer.size - wrote * sizeof(wchar_t))));

				next_size += buffer.size;
			}

			if (next_size > buffer.flushlim) // if size * sizeof(wchar_t) > flushlim
			{
				return io.write(data, size);
			}
		}

		memcpy(data, buffer.data + buffer.size, size * sizeof(wchar_t));

		if (next_size > buffer.flushlim || flush)
		{
			const usize wrote = io.write(reinterpret_cast<const wchar_t *>(buffer.data), next_size / sizeof(wchar_t));
			if (!fio_expect(wrote == next_size / sizeof(wchar_t)))
				return 0; // todo memcpy(buffer.data + wrote, buffer.data, -(buffer.size = -(-buffer.size - wrote * sizeof(wchar_t))));

			buffer.size = 0;
		}
		else
		{
			buffer.size = -static_cast<short>(next_size);
		}

		return size;
	}

	fio_inline const wchar_t * write(io_type io, write_buffer & buffer, const wchar_t * begin, const wchar_t * end, bool flush = false)
	{
		return begin + write(io, buffer, begin, end - begin, flush);
	}

#endif

	template <typename T>
	inline auto write(io_type & io, write_buffer & buffer, T value, bool flush = false)
		-> decltype(to_chars(value, nullptr), usize())
	{
#if defined(_MSC_VER)
		if (buffer.size < 0) // utfw
		{
			const usize wrote = io.write(reinterpret_cast<const wchar_t *>(buffer.data), -buffer.size / sizeof(wchar_t));
			if (!fio_expect(wrote == static_cast<usize>(-buffer.size / sizeof(wchar_t))))
				return 0; // todo memcpy(buffer.data + wrote, buffer.data, -(buffer.size = -(-buffer.size - wrote * sizeof(wchar_t))));

			buffer.size = 0;
		}
#endif

		if (!fio_expect(static_cast<usize>(buffer.capacity - buffer.size) >= 32)) // todo 32 for 64bit numbers, else 16
			return 0;

		char * const begin = buffer.data + buffer.size;

		char * const end = to_chars(value, begin);

		const usize size = end - begin;
		const usize next_size = end - buffer.data;

		if (next_size > buffer.flushlim || flush)
		{
			const usize wrote = io.write(buffer.data, next_size);
			if (!fio_expect(wrote == next_size))
				return size; // todo memcpy(buffer.data + wrote, buffer.data, buffer.size = (next_size - wrote));

			buffer.size = 0;
		}
		else
		{
			buffer.size = static_cast<short>(next_size);
		}

		return size;
	}
}

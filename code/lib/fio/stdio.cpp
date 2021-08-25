#include "fio/stdio.hpp"

namespace fio
{
#if defined(_MSC_VER)

	io_type io_stdout{INVALID_HANDLE_VALUE};

#else

	io_type io_stdout{STDOUT_FILENO};

#endif

	fio_thread write_buffer buffer_stdout;

#if defined(_MSC_VER)

	bool set_stdout(HANDLE handle)
	{
		switch (::GetFileType(handle))
		{
		case FILE_TYPE_DISK:
		case FILE_TYPE_PIPE:
			// todo
			return false;
		case FILE_TYPE_CHAR:
		{
			HANDLE old = io_stdout.exchange(handle);
			if (old != INVALID_HANDLE_VALUE)
			{
				::CloseHandle(old);
			}
			return true;
		}
		case FILE_TYPE_REMOTE:
		case FILE_TYPE_UNKNOWN:
			return false;
		default:
			fio_unreachable();
		}
	}

	bool set_stdout_console()
	{
		return set_stdout(::CreateFileW(L"CONOUT$", GENERIC_WRITE, FILE_SHARE_WRITE, nullptr, OPEN_EXISTING, 0, nullptr));
	}

#else

	bool set_stdout(int fd)
	{
		int old = io_stdout.exchange(fd);
		if (old != -1)
		{
			::close(old);
		}
		return true;
	}

#endif
}

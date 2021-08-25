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
}

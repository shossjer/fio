#include <catch2/catch.hpp>

#include "fio/mem.hpp"

#include "catchhacks.hpp"

#include <vector>

#if defined(_MSC_VER)
# include <Windows.h>
#else
# include <fcntl.h>
# include <sys/mman.h>
# include <unistd.h>
#endif

TEST_CASE("file write", "[.][dump]")
{
	BENCHMARK_DUMP("plot/file_write.dump", log_style, 1, 27, "#bytes")
	{
		BENCHMARK_GROUP("fputc (std)")(Catch::Benchmark::Groupometer meter)
		{
			meter.measure([&](int)
			{
				FILE * file = fopen("bnc.tmp", "wb");
				size_t remaining = meter.size();
				do
				{
					remaining--;
					fputc(static_cast<char>(remaining), file);
				}
				while (remaining > 0);
				fclose(file);
			});
		};

		BENCHMARK_GROUP("fwrite once (std)")(Catch::Benchmark::Groupometer meter)
		{
			meter.measure([&](int)
			{
				FILE * file = fopen("bnc.tmp", "wb");
				std::vector<char> buffer;
				size_t remaining = meter.size();
				do
				{
					remaining--;
					buffer.push_back(static_cast<char>(remaining));
				}
				while (remaining > 0);
				fwrite(buffer.data(), 1, buffer.size(), file);
				fclose(file);
			});
		};

#if defined(_MSC_VER)

		BENCHMARK_GROUP("WriteFile parts (win32)")(Catch::Benchmark::Groupometer meter)
		{
			meter.measure([&](int)
			{
				HANDLE hFile = ::CreateFileW(L"bnc.tmp", GENERIC_WRITE, 0, nullptr, CREATE_ALWAYS, 0, nullptr);
				std::vector<char> buffer;
				size_t remaining = meter.size();
				do
				{
					remaining--;
					buffer.push_back(static_cast<char>(remaining));
				}
				while (remaining > 0);
				const char * end = buffer.data() + buffer.size();
				/*size_t*/ remaining = buffer.size();
				if (remaining > DWORD(-1))
				{
					do
					{
						DWORD wrote;
						::WriteFile(hFile, end - remaining, DWORD(-1), &wrote, nullptr);

						remaining -= wrote;
					}
					while (remaining > DWORD(-1));
				}
				DWORD wrote;
				::WriteFile(hFile, end - remaining, static_cast<DWORD>(remaining), &wrote, nullptr);
				::CloseHandle(hFile);
			});
		};

		BENCHMARK_GROUP("view once (win32)")(Catch::Benchmark::Groupometer meter)
		{
			SYSTEM_INFO system_info;
			::GetSystemInfo(&system_info);

			meter.measure([&](int)
			{
				HANDLE hFile = ::CreateFileW(L"bnc.tmp", GENERIC_READ | GENERIC_WRITE, 0, nullptr, CREATE_ALWAYS, 0, nullptr);
				LARGE_INTEGER file_size;
				file_size.QuadPart = meter.size();
				::SetFilePointerEx(hFile, file_size, nullptr, FILE_BEGIN);
				::SetEndOfFile(hFile);
				HANDLE hMapping = ::CreateFileMappingW(hFile, nullptr, PAGE_READWRITE, 0, 0, nullptr);
				void * view = ::MapViewOfFile(hMapping, FILE_MAP_WRITE, 0, 0, 0);
				size_t remaining = meter.size();
				char * end = static_cast<char *>(view) + meter.size();
				do
				{
					*(end - remaining) = static_cast<char>(remaining);
					remaining--;
				}
				while (remaining > 0);

				::UnmapViewOfFile(view);
				::CloseHandle(hMapping);
				::CloseHandle(hFile);
			});
		};

		BENCHMARK_GROUP("view offset (win32)")(Catch::Benchmark::Groupometer meter)
		{
			SYSTEM_INFO system_info;
			::GetSystemInfo(&system_info);

			meter.measure([&](int)
			{
				HANDLE hFile = ::CreateFileW(L"bnc.tmp", GENERIC_READ | GENERIC_WRITE, 0, nullptr, CREATE_ALWAYS, 0, nullptr);
				LARGE_INTEGER file_size;
				file_size.QuadPart = 0;
				size_t remaining = meter.size();
				do
				{
					LARGE_INTEGER offset = file_size;
					file_size.QuadPart += system_info.dwAllocationGranularity;
					::SetFilePointerEx(hFile, file_size, nullptr, FILE_BEGIN);
					::SetEndOfFile(hFile);
					HANDLE hMapping = ::CreateFileMappingW(hFile, nullptr, PAGE_READWRITE, 0, 0, nullptr);
					void * view = ::MapViewOfFile(hMapping, FILE_MAP_WRITE, offset.HighPart, offset.LowPart, system_info.dwAllocationGranularity);

					size_t count = remaining < system_info.dwAllocationGranularity ? remaining : system_info.dwAllocationGranularity;
					remaining -= count;
					char * end = static_cast<char *>(view) + count;
					do
					{
						*(end - count) = static_cast<char>(count);
						count--;
					}
					while (count > 0);

					::UnmapViewOfFile(view);
					::CloseHandle(hMapping);
				}
				while (remaining > 0);
				file_size.QuadPart = meter.size();
				::SetFilePointerEx(hFile, file_size, nullptr, FILE_BEGIN);
				::SetEndOfFile(hFile);
				::CloseHandle(hFile);
			});
		};

		BENCHMARK_GROUP("view all (win32)")(Catch::Benchmark::Groupometer meter)
		{
			SYSTEM_INFO system_info;
			::GetSystemInfo(&system_info);

			meter.measure([&](int)
			{
				HANDLE hFile = ::CreateFileW(L"bnc.tmp", GENERIC_READ | GENERIC_WRITE, 0, nullptr, CREATE_ALWAYS, 0, nullptr);
				LARGE_INTEGER file_size;
				file_size.QuadPart = 0;
				size_t remaining = meter.size();
				do
				{
					file_size.QuadPart += system_info.dwAllocationGranularity;
					::SetFilePointerEx(hFile, file_size, nullptr, FILE_BEGIN);
					::SetEndOfFile(hFile);
					HANDLE hMapping = ::CreateFileMappingW(hFile, nullptr, PAGE_READWRITE, 0, 0, nullptr);
					void * view = ::MapViewOfFile(hMapping, FILE_MAP_WRITE, 0, 0, 0);

					if (remaining <= system_info.dwAllocationGranularity)
					{
						char * end = static_cast<char *>(view) + meter.size();
						do
						{
							*(end - remaining) = static_cast<char>(remaining);
							remaining--;
						}
						while (remaining > 0);

						::UnmapViewOfFile(view);
						::CloseHandle(hMapping);

						break;
					}

					size_t count = system_info.dwAllocationGranularity;
					remaining -= count;
					char * end = static_cast<char *>(view) + file_size.QuadPart;
					do
					{
						*(end - count) = static_cast<char>(count);
						count--;
					}
					while (count > 0);

					::UnmapViewOfFile(view);
					::CloseHandle(hMapping);
				}
				while (true);
				file_size.QuadPart = meter.size();
				::SetFilePointerEx(hFile, file_size, nullptr, FILE_BEGIN);
				::SetEndOfFile(hFile);
				::CloseHandle(hFile);
			});
		};

		BENCHMARK_GROUP("view offset double (win32)")(Catch::Benchmark::Groupometer meter)
		{
			SYSTEM_INFO system_info;
			::GetSystemInfo(&system_info);

			meter.measure([&](int)
			{
				HANDLE hFile = ::CreateFileW(L"bnc.tmp", GENERIC_READ | GENERIC_WRITE, 0, nullptr, CREATE_ALWAYS, 0, nullptr);
				LARGE_INTEGER file_size;
				file_size.QuadPart = system_info.dwAllocationGranularity;
				LARGE_INTEGER offset;
				offset.QuadPart = 0;
				size_t remaining = meter.size();
				goto entry;
				do
				{
					offset.QuadPart += file_size.QuadPart;
					file_size.QuadPart *= 2;
				entry:
					::SetFilePointerEx(hFile, file_size, nullptr, FILE_CURRENT);
					::SetEndOfFile(hFile);
					HANDLE hMapping = ::CreateFileMappingW(hFile, nullptr, PAGE_READWRITE, 0, 0, nullptr);
					void * view = ::MapViewOfFile(hMapping, FILE_MAP_WRITE, offset.HighPart, offset.LowPart, 0);

					size_t count = remaining < static_cast<size_t>(file_size.QuadPart) ? remaining : static_cast<size_t>(file_size.QuadPart);
					remaining -= count;
					char * end = static_cast<char *>(view) + count;
					do
					{
						*(end - count) = static_cast<char>(count);
						count--;
					}
					while (count > 0);

					::UnmapViewOfFile(view);
					::CloseHandle(hMapping);
				}
				while (remaining > 0);
				file_size.QuadPart = meter.size();
				::SetFilePointerEx(hFile, file_size, nullptr, FILE_BEGIN);
				::SetEndOfFile(hFile);
				::CloseHandle(hFile);
			});
		};

		BENCHMARK_GROUP("view all double (win32)")(Catch::Benchmark::Groupometer meter)
		{
			SYSTEM_INFO system_info;
			::GetSystemInfo(&system_info);

			meter.measure([&](int)
			{
				HANDLE hFile = ::CreateFileW(L"bnc.tmp", GENERIC_READ | GENERIC_WRITE, 0, nullptr, CREATE_ALWAYS, 0, nullptr);
				LARGE_INTEGER file_size;
				file_size.QuadPart = system_info.dwAllocationGranularity;
				size_t remaining = meter.size();
				size_t available = system_info.dwAllocationGranularity;
				goto entry;
				do
				{
					available = file_size.QuadPart;
					file_size.QuadPart *= 2;
				entry:
					::SetFilePointerEx(hFile, file_size, nullptr, FILE_BEGIN);
					::SetEndOfFile(hFile);
					HANDLE hMapping = ::CreateFileMappingW(hFile, nullptr, PAGE_READWRITE, 0, 0, nullptr);
					void * view = ::MapViewOfFile(hMapping, FILE_MAP_WRITE, 0, 0, 0);

					if (remaining <= available)
					{
						char * end = static_cast<char *>(view) + meter.size();
						do
						{
							*(end - remaining) = static_cast<char>(remaining);
							remaining--;
						}
						while (remaining > 0);

						::UnmapViewOfFile(view);
						::CloseHandle(hMapping);

						break;
					}

					size_t count = available;
					remaining -= count;
					char * end = static_cast<char *>(view) + file_size.QuadPart;
					do
					{
						*(end - count) = static_cast<char>(count);
						count--;
					}
					while (count > 0);

					::UnmapViewOfFile(view);
					::CloseHandle(hMapping);
				}
				while (true);
				file_size.QuadPart = meter.size();
				::SetFilePointerEx(hFile, file_size, nullptr, FILE_BEGIN);
				::SetEndOfFile(hFile);
				::CloseHandle(hFile);
			});
		};

#else

		BENCHMARK_GROUP("write parts (posix)")(Catch::Benchmark::Groupometer meter)
		{
			meter.measure([&](int)
			{
				int fd = ::open("bnc.tmp", O_WRONLY | O_CREAT, 0664);
				std::vector<char> buffer;
				size_t remaining = meter.size();
				do
				{
					remaining--;
					buffer.push_back(static_cast<char>(remaining));
				}
				while (remaining > 0);
				const char * end = buffer.data() + buffer.size();
				/*size_t*/ remaining = buffer.size();
				do
				{
					ssize_t wrote = ::write(fd, end - remaining, remaining);

					remaining -= wrote;
				}
				while (remaining > 0);
				::close(fd);
			});
		};

		BENCHMARK_GROUP("mmap once (posix)")(Catch::Benchmark::Groupometer meter)
		{
			meter.measure([&](int)
			{
				int fd = ::open("bnc.tmp", O_RDWR | O_CREAT /*| O_EXCL*/, 0664);
				size_t file_size = meter.size();
				int kjhs1 = ::ftruncate(fd, file_size);
				fio_unused(kjhs1);
				void * map = ::mmap(nullptr, file_size, PROT_WRITE, MAP_SHARED, fd, 0);
				size_t remaining = meter.size();
				char * end = static_cast<char *>(map) + remaining;
				do
				{
					*(end - remaining) = static_cast<char>(remaining);

					remaining--;
				}
				while (remaining > 0);
				::munmap(map, file_size);
				::close(fd);
			});
		};

		BENCHMARK_GROUP("mmap offset (posix)")(Catch::Benchmark::Groupometer meter)
		{
			const size_t pagesize = ::sysconf(_SC_PAGESIZE);

			meter.measure([&](int)
			{
				int fd = ::open("bnc.tmp", O_RDWR | O_CREAT /*| O_EXCL*/, 0664);
				size_t file_size = pagesize;
				int kjhs1 = ::ftruncate(fd, file_size);
				fio_unused(kjhs1);
				void * map = ::mmap(nullptr, pagesize, PROT_WRITE, MAP_SHARED, fd, 0);
				size_t remaining = meter.size();

				int kjhs2;
				goto entry;

				do
				{
					kjhs2 = ::ftruncate(fd, file_size + pagesize);
					fio_unused(kjhs2);
					map = ::mmap(map, pagesize, PROT_WRITE, MAP_SHARED | MAP_FIXED, fd, file_size);
					file_size += pagesize;

				entry:
					size_t count = remaining < pagesize ? remaining : pagesize;
					remaining -= count;
					char * end = static_cast<char *>(map) + count;
					do
					{
						*(end - count) = static_cast<char>(count);
						count--;
					}
					while (count > 0);
				}
				while (remaining > 0);

				::munmap(map, pagesize);
				int kjhs3 = ::ftruncate(fd, meter.size());
				fio_unused(kjhs3);
				::close(fd);
			});
		};

		BENCHMARK_GROUP("mmap + remap (linux)")(Catch::Benchmark::Groupometer meter)
		{
			const size_t pagesize = ::sysconf(_SC_PAGESIZE);

			meter.measure([&](int)
			{
				int fd = ::open("bnc.tmp", O_RDWR | O_CREAT /*| O_EXCL*/, 0664);
				size_t file_size = pagesize;
				int kjhs1 = ::ftruncate(fd, file_size);
				fio_unused(kjhs1);
				void * map = ::mmap(nullptr, file_size, PROT_WRITE, MAP_SHARED, fd, 0);
				size_t remaining = meter.size();

				if (remaining > pagesize)
				{
					do
					{
						size_t count = pagesize;
						remaining -= count;
						char * end = static_cast<char *>(map) + file_size;
						do
						{
							*(end - count) = static_cast<char>(count);
							count--;
						}
						while (count > 0);

						int kjhs2 = ::ftruncate(fd, file_size + pagesize);
						fio_unused(kjhs2);
						map = ::mremap(map, file_size, file_size + pagesize, MREMAP_MAYMOVE);
						file_size += pagesize;
					}
					while (remaining > pagesize);
				}
				{
					char * end = static_cast<char *>(map) + meter.size();
					do
					{
						*(end - remaining) = static_cast<char>(remaining);
						remaining--;
					}
					while (remaining > 0);
				}

				::munmap(map, file_size);
				int kjhs3 = ::ftruncate(fd, meter.size());
				fio_unused(kjhs3);
				::close(fd);
			});
		};

		BENCHMARK_GROUP("mmap offset double (posix)")(Catch::Benchmark::Groupometer meter)
		{
			const size_t pagesize = ::sysconf(_SC_PAGESIZE);

			meter.measure([&](int)
			{
				int fd = ::open("bnc.tmp", O_RDWR | O_CREAT /*| O_EXCL*/, 0664);
				size_t file_size = pagesize;
				size_t offset = 0;
				size_t remaining = meter.size();

				goto entry;

				do
				{
					offset += file_size;
					file_size *= 2;
				entry:
					int kjhs2 = ::ftruncate(fd, offset + file_size);
					fio_unused(kjhs2);
					void * map = ::mmap(nullptr, file_size, PROT_WRITE, MAP_SHARED, fd, offset);

					size_t count = remaining < file_size ? remaining : file_size;
					remaining -= count;
					char * end = static_cast<char *>(map) + count;
					do
					{
						*(end - count) = static_cast<char>(count);
						count--;
					}
					while (count > 0);

					::munmap(map, file_size);
				}
				while (remaining > 0);

				int kjhs3 = ::ftruncate(fd, meter.size());
				fio_unused(kjhs3);
				::close(fd);
			});
		};

		BENCHMARK_GROUP("mmap + remap double (linux)")(Catch::Benchmark::Groupometer meter)
		{
			const size_t pagesize = ::sysconf(_SC_PAGESIZE);

			meter.measure([&](int)
			{
				int fd = ::open("bnc.tmp", O_RDWR | O_CREAT /*| O_EXCL*/, 0664);
				size_t file_size = pagesize;
				int kjhs1 = ::ftruncate(fd, file_size);
				fio_unused(kjhs1);
				void * map = ::mmap(nullptr, file_size, PROT_WRITE, MAP_SHARED, fd, 0);
				size_t remaining = meter.size();
				size_t available = file_size;

				if (remaining > available)
				{
					do
					{
						size_t count = available;
						remaining -= count;
						char * end = static_cast<char *>(map) + file_size;
						do
						{
							*(end - count) = static_cast<char>(count);
							count--;
						}
						while (count > 0);

						int kjhs2 = ::ftruncate(fd, file_size * 2);
						fio_unused(kjhs2);
						map = ::mremap(map, file_size, file_size * 2, MREMAP_MAYMOVE);
						available = file_size;
						file_size *= 2;
					}
					while (remaining > available);
				}
				{
					char * end = static_cast<char *>(map) + meter.size();
					do
					{
						*(end - remaining) = static_cast<char>(remaining);
						remaining--;
					}
					while (remaining > 0);
				}

				::munmap(map, file_size);
				int kjhs3 = ::ftruncate(fd, meter.size());
				fio_unused(kjhs3);
				::close(fd);
			});
		};

#endif
	}
}

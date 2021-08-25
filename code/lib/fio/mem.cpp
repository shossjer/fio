#include "fio/mem.hpp"
#include "fio/cpuid.hpp"

namespace
{
	fio_target("avx512f") void memcpy_avx512f(const void * src, void * dst, fio::usize size)
	{
		// todo msvc does a lot of super funky movs
		fio_unused(fio_expect(16 < size));

//#if !(defined(__SSE__) || (defined(_MSC_VER) && (defined(_M_X64) || defined(_M_AMD64) || (defined(_M_IX86_FP) && _M_IX86_FP >= 1))))
		if (size <= 32)
		{
			const __m128i a = _mm_loadu_si128(reinterpret_cast<const __m128i *>(reinterpret_cast<const fio::uint8 *>(src) + 0));
			_mm_storeu_si128(reinterpret_cast<__m128i *>(reinterpret_cast<fio::uint8 *>(dst) + 0), a);
			const __m128i b = _mm_loadu_si128(reinterpret_cast<const __m128i *>(reinterpret_cast<const fio::uint8 *>(src) + size - 16));
			_mm_storeu_si128(reinterpret_cast<__m128i *>(reinterpret_cast<fio::uint8 *>(dst) + size - 16), b);
		}
		else
//#endif
//#if !(defined(__AVX__))
		if (size <= 64)
		{
			const __m256i a = _mm256_loadu_si256(reinterpret_cast<const __m256i *>(reinterpret_cast<const fio::uint8 *>(src) + 0));
			_mm256_storeu_si256(reinterpret_cast<__m256i *>(reinterpret_cast<fio::uint8 *>(dst) + 0), a);
			const __m256i b = _mm256_loadu_si256(reinterpret_cast<const __m256i *>(reinterpret_cast<const fio::uint8 *>(src) + size - 32));
			_mm256_storeu_si256(reinterpret_cast<__m256i *>(reinterpret_cast<fio::uint8 *>(dst) + size - 32), b);
		}
		else
//#endif
		{
			fio::usize end_index;

//#if !defined(__AVX__)
			if (size <= 128)
			{
				end_index = 0;
			}
			else
			{
//#endif
				end_index = size - 128;
				fio::usize index = 0;
				do
				{
					const __m512i a = _mm512_loadu_si512(reinterpret_cast<const fio::uint8 *>(src) + index + 0);
					_mm512_storeu_si512(reinterpret_cast<fio::uint8 *>(dst) + index + 0, a);
					const __m512i b = _mm512_loadu_si512(reinterpret_cast<const fio::uint8 *>(src) + index + 64);
					_mm512_storeu_si512(reinterpret_cast<fio::uint8 *>(dst) + index + 64, b);

					index += 128;
				}
				while (index < end_index);
//#if !defined(__AVX__)
			}
//#endif

			const __m512i a = _mm512_loadu_si512(reinterpret_cast<const fio::uint8 *>(src) + end_index + 0);
			_mm512_storeu_si512(reinterpret_cast<fio::uint8 *>(dst) + end_index + 0, a);
			const __m512i b = _mm512_loadu_si512(reinterpret_cast<const fio::uint8 *>(src) + size - 64);
			_mm512_storeu_si512(reinterpret_cast<fio::uint8 *>(dst) + size - 64, b);
		}
	}

	fio_target("avx") void memcpy_avx(const void * src, void * dst, fio::usize size)
	{
		// todo msvc does a lot of super funky movs
		fio_unused(fio_expect(16 < size));

//#if !(defined(__SSE__) || (defined(_MSC_VER) && (defined(_M_X64) || defined(_M_AMD64) || (defined(_M_IX86_FP) && _M_IX86_FP >= 1))))
		if (size <= 32)
		{
			const __m128i a = _mm_loadu_si128(reinterpret_cast<const __m128i *>(reinterpret_cast<const fio::uint8 *>(src) + 0));
			_mm_storeu_si128(reinterpret_cast<__m128i *>(reinterpret_cast<fio::uint8 *>(dst) + 0), a);
			const __m128i b = _mm_loadu_si128(reinterpret_cast<const __m128i *>(reinterpret_cast<const fio::uint8 *>(src) + size - 16));
			_mm_storeu_si128(reinterpret_cast<__m128i *>(reinterpret_cast<fio::uint8 *>(dst) + size - 16), b);
		}
		else
//#endif
		{
			fio::usize end_index;

//#if !defined(__AVX__)
			if (size <= 64)
			{
				end_index = 0;
			}
			else
			{
//#endif
				end_index = size - 64;
				fio::usize index = 0;
				do
				{
					const __m256i a = _mm256_loadu_si256(reinterpret_cast<const __m256i *>(reinterpret_cast<const fio::uint8 *>(src) + index + 0));
					_mm256_storeu_si256(reinterpret_cast<__m256i *>(reinterpret_cast<fio::uint8 *>(dst) + index + 0), a);
					const __m256i b = _mm256_loadu_si256(reinterpret_cast<const __m256i *>(reinterpret_cast<const fio::uint8 *>(src) + index + 32));
					_mm256_storeu_si256(reinterpret_cast<__m256i *>(reinterpret_cast<fio::uint8 *>(dst) + index + 32), b);

					index += 64;
				}
				while (index < end_index);
//#if !defined(__AVX__)
			}
//#endif

			const __m256i a = _mm256_loadu_si256(reinterpret_cast<const __m256i *>(reinterpret_cast<const fio::uint8 *>(src) + end_index + 0));
			_mm256_storeu_si256(reinterpret_cast<__m256i *>(reinterpret_cast<fio::uint8 *>(dst) + end_index + 0), a);
			const __m256i b = _mm256_loadu_si256(reinterpret_cast<const __m256i *>(reinterpret_cast<const fio::uint8 *>(src) + size - 32));
			_mm256_storeu_si256(reinterpret_cast<__m256i *>(reinterpret_cast<fio::uint8 *>(dst) + size - 32), b);
		}
	}

	fio_target("sse2") void memcpy_sse2(const void * src, void * dst, fio::usize size)
	{
		// todo msvc does a lot of super funky movs
		fio_unused(fio_expect(16 < size));

		fio::usize end_index;

//#if !(defined(__SSE__) || (defined(_MSC_VER) && (defined(_M_X64) || defined(_M_AMD64) || (defined(_M_IX86_FP) && _M_IX86_FP >= 1))))
		if (size < 32)
		{
			end_index = 0;
		}
		else
//#endif
		{
			if (size < 64)
			{
				end_index = 0;
			}
			else
			{
				end_index = size - 64;
				fio::usize index = 0;
				do
				{
					const __m128i a = _mm_loadu_si128(reinterpret_cast<const __m128i *>(reinterpret_cast<const fio::uint8 *>(src) + index + 0));
					_mm_storeu_si128(reinterpret_cast<__m128i *>(reinterpret_cast<fio::uint8 *>(dst) + index + 0), a);
					const __m128i b = _mm_loadu_si128(reinterpret_cast<const __m128i *>(reinterpret_cast<const fio::uint8 *>(src) + index + 16));
					_mm_storeu_si128(reinterpret_cast<__m128i *>(reinterpret_cast<fio::uint8 *>(dst) + index + 16), b);
					const __m128i c = _mm_loadu_si128(reinterpret_cast<const __m128i *>(reinterpret_cast<const fio::uint8 *>(src) + index + 32));
					_mm_storeu_si128(reinterpret_cast<__m128i *>(reinterpret_cast<fio::uint8 *>(dst) + index + 32), c);
					const __m128i d = _mm_loadu_si128(reinterpret_cast<const __m128i *>(reinterpret_cast<const fio::uint8 *>(src) + index + 48));
					_mm_storeu_si128(reinterpret_cast<__m128i *>(reinterpret_cast<fio::uint8 *>(dst) + index + 48), d);

					index += 64;
				}
				while (index < end_index);
			}

			const __m128i b = _mm_loadu_si128(reinterpret_cast<const __m128i *>(reinterpret_cast<const fio::uint8 *>(src) + end_index + 16));
			_mm_storeu_si128(reinterpret_cast<__m128i *>(reinterpret_cast<fio::uint8 *>(dst) + end_index + 16), b);
			const __m128i c = _mm_loadu_si128(reinterpret_cast<const __m128i *>(reinterpret_cast<const fio::uint8 *>(src) + size - 32));
			_mm_storeu_si128(reinterpret_cast<__m128i *>(reinterpret_cast<fio::uint8 *>(dst) + size - 32), c);
		}

		const __m128i a = _mm_loadu_si128(reinterpret_cast<const __m128i *>(reinterpret_cast<const fio::uint8 *>(src) + end_index + 0));
		_mm_storeu_si128(reinterpret_cast<__m128i *>(reinterpret_cast<fio::uint8 *>(dst) + end_index + 0), a);
		const __m128i d = _mm_loadu_si128(reinterpret_cast<const __m128i *>(reinterpret_cast<const fio::uint8 *>(src) + size - 16));
		_mm_storeu_si128(reinterpret_cast<__m128i *>(reinterpret_cast<fio::uint8 *>(dst) + size - 16), d);
	}

	fio_target("sse") void memcpy_sse(const void * src, void * dst, fio::usize size)
	{
		// todo msvc does a lot of super funky movs
		fio_unused(fio_expect(16 < size));

		fio::usize end_index;

//#if !(defined(__SSE__) || (defined(_MSC_VER) && (defined(_M_X64) || defined(_M_AMD64) || (defined(_M_IX86_FP) && _M_IX86_FP >= 1))))
		if (size <= 32)
		{
			end_index = 0;
		}
		else
//#endif
		{
			if (size <= 64)
			{
				end_index = 0;
			}
			else
			{
				end_index = size - 64;
				fio::usize index = 0;
				do
				{
					const __m128 a = _mm_loadu_ps(reinterpret_cast<const float *>(reinterpret_cast<const fio::uint8 *>(src) + index + 0));
					_mm_storeu_ps(reinterpret_cast<float *>(reinterpret_cast<fio::uint8 *>(dst) + index + 0), a);
					const __m128 b = _mm_loadu_ps(reinterpret_cast<const float *>(reinterpret_cast<const fio::uint8 *>(src) + index + 16));
					_mm_storeu_ps(reinterpret_cast<float *>(reinterpret_cast<fio::uint8 *>(dst) + index + 16), b);
					const __m128 c = _mm_loadu_ps(reinterpret_cast<const float *>(reinterpret_cast<const fio::uint8 *>(src) + index + 32));
					_mm_storeu_ps(reinterpret_cast<float *>(reinterpret_cast<fio::uint8 *>(dst) + index + 32), c);
					const __m128 d = _mm_loadu_ps(reinterpret_cast<const float *>(reinterpret_cast<const fio::uint8 *>(src) + index + 48));
					_mm_storeu_ps(reinterpret_cast<float *>(reinterpret_cast<fio::uint8 *>(dst) + index + 48), d);

					index += 64;
				}
				while (index < end_index);
			}

			const __m128 b = _mm_loadu_ps(reinterpret_cast<const float *>(reinterpret_cast<const fio::uint8 *>(src) + end_index + 16));
			_mm_storeu_ps(reinterpret_cast<float *>(reinterpret_cast<fio::uint8 *>(dst) + end_index + 16), b);
			const __m128 c = _mm_loadu_ps(reinterpret_cast<const float *>(reinterpret_cast<const fio::uint8 *>(src) + size - 32));
			_mm_storeu_ps(reinterpret_cast<float *>(reinterpret_cast<fio::uint8 *>(dst) + size - 32), c);
		}

		const __m128 a = _mm_loadu_ps(reinterpret_cast<const float *>(reinterpret_cast<const fio::uint8 *>(src) + end_index + 0));
		_mm_storeu_ps(reinterpret_cast<float *>(reinterpret_cast<fio::uint8 *>(dst) + end_index + 0), a);
		const __m128 d = _mm_loadu_ps(reinterpret_cast<const float *>(reinterpret_cast<const fio::uint8 *>(src) + size - 16));
		_mm_storeu_ps(reinterpret_cast<float *>(reinterpret_cast<fio::uint8 *>(dst) + size - 16), d);
	}

	void memcpy_generic(const void * src, void * dst, fio::usize size)
	{
		// todo msvc does a lot of super funky movs
		fio_unused(fio_expect(16 < size));

		fio::usize end_index;

		if (size <= 32)
		{
			end_index = 0;
		}
		else
		{
			end_index = size - 32;
			fio::usize index = 0;
			do
			{
				const fio::uint64 a = *reinterpret_cast<const fio::uint64 *>(reinterpret_cast<const fio::uint8 *>(src) + index + 0);
				*reinterpret_cast<fio::uint64 *>(reinterpret_cast<fio::uint8 *>(dst) + index + 0) = a;
				const fio::uint64 b = *reinterpret_cast<const fio::uint64 *>(reinterpret_cast<const fio::uint8 *>(src) + index + 8);
				*reinterpret_cast<fio::uint64 *>(reinterpret_cast<fio::uint8 *>(dst) + index + 8) = b;
				const fio::uint64 c = *reinterpret_cast<const fio::uint64 *>(reinterpret_cast<const fio::uint8 *>(src) + index + 16);
				*reinterpret_cast<fio::uint64 *>(reinterpret_cast<fio::uint8 *>(dst) + index + 16) = c;
				const fio::uint64 d = *reinterpret_cast<const fio::uint64 *>(reinterpret_cast<const fio::uint8 *>(src) + index + 24);
				*reinterpret_cast<fio::uint64 *>(reinterpret_cast<fio::uint8 *>(dst) + index + 24) = d;

				index += 32;
			}
			while (index < end_index);
		}

		const fio::uint64 a = *reinterpret_cast<const fio::uint64 *>(reinterpret_cast<const fio::uint8 *>(src) + end_index + 0);
		*reinterpret_cast<fio::uint64 *>(reinterpret_cast<fio::uint8 *>(dst) + end_index + 0) = a;
		const fio::uint64 b = *reinterpret_cast<const fio::uint64 *>(reinterpret_cast<const fio::uint8 *>(src) + end_index + 8);
		*reinterpret_cast<fio::uint64 *>(reinterpret_cast<fio::uint8 *>(dst) + end_index + 8) = b;
		const fio::uint64 c = *reinterpret_cast<const fio::uint64 *>(reinterpret_cast<const fio::uint8 *>(src) + size - 16);
		*reinterpret_cast<fio::uint64 *>(reinterpret_cast<fio::uint8 *>(dst) + size - 16) = c;
		const fio::uint64 d = *reinterpret_cast<const fio::uint64 *>(reinterpret_cast<const fio::uint8 *>(src) + size - 8);
		*reinterpret_cast<fio::uint64 *>(reinterpret_cast<fio::uint8 *>(dst) + size - 8) = d;
	}
}

fio_resolve(memcpy, void, const void * src, void * dst, fio::usize size)
{
	fio_cpuinit();
	if (fio_cpucheck(AVX512F))
		return fio_cpucall(memcpy, avx512f, src, dst, size);
	else if (fio_cpucheck(AVX))
		return fio_cpucall(memcpy, avx, src, dst, size);
	else if (fio_cpucheck(SSE2))
		return fio_cpucall(memcpy, sse2, src, dst, size);
	else if (fio_cpucheck(SSE))
		return fio_cpucall(memcpy, sse, src, dst, size);
	else
		return fio_cpucall(memcpy, generic, src, dst, size);
}

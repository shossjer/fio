#pragma once

#include "fio/compiler.hpp"
#include "fio/stdint.hpp"

#if defined(_MSC_VER)
# include <intrin.h>
#endif

#if defined(__GNUC__)
# if defined(_M_X64) || defined(_M_AMD64) || defined(__x86_64__) || (defined(_MSC_VER) && defined(_M_IX86)) || defined(__i386__)
#  include <x86intrin.h>
# endif
#endif

namespace fio
{
	namespace detail
	{
#if defined(__GNUC__)
		extern void memcpy(const void * src, void * dst, usize size);
#else
		extern void (* memcpy)(const void * src, void * dst, usize size);
#endif
	}

#if defined(__AVX512F__)
	constexpr usize small_memcpy_size = 256;
#elif defined(__AVX__)
	constexpr usize small_memcpy_size = 128;
#elif defined(__SSE__) || (defined(_MSC_VER) && (defined(_M_X64) || defined(_M_AMD64) || (defined(_M_IX86_FP) && _M_IX86_FP >= 1)))
	constexpr usize small_memcpy_size = 64;
#elif defined(_M_X64) || defined(_M_AMD64) || defined(__x86_64__)
	constexpr usize small_memcpy_size = 32;
#else
	constexpr usize small_memcpy_size = 16;
#endif

	fio_inline void memcpy(const void * src, void * dst, usize size)
	{
		if (size <= small_memcpy_size)
		{
			switch (size)
			{
#if defined(__AVX512F__)
			case 256:
			case 255:
			case 254:
			case 253:
			case 252:
			case 251:
			case 250:
			case 249:
			case 248:
			case 247:
			case 246:
			case 245:
			case 244:
			case 243:
			case 242:
			case 241:
			case 240:
			case 239:
			case 238:
			case 237:
			case 236:
			case 235:
			case 234:
			case 233:
			case 232:
			case 231:
			case 230:
			case 229:
			case 228:
			case 227:
			case 226:
			case 225:
			case 224:
			case 223:
			case 222:
			case 221:
			case 220:
			case 219:
			case 218:
			case 217:
			case 216:
			case 215:
			case 214:
			case 213:
			case 212:
			case 211:
			case 210:
			case 209:
			case 208:
			case 207:
			case 206:
			case 205:
			case 204:
			case 203:
			case 202:
			case 201:
			case 200:
			case 199:
			case 198:
			case 197:
			case 196:
			case 195:
			case 194:
			case 193:
				_mm512_storeu_si512(reinterpret_cast<uint8 *>(dst) + 128, _mm512_loadu_si512(reinterpret_cast<const uint8 *>(src) + 128));
				fio_fallthrough;
			case 192:
			case 191:
			case 190:
			case 189:
			case 188:
			case 187:
			case 186:
			case 185:
			case 184:
			case 183:
			case 182:
			case 181:
			case 180:
			case 179:
			case 178:
			case 177:
			case 176:
			case 175:
			case 174:
			case 173:
			case 172:
			case 171:
			case 170:
			case 169:
			case 168:
			case 167:
			case 166:
			case 165:
			case 164:
			case 163:
			case 162:
			case 161:
			case 160:
			case 159:
			case 158:
			case 157:
			case 156:
			case 155:
			case 154:
			case 153:
			case 152:
			case 151:
			case 150:
			case 149:
			case 148:
			case 147:
			case 146:
			case 145:
			case 144:
			case 143:
			case 142:
			case 141:
			case 140:
			case 139:
			case 138:
			case 137:
			case 136:
			case 135:
			case 134:
			case 133:
			case 132:
			case 131:
			case 130:
			case 129:
				_mm512_storeu_si512(reinterpret_cast<uint8 *>(dst) + 64, _mm512_loadu_si512(reinterpret_cast<const uint8 *>(src) + 64));
				fio_fallthrough;
#endif
#if defined(__AVX__)
			case 128:
			case 127:
			case 126:
			case 125:
			case 124:
			case 123:
			case 122:
			case 121:
			case 120:
			case 119:
			case 118:
			case 117:
			case 116:
			case 115:
			case 114:
			case 113:
			case 112:
			case 111:
			case 110:
			case 109:
			case 108:
			case 107:
			case 106:
			case 105:
			case 104:
			case 103:
			case 102:
			case 101:
			case 100:
			case 99:
			case 98:
			case 97:
# if !defined(__AVX512F__)
				_mm256_storeu_si256(reinterpret_cast<__m256i *>(reinterpret_cast<uint8 *>(dst) + 64), _mm256_loadu_si256(reinterpret_cast<const __m256i *>(reinterpret_cast<const uint8 *>(src) + 64)));
				fio_fallthrough;
# endif
			case 96:
			case 95:
			case 94:
			case 93:
			case 92:
			case 91:
			case 90:
			case 89:
			case 88:
			case 87:
			case 86:
			case 85:
			case 84:
			case 83:
			case 82:
			case 81:
			case 80:
			case 79:
			case 78:
			case 77:
			case 76:
			case 75:
			case 74:
			case 73:
			case 72:
			case 71:
			case 70:
			case 69:
			case 68:
			case 67:
			case 66:
			case 65:
# if defined(__AVX512F__)
				_mm512_storeu_si512(reinterpret_cast<uint8 *>(dst) + size - 64, _mm512_loadu_si512(reinterpret_cast<const uint8 *>(src) + size - 64));
# else
				_mm256_storeu_si256(reinterpret_cast<__m256i *>(reinterpret_cast<uint8 *>(dst) + 32), _mm256_loadu_si256(reinterpret_cast<const __m256i *>(reinterpret_cast<const uint8 *>(src) + 32)));
# endif
				fio_fallthrough;
#endif
#if defined(__SSE__) || (defined(_MSC_VER) && (defined(_M_X64) || defined(_M_AMD64) || (defined(_M_IX86_FP) && _M_IX86_FP >= 1)))
			case 64:
# if defined(__AVX512F__)
				_mm512_storeu_si512(reinterpret_cast<uint8 *>(dst) + 0, _mm512_loadu_si512(reinterpret_cast<const uint8 *>(src) + 0));
				return;
# endif
			case 63:
			case 62:
			case 61:
			case 60:
			case 59:
			case 58:
			case 57:
			case 56:
			case 55:
			case 54:
			case 53:
			case 52:
			case 51:
			case 50:
			case 49:
# if !defined(__AVX__)
#  if defined(__SSE2__) || (defined(_MSC_VER) && (defined(_M_X64) || defined(_M_AMD64) || (defined(_M_IX86_FP) && _M_IX86_FP >= 2)))
				_mm_storeu_si128(reinterpret_cast<__m128i *>(reinterpret_cast<uint8 *>(dst) + 32), _mm_loadu_si128(reinterpret_cast<const __m128i *>(reinterpret_cast<const uint8 *>(src) + 32)));
#  else
				_mm_storeu_ps(reinterpret_cast<float *>(reinterpret_cast<uint8 *>(dst) + 32), _mm_loadu_ps(reinterpret_cast<const float *>(reinterpret_cast<const uint8 *>(src) + 32)));
#  endif
				fio_fallthrough;
# endif
			case 48:
			case 47:
			case 46:
			case 45:
			case 44:
			case 43:
			case 42:
			case 41:
			case 40:
			case 39:
			case 38:
			case 37:
			case 36:
			case 35:
			case 34:
			case 33:
# if defined(__AVX__)
				_mm256_storeu_si256(reinterpret_cast<__m256i *>(reinterpret_cast<uint8 *>(dst) + size - 32), _mm256_loadu_si256(reinterpret_cast<const __m256i *>(reinterpret_cast<const uint8 *>(src) + size - 32)));
# else
#  if defined(__SSE2__) || (defined(_MSC_VER) && (defined(_M_X64) || defined(_M_AMD64) || (defined(_M_IX86_FP) && _M_IX86_FP >= 2)))
				_mm_storeu_si128(reinterpret_cast<__m128i *>(reinterpret_cast<uint8 *>(dst) + 16), _mm_loadu_si128(reinterpret_cast<const __m128i *>(reinterpret_cast<const uint8 *>(src) + 16)));
#  else
				_mm_storeu_ps(reinterpret_cast<float *>(reinterpret_cast<uint8 *>(dst) + 16), _mm_loadu_ps(reinterpret_cast<const float *>(reinterpret_cast<const uint8 *>(src) + 16)));
#  endif
# endif
				fio_fallthrough;
#endif
#if defined(_M_X64) || defined(_M_AMD64) || defined(__x86_64__)
			case 32:
# if defined(__AVX__)
				_mm256_storeu_si256(reinterpret_cast<__m256i *>(reinterpret_cast<uint8 *>(dst) + 0), _mm256_loadu_si256(reinterpret_cast<const __m256i *>(reinterpret_cast<const uint8 *>(src) + 0)));
				return;
# endif
			case 31:
			case 30:
			case 29:
			case 28:
			case 27:
			case 26:
			case 25:
# if !(defined(__SSE__) || (defined(_MSC_VER) && (defined(_M_X64) || defined(_M_AMD64) || (defined(_M_IX86_FP) && _M_IX86_FP >= 1))))
				*(reinterpret_cast<uint64 *>(reinterpret_cast<uint8 *>(dst) + 16)) = *(reinterpret_cast<const uint64 *>(reinterpret_cast<const uint8 *>(src) + 16));
				fio_fallthrough;
# endif
			case 24:
			case 23:
			case 22:
			case 21:
			case 20:
			case 19:
			case 18:
			case 17:
# if defined(__SSE__) || (defined(_MSC_VER) && (defined(_M_X64) || defined(_M_AMD64) || (defined(_M_IX86_FP) && _M_IX86_FP >= 1)))
#  if defined(__SSE2__) || (defined(_MSC_VER) && (defined(_M_X64) || defined(_M_AMD64) || (defined(_M_IX86_FP) && _M_IX86_FP >= 2)))
				_mm_storeu_si128(reinterpret_cast<__m128i *>(reinterpret_cast<uint8 *>(dst) + size - 16), _mm_loadu_si128(reinterpret_cast<const __m128i *>(reinterpret_cast<const uint8 *>(src) + size - 16)));
#  else
				_mm_storeu_ps(reinterpret_cast<float *>(reinterpret_cast<uint8 *>(dst) + size - 16), _mm_loadu_ps(reinterpret_cast<const float *>(reinterpret_cast<const uint8 *>(src) + size - 16)));
#  endif
# else
				*(reinterpret_cast<uint64 *>(reinterpret_cast<uint8 *>(dst) + 8)) = *(reinterpret_cast<const uint64 *>(reinterpret_cast<const uint8 *>(src) + 8));
# endif
				fio_fallthrough;
#endif
			case 16:
# if defined(__SSE__) || (defined(_MSC_VER) && (defined(_M_X64) || defined(_M_AMD64) || (defined(_M_IX86_FP) && _M_IX86_FP >= 1)))
#  if defined(__SSE2__) || (defined(_MSC_VER) && (defined(_M_X64) || defined(_M_AMD64) || (defined(_M_IX86_FP) && _M_IX86_FP >= 2)))
				_mm_storeu_si128(reinterpret_cast<__m128i *>(reinterpret_cast<uint8 *>(dst) + 0), _mm_loadu_si128(reinterpret_cast<const __m128i *>(reinterpret_cast<const uint8 *>(src) + 0)));
#  else
				_mm_storeu_ps(reinterpret_cast<float *>(reinterpret_cast<uint8 *>(dst) + 0), _mm_loadu_ps(reinterpret_cast<const float *>(reinterpret_cast<const uint8 *>(src) + 0)));
#  endif
				return;
# endif
			case 15:
			case 14:
			case 13:
# if !(defined(_M_X64) || defined(_M_AMD64) || defined(__x86_64__))
				*(reinterpret_cast<uint32 *>(reinterpret_cast<uint8 *>(dst) + 8)) = *(reinterpret_cast<const uint32 *>(reinterpret_cast<const uint8 *>(src) + 8));
				fio_fallthrough;
# endif
			case 12:
			case 11:
			case 10:
			case 9:
# if defined(_M_X64) || defined(_M_AMD64) || defined(__x86_64__)
				*(reinterpret_cast<uint64 *>(reinterpret_cast<uint8 *>(dst) + size - 8)) = *(reinterpret_cast<const uint64 *>(reinterpret_cast<const uint8 *>(src) + size - 8));
# else
				*(reinterpret_cast<uint32 *>(reinterpret_cast<uint8 *>(dst) + 4)) = *(reinterpret_cast<const uint32 *>(reinterpret_cast<const uint8 *>(src) + 4));
# endif
				fio_fallthrough;
			case 8:
# if defined(_M_X64) || defined(_M_AMD64) || defined(__x86_64__)
				* (reinterpret_cast<uint64 *>(reinterpret_cast<uint8 *>(dst) + 0)) = *(reinterpret_cast<const uint64 *>(reinterpret_cast<const uint8 *>(src) + 0));
				return;
# endif
			case 7:
			case 6:
			case 5:
				*(reinterpret_cast<uint32 *>(reinterpret_cast<uint8 *>(dst) + size - 4)) = *(reinterpret_cast<const uint32 *>(reinterpret_cast<const uint8 *>(src) + size - 4));
				fio_fallthrough;
			case 4:
				*reinterpret_cast<uint32 *>(dst) = *reinterpret_cast<const uint32 *>(src);
				return;
			case 3:
				*(reinterpret_cast<uint8 *>(dst) + 2) = *(reinterpret_cast<const uint8 *>(src) + 2);
				fio_fallthrough;
			case 2:
				*reinterpret_cast<uint16 *>(dst) = *reinterpret_cast<const uint16 *>(src);
				return;
			case 1:
				*reinterpret_cast<uint8 *>(dst) = *reinterpret_cast<const uint8 *>(src);
				fio_fallthrough;
			case 0: return;
			default: fio_unreachable();
			}
		}

		return detail::memcpy(src, dst, size);
	}
}

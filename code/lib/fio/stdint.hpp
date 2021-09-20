#pragma once

namespace fio
{
	using usize = decltype(sizeof 0);
	using ssize = decltype(static_cast<char *>(0) - static_cast<char *>(0));

	using uptr = usize;

#if defined(__UINT64_TYPE__)
	using uint64 = __UINT64_TYPE__;
#elif defined(_MSC_VER)
	using uint64 = unsigned __int64;
#elif defined(_M_X64) || defined(_M_AMD64) || defined(__x86_64__)
# error Missing implementation!
#endif

#if defined(__UINT32_TYPE__)
	using uint32 = __UINT32_TYPE__;
#elif defined(_MSC_VER)
	using uint32 = unsigned __int32;
#else
# error Missing implementation!
#endif

#if defined(__UINT16_TYPE__)
	using uint16 = __UINT16_TYPE__;
#elif defined(_MSC_VER)
	using uint16 = unsigned __int16;
#else
# error Missing implementation!
#endif

#if defined(__UINT8_TYPE__)
	using uint8 = __UINT8_TYPE__;
#elif defined(_MSC_VER)
	using uint8 = unsigned __int8;
#else
# error Missing implementation!
#endif

#if defined(__INT64_TYPE__)
	using sint64 = __INT64_TYPE__;
#elif defined(_MSC_VER)
	using sint64 = signed __int64;
#elif defined(_M_X64) || defined(_M_AMD64) || defined(__x86_64__)
# error Missing implementation!
#endif

#if defined(__INT32_TYPE__)
	using sint32 = __INT32_TYPE__;
#elif defined(_MSC_VER)
	using sint32 = signed __int32;
#else
# error Missing implementation!
#endif

#if defined(__INT16_TYPE__)
	using sint16 = __INT16_TYPE__;
#elif defined(_MSC_VER)
	using sint16 = signed __int16;
#else
# error Missing implementation!
#endif

#if defined(__INT8_TYPE__)
	using sint8 = __INT8_TYPE__;
#elif defined(_MSC_VER)
	using sint8 = signed __int8;
#else
# error Missing implementation!
#endif
}

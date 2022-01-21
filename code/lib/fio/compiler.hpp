#pragma once

#ifndef __has_builtin
# define __has_builtin(x) 0
#endif

#if defined(_DEBUG) || !defined(NDEBUG)
// in debug, breaks into debugger before crashing, otherwise optimizes
// assuming that the expression is true
# define fio_assert(x) static_cast<void>((x) ? true : (fio_break(), fio_crash(), false))
#else
// in debug, breaks into debugger before crashing, otherwise optimizes
// assuming that the expression is true
# define fio_assert(x) fio_assume(x)
#endif

#if __has_builtin(__builtin_assume)
// optimize knowing that the expression is true
# define fio_assume(x) __builtin_assume(x)
#elif defined(_MSC_VER)
// optimize knowing that the expression is true
# define fio_assume(x) __assume(x)
#else
// optimize knowing that the expression is true
# define fio_assume(x) static_cast<void>((x) ? true : (fio_unreachable(), false))
#endif

#if __has_builtin(__builtin_debugtrap)
// break into the debugger
# define fio_break() __builtin_debugtrap()
#elif defined(_MSC_VER)
// break into the debugger
# define fio_break() __debugbreak()
#elif defined(__x86_64__) || defined(__i386__)
// break into the debugger
# define fio_break() [](){ __asm__("int3"); }()
#else
# error Missing implementation!
#endif

#if __has_builtin(__builtin_trap) || defined(__GNUC__)
// crash the process
# define fio_crash() __builtin_trap()
#elif defined(_MSC_VER)
// crash the process
# define fio_crash() __fastfail(0)
// failure code zero should not be used, but we should not crash
// either so :shrug:
#else
# error Missing implementation!
#endif

#if defined(_DEBUG) || !defined(NDEBUG)
// breaks into the debugger if false (in debug builds), optimize
// knowing that the expression is true (in nondebug builds)
# define fio_expect(x) ((x) ? true : (fio_break(), false))
#else
// breaks into the debugger if false (in debug builds), optimize
// knowing that the expression is true (in nondebug builds)
# define fio_expect(x) (fio_assume(x), true)
#endif

#if defined(__GNUC__)
// silence warning about fall through in switches
# define fio_fallthrough __attribute__((fallthrough))
#else
// silence warning about fall through in switches
# define fio_fallthrough do {} while(0)
#endif

#if defined(_MSC_VER)
// optimize this call away
# define fio_inline __forceinline
#else
// optimize this call away
# define fio_inline inline __attribute__((always_inline))
#endif

#if defined(__GNUC__)
// overrides targeted architecture
# define fio_target(...) __attribute__((target (__VA_ARGS__)))
// https://gcc.gnu.org/onlinedocs/gcc/Common-Function-Attributes.html#target
// https://gcc.gnu.org/onlinedocs/gcc/Function-Multiversioning.html
#elif defined(_MSC_VER)
// overrides targeted architecture
# define fio_target(...)
#else
# error Missing implementation!
#endif

#if !defined(FIO_NOTHREADSYNC)
# if defined(__GNUC__)
// thread storage duration
#  define fio_thread __thread
// note gcc is awful at optimizing c++11 thread_local, but its own
// __thread extension works perfectly
# elif defined(_MSC_VER)
// thread storage duration
#  define fio_thread thread_local
# else
#  error Missing implementation!
# endif
#else
# define fio_thread
#endif

#if __has_builtin(__builtin_unreachable) ||\
	(defined(__GNUC__) && (__GNUC__ > 4 || (__GNUC__ == 4 && (__GNUC_MINOR__ >= 5))))
// optimize knowing that this branch is impossible
# define fio_unreachable() __builtin_unreachable()
#elif defined(_MSC_VER)
// optimize knowing that this branch is impossible
# define fio_unreachable() __assume(0)
#else
# error Missing implementation!
#endif

// silence warning about unused variable
# define fio_unused(x) static_cast<void>(x)

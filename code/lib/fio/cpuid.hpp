#if defined(__GNUC__)

# define fio_cpucall(stem, alt, ...) stem##_##alt
# define fio_cpuinit() __builtin_cpu_init()
# define fio_cpucheck(feature) __builtin_cpu_supports(FIO_FEATURE_NAME_##feature)
# define fio_resolve(stem, ret, ...) \
namespace fio { namespace detail { __attribute__((ifunc ("resolve_" #stem))) ret stem(__VA_ARGS__); }} \
extern "C" { ret (* resolve_##stem())(__VA_ARGS__); } \
ret (* resolve_##stem())(__VA_ARGS__)

# define FIO_FEATURE_NAME_SSE "sse"
# define FIO_FEATURE_NAME_SSE2 "sse2"
# define FIO_FEATURE_NAME_AVX "avx"
# define FIO_FEATURE_NAME_AVX512F "avx512f"

#else

# define fio_cpucall(stem, alt, ...) fio::detail::stem = stem##_##alt, stem##_##alt(__VA_ARGS__)
# define fio_cpuinit() if (fio::cpuid_uninited()) fio::cpuid_init()
# define fio_cpucheck(feature) fio::cpuid_supports(fio::cpuid_feature::feature)
# define fio_resolve(stem, ret, ...) \
static ret resolve_##stem(__VA_ARGS__); \
namespace fio { namespace detail { ret (* stem)(__VA_ARGS__) = resolve_##stem; }} \
static ret resolve_##stem(__VA_ARGS__)

# define static_cpuid_init() \
namespace fio { struct cpuid_init_type { explicit cpuid_init_type() { cpuid_init(); } }; } \
static fio::cpuid_init_type static_cpuid_init_once

namespace fio
{
	enum class cpuid_feature : unsigned int
	{
		SSE     = 1u << 0,
		SSE2    = 1u << 1,
		AVX     = 1u << 2,
		AVX512F = 1u << 3,
	};

	extern void cpuid_init();

	fio_inline bool cpuid_uninited()
	{
		extern unsigned int cpuid_feature_cache;

		return cpuid_feature_cache == 0;
	}

	fio_inline bool cpuid_supports(cpuid_feature feature)
	{
		extern unsigned int cpuid_feature_cache;

		if (fio_expect(cpuid_feature_cache != 0))
		{
			return (cpuid_feature_cache & static_cast<unsigned int>(feature)) != 0;
		}
		else
		{
			return false;
		}
	}
}

#endif

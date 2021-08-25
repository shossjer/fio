#if !defined(__GNUC__)

#if defined(_MSC_VER)
# include <intrin.h>
#elif defined(__GNUC__)
# include <cpuid.h>
#endif

#define CHECK_BIT(reg, bit) (reg & (1u << bit))

namespace
{
#if defined(_MSC_VER)
	using reg_type = int;
#elif defined(__GNUC__)
	using reg_type = unsigned int;
#else
# error Missing implementation!
#endif

	void get_cpuid(int n, reg_type * a)
	{
#if defined(_MSC_VER)
		__cpuid(a, n);
#elif defined(__GNUC__)
		__get_cpuid(n, a + 0, a + 1, a + 2, a + 3);
#else
# error Missing implementation!
#endif
	}
}

namespace fio
{
	enum class cpuid_feature : unsigned int
	{
		SSE     = 1u << 0,
		SSE2    = 1u << 1,
		AVX     = 1u << 2,
		AVX512F = 1u << 3,
	};

	unsigned int cpuid_feature_cache = 0;

	void cpuid_init()
	{
		reg_type info[4];

		get_cpuid(0, info);
		const unsigned int max_id = info[0];

		if (max_id >= 1)
		{
			get_cpuid(1, info);
			const int ecx = info[2];
			const int edx = info[3];
			if (CHECK_BIT(ecx, 28)) cpuid_feature_cache |= static_cast<unsigned int>(cpuid_feature::AVX);
			if (CHECK_BIT(edx, 25)) cpuid_feature_cache |= static_cast<unsigned int>(cpuid_feature::SSE);
			if (CHECK_BIT(edx, 26)) cpuid_feature_cache |= static_cast<unsigned int>(cpuid_feature::SSE2);
		}

		if (max_id >= 7)
		{
			get_cpuid(7, info);
			const int ebx = info[1];
			if (CHECK_BIT(ebx, 16)) cpuid_feature_cache |= static_cast<unsigned int>(cpuid_feature::AVX512F);
		}

		cpuid_feature_cache |= 0x80000000;
	}
}

#endif

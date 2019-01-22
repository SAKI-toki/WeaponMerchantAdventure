/**
* @file pow_n.h
* @brief ‘æ“ñˆø”‚ªintŒ^‚Ìpow
* @author ÎR —I
* @date 2019/01/09
*/
#pragma once
#ifndef SAKI_POW_N_2019_01_09
#define SAKI_POW_N_2019_01_09
#include <cstddef>

namespace saki
{
	namespace details
	{
		/**
		* @brief pow‚©‚ç”h¶
		*/
		template<typename T>
		constexpr T pow_n(T x, int y)
		{
			T sum = static_cast<T>(1);
			for (int i = 0; i < y; ++i)
			{
				sum *= x;
			}
			for (int i = 0; i > y; --i)
			{
				sum /= x;
			}
			return sum;
		}
		template<typename T>
		constexpr T pow_n(T x, size_t y)
		{
			T sum = static_cast<T>(1);
			for (size_t i = 0; i < y; ++i)
			{
				sum *= x;
			}
			return sum;
		}
	}
}
#endif //SAKI_POW_N_2019_01_09
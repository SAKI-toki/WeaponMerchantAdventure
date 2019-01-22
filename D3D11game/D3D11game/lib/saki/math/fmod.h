/**
* @file fmod.h
* @brief コンパイル時float,double剰余
* @author 石山 悠
* @date 2019/01/02
*/
#pragma once
#ifndef SAKI_FMOD_2019_01_02
#define SAKI_FMOD_2019_01_02
#include <type_traits>
#include <limits>
#include <saki/math/isnan.h>
#include <saki/math/signbit.h>
#include <saki/math/isinf.h>

namespace saki
{
	/**
	* @brief コンパイル時float,double剰余
	* @param x 割られる数
	* @param y 割る数
	* @return 剰余
	*/
	template<typename T>
	constexpr T fmod(T x, T y)
	{
		if (saki::isnan(x))
		{
			if (saki::isnan(y))
			{
				return saki::signbit(x) && saki::signbit(y) ?
					-std::numeric_limits<T>::quiet_NaN() :
					std::numeric_limits<T>::quiet_NaN();
			}
			else
			{
				return x;
			}
		}
		if (saki::isnan(y))return static_cast<T>(y);
		if (saki::isinf(x) || y == 0)
		{
			return -std::numeric_limits<T>::quiet_NaN();
		}
		if (x == 0)return static_cast<T>(x);
		if (saki::isinf(y))
		{
			return static_cast<T>(x);
		}

		//処理
		return static_cast<T>(x - static_cast<int>(x / y) * y);
	}
	/**
	* @brief 型が違う場合はそろえる
	*/
	template<typename T = double, typename T1, typename T2>
	constexpr T fmod(T1 x, T2 y)
	{
		return saki::fmod(static_cast<T>(x), static_cast<T>(y));
	}
}
#endif //SAKI_FMOD_2019_01_02
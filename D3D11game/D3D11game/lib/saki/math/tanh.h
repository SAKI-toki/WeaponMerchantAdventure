/**
* @file tanh.h
* @brief コンパイル時tanh
* @author 石山 悠
* @date 2019/01/08
*/
#pragma once
#ifndef SAKI_TANH_2019_01_08
#define SAKI_TANH_2019_01_08
#include <type_traits>
#include <limits>
#include <saki/math/isnan.h>
#include <saki/math/isinf.h>
#include <saki/math/copysign.h>
#include <saki/math/sinh.h>
#include <saki/math/cosh.h>

namespace saki
{
	/**
	* @brief コンパイル時tanh
	*/
	template<typename T,
		typename std::enable_if_t<std::is_floating_point_v<T>, std::nullptr_t> = nullptr>
		constexpr T tanh(T x)
	{
		if (saki::isnan(x) || x == 0)return x;
		if (saki::isinf(x))return static_cast<T>(saki::copysign(1, x));

		return saki::sinh(x) / saki::cosh(x);
	}
	/**
	* @brief 引数がint型の場合に、戻り値をdouble型にするためのもの
	*/
	template<typename T,
		typename std::enable_if_t<std::is_integral_v<T>, std::nullptr_t> = nullptr>
		constexpr double tanh(T x)
	{
		return saki::tanh(static_cast<double>(x));
	}
}
#endif //SAKI_TANH_2019_01_08
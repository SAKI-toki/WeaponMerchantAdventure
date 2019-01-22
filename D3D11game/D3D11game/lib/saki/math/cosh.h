/**
* @file cosh.h
* @brief コンパイル時cosh
* @author 石山 悠
* @date 2019/01/08
*/
#pragma once
#ifndef SAKI_COSH_2019_01_08
#define SAKI_COSH_2019_01_08
#include <cstddef>
#include <type_traits>
#include <limits>
#include <saki/math/factorial.h>
#include <saki/math/pow.h>
#include <saki/math/isnan.h>
#include <saki/math/isinf.h>

namespace saki
{
	/**
	* @brief コンパイル時cosh
	*/
	template<typename T,
		typename std::enable_if_t<std::is_floating_point_v<T>, std::nullptr_t> = nullptr>
		constexpr T cosh(T x)
	{
		if (saki::isnan(x) || saki::isinf(x))return x;
		if (x == 0)return static_cast<T>(1);
		T sum = 0;
		size_t n = 0;
		while (2 * n <= saki::factorial_limits<T>::limit)
		{
			sum += static_cast<T>(saki::pow(x, 2 * n) / saki::factorial<T>(2 * n));
			++n;
		}
		return sum;
	}
	/**
	* @brief 引数がint型の場合に、戻り値をdouble型にするためのもの
	*/
	template<typename T,
		typename std::enable_if_t<std::is_integral_v<T>, std::nullptr_t> = nullptr>
		constexpr double cosh(T x)
	{
		return saki::cosh(static_cast<double>(x));
	}
}
#endif //SAKI_COSH_2019_01_08
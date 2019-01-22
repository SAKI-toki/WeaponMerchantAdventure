/**
* @file cos.h
* @brief コンパイル時cos
* @author 石山 悠
* @date 2019/01/05
*/
#pragma once
#ifndef SAKI_COS_2019_01_05
#define SAKI_COS_2019_01_05
#include <cstddef>
#include <type_traits>
#include <limits>
#include <saki/math/factorial.h>
#include <saki/math/pi.h>
#include <saki/math/pow.h>
#include <saki/math/isnan.h>
#include <saki/math/isinf.h>

namespace saki
{
	/**
	* @brief コンパイル時cos
	* @param x ラジアン角
	*/
	template<typename T,
		typename std::enable_if_t<std::is_floating_point_v<T>, std::nullptr_t> = nullptr>
		constexpr T cos(T x)
	{
		//NaN
		if (saki::isnan(x))return x;
		//inf
		if (saki::isinf(x))
		{
			return -std::numeric_limits<T>::quiet_NaN();
		}
		//-PI≦x≦PIの範囲に収める
		while (x > saki::PI<T>)x -= saki::PI<T> * 2;
		while (x < -saki::PI<T>)x += saki::PI<T> * 2;

		T sum = 0;
		size_t n = 0;
		while (n <= saki::factorial_limits<T>::limit / 2)
		{
			sum += static_cast<T>(((n % 2 == 0) ? 1 : -1) *
				saki::pow<T>(x, 2 * n) /
				saki::factorial<T>(2 * n));
			++n;
		}
		return sum;
	}
	/**
	* @brief 引数がint型の場合に、戻り値をdouble型にするためのもの
	* @param x int型のラジアン角
	*/
	template<typename T,
		typename std::enable_if_t<std::is_integral_v<T>, std::nullptr_t> = nullptr>
		constexpr double cos(T x)
	{
		return saki::cos(static_cast<double>(x));
	}
}
#endif //SAKI_COS_2019_01_05
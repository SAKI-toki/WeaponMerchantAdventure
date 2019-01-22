/**
* @file exp.h
* @brief �R���p�C����exp
* @author �ΎR �I
* @date 2019/01/06
*/
#pragma once
#ifndef SAKI_EXP_2019_01_06
#define SAKI_EXP_2019_01_06
#include <cstddef>
#include <limits>
#include <type_traits>
#include <saki/math/factorial.h>
#include <saki/math/isnan.h>
#include <saki/math/details/pow_n.h>

namespace saki
{
	/**
	* @brief �R���p�C����exp
	*/
	template<typename T,
		typename std::enable_if_t<std::is_floating_point_v<T>, std::nullptr_t> = nullptr>
		constexpr T exp(T x)
	{
		if (saki::isnan(x) || x == std::numeric_limits<T>::infinity())return x;
		if (x == -std::numeric_limits<T>::infinity())return 0;
		if (x == 0)return static_cast<T>(1);

		T sum = 0;
		size_t n = 0;
		while (n <= saki::factorial_limits<T>::limit)
		{
			sum += saki::details::pow_n(x, n) / saki::factorial<T>(n);
			++n;
		}
		return sum;
	}
	/**
	* @brief ������int�^�̏ꍇ�ɁA�߂�l��double�^�ɂ��邽�߂̂���
	*/
	template<typename T,
		typename std::enable_if_t<std::is_integral_v<T>, std::nullptr_t> = nullptr>
		constexpr double exp(T x)
	{
		return saki::exp(static_cast<double>(x));
	}
}
#endif //SAKI_EXP_2019_01_06
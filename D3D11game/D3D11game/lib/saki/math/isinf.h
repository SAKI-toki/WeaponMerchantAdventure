/**
* @file isinf.h
* @brief コンパイル時isinf
* @author 石山 悠
* @date 2019/01/08
*/
#pragma once
#ifndef SAKI_ISINF_2019_01_08
#define SAKI_ISINF_2019_01_08
#include <limits>
#include <type_traits>

namespace saki
{
	/**
	* @brief コンパイル時isinf
	*/
	template<typename T,
		typename std::enable_if_t<std::is_floating_point_v<T>, std::nullptr_t> = nullptr>
	constexpr bool isinf(T x)
	{
		return x == std::numeric_limits<T>::infinity() ||
			x == -std::numeric_limits<T>::infinity();
	}
	/**
	* @brief コンパイル時isinf
	* @details integralの場合は必ずfalse
	*/
	template<typename T,
		typename std::enable_if_t<std::is_integral_v<T>, std::nullptr_t> = nullptr>
		constexpr bool isinf(T x)
	{
		return false;
	}
}
#endif //SAKI_ISINF_2019_01_08
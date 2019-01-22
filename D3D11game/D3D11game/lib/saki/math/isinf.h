/**
* @file isinf.h
* @brief �R���p�C����isinf
* @author �ΎR �I
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
	* @brief �R���p�C����isinf
	*/
	template<typename T,
		typename std::enable_if_t<std::is_floating_point_v<T>, std::nullptr_t> = nullptr>
	constexpr bool isinf(T x)
	{
		return x == std::numeric_limits<T>::infinity() ||
			x == -std::numeric_limits<T>::infinity();
	}
	/**
	* @brief �R���p�C����isinf
	* @details integral�̏ꍇ�͕K��false
	*/
	template<typename T,
		typename std::enable_if_t<std::is_integral_v<T>, std::nullptr_t> = nullptr>
		constexpr bool isinf(T x)
	{
		return false;
	}
}
#endif //SAKI_ISINF_2019_01_08
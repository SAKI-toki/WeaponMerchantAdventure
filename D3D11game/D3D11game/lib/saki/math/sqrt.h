/**
* @file sqrt.h
* @brief �R���p�C����������
* @author �ΎR �I
* @date 2018/11/21
*/
#pragma once
#ifndef SAKI_SQRT_2018_11_21
#define SAKI_SQRT_2018_11_21
#include <limits>
#include <type_traits>
#include <saki/math/isnan.h>
#include <saki/math/isinf.h>

namespace saki
{
	/**
	* @brief �R���p�C����������
	* @param x �����������߂�l
	* @details �A���S���Y���̓o�r���j�A�̕������𗘗p
	*/
	template<typename T,
		typename std::enable_if_t<std::is_floating_point_v<T>, std::nullptr_t> = nullptr>
	constexpr T sqrt(T x)
	{
		if (saki::isnan(x) ||
			x == std::numeric_limits<T>::infinity() ||
			x == 0)return x;
		if (x < 0)return -std::numeric_limits<T>::quiet_NaN();

		T prev = static_cast<T>(x / 2.0);
		T next = static_cast<T>((prev + x / prev) * 0.5);
		while (!saki::isnan(prev) && !saki::isinf(prev) && prev != next)
		{
			prev = next;
			next = static_cast<T>((prev + x / prev) * 0.5);
		}
		return prev;
	}
	/**
	* @brief ������int�^�̏ꍇ�ɁA�߂�l��double�^�ɂ��邽�߂̂���
	*/
	template<typename T,
		typename std::enable_if_t<std::is_integral_v<T>, std::nullptr_t> = nullptr>
		constexpr double sqrt(T x)
	{
		return saki::sqrt(static_cast<double>(x));
	}
}
#endif //SAKI_SQRT_2018_11_21
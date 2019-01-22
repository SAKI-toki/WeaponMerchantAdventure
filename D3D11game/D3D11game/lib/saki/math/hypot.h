/**
* @file hypot.h
* @brief �R���p�C����hypot
* @author �ΎR �I
* @date 2019/01/08
*/
#pragma once
#ifndef SAKI_HYPOT_2019_01_08
#define SAKI_HYPOT_2019_01_08
#include <limits>
#include <type_traits>
#include <saki/math/isnan.h>
#include <saki/math/sqrt.h>
#include <saki/math/abs.h>
#include <saki/math/isinf.h>

namespace saki
{
	///------2����--------
	/**
	* @brief �R���p�C�����ݏ�
	*/
	template<typename T,
		typename std::enable_if_t<std::is_floating_point_v<T>, std::nullptr_t> = nullptr>
		constexpr T hypot(T x, T y)
	{
		if (saki::isinf(x) || saki::isinf(y))return std::numeric_limits<T>::infinity();
		if (saki::isnan(x))return x;
		if (saki::isnan(y))return y;

		if (x == 0)
		{
			if (y == 0)
			{
				//x==0&&y==0
				return 0;
			}
			else
			{
				//y==0
				return saki::abs(y);
			}
		}
		else if (y == 0)
		{
			//x==0
			return saki::abs(x);
		}
		return saki::sqrt(x * x + y * y);
	}
	/**
	* @brief �^���Ⴄ�ꍇ�͂��낦��
	*/
	template<typename T1, typename T2>
	constexpr double hypot(T1 x, T2 y)
	{
		return saki::hypot(static_cast<double>(x), static_cast<double>(y));
	}

	///------3����--------

	/**
	* @brief �R���p�C�����ݏ�
	*/
	template<typename T,
		typename std::enable_if_t<std::is_floating_point_v<T>, std::nullptr_t> = nullptr>
		constexpr T hypot(T x, T y, T z)
	{
		if (saki::isinf(x) || saki::isinf(y) || saki::isinf(z))return std::numeric_limits<T>::infinity();
		if (saki::isnan(x))return x;
		if (saki::isnan(y))return y;
		if (saki::isnan(z))return z;


		if (x == 0)
		{
			if (y == 0)
			{
				if (z == 0)
				{
					//x==0&&y==0&&z==0
					return 0;
				}
			}
			else if (z == 0)
			{
				//x==0&&z==0
				return saki::abs(y);
			}
			else
			{
				//x==0
				return saki::sqrt(y * y + z * z);
			}
		}
		else if (y == 0)
		{
			if (z == 0)
			{
				//y==0&&z==0
				return saki::abs(x);
			}
			else
			{
				//y==0
				return saki::sqrt(x * x + z * z);
			}
		}
		else if (z == 0)
		{
			//z==0
			return saki::sqrt(x * x + y * y);
		}
		return saki::sqrt(x * x + y * y + z * z);
	}
	/**
	*@brief �^���Ⴄ�ꍇ�͂��낦��
	*/
	template<typename T1, typename T2, typename T3>
	constexpr double hypot(T1 x, T2 y, T3 z)
	{
		return saki::hypot(static_cast<double>(x), static_cast<double>(y), static_cast<double>(z));
	}
}
#endif //SAKI_HYPOT_2019_01_08
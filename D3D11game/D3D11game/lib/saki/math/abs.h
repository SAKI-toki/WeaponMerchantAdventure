/**
* @file abs.h
* @brief コンパイル時絶対値
* @author 石山 悠
* @date 2018/11/21
*/
#pragma once
#ifndef SAKI_ABS_2018_11_21
#define SAKI_ABS_2018_11_21
#include <limits>
#include <saki/math/isnan.h>

namespace saki
{
	/**
	* @brief コンパイル時絶対値
	* @param x 絶対値を求める値
	*/
	template<typename T>
	constexpr T abs(T x)
	{
		if (saki::isnan(x))return x;
		return x < 0 ? -x : x;
	}
}
#endif //SAKI_ABS_2018_11_21
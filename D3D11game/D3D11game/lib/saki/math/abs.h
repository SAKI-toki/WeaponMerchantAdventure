/**
* @file abs.h
* @brief �R���p�C������Βl
* @author �ΎR �I
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
	* @brief �R���p�C������Βl
	* @param x ��Βl�����߂�l
	*/
	template<typename T>
	constexpr T abs(T x)
	{
		if (saki::isnan(x))return x;
		return x < 0 ? -x : x;
	}
}
#endif //SAKI_ABS_2018_11_21
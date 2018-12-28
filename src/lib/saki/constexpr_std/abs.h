/**
* @file abs.h
* @brief �R���p�C������Βl
* @author �ΎR �I
* @date 2018/11/21
*/
#pragma once
#ifndef SAKI_ABS_2018_11_21
#define SAKI_ABS_2018_11_21

namespace saki
{
	/**
	* @brief �R���p�C������Βl
	* @param n ��Βl�����߂�l
	*/
	template<typename T>
	constexpr T abs(T n)
	{
		return n < 0 ? -n : n;
	}
}
#endif //SAKI_ABS_2018_11_21
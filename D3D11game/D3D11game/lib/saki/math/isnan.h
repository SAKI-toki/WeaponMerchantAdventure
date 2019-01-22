/**
* @file isnan.h
* @brief Not a Number���ǂ������肷��֐�
* @author �ΎR �I
* @date 2019/01/02
*/
#pragma once
#ifndef SAKI_ISNAN_2019_01_02
#define SAKI_ISNAN_2019_01_02

namespace saki
{
	/**
	* @brief Not a Number���ǂ�������
	* @param x ���肷��l
	* @return NaN���ǂ���
	*/
	template<typename T>
	constexpr bool isnan(T x)
	{
		return !(x == x);
	}
}
#endif //SAKI_ISNAN_2019_01_02
/**
* @file sqrt.h
* @brief �R���p�C����������
* @author �ΎR �I
* @date 2018/11/21
*/
#pragma once
#ifndef SAKI_SQRT_2018_11_21
#define SAKI_SQRT_2018_11_21
#include <cmath> //for nan
namespace saki
{
	/**
	* @brief �R���p�C����������
	* @param n �����������߂�l
	* @details �A���S���Y���̓o�r���j�A�̕������𗘗p
	*/
	template<typename T1 = double, typename T2 = double>
	constexpr T1 sqrt(const T2& n)
	{
		//0���Z�╉���̌v�Z�����Ȃ��悤�ɂ���
		if (n == 0)return 0;
		if (n < 0)return -nan("ind");
		T1 prev = n / 2;
		T1 next = (prev + n / prev) * 0.5;
		while (prev != next)
		{
			prev = next;
			next = (prev + n / prev) * 0.5;
		}
		return prev;
	}
}
#endif //SAKI_SQRT_2018_11_21
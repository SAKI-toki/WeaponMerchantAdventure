/**
* @file factorial.h
* @brief �K��
* @author �ΎR �I
* @date 2018/11/22
*/
#pragma once
#ifndef SAKI_FACTORIAL_2018_11_22
#define SAKI_FACTORIAL_2018_11_22

namespace saki
{
	/**
	* @brief �K��(�����o�[�W����)
	* @param N 1����N�܂ł̊K������߂�
	* @details �����ɒl�����邽�߁A���s���̒l�ł��g�p�ł���
	*/
	template<typename T = unsigned long long>
	constexpr T factorial(unsigned int N)
	{
		return N * ((N > 1) ? factorial<T>(N - 1) : 1);
	}
	/**
	* @brief �K��(�������o�[�W����)
	* @details �������ɒl�����邽�߁A���s���̒l�͎g�p�ł��Ȃ�
	*/
	template<unsigned int N, typename T = unsigned long long>
	constexpr T factorial()
	{
		if constexpr (N > 1)
		{
			return N * factorial<N - 1, T>();
		}
		else
		{
			return N;
		}
	}
}
#endif //SAKI_FACTORIAL_2018_11_22
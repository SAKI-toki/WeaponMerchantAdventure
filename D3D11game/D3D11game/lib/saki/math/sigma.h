/**
* @file sigma.h
* @brief ���w�̃V�O�}(��)
* @author �ΎR �I
* @date 2018/12/10
*/
#pragma once
#ifndef SAKI_SIGMA_2018_12_10
#define SAKI_SIGMA_2018_12_10
#include <saki/binary_operator/return_param.h>

namespace saki
{
	/**
	* @brief ���w�̃V�O�}���ȒP�Ɏ���
	* @param start �����l
	* @param end �J��Ԃ��̏I���(���̒l���g�p������I��)
	* @param f �֐�
	* @return �v�Z����
	* @details start>end�̏ꍇ�A0���Ԃ�
	*/
	template<typename T = int, typename Func = saki::ReturnParam>
	constexpr T sigma(T start, const T& end, Func&& f = Func())
	{
		T sum = 0;
		for (; start <= end; ++start)
		{
			sum += f(start);
		}
		return sum;
	}
}
#endif //SAKI_SIGMA_2018_12_10
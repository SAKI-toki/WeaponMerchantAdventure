/**
* @file return_param.h
* @brief ���̂܂܈����̒l��Ԃ�
* @author �ΎR �I
* @date 2018/12/10
*/
#pragma once
#ifndef SAKI_RETURN_PARAM_2018_12_10
#define SAKI_RETURN_PARAM_2018_12_10

namespace saki
{
	/**
	* @brief ���̂܂܈�����Ԃ��֐��I�u�W�F�N�g
	*/
	struct ReturnParam
	{
		template<typename T>
		constexpr T operator()(const T& t)const
		{
			return t;
		}
	};
}
#endif //SAKI_RETURN_PARAM_2018_12_10
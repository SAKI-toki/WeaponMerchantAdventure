/**
* @file accumulate.h
* @brief ������accumulate�֐��̊ȗ���
* @author �ΎR �I
* @date 2018/12/06
*/
/*
�S�Ă̗v�f�����v�i���͎w�肵�����Z�q�j���R���e�i�N���X�Ə����l��n�������ŉ\�ɂ���
�W�����C�u�����ł�Iterator��n���̂ŁA�S�ĂȂ炱�������g�����ق����ǂ�
*/
#pragma once
#ifndef SAKI_ACCUMULATE_2018_12_06
#define SAKI_ACCUMULATE_2018_12_06
#include <type_traits> //for remove_reference_t
namespace saki
{
	/**
	* @brief �S�Ă̒l�̍��v
	* @param con �R���e�i�N���X
	* @param init �����l
	* @return ���v��Ԃ�
	*/
	template<typename Container>
	auto accumulate(Container&& con, typename std::remove_reference_t<Container>::value_type init = 0)
	{
		for (auto&& n : con)
		{
			init = init + n;
		}
		return init;
	}
	/**
	* @brief ������2�̊֐����w�肵�A��������ׂĂ̗v�f�ŉ�
	* @param con �R���e�i�N���X
	* @param init �����l
	* @param binary_op ������2�̊֐�
	* @return �S�Ă̗v�f���񂵂�����
	*/
	template<typename Container, typename BinaryOperation>
	auto accumulate(Container&& con, BinaryOperation&& binary_op, 
		typename std::remove_reference_t<Container>::value_type init = 0)
	{
		for (auto&& n : con)
		{
			init = binary_op(init, n);
		}
		return init;
	}

}
#endif //SAKI_ACCUMULATE_2018_12_06
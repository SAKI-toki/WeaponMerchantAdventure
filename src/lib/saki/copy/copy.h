/**
* @file copy.h
* @brief ������copy�֐��̊ȗ���
* @author �ΎR �I
* @date 2018/12/09
*/
#pragma once
#ifndef SAKI_COPY_2018_12_09
#define SAKI_COPY_2018_12_09
#include <iterator>
#include <saki/meta/can_begin_method.h>

namespace saki
{
	/**
	* @brief �R���e�i�ƃR���e�i��n��copy
	* @param con1 �R�s�[����R���e�i�N���X
	* @param con2 �y�[�X�g����R���e�i�N���X
	*/
	template <typename Container1, typename Container2, typename std::enable_if_t<can_begin_v<Container2>, std::nullptr_t> = nullptr>
	auto copy(Container1&& con1, Container2&& con2)
	{
		auto con1itr = std::begin(con1);
		auto con1end = std::end(con1);
		auto con2itr = std::begin(con2);
		while (con1itr != con1end)
		{
			*(con2itr++) = *(con1itr++);
		}
		return con2itr;
	}
	/**
	* @brief �R���e�i�ƃR���e�i��n��copy
	* @param con �R�s�[����R���e�i�N���X
	* @param outitr �y�[�X�g����R���e�i�N���X�̍ŏ��̃C�e���[�^�[
	*/
	template <typename Container, typename OutItr, typename std::enable_if_t<!can_begin_v<OutItr>, std::nullptr_t> = nullptr>
	auto copy(Container&& con, OutItr outitr)
	{
		auto conitr = std::begin(con);
		auto conend = std::end(con);
		while (conitr != conend)
		{
			*(outitr++) = *(conitr++);
		}
		return outitr;
	}
}
#endif //SAKI_COPY_2018_12_09
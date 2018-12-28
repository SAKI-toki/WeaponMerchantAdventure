/**
* @file split.h
* @brief ������̕���
* @author �ΎR �I
* @date 2018/12/14
*/
#pragma once
#ifndef SAKI_SPLIT_2018_12_14
#define SAKI_SPLIT_2018_12_14
#include <string>
#include <sstream>
#include <vector>

namespace saki
{
	/**
	* @brief string�^����؂������̂�vector�ŕԂ�
	* @param str ��؂�Ώۂ̕�����
	* @param separation ��؂蕶��
	* @return ��؂�����������i�[����vector�N���X
	*/
	std::vector<std::string> split(std::string str, const char separation)
	{
		//��؂�����������i�[
		std::vector<std::string> str_list;
		std::stringstream ss(str);
		std::string buffer;
		//�p�X��/���Ƃɋ�؂�
		while (std::getline(ss, buffer, '/'))
		{
			str_list.push_back(buffer);
		}
		return str_list;
	}
}
#endif //SAKI_SPLIT_2018_12_14
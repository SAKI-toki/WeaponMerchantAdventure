/**
* @file pi.h
* @brief �~�����̃e���v���[�g�ϐ�
* @author �ΎR �I
* @date 2018/10/15
*/
#pragma once
#ifndef SAKI_PI_2018_10_15
#define SAKI_PI_2018_10_15
namespace saki
{
	/**
	* @brief �~�����̃e���v���[�g�ϐ�
	*/
	template<typename T>
	static constexpr auto PI =
		static_cast<T>(3.14159265358979323846);
	/**
	* @brief �~������1/2�̃e���v���[�g�ϐ�
	*/
	template<typename T>
	static constexpr auto PI_HALF = PI<T> / 2;
	/**
	* @brief �~������1/4�̃e���v���[�g�ϐ�
	*/
	template<typename T>
	static constexpr auto PI_QUARTER = PI<T> / 4;
}
#endif //SAKI_PI_2018_10_15
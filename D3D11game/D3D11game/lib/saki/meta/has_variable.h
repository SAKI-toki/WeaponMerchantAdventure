/**
* @file has_variable.h
* @brief �w�肵���^������̕ϐ��������Ă��邩�ǂ������肷�郁�^�֐�
* @author �ΎR �I
* @date 2018/12/29
*/
#pragma once
#ifndef SAKI_HAS_CHECK_METHOD_2018_12_23
#define SAKI_HAS_CHECK_METHOD_2018_12_23
#include <type_traits>

namespace saki
{
	/**
	* @brief �ϐ�x�������Ă��邩�ǂ����𔻒肷��\����
	*/
	template<typename T>
	struct has_x
	{
	private:
		template<typename U>
		static constexpr std::true_type check_check(decltype(std::declval<U>().x))* u);
		template<typename U>
		static constexpr std::false_type check_check(...);
	public:
		static constexpr auto value = decltype(check_check<T>(nullptr))::value;
	};
	/**
	* @brief has_x���ȒP�ɌĂяo����ϐ�
	*/
	template<typename T>
	static constexpr auto has_x_v = saki::has_check<T>::value;
}
#endif //SAKI_HAS_CHECK_METHOD_2018_12_23
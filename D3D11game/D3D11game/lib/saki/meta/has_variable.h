/**
* @file has_variable.h
* @brief 指定した型が特定の変数を持っているかどうか判定するメタ関数
* @author 石山 悠
* @date 2018/12/29
*/
#pragma once
#ifndef SAKI_HAS_CHECK_METHOD_2018_12_23
#define SAKI_HAS_CHECK_METHOD_2018_12_23
#include <type_traits>

namespace saki
{
	/**
	* @brief 変数xを持っているかどうかを判定する構造体
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
	* @brief has_xを簡単に呼び出せる変数
	*/
	template<typename T>
	static constexpr auto has_x_v = saki::has_check<T>::value;
}
#endif //SAKI_HAS_CHECK_METHOD_2018_12_23
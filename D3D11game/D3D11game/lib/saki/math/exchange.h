/**
* @file exchange.h
* @brief コンパイル時exchange
* @author 石山 悠
* @date 2018/11/21
*/
#pragma once
#ifndef SAKI_EXCHANGE_2018_11_21
#define SAKI_EXCHANGE_2018_11_21
#include <type_traits>

namespace saki
{
	/**
	* @brief コンパイル時exchange
	* @param obj 値を入れられる値
	* @param new_val 値に入れる値
	*/
	template<typename T, typename U = T>
	constexpr T exchange(T& obj, U&& new_val)
	{
		T t1 = std::move(obj);
		obj = std::forward<U>(new_val);
		return t1;
	}
}
#endif //SAKI_EXCHANGE_2018_11_21
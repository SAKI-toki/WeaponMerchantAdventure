/**
* @file abs.h
* @brief コンパイル時絶対値
* @author 石山 悠
* @date 2018/11/21
*/
#pragma once
#ifndef SAKI_ABS_2018_11_21
#define SAKI_ABS_2018_11_21

namespace saki
{
	/**
	* @brief コンパイル時絶対値
	* @param n 絶対値を求める値
	*/
	template<typename T>
	constexpr T abs(T n)
	{
		return n < 0 ? -n : n;
	}
}
#endif //SAKI_ABS_2018_11_21
/**
* @file sqrt.h
* @brief コンパイル時平方根
* @author 石山 悠
* @date 2018/11/21
*/
#pragma once
#ifndef SAKI_SQRT_2018_11_21
#define SAKI_SQRT_2018_11_21
#include <cmath> //for nan
namespace saki
{
	/**
	* @brief コンパイル時平方根
	* @param n 平方根を求める値
	* @details アルゴリズムはバビロニアの平方根を利用
	*/
	template<typename T1 = double, typename T2 = double>
	constexpr T1 sqrt(const T2& n)
	{
		//0除算や負数の計算をしないようにする
		if (n == 0)return 0;
		if (n < 0)return -nan("ind");
		T1 prev = n / 2;
		T1 next = (prev + n / prev) * 0.5;
		while (prev != next)
		{
			prev = next;
			next = (prev + n / prev) * 0.5;
		}
		return prev;
	}
}
#endif //SAKI_SQRT_2018_11_21
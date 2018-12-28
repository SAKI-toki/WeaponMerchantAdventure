/**
* @file sigma.h
* @brief 数学のシグマ(Σ)
* @author 石山 悠
* @date 2018/12/10
*/
#pragma once
#ifndef SAKI_SIGMA_2018_12_10
#define SAKI_SIGMA_2018_12_10
#include <saki/binary_operator/return_param.h>

namespace saki
{
	/**
	* @brief 数学のシグマを簡単に実装
	* @param start 初期値
	* @param end 繰り返しの終わり(この値を使用したら終了)
	* @param f 関数
	* @return 計算結果
	* @details start>endの場合、0が返る
	*/
	template<typename T = int, typename Func = saki::ReturnParam>
	constexpr T sigma(T start, const T& end, Func&& f = Func())
	{
		T sum = 0;
		for (; start <= end; ++start)
		{
			sum += f(start);
		}
		return sum;
	}
}
#endif //SAKI_SIGMA_2018_12_10
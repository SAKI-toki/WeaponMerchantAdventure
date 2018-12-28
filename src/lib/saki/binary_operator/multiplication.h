/**
* @file multiplication.h
* @brief 掛け算のオペレーターを呼び出すconstexpr関数オブジェクト
* @author 石山 悠
* @date 2018/12/08
*/
#pragma once
#ifndef SAKI_MULTIPLICATION_2018_12_08
#define SAKI_MULTIPLICATION_2018_12_08

namespace saki
{
	/**
	* @brief 掛け算のconstexpr対応した関数オブジェクト
	*/
	struct multiplication
	{
		template<typename T1, typename T2>
		constexpr auto operator()(const T1& t1, const T2& t2)const
		{
			return t1 * t2;
		}
	};
}
#endif //SAKI_MULTIPLICATION_2018_12_08
/**
* @file pi.h
* @brief 円周率のテンプレート変数
* @author 石山 悠
* @date 2018/10/15
*/
#pragma once
#ifndef SAKI_PI_2018_10_15
#define SAKI_PI_2018_10_15
namespace saki
{
	/**
	* @brief 円周率のテンプレート変数
	*/
	template<typename T>
	constexpr auto PI = static_cast<T>(3.14159265358979323846264338327950288);
}
#endif //SAKI_PI_2018_10_15
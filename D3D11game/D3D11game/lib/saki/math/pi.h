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
	static constexpr auto PI =
		static_cast<T>(3.14159265358979323846);
	/**
	* @brief 円周率の1/2のテンプレート変数
	*/
	template<typename T>
	static constexpr auto PI_HALF = PI<T> / 2;
	/**
	* @brief 円周率の1/4のテンプレート変数
	*/
	template<typename T>
	static constexpr auto PI_QUARTER = PI<T> / 4;
}
#endif //SAKI_PI_2018_10_15
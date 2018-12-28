/**
* @file distance.h
* @brief 2点間の距離を測る
* @author 石山 悠
* @date 2018/12/06
*/
#pragma once
#ifndef SAKI_DISTANCE_2018_12_06
#define SAKI_DISTANCE_2018_12_06
#include <saki/constexpr_std/sqrt.h>

namespace saki
{
	/**
	* @brief 二点間の距離(XY)
	* @details C++17現在、標準ライブラリのsqrtがconstexprではないので、自作sqrtを利用しconstexprに対応
	*/
	template<typename U = double, typename T1, typename T2>
	constexpr U distanceXY(const T1& v1, const T2& v2)
	{
		return saki::sqrt<U>(
			(v1.x - v2.x) * (v1.x - v2.x) +
			(v1.y - v2.y) * (v1.y - v2.y));
	}
	/**
	* @brief 二点間の距離(XZ)
	*/
	template<typename U = double, typename T1, typename T2>
	constexpr U distanceXZ(const T1& v1, const T2& v2)
	{
		return saki::sqrt<U>(
			(v1.x - v2.x) * (v1.x - v2.x) +
			(v1.z - v2.z) * (v1.z - v2.z));
	}
	/**
	* @brief 二点間の距離(YZ)
	*/
	template<typename U = double, typename T1, typename T2>
	constexpr U distanceYZ(const T1& v1, const T2& v2)
	{
		return saki::sqrt<U>(
			(v1.y - v2.y) * (v1.y - v2.y) +
			(v1.z - v2.z) * (v1.z - v2.z));
	}
	/**
	* @brief 二点間の距離(XYZ)
	*/
	template<typename U = double, typename T1, typename T2>
	constexpr U distanceXYZ(const T1& v1, const T2& v2)
	{
		return saki::sqrt<U>(
			(v1.x - v2.x) * (v1.x - v2.x) +
			(v1.y - v2.y) * (v1.y - v2.y) +
			(v1.z - v2.z) * (v1.z - v2.z));
	}
}
#endif //SAKI_DISTANCE_2018_12_06
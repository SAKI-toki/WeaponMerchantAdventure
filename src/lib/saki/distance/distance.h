/**
* @file distance.h
* @brief 2�_�Ԃ̋����𑪂�
* @author �ΎR �I
* @date 2018/12/06
*/
#pragma once
#ifndef SAKI_DISTANCE_2018_12_06
#define SAKI_DISTANCE_2018_12_06
#include <saki/constexpr_std/sqrt.h>

namespace saki
{
	/**
	* @brief ��_�Ԃ̋���(XY)
	* @details C++17���݁A�W�����C�u������sqrt��constexpr�ł͂Ȃ��̂ŁA����sqrt�𗘗p��constexpr�ɑΉ�
	*/
	template<typename U = double, typename T1, typename T2>
	constexpr U distanceXY(const T1& v1, const T2& v2)
	{
		return saki::sqrt<U>(
			(v1.x - v2.x) * (v1.x - v2.x) +
			(v1.y - v2.y) * (v1.y - v2.y));
	}
	/**
	* @brief ��_�Ԃ̋���(XZ)
	*/
	template<typename U = double, typename T1, typename T2>
	constexpr U distanceXZ(const T1& v1, const T2& v2)
	{
		return saki::sqrt<U>(
			(v1.x - v2.x) * (v1.x - v2.x) +
			(v1.z - v2.z) * (v1.z - v2.z));
	}
	/**
	* @brief ��_�Ԃ̋���(YZ)
	*/
	template<typename U = double, typename T1, typename T2>
	constexpr U distanceYZ(const T1& v1, const T2& v2)
	{
		return saki::sqrt<U>(
			(v1.y - v2.y) * (v1.y - v2.y) +
			(v1.z - v2.z) * (v1.z - v2.z));
	}
	/**
	* @brief ��_�Ԃ̋���(XYZ)
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
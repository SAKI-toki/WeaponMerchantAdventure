/**
* @file isnan.h
* @brief Not a Number‚©‚Ç‚¤‚©”»’è‚·‚éŠÖ”
* @author ÎR —I
* @date 2019/01/02
*/
#pragma once
#ifndef SAKI_ISNAN_2019_01_02
#define SAKI_ISNAN_2019_01_02

namespace saki
{
	/**
	* @brief Not a Number‚©‚Ç‚¤‚©”»’è
	* @param x ”»’è‚·‚é’l
	* @return NaN‚©‚Ç‚¤‚©
	*/
	template<typename T>
	constexpr bool isnan(T x)
	{
		return !(x == x);
	}
}
#endif //SAKI_ISNAN_2019_01_02
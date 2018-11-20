/**
* @file degree_radian_conversion.h
* @brief Šp“x‚Ì•ÏŠ·
* @author ÎR —I
* @date 2018/11/13
*/
#ifndef SAKI_DEGREE_RADIAN_CONVERSION_2018_11_13
#define SAKI_DEGREE_RADIAN_CONVERSION_2018_11_13
#include "../pi.h"
namespace saki
{
	/**
	* @brief Degree‚©‚çRadian‚É•ÏŠ·
	* @param deg Radian‚É•ÏŠ·‚·‚éDegree
	*/
	template<typename Rad, typename Deg>
	inline constexpr Rad to_radian(const Deg& deg)
	{
		return static_cast<Rad>(deg * 0.0174532925199389);
	}
	/**
	* @brief Radian‚©‚çDegree‚É•ÏŠ·
	* @param rad Degree‚É•ÏŠ·‚·‚éRadian
	*/
	template<typename Deg, typename Rad>
	inline constexpr Deg to_degree(const Rad& rad)
	{
		return static_cast<Deg>(rad * 57.29577951309679);
	}
}
#endif //SAKI_DEGREE_RADIAN_CONVERSION_2018_11_13
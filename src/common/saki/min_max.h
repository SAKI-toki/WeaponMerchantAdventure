/**
* @file min_max.h
* @brief å^Ç≤Ç∆ÇÃç≈è¨ílÇ∆ç≈ëÂílÇÃíËêîâª
* @author êŒéR óI
* @date 2018/11/12
*/
#ifndef SAKI_MIN_MAX_2018_11_12
#define SAKI_MIN_MAX_2018_11_12
#include "type_alias.h"
namespace
{
	constexpr saki_int8 SAKI_INT8_MIN = -127i8 - 1;
	constexpr saki_int8 SAKI_INT8_MAX = 127i8;

	constexpr saki_uint8 SAKI_UINT8_MIN = 0;
	constexpr saki_uint8 SAKI_UINT8_MAX = 0xffui8;

	constexpr saki_int16 SAKI_INT16_MIN = -32767i16 - 1;
	constexpr saki_int16 SAKI_INT16_MAX = 32767i16;

	constexpr saki_uint16 SAKI_UINT16_MIN = 0;
	constexpr saki_uint16 SAKI_UINT16_MAX = 0xffffui16;

	constexpr saki_int32 SAKI_INT32_MIN = -2147483647i32 - 1;
	constexpr saki_int32 SAKI_INT32_MAX = 2147483647i32;

	constexpr saki_uint32 SAKI_UINT32_MIN = 0;
	constexpr saki_uint32 SAKI_UINT32_MAX = 0xffffffffui32;

	constexpr saki_int64 SAKI_INT64_MIN = -9223372036854775807i64 - 1;
	constexpr saki_int64 SAKI_INT64_MAX = 9223372036854775807i64;

	constexpr saki_uint64 SAKI_UINT64_MIN = 0;
	constexpr saki_uint64 SAKI_UINT64_MAX = 0xffffffffffffffffui64;
}
#endif //SAKI_MIN_MAX_2018_11_12
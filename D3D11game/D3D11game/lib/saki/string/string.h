/**
* @file string.h
* @brief コンパイル時stringクラス
* @author 石山 悠
* @date 2019/01/09
*/
#pragma once
#ifndef SAKI_STRING_2019_01_09
#define SAKI_STRING_2019_01_09
#include <cstddef>
#include <saki/array/array.h>

namespace saki
{
	template<typename T, size_t N>
	class string_base
	{
		saki::array<T, N> str;
	public:
		string_base() :str() {}
		string_base(const saki::array<T, N>& arr) :str(arr) {}
	};
}
#endif //SAKI_STRING_2019_01_09
/**
* @file fibonacci.h
* @brief �t�B�{�i�b�`������o���֐�
* @author �ΎR �I
* @date 2018/12/28
*/
#pragma once
#ifndef SAKI_FIBONACCI_2018_12_28
#define SAKI_FIBONACCI_2018_12_28
#include <cstdint>
#include <cstddef>
#include <saki/math/exchange.h>

namespace saki
{
	/**
	* @brief �t�B�{�i�b�`��������߂�֐�
	*/
	template<size_t N, typename T = double>
	constexpr T fibonacci()
	{
		return saki::fibonacci<T>(N);
	}

	/**
	* @brief �t�B�{�i�b�`���񋁂߂�֐�
	* @param N ���߂����ԍ�
	*/
	template<typename T = double>
	constexpr T fibonacci(size_t N)
	{
		T prev1 = 1;
		T prev2 = 1;
		for (size_t i = 3; i <= N; ++i)
		{
			prev2 = saki::exchange(prev1, prev1 + prev2);
		}
		return prev1;
	}
}
#endif //SAKI_FIBONACCI_2018_12_28
/**
* @file random.h
* @brief 決められた範囲でランダムな値を取得する
* @author 石山 悠
* @date 2018/10/31
*/
/*
決められた範囲でランダムな値を取得する関数です
イメージとしてはUnityのRandom.Range(0,10)のような感じです
*/
#ifndef SAKI_RANDOM_2018_10_31
#define SAKI_RANDOM_2018_10_31
#include <random>
#include <assert.h>	//for assert
namespace saki
{
	/**
	* @brief 最小値と最大値を引数にとり、その間からランダムな値を返す
	* @param min 最小値
	* @param max 最大値
	* @details 最大値を含むランダムな値を返す、C++17環境以降での使用のみ可
	*/
	template<typename T>
	T random(const T min, const T max)
	{
		assert(min <= max);
		std::random_device rd;
		std::mt19937 mt(rd());
		if constexpr (std::is_integral_v<T>)
		{
			std::uniform_int_distribution<int> rnd(min, max);
			return rnd(mt);
		}
		else
		{
			std::uniform_real_distribution<T> rnd(min, max);
			return rnd(mt);
		}
	}

	/**
	* @brief int型は特殊化する
	* @param min 最小値
	* @param max 最大値
	* @details 最大値を含むランダムな値を返す
	*/
	/*template<>
	int random<int>(const int min, const int max)
	{

		std::random_device rd;
		std::mt19937 mt(rd());
		std::uniform_int_distribution<int> rnd(min, max);

		return rnd(mt);
	}*/
}
#endif //SAKI_RANDOM_2018_10_31
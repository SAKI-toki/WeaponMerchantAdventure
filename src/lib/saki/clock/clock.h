/**
* @file clock.h
* @brief 時間を測るクラス
* @author 石山 悠
* @date 2018/12/04
*/
#pragma once
#ifndef SAKI_CLOCK_2018_12_04
#define SAKI_CLOCK_2018_12_04
#include <saki/singleton/singleton.h>
#include <ctime>
namespace saki
{
	/**
	* @brief 時間を測るクラス
	*/
	class Clock :public saki::Singleton<Clock>
	{
		clock_t start_time;//開始時間
	public:
		/**
		* @brief コンストラクタ
		*/
		Clock() :start_time(clock()) {}
		/**
		* @brief 開始時間のセット
		*/
		void start()
		{
			start_time = clock();
		}
		/**
		* @brief 開始時間をセットしてからの時間を返す
		* @param ms trueならミリ秒,falseなら秒で返す
		* return 時間
		*/
		template<typename T = double>
		T end(bool ms = true)
		{
			clock_t end_time = clock();
			return static_cast<T>(static_cast<double>(end_time - start_time) / ((ms) ? 1 : (CLOCKS_PER_SEC)));
		}
		/**
		* @brief 開始時間をセットしてからの時間を返し、そこからまた時間をスタートする
		* @param ms trueならミリ秒,falseなら秒で返す
		* return 時間
		*/
		template<typename T = double>
		T end_and_start(bool ms = true)
		{
			auto end_time = end<T>(ms);
			start();
			return end_time;
		}
	};
}
#endif //SAKI_CLOCK_2018_12_04
/**
* @file iota.h
* @brief 既存のiota関数の簡略化＋拡張
* @author 石山 悠
* @date 2018/12/06
*/
/*
配列の中身全てに連番をつける場合はイテレーターを渡さず、コンテナクラスをそのまま渡すだけでよい
さらに最初の値の設定や、いくつおきに値を格納するかを決めることができる
*/
#pragma once
#ifndef SAKI_IOTA_2018_12_06
#define SAKI_IOTA_2018_12_06
#include <type_traits> //for remove_reference_t
namespace saki
{
	/**
	* @brief 全ての値に連番をつける
	* @param con コンテナクラス
	* @param init 最初の値
	* @param interval いくつおきに値を格納させるか
	*/
	template<typename Container>
	void iota(Container&& con, typename std::remove_reference_t<Container>::value_type init = 0, typename std::remove_reference_t<Container>::value_type interval = 1)
	{
		for (auto&& n : con)
		{
			n = init;
			init = init + interval;
		}
	}

	/**
	* @brief 決まった範囲に連番をつける
	* @param start スタートのイテレーター
	* @param end 終わりのイテレーター
	* @param init 最初の値
	* @param interval いくつおきに値を格納させるか
	*/
	template<typename Iterator>
	void iota(Iterator start, const Iterator& end, typename std::remove_reference_t<Iterator>::value_type init = 0, typename std::remove_reference_t<Iterator>::value_type interval = 1)
	{
		for (; start != end; ++start)
		{
			*start = init;
			init = init + interval;
		}
	}
}
#endif //SAKI_IOTA_2018_12_06
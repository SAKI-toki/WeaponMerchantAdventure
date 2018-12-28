/**
* @file for_each.h
* @brief 既存のfor_each関数の簡略化＋拡張
* @author 石山 悠
* @date 2018/12/06
*/
/*
全ての要素に関数を適用するときにコンテナクラスと関数を渡すだけで可能にした
さらに、拡張機能として、引数2以降に任意の値を入れて実行することができるようにした
標準ライブラリではIteratorを渡すので、全てならこっちを使ったほうが良い
*/
#pragma once
#ifndef SAKI_FOR_EACH_2018_12_06
#define SAKI_FOR_EACH_2018_12_06
namespace saki
{
	/**
	* @brief 関数をすべての要素で実行する
	* @param con コンテナクラス
	* @param f 実行する関数
	* @param args 実行する関数の引数２以降に入れる値
	*/
	template<typename Container, typename Func, typename ...Args>
	Func for_each(Container&& con, Func&& f, Args ...args)
	{
		for (auto&& n : con)
		{
			f(n, args...);
		}
		return f;
	}
}

#endif //SAKI_FOR_EACH_2018_12_06
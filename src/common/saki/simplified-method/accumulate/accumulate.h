/**
* @file accumulate.h
* @brief 既存のaccumulate関数の簡略化
* @author 石山 悠
* @date 2018/10/07
*/
/*
全ての要素を合計（又は指定した演算子）をコンテナクラスと初期値を渡すだけで可能にした
標準ライブラリではIteratorを渡すので、全てならこっちを使ったほうが良い
*/
#ifndef SAKI_ACCUMULATE_2018_10_07
#define SAKI_ACCUMULATE_2018_10_07
namespace saki
{
	/**
	* @brief			全ての値の合計
	* @param con		コンテナクラス
	* @param init		初期値
	* @return			合計を返す
	*/
	template<typename Container, typename T>
	T accumulate(const Container& con, T init)
	{
		for (const auto& n : con)
		{
			init = init + n;
		}
		return init;
	}
	/**
	* @brief			引数が2つの関数を指定し、それをすべての要素で回す
	* @param con		コンテナクラス
	* @param init		初期値
	* @param binary_op	引数が2つの関数
	* @return			全ての要素を回した結果
	* @details			注意：0除算に気を付けてください
	*/
	template<typename Container, typename T, typename BinaryOperation>
	T accumulate(const Container& con, T init, const  BinaryOperation& binary_op)
	{
		for (const auto& n : con)
		{
			init = binary_op(init, n);
		}
		return init;
	}

}
#endif //SAKI_ACCUMULATE_2018_10_07
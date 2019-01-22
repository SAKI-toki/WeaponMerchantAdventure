/**
* @file array.h
* @brief コンパイル時固定長配列クラス
* @author 石山 悠
* @date 2018/12/24
*/
#pragma once
#ifndef SAKI_ARRAY_2018_12_24
#define SAKI_ARRAY_2018_12_24
#include <cstddef>
#include <saki/macro/type_macro.h>
#include <saki/array/details/array_operator.h>

#include <saki/iterator/iterator.h>

namespace saki
{
	/**
	* @brief コンパイル時固定長配列クラス
	*/
	template<typename T, size_t Size>
	class Array
	{
	public:
		SAKI_TYPE_MACRO(T)
	private:
		value_type arr[Size]{};
	public:
		/**
		* @brief 引数なしコンストラクタ
		* @details 全て0で初期化
		*/
		constexpr Array()
		{}
		/**
		* @brief 配列の要素だけ値を受け取るコンストラクタ
		* @param u 配列の初期化値
		*/
		template<typename ...U>
		explicit constexpr Array(const U& ...u) :
			arr{ u... }
		{}
		//デフォルトを使用
		//デフォルトではメンバ変数のコピー、ムーブを行う
		Array(const Array<T, Size>&) = default;
		Array<T, Size>& operator=(const Array<T, Size>&) = default;
		Array(Array<T, Size>&&)noexcept = default;
		Array<T, Size>& operator=(Array<T, Size>&&)noexcept = default;
		/**
		* @brief []演算子
		*/
		constexpr reference operator[](size_t index)
		{
			return arr[index];
		}
		/**
		* @brief []演算子(constexpr)
		*/
		constexpr const_reference operator[](size_t index)const
		{
			return arr[index];
		}
		/**
		* @brief 配列の大きさを取得
		* @return 配列の大きさ
		*/
		constexpr size_type size()const
		{
			return Size;
		}
		constexpr saki::iterator<T> begin()
		{
			return saki::iterator<T>(arr);
		}
		constexpr saki::iterator<T> end()
		{
			return saki::iterator<T>(arr + Size);
		}
	};

	template<typename T>
	class Array<T, 0>
	{
	public:
		SAKI_TYPE_MACRO(T)
	public:
		/**
		* @brief 引数なしコンストラクタ
		*/
		constexpr Array()
		{}
	};
	/**
	* @brief 配列の連結
	* @param arr1,arr2 連結する配列
	* @return 連結した配列
	*/
	template<typename T, size_t Size1, size_t Size2>
	constexpr auto arraycat(const saki::Array<T, Size1>& arr1, const saki::Array<T, Size2>& arr2)
	{
		saki::Array<T, Size1 + Size2> arr{};
		size_t index = 0;
		for (size_t i = 0; i < arr1.size(); ++i)
		{
			arr[index++] = arr1[i];
		}
		for (size_t i = 0; i < arr2.size(); ++i)
		{
			arr[index++] = arr2[i];
		}
		return arr;
	}
}
#endif //SAKI_ARRAY_2018_12_24
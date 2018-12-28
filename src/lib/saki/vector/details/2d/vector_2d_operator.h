/**
* @file vector_2d_operator.h
* @brief Vector2クラスの演算子
* @author 石山 悠
* @date 2018/12/13
*/
#pragma once
#ifndef SAKI_VECTOR_2D_OPERATOR_2018_12_13
#define SAKI_VECTOR_2D_OPERATOR_2018_12_13
#include <saki/binary_operator/binary_operator.h>
#include <type_traits>

namespace saki
{
	//プロトタイプ宣言
	template<typename T>
	class Vector2;
	namespace details
	{
		/**
		* @brief ベクトル同士の演算
		*/
		template<typename T1, typename T2, typename Func>
		constexpr auto vector2_vector2_some_operator(const Vector2<T1>& v1, const Vector2<T2>& v2, Func&& f)
		{
			return Vector2<decltype(std::declval<T1>() + std::declval<T2>())>
			{ f(v1.x, v2.x), f(v1.y, v2.y) };
		}
		/**
		* @brief ベクトルとスカラの演算
		*/
		template<typename T1, typename T2, typename Func>
		constexpr auto vector2_scalar_some_operator(const Vector2<T1>& v, const T2& scalar, Func&& f)
		{
			return Vector2<decltype(std::declval<T1>() * std::declval<T2>())>
			{  f(v.x, scalar), f(v.y, scalar)  };
		}
	}
	/**
	* @brief +演算子
	*/
	template<typename T1, typename T2>
	constexpr auto operator+(const Vector2<T1>& v1, const Vector2<T2>& v2)
	{
		return details::vector2_vector2_some_operator(v1, v2, addition());
	}
	/**
	* @brief -演算子
	*/
	template<typename T1, typename T2>
	constexpr auto operator-(const Vector2<T1>& v1, const Vector2<T2>& v2)
	{
		return details::vector2_vector2_some_operator(v1, v2, subtraction());
	}
	/**
	* @brief *演算子(ベクトル*スカラ)
	*/
	template<typename T1, typename T2>
	constexpr auto operator*(const Vector2<T1>& v, const T2& scalar)
	{
		return details::vector2_scalar_some_operator(v, scalar, multiplication());
	}
	/**
	* @brief *演算子(スカラ*ベクトル)
	*/
	template<typename T1, typename T2>
	constexpr auto operator*(const T1& scalar, const Vector2<T2>& v)
	{
		return v * scalar;
	}
	/**
	* @brief *演算子(ベクトル)
	*/
	template<typename T1, typename T2>
	constexpr auto operator*(const Vector2<T1>& v1, const Vector2<T2>& v2)
	{
		return details::vector2_vector2_some_operator(v1, v2, multiplication());
	}
	/**
	* @brief /演算子(スカラ)
	*/
	template<typename T1, typename T2>
	constexpr auto operator/(const Vector2<T1>& v, const T2& scalar)
	{
		return details::vector2_scalar_some_operator(v, scalar, division());
	}
	/**
	* @brief /演算子(ベクトル)
	*/
	template<typename T1, typename T2>
	constexpr auto operator/(const Vector2<T1>& v1, const Vector2<T2>& v2)
	{
		return details::vector2_vector2_some_operator(v1, v2, division());
	}
	/**
	* @brief ==演算子
	*/
	template<typename T>
	constexpr bool operator==(const Vector2<T>& v1, const Vector2<T>& v2)
	{
		return v1.x == v2.x && v1.y == v2.y;
	}
	/**
	* @brief !=演算子
	*/
	template<typename T>
	constexpr bool operator!=(const Vector2<T>& v1, const Vector2<T>& v2)
	{
		return !(v1 == v2);
	}
	/**
	* @brief ==演算子(型不一致)
	* @details この関数の使用は推奨しない
	*/
	template<typename T1, typename T2>[[deprecated("type_mismatch")]]
		constexpr bool operator==(const Vector2<T1>& v1, const Vector2<T2>& v2)
	{
		return v1.x == v2.x && v1.y == v2.y;
	}
	/**
	* @brief !=演算子(型不一致)
	* @details この関数の使用は推奨しない
	*/
	template<typename T1, typename T2>[[deprecated("type_mismatch")]]
		constexpr bool operator!=(const Vector2<T1>& v1, const Vector2<T2>& v2)
	{
		return !(v1 == v2);
	}
}
#endif //SAKI_VECTOR_2D_OPERATOR_2018_12_13
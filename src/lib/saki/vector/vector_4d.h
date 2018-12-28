/**
* @file vector_4d.h
* @brief 4次元でのベクトル
* @author 石山 悠
* @date 2018/12/13
*/
#pragma once
#ifndef SAKI_VECTOR_4D_2018_12_13
#define SAKI_VECTOR_4D_2018_12_13
#include <limits> //for numeric_limits
#include <saki/constexpr_std/sqrt.h> //for constexpr_sqrt
#include <saki/vector/details/4d/vector_4d_operator.h>
#include <saki/macro/type_macro.h>

namespace saki
{
	/**
	* @brief 4次元でのベクトル
	*/
	template<typename T>
	class Vector4
	{
	public:
		SAKI_TYPE_MACRO(T)
	public:
		T x, y, z, w;
		/**
		* @brief 引数なしコンストラクタ
		* @details 全て0で初期化
		*/
		constexpr Vector4() :
			x(T()), y(T()), z(T()), w(T())
		{}
		/**
		* @brief 引数ありコンストラクタ
		* @param _x xの初期値
		* @param _y yの初期値
		* @param _z zの初期値
		* @param _w wの初期値
		*/
		constexpr Vector4(const T& _x, const T& _y, const T& _z, const T& _w) :
			x(_x), y(_y), z(_z), w(_w)
		{}
		/**
		* @brief 生配列からの初期化
		* @param pointer 配列のポインタ
		*/
		explicit constexpr Vector4(const T* const pointer) :
			x(*pointer), y(*(pointer + 1)), z(*(pointer + 2)), w(*(pointer + 3))
		{}
		//デフォルトを使用
		//デフォルトではメンバ変数のコピー、ムーブを行う
		Vector4(const Vector4<T>&) = default;
		Vector4<T>& operator=(const Vector4<T>&) = default;
		Vector4(Vector4<T>&&)noexcept = default;
		Vector4& operator=(Vector4<T>&&)noexcept = default;
		/**
		* @brief +=演算子
		*/
		template<typename U = T>
		auto operator+=(const Vector4<U>& other)
		{
			*this = *this + other;
			return *this;
		}
		/**
		* @brief -=演算子
		*/
		template<typename U = T>
		auto operator-=(const Vector4<U>& other)
		{
			*this = *this - other;
			return *this;
		}
		/**
		* @brief *=演算子(スカラ)
		*/
		template<typename U = T>
		auto operator*=(const U& scalar)
		{
			*this = *this * scalar;
			return *this;
		}
		/**
		* @brief *=演算子(ベクトル)
		*/
		template<typename U = T>
		auto operator*=(const Vector4<U>& other)
		{
			*this = *this * other;
			return *this;
		}
		/**
		* @brief /=演算子(スカラ)
		*/
		template<typename U = T>
		auto operator/=(const U& scalar)
		{
			*this = *this / scalar;
			return *this;
		}
		/**
		* @brief /=演算子(ベクトル)
		*/
		template<typename U = T>
		auto operator/=(const Vector4<U>& other)
		{
			*this = *this / other;
			return *this;
		}
		/**
		* @brief 単項+演算子
		*/
		constexpr Vector4<T> operator+()const
		{
			return *this;
		}
		/**
		* @brief 単項-演算子
		*/
		constexpr Vector4<T> operator-()const
		{
			return Vector4<T>(this->x * (-1), this->y * (-1), this->z * (-1), this->w * (-1));
		}
		/**
		* @brief []演算子
		*/
		T& operator[](const unsigned int index)
		{
			return (index == 0) ? this->x : (index == 1) ? this->y : (index == 2) ? this->z : this->w;
		}
		/**
		* @brief []演算子(constexpr)
		*/
		constexpr T operator[](const unsigned int index)const
		{
			return (index == 0) ? this->x : (index == 1) ? this->y : (index == 2) ? this->z : this->w;
		}
		/**
		* @brief ++演算子(前置)
		*/
		Vector4<T>& operator++()
		{
			this->x += 1; this->y += 1; this->z += 1; this->w += 1;
			return *this;
		}
		/**
		* @brief ++演算子(後置)
		*/
		Vector4<T> operator++(int)
		{
			Vector4<T> temp = *this;
			this->x += 1; this->y += 1; this->z += 1; this->w += 1;
			return temp;
		}
		/**
		* @brief --演算子(前置)
		*/
		Vector4<T>& operator--()
		{
			this->x -= 1; this->y -= 1; this->z -= 1; this->w -= 1;
			return *this;
		}
		/**
		* @brief --演算子(後置)
		*/
		Vector4<T> operator--(int)
		{
			Vector4<T> temp = *this;
			this->x -= 1; this->y -= 1; this->z -= 1; this->w -= 1;
			return temp;
		}
		/**
		* @brief 正規化
		* @details int型の場合、すべての要素が0で返ります
		*/
		void normalize()
		{
			//分母
			auto den = saki::sqrt(this->x * this->x + this->y * this->y + this->z * this->z + this->w * this->w);
			if (den == 0)
			{
				this->x = 0;
				this->y = 0;
				this->z = 0;
				this->w = 0;
			}
			else
			{
				this->x /= den;
				this->y /= den;
				this->z /= den;
				this->w /= den;
			}
		}
		/**
		* @brief 正規化
		* @return 正規化したもの
		* @details thisは正規化しない、int型の場合、すべての要素が0で帰ります
		*/
		template<typename U = double>
		constexpr Vector4<U> return_normalize()const
		{
			//分母
			auto den = saki::sqrt(this->x * this->x + this->y * this->y + this->z * this->z + this->w * this->w);
			if (den == 0)
			{
				return Vector4<U>
					(static_cast<U>(0),//x
						static_cast<U>(0),//y
						static_cast<U>(0),//z
						static_cast<U>(0));//w
			}
			else
			{
				return Vector4<U>
					(static_cast<U>(this->x / den),//x
						static_cast<U>(this->y / den),//y
						static_cast<U>(this->z / den),//z
						static_cast<U>(this->w / den));//w
			}
		}
	};

	/**
	* @brief Vector4のオールゼロ
	*/
	template<typename T>
	static constexpr Vector4<T> vector4_zero{ static_cast<T>(0), static_cast<T>(0), static_cast<T>(0),static_cast<T>(0) };
	/**
	* @brief Vector4のオールワン
	*/
	template<typename T>
	static constexpr Vector4<T> vector4_one{ static_cast<T>(1), static_cast<T>(1), static_cast<T>(1),static_cast<T>(1) };
	/**
	* @brief Vector4の最小値
	*/
	template<typename T>
	static constexpr Vector4<T> vector4_min{ std::numeric_limits<T>::min(), std::numeric_limits<T>::min(), std::numeric_limits<T>::min(), std::numeric_limits<T>::min() };
	/**
	* @brief Vector4の最大値
	*/
	template<typename T>
	static constexpr Vector4<T> vector4_max{ std::numeric_limits<T>::max(), std::numeric_limits<T>::max(), std::numeric_limits<T>::max(), std::numeric_limits<T>::max() };
	/**
	* @brief 内積
	*/
	template<typename U = double, typename T1, typename T2>
	constexpr U dot(const Vector4<T1>& v1, const Vector4<T2>& v2)
	{
		return static_cast<U>(v1.x * v2.x + v1.y * v2.y + v1.z * v2.z + v1.w * v2.w);
	}
	/**
	* @brief 線形補間
	* @details Quaternionは使用していません
	*/
	template<typename U = double, typename T1, typename T2, typename T = double>
	constexpr Vector4<U> lerp(const Vector4<T1>& v1, const Vector4<T2>& v2, const T& t, const T& base = 1)
	{
		auto ratio = t / base;
		return Vector4<U>(
			v1.x + (v2.x - v1.x) * ratio,
			v1.y + (v2.y - v1.y) * ratio,
			v1.z + (v2.z - v1.z) * ratio,
			v1.w + (v2.w - v1.w) * ratio);
	}
}

#endif //SAKI_VECTOR_4D_2018_12_13
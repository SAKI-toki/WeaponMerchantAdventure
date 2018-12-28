/**
* @file vector_3d.h
* @brief 3次元でのベクトル
* @author 石山 悠
* @date 2018/12/06
*/
#pragma once
#ifndef SAKI_VECTOR_3D_2018_12_06
#define SAKI_VECTOR_3D_2018_12_06
#include <limits> //for numeric_limits
#include <saki/constexpr_std/sqrt.h> //for constexpr_sqrt
#include <saki/vector/details/3d/vector_3d_operator.h>
#include <saki/macro/type_macro.h>

namespace saki
{
	/**
	* @brief 3次元でのベクトル
	*/
	template<typename T>
	class Vector3
	{
	public:
		SAKI_TYPE_MACRO(T)
	public:
		T x, y, z;
		/**
		* @brief 引数なしコンストラクタ
		* @details 全て0で初期化
		*/
		constexpr Vector3() :
			x(T()), y(T()), z(T())
		{}
		/**
		* @brief 引数ありコンストラクタ
		* @param _x xの初期値
		* @param _y yの初期値
		* @param _z zの初期値
		*/
		constexpr Vector3(const T& _x, const T& _y, const T& _z) :
			x(_x), y(_y), z(_z)
		{}
		/**
		* @brief 生配列からの初期化
		* @param pointer 配列のポインタ
		*/
		explicit constexpr Vector3(const T* const pointer) :
			x(*pointer), y(*(pointer + 1)), z(*(pointer + 2))
		{}
		//デフォルトを使用
		//デフォルトではメンバ変数のコピー、ムーブを行う
		Vector3(const Vector3<T>&) = default;
		Vector3<T>& operator=(const Vector3<T>&) = default;
		Vector3(Vector3<T>&&)noexcept = default;
		Vector3& operator=(Vector3<T>&&)noexcept = default;
		/**
		* @brief +=演算子
		*/
		template<typename U = T>
		auto operator+=(const Vector3<U>& other)
		{
			*this = *this + other;
			return *this;
		}
		/**
		* @brief -=演算子
		*/
		template<typename U = T>
		auto operator-=(const Vector3<U>& other)
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
		auto operator*=(const Vector3<U>& other)
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
		auto operator/=(const Vector3<U>& other)
		{
			*this = *this / other;
			return *this;
		}
		/**
		* @brief 単項+演算子
		*/
		constexpr Vector3<T> operator+()const
		{
			return *this;
		}
		/**
		* @brief 単項-演算子
		*/
		constexpr Vector3<T> operator-()const
		{
			return Vector3<T>(this->x * (-1), this->y * (-1), this->z * (-1));
		}
		/**
		* @brief []演算子
		*/
		T& operator[](const unsigned int index)
		{
			return (index == 0) ? this->x : (index == 1) ? this->y : this->z;
		}
		/**
		* @brief []演算子(constexpr)
		*/
		constexpr T operator[](const unsigned int index)const
		{
			return (index == 0) ? this->x : (index == 1) ? this->y : this->z;
		}
		/**
		* @brief ++演算子(前置)
		*/
		Vector3<T>& operator++()
		{
			this->x += 1; this->y += 1; this->z += 1;
			return *this;
		}
		/**
		* @brief ++演算子(後置)
		*/
		Vector3<T> operator++(int)
		{
			Vector3<T> temp = *this;
			this->x += 1; this->y += 1; this->z += 1;
			return temp;
		}
		/**
		* @brief --演算子(前置)
		*/
		Vector3<T>& operator--()
		{
			this->x -= 1; this->y -= 1; this->z -= 1;
			return *this;
		}
		/**
		* @brief --演算子(後置)
		*/
		Vector3<T> operator--(int)
		{
			Vector3<T> temp = *this;
			this->x -= 1; this->y -= 1; this->z -= 1;
			return temp;
		}
		/**
		* @brief 正規化
		* @details int型の場合、すべての要素が0で返ります
		*/
		void normalize()
		{
			//分母
			auto den = saki::sqrt(this->x * this->x + this->y * this->y + this->z * this->z);
			if (den == 0)
			{
				this->x = 0;
				this->y = 0;
				this->z = 0;
			}
			else
			{
				this->x /= den;
				this->y /= den;
				this->z /= den;
			}
		}
		/**
		* @brief 正規化
		* @return 正規化したもの
		* @details thisは正規化しない、int型の場合、すべての要素が0で帰ります
		*/
		template<typename U = double>
		constexpr Vector3<U> return_normalize()const
		{
			//分母
			auto den = saki::sqrt(this->x * this->x + this->y * this->y + this->z * this->z);
			if (den == 0)
			{
				return Vector3<U>
					(static_cast<U>(0),//x
						static_cast<U>(0),//y
						static_cast<U>(0));//z
			}
			else
			{
				return Vector3<U>
					(static_cast<U>(this->x / den),//x
						static_cast<U>(this->y / den),//y
						static_cast<U>(this->z / den));//z
			}
		}
	};

	/**
	* @brief Vector3のオールゼロ
	*/
	template<typename T>
	static constexpr Vector3<T> vector3_zero{ static_cast<T>(0), static_cast<T>(0), static_cast<T>(0) };
	/**
	* @brief Vector3のオールワン
	*/
	template<typename T>
	static constexpr Vector3<T> vector3_one{ static_cast<T>(1), static_cast<T>(1), static_cast<T>(1) };
	/**
	* @brief Vector3の最小値
	*/
	template<typename T>
	static constexpr Vector3<T> vector3_min{ std::numeric_limits<T>::min(), std::numeric_limits<T>::min(), std::numeric_limits<T>::min() };
	/**
	* @brief Vector3の最大値
	*/
	template<typename T>
	static constexpr Vector3<T> vector3_max{ std::numeric_limits<T>::max(), std::numeric_limits<T>::max(), std::numeric_limits<T>::max() };
	/**
	* @brief 内積
	*/
	template<typename U = double, typename T1, typename T2>
	constexpr U dot(const Vector3<T1>& v1, const Vector3<T2>& v2)
	{
		return static_cast<U>(v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
	}
	/**
	* @brief 外積
	*/
	template<typename U = double, typename T1, typename T2>
	constexpr Vector3<U> cross(const Vector3<T1>& v1, const Vector3<T2>& v2)
	{
		return Vector3<U>(
			v1.y * v2.z - v1.z * v1.y, //x
			v1.z * v2.x - v1.x * v1.z, //y
			v1.x * v2.y - v1.y * v1.x);//z
	}
	/**
	* @brief 線形補間
	* @details Quaternionは使用していません
	*/
	template<typename U = double, typename T1, typename T2, typename T = double>
	constexpr Vector3<U> lerp(const Vector3<T1>& v1, const Vector3<T2>& v2, const T& t, const T& base = 1)
	{
		auto ratio = t / base;
		return Vector3<U>(
			v1.x + (v2.x - v1.x) * ratio,
			v1.y + (v2.y - v1.y) * ratio,
			v1.z + (v2.z - v1.z) * ratio);
	}
}

#endif //SAKI_VECTOR_3D_2018_12_06
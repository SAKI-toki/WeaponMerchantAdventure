/**
* @file matrix.h
* @brief 行列
* @author 石山 悠
* @date 2018/12/13
*/
#pragma once
#ifndef SAKI_MATRIX_2018_12_13
#define SAKI_MATRIX_2018_12_13
#include <saki/matrix/details/matrix_operator.h>
#include <saki/macro/type_macro.h>
#include <saki/vector/vector_4d.h>

namespace saki
{
	/**
	* @brief 行列
	*/
	template<typename T>
	class Matrix
	{
		T m[4][4];
	public:
		SAKI_TYPE_MACRO(T)
	public:
		/**
		* @brief 引数なしコンストラクタ
		* @details Identity初期化
		*/
		constexpr Matrix() :
			m{ {1,0,0,0},
			{0,1,0,0},
			{0,0,1,0},
			{0,0,0,1} }
		{}
		/**
		* @brief 引数ありコンストラクタ
		*/
		constexpr Matrix(
			const T& m00, const T& m01, const T& m02, const T& m03,
			const T& m10, const T& m11, const T& m12, const T& m13,
			const T& m20, const T& m21, const T& m22, const T& m23,
			const T& m30, const T& m31, const T& m32, const T& m33) :
			m{ {m00,m01,m02,m03},
				{m10,m11,m12,m13},
				{m20,m21,m22,m23},
				{m30,m31,m32,m33} }
		{}
		/**
		* @brief 生配列からの初期化
		* @param arr 4*4の配列
		*/
		template<typename U>
		explicit constexpr Matrix(const U arr[4][4]) :
			m{ {static_cast<T>(arr[0][0]),static_cast<T>(arr[0][1]),static_cast<T>(arr[0][2]),static_cast<T>(arr[0][3])},
			{static_cast<T>(arr[1][0]),static_cast<T>(arr[1][1]),static_cast<T>(arr[1][2]),static_cast<T>(arr[1][3])},
			{static_cast<T>(arr[2][0]),static_cast<T>(arr[2][1]),static_cast<T>(arr[2][2]),static_cast<T>(arr[2][3])},
			{static_cast<T>(arr[3][0]),static_cast<T>(arr[3][1]),static_cast<T>(arr[3][2]),static_cast<T>(arr[3][3])} }
		{}
		/**
		* @brief vector4での初期化
		* @param v1 1行目
		* @param v2 2行目
		* @param v3 3行目
		* @param v4 4行目
		*/
		template<typename U1, typename U2, typename U3, typename U4>
		constexpr Matrix(const Vector4<U1> v1, const Vector4<U2> v2, const Vector4<U3> v3, const Vector4<U4> v4) :
			m{ {static_cast<T>(v1.x),static_cast<T>(v1.y),static_cast<T>(v1.z),static_cast<T>(v1.w)},
			{static_cast<T>(v2.x),static_cast<T>(v2.y),static_cast<T>(v2.z),static_cast<T>(v2.w)},
			{static_cast<T>(v3.x),static_cast<T>(v3.y),static_cast<T>(v3.z),static_cast<T>(v3.w)},
			{static_cast<T>(v4.x),static_cast<T>(v4.y),static_cast<T>(v4.z),static_cast<T>(v4.w)} }
		{}
		//デフォルトを使用
		//デフォルトではメンバ変数のコピー、ムーブを行う
		Matrix(const Matrix<T>&) = default;
		Matrix<T>& operator=(const Matrix<T>&) = default;
		Matrix(Matrix<T>&&)noexcept = default;
		Matrix& operator=(Matrix<T>&&)noexcept = default;
		/**
		* @brief +=演算子
		*/
		template<typename U = T>
		auto operator+=(const Matrix<U>& other)
		{
			*this = *this + other;
			return *this;
		}
		/**
		* @brief -=演算子
		*/
		template<typename U = T>
		auto operator-=(const Matrix<U>& other)
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
		* @brief *=演算子(行列)
		*/
		template<typename U = T>
		auto operator*=(const Matrix<U>& other)
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
		* @brief 単項+演算子
		*/
		constexpr Matrix<T> operator+()const
		{
			return *this;
		}
		/**
		* @brief 単項-演算子
		*/
		constexpr Matrix<T> operator-()const
		{
			return Matrix<T>(
				this->at_constexpr(0, 0) * (-1), this->at_constexpr(0, 1) * (-1),
				this->at_constexpr(0, 2) * (-1), this->at_constexpr(0, 3) * (-1),
				this->at_constexpr(1, 0) * (-1), this->at_constexpr(1, 1) * (-1),
				this->at_constexpr(1, 2) * (-1), this->at_constexpr(1, 3) * (-1),
				this->at_constexpr(2, 0) * (-1), this->at_constexpr(2, 1) * (-1),
				this->at_constexpr(2, 2) * (-1), this->at_constexpr(2, 3) * (-1),
				this->at_constexpr(3, 0) * (-1), this->at_constexpr(3, 1) * (-1),
				this->at_constexpr(3, 2) * (-1), this->at_constexpr(3, 3) * (-1)
				);
		}
		/**
		* @brief []演算子
		*/
		T* operator[](const unsigned int index)
		{
			return m[index];
		}
		/**
		* @brief []演算子では表現できないため、普通の関数にした
		* @param row,col 行、列
		* @details 自作arrayクラスを作成すればできるが、とりあえず今はこのままで
		*/
		constexpr T at_constexpr(const unsigned int row, const unsigned int col)const
		{
			return m[row][col];
		}

		/**
		* @brief 単位行列に変換
		*/
		void identity()
		{
			for (int i = 0; i < 4; ++i)
			{
				for (int j = 0; j < 4; ++j)
				{
					m[i][j] = (i == j) ? 1 : 0;
				}
			}
		}
	};

	/**
	* @brief 単位行列
	*/
	template<typename T>
	static constexpr Matrix<T> matrix_identity{
		static_cast<T>(1), static_cast<T>(0), static_cast<T>(0), static_cast<T>(0) ,
		static_cast<T>(0), static_cast<T>(1), static_cast<T>(0), static_cast<T>(0) ,
		static_cast<T>(0), static_cast<T>(0), static_cast<T>(1), static_cast<T>(0) ,
		static_cast<T>(0), static_cast<T>(0), static_cast<T>(0), static_cast<T>(1)
	};
}
#endif //SAKI_MATRIX_2018_12_13
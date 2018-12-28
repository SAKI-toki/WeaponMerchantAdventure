/**
* @file matrix_operator.h
* @brief Matrix�N���X�̉��Z�q
* @author �ΎR �I
* @date 2018/12/13
*/
#pragma once
#ifndef SAKI_MATRIX_OPERATOR_2018_12_13
#define SAKI_MATRIX_OPERATOR_2018_12_13
#include <saki/binary_operator/binary_operator.h>

namespace saki
{
	//�v���g�^�C�v�錾
	template<typename T>
	class Matrix;
	namespace details
	{
		/**
		* @brief �s�񓯎m�̉��Z(+��-)
		*/
		template<typename T1, typename T2, typename Func>
		constexpr auto matrix_matrix_some_operator(const Matrix<T1>& m1, const Matrix<T2>& m2, Func&& f)
		{
			return Matrix<decltype(std::declval<T1>() * std::declval<T2>())>
			{
				f(m1.at_constexpr(0, 0), m2.at_constexpr(0, 0)), f(m1.at_constexpr(0, 1), m2.at_constexpr(0, 1)),
					f(m1.at_constexpr(0, 2), m2.at_constexpr(0, 2)), f(m1.at_constexpr(0, 3), m2.at_constexpr(0, 3)),
					f(m1.at_constexpr(1, 0), m2.at_constexpr(1, 0)), f(m1.at_constexpr(1, 1), m2.at_constexpr(1, 1)),
					f(m1.at_constexpr(1, 2), m2.at_constexpr(1, 2)), f(m1.at_constexpr(1, 3), m2.at_constexpr(1, 3)),
					f(m1.at_constexpr(2, 0), m2.at_constexpr(2, 0)), f(m1.at_constexpr(2, 1), m2.at_constexpr(2, 1)),
					f(m1.at_constexpr(2, 2), m2.at_constexpr(2, 2)), f(m1.at_constexpr(2, 3), m2.at_constexpr(2, 3)),
					f(m1.at_constexpr(3, 0), m2.at_constexpr(3, 0)), f(m1.at_constexpr(3, 1), m2.at_constexpr(3, 1)),
					f(m1.at_constexpr(3, 2), m2.at_constexpr(3, 2)), f(m1.at_constexpr(3, 3), m2.at_constexpr(3, 3))
			};
		}
		/**
		* @brief �s��ƃX�J���̉��Z
		*/
		template<typename T1, typename T2, typename Func>
		constexpr auto matrix_scalar_some_operator(const Matrix<T1>& m, const T2& scalar, Func&& f)
		{
			return Matrix<decltype(std::declval<T1>() * std::declval<T2>())>
			{
				f(m.at_constexpr(0, 0), scalar), f(m.at_constexpr(0, 1), scalar),
					f(m.at_constexpr(0, 2), scalar), f(m.at_constexpr(0, 3), scalar),
					f(m.at_constexpr(1, 0), scalar), f(m.at_constexpr(1, 1), scalar),
					f(m.at_constexpr(1, 2), scalar), f(m.at_constexpr(1, 3), scalar),
					f(m.at_constexpr(2, 0), scalar), f(m.at_constexpr(2, 1), scalar),
					f(m.at_constexpr(2, 2), scalar), f(m.at_constexpr(2, 3), scalar),
					f(m.at_constexpr(3, 0), scalar), f(m.at_constexpr(3, 1), scalar),
					f(m.at_constexpr(3, 2), scalar), f(m.at_constexpr(3, 3), scalar)
			};
		}
	}
	/**
	* @brief +���Z�q
	*/
	template<typename T1, typename T2>
	constexpr auto operator+(const Matrix<T1>& m1, const Matrix<T2>& m2)
	{
		return details::matrix_matrix_some_operator(m1, m2, addition());
	}
	/**
	* @brief -���Z�q
	*/
	template<typename T1, typename T2>
	constexpr auto operator-(const Matrix<T1>& m1, const Matrix<T2>& m2)
	{
		return details::matrix_matrix_some_operator(m1, m2, subtraction());
	}
	/**
	* @brief *���Z�q(�s��*�X�J��)
	*/
	template<typename T1, typename T2>
	constexpr auto operator*(const Matrix<T1>& m, const T2& scalar)
	{
		return details::matrix_scalar_some_operator(m, scalar, multiplication());
	}
	/**
	* @brief *���Z�q(�X�J��*�s��)
	*/
	template<typename T1, typename T2>
	constexpr auto operator*(const T1& scalar, const Matrix<T2>& m)
	{
		return m * scalar;
	}
	/**
	* @brief *���Z�q(�s��*�s��)
	*/
	template<typename T1, typename T2>
	constexpr auto operator*(const Matrix<T1>& m1, const Matrix<T2>& m2)
	{
		using m_type = decltype(std::declval<T1>() * std::declval<T2>());
		m_type arr[4][4]{};
		for (int i = 0; i < 4; ++i)
		{
			for (int j = 0; j < 4; ++j)
			{
				m_type sum = 0;
				for (int k = 0; k < 4; ++k)
				{
					sum += m1.at_constexpr(i, k)*m2.at_constexpr(k, j);
				}
				arr[i][j] = sum;
			}
		}
		return Matrix<m_type>{arr};
	}
	/**
	* @brief /���Z�q(�X�J��)
	*/
	template<typename T1, typename T2>
	constexpr auto operator/(const Matrix<T1>& m, const T2& scalar)
	{
		return details::matrix_scalar_some_operator(m, scalar, division());
	}
	/**
	* @brief ==���Z�q
	*/
	template<typename T>
	constexpr bool operator==(const Matrix<T>& m1, const Matrix<T>& m2)
	{
		for (int i = 0; i < 4; ++i)
		{
			for (int j = 0; j < 4; ++j)
			{
				if (m1.at_constexpr(i, j) != m2.at_constexpr(i, j)) { return false; }
			}
		}
		return true;
	}
	/**
	* @brief !=���Z�q
	*/
	template<typename T>
	constexpr bool operator!=(const Matrix<T>& m1, const Matrix<T>& m2)
	{
		return !(m1 == m2);
	}
	/**
	* @brief ==���Z�q(�^�s��v)
	* @details ���̊֐��̎g�p�͐������Ȃ�
	*/
	template<typename T1, typename T2>[[deprecated("type_mismatch")]]
		constexpr bool operator==(const Matrix<T1>& m1, const Matrix<T2>& m2)
	{
		for (int i = 0; i < 4; ++i)
		{
			for (int j = 0; j < 4; ++j)
			{
				if (m1.at_constexpr(i, j) != m2.at_constexpr(i, j)) { return false; }
			}
		}
		return true;
	}
	/**
	* @brief !=���Z�q(�^�s��v)
	* @details ���̊֐��̎g�p�͐������Ȃ�
	*/
	template<typename T1, typename T2>[[deprecated("type_mismatch")]]
		constexpr bool operator!=(const Matrix<T1>& m1, const Matrix<T2>& m2)
	{
		return !(m1 == m2);
	}
}
#endif //SAKI_MATRIX_OPERATOR_2018_12_13
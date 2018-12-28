/**
* @file transform_operator.h
* @brief transform�N���X�̉��Z�q
* @author �ΎR �I
* @date 2018/12/16
*/
#pragma once
#ifndef SAKI_TRANSFORM_OPERATOR_2018_12_16
#define SAKI_TRANSFORM_OPERATOR_2018_12_16

namespace saki
{
	//�v���g�^�C�v�錾
	template<typename T>
	class Transform;
	namespace details
	{
		/**
		* @brief Transform���m�̉��Z
		*/
		template<typename T1, typename T2, typename Func>
		constexpr auto transform_transform_some_operator(const Transform<T1>& v1, const Transform<T2>& v2, Func&& f)
		{
			return Transform<decltype(std::declval<T1>() + std::declval<T2>())>
			{ f(v1.get_pos(), v2.get_pos()), f(v1.get_rot(), v2.get_rot()), f(v1.get_scale(), v2.get_scale()) };
		}
		/**
		* @brief Transform�ƃX�J���̉��Z
		*/
		template<typename T1, typename T2, typename Func>
		constexpr auto transform_scalar_some_operator(const Transform<T1>& v, const T2& scalar, Func&& f)
		{
			return Transform<decltype(std::declval<T1>() * std::declval<T2>())>
			{  f(v.get_pos(), scalar), f(v.get_rot(), scalar)  f(v.get_scale(), scalar) };
		}
	}
	/**
	* @brief +���Z�q
	*/
	template<typename T1, typename T2>
	constexpr auto operator+(const Transform<T1>& v1, const Transform<T2>& v2)
	{
		return details::transform_transform_some_operator(v1, v2, addition());
	}
	/**
	* @brief -���Z�q
	*/
	template<typename T1, typename T2>
	constexpr auto operator-(const Transform<T1>& v1, const Transform<T2>& v2)
	{
		return details::transform_transform_some_operator(v1, v2, subtraction());
	}
	/**
	* @brief *���Z�q(Transform*�X�J��)
	*/
	template<typename T1, typename T2>
	constexpr auto operator*(const Transform<T1>& v, const T2& scalar)
	{
		return details::transform_scalar_some_operator(v, scalar, multiplication());
	}
	/**
	* @brief *���Z�q(�X�J��*Transform)
	*/
	template<typename T1, typename T2>
	constexpr auto operator*(const T1& scalar, const Transform<T2>& v)
	{
		return v * scalar;
	}
	/**
	* @brief /���Z�q(�X�J��)
	*/
	template<typename T1, typename T2>
	constexpr auto operator/(const Transform<T1>& v, const T2& scalar)
	{
		return details::transform_scalar_some_operator(v, scalar, division());
	}
	/**
	* @brief ==���Z�q
	*/
	template<typename T>
	constexpr bool operator==(const Transform<T>& v1, const Transform<T>& v2)
	{
		return v1.get_pos() == v2.get_pos() && v1.get_rot() == v2.get_rot() && v1.get_scale() == v2.get_scale();
	}
	/**
	* @brief !=���Z�q
	*/
	template<typename T>
	constexpr bool operator!=(const Transform<T>& v1, const Transform<T>& v2)
	{
		return !(v1 == v2);
	}
	/**
	* @brief ==���Z�q(�^�s��v)
	* @details ���̊֐��̎g�p�͐������Ȃ�
	*/
	template<typename T1, typename T2>[[deprecated("type_mismatch")]]
		constexpr bool operator==(const Transform<T1>& v1, const Transform<T2>& v2)
	{
		return v1.get_pos() == v2.get_pos() && v1.get_rot() == v2.get_rot() && v1.get_scale() == v2.get_scale();
	}
	/**
	* @brief !=���Z�q(�^�s��v)
	* @details ���̊֐��̎g�p�͐������Ȃ�
	*/
	template<typename T1, typename T2>[[deprecated("type_mismatch")]]
		constexpr bool operator!=(const Transform<T1>& v1, const Transform<T2>& v2)
	{
		return !(v1 == v2);
	}
}
#endif //SAKI_TRANSFORM_OPERATOR_2018_12_16
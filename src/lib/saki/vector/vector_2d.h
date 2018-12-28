/**
* @file vector_2d.h
* @brief 2�����ł̃x�N�g��
* @author �ΎR �I
* @date 2018/12/13
*/
#pragma once
#ifndef SAKI_VECTOR_2D_2018_12_13
#define SAKI_VECTOR_2D_2018_12_13
#include <limits> //for numeric_limits
#include <saki/constexpr_std/sqrt.h> //for constexpr_sqrt
#include <saki/vector/details/2d/vector_2d_operator.h>
#include <saki/macro/type_macro.h>


namespace saki
{
	/**
	* @brief 2�����ł̃x�N�g��
	*/
	template<typename T>
	class Vector2
	{
	public:
		SAKI_TYPE_MACRO(T)
	public:
		T x, y;
		/**
		* @brief �����Ȃ��R���X�g���N�^
		* @details �S��0�ŏ�����
		*/
		constexpr Vector2() :
			x(static_cast<T>(0)), y(static_cast<T>(0))
		{}
		/**
		* @brief ��������R���X�g���N�^
		* @param _x x�̏����l
		* @param _y y�̏����l
		*/
		constexpr Vector2(const T& _x, const T& _y) :
			x(_x), y(_y)
		{}
		/**
		* @brief ���z�񂩂�̏�����
		* @param pointer �z��̃|�C���^
		*/
		explicit constexpr Vector2(const T* const pointer) :
			x(*pointer), y(*(pointer + 1))
		{}
		//�f�t�H���g���g�p
		//�f�t�H���g�ł̓����o�ϐ��̃R�s�[�A���[�u���s��
		Vector2(const Vector2<T>&) = default;
		Vector2<T>& operator=(const Vector2<T>&) = default;
		Vector2(Vector2<T>&&)noexcept = default;
		Vector2& operator=(Vector2<T>&&)noexcept = default;
		/**
		* @brief +=���Z�q
		*/
		template<typename U = T>
		auto operator+=(const Vector2<U>& other)
		{
			*this = *this + other;
			return *this;
		}
		/**
		* @brief -=���Z�q
		*/
		template<typename U = T>
		auto operator-=(const Vector2<U>& other)
		{
			*this = *this - other;
			return *this;
		}
		/**
		* @brief *=���Z�q(�X�J��)
		*/
		template<typename U = T>
		auto operator*=(const U& scalar)
		{
			*this = *this * scalar;
			return *this;
		}
		/**
		* @brief *=���Z�q(�x�N�g��)
		*/
		template<typename U = T>
		auto operator*=(const Vector2<U>& other)
		{
			*this = *this * other;
			return *this;
		}
		/**
		* @brief /=���Z�q(�X�J��)
		*/
		template<typename U = T>
		auto operator/=(const U& scalar)
		{
			*this = *this / scalar;
			return *this;
		}
		/**
		* @brief /=���Z�q(�x�N�g��)
		*/
		template<typename U = T>
		auto operator/=(const Vector2<U>& other)
		{
			*this = *this / other;
			return *this;
		}
		/**
		* @brief �P��+���Z�q
		*/
		constexpr Vector2<T> operator+()const
		{
			return *this;
		}
		/**
		* @brief �P��-���Z�q
		*/
		constexpr Vector2<T> operator-()const
		{
			return Vector2<T>(this->x * (-1), this->y * (-1));
		}
		/**
		* @brief []���Z�q
		*/
		T& operator[](const unsigned int index)
		{
			return (index == 0) ? this->x : this->y;
		}
		/**
		* @brief []���Z�q(constexpr)
		*/
		constexpr T operator[](const unsigned int index)const
		{
			return (index == 0) ? this->x : this->y;
		}
		/**
		* @brief ++���Z�q(�O�u)
		*/
		Vector2<T>& operator++()
		{
			this->x += 1; this->y += 1;
			return *this;
		}
		/**
		* @brief ++���Z�q(��u)
		*/
		Vector2<T> operator++(int)
		{
			Vector2<T> temp = *this;
			this->x += 1; this->y += 1;
			return temp;
		}
		/**
		* @brief --���Z�q(�O�u)
		*/
		Vector2<T>& operator--()
		{
			this->x -= 1; this->y -= 1;
			return *this;
		}
		/**
		* @brief --���Z�q(��u)
		*/
		Vector2<T> operator--(int)
		{
			Vector2<T> temp = *this;
			this->x -= 1; this->y -= 1;
			return temp;
		}
		/**
		* @brief ���K��
		* @details int�^�̏ꍇ�A���ׂĂ̗v�f��0�ŋA��܂�
		*/
		void normalize()
		{
			//����
			auto den = saki::sqrt(this->x * this->x + this->y * this->y);
			if (den == 0)
			{
				this->x = 0;
				this->y = 0;
			}
			else
			{
				this->x /= den;
				this->y /= den;
			}
		}
		/**
		* @brief ���K��
		* @return ���K����������
		* @details this�͐��K�����Ȃ��Aint�^�̏ꍇ�A���ׂĂ̗v�f��0�ŕԂ�܂�
		*/
		template<typename U = double>
		constexpr Vector2<U> return_normalize()const
		{
			//����
			auto den = saki::sqrt(this->x * this->x + this->y * this->y);
			if (den == 0)
			{
				return Vector2<U>
					(static_cast<U>(0),//x
						static_cast<U>(0));//y
			}
			else
			{
				return Vector2<U>
					(static_cast<U>(this->x / den),//x
						static_cast<U>(this->y / den));//y
			}
		}
	};
	/**
	* @brief Vector2�̃I�[���[��
	*/
	template<typename T>
	static constexpr Vector2<T> vector2_zero{ static_cast<T>(0), static_cast<T>(0) };
	/**
	* @brief Vector2�̃I�[������
	*/
	template<typename T>
	static constexpr Vector2<T> vector2_one{ static_cast<T>(1), static_cast<T>(1) };
	/**
	* @brief Vector2�̍ŏ��l
	*/
	template<typename T>
	static constexpr Vector2<T> vector2_min{ std::numeric_limits<T>::min(), std::numeric_limits<T>::min() };
	/**
	* @brief Vector2�̍ő�l
	*/
	template<typename T>
	static constexpr Vector2<T> vector2_max{ std::numeric_limits<T>::max(), std::numeric_limits<T>::max() };

	/**
	* @brief ����
	*/
	template<typename U = double, typename T1, typename T2>
	constexpr U dot(const Vector2<T1>& v1, const Vector2<T2>& v2)
	{
		return static_cast<U>(v1.x*v2.x + v1.y*v2.y);
	}
	/**
	* @brief �O��
	*/
	template<typename U = double, typename T1, typename T2>
	constexpr U cross(const Vector2<T1>& v1, const Vector2<T2>& v2)
	{
		return static_cast<U>(v1.x * v2.y - v1.y * v2.x);
	}

	/**
	* @brief ���`���
	* @details Quaternion�͎g�p���Ă��܂���
	*/
	template<typename U = double, typename T1, typename T2, typename T = double>
	constexpr Vector2<U> lerp(const Vector2<T1>& v1, const Vector2<T2>& v2, const T& t, const T& base = 1)
	{
		auto ratio = t / base;
		return Vector2<U>(
			v1.x + (v2.x - v1.x) * ratio,
			v1.y + (v2.y - v1.y) * ratio);
	}
}
#endif //SAKI_VECTOR_2D_2018_12_13
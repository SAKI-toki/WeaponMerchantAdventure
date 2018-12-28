/**
* @file transform.h
* @brief transform�N���X
* @author �ΎR �I
* @date 2018/12/16
*/
#pragma once
#ifndef SAKI_TRANSFORM_2D_2018_12_16
#define SAKI_TRANSFORM_2D_2018_12_16

#include <saki/vector/vector_3d.h>
#include <saki/transform/details/transform_operator.h>

namespace saki
{
	/**
	* @brief transform�N���X
	* @details �N�H�[�^�j�I���͎g�p���Ă��܂���
	*/
	template<typename T>
	class Transform
	{
		//�ʒu
		Vector3<T> position;
		//��]
		Vector3<T> rotation;
		//�g�k
		Vector3<T> scale;
	public:
		/**
		* @brief �����Ȃ��R���X�g���N�^
		*/
		constexpr Transform() :
			position(vector3_zero<T>), rotation(vector3_zero<T>), scale(vector3_one<T>)
		{}
		/**
		* @brief �e�l�������ɂƂ�R���X�g���N�^
		* @param pos �ʒu
		* @param rot ��]
		* @param sca �g�k
		*/
		constexpr Transform(const Vector3<T>& pos, const Vector3<T> rot, const Vector3<T>sca) :
			position(pos), rotation(rot), scale(sca)
		{}
		//�R�s�[���[�u�̓f�t�H���g���g�p
		Transform(const Transform<T>&) = default;
		Transform<T>& operator=(const Transform<T>&) = default;
		Transform(Transform<T>&&) = default;
		Transform<T>& operator=(Transform<T>&&) = default;

		/**
		* @brief �ړ�
		*/
		void move(const Vector3<T>& pos)
		{
			position += pos;
		}
		/**
		* @brief ��]
		*/
		void rotate(const Vector3<T>& rot)
		{
			rotation += rot;
		}
		/**
		* @brief �g��
		*/
		void expantion(const Vector3<T>& sca)
		{
			scale += sca;
		}
		/**
		* @brief �ʒu�̃Q�b�^
		*/
		auto get_pos()const
		{
			return position;
		}
		/**
		* @brief �ʒu�̃Z�b�^
		* @param pos �ʒu
		*/
		void set_pos(const Vector3<T>& pos)
		{
			position = pos;
		}
		/**
		* @brief ��]�̃Q�b�^
		*/
		auto get_rot()const
		{
			return rotation;
		}
		/**
		* @brief ��]�̃Z�b�^
		* @param rot ��]
		*/
		void set_rot(const Vector3<T>& rot)
		{
			rotation = rot;
		}
		/**
		* @brief �g�k�̃Q�b�^
		*/
		auto get_scale()const
		{
			return scale;
		}
		/**
		* @brief �g�k�̃Z�b�^
		* @param sca �g�k
		*/
		void set_scale(const Vector3<T>& sca)
		{
			scale = sca;
		}
		/**
		* @brief +=���Z�q
		*/
		template<typename U = T>
		auto operator+=(const Transform<U>& other)
		{
			*this = *this + other;
			return *this;
		}
		/**
		* @brief -=���Z�q
		*/
		template<typename U = T>
		auto operator-=(const Transform<U>& other)
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
		* @brief /= ���Z�q(�X�J��)
		*/
		template<typename U = T>
		auto operator/=(const U& scalar)
		{
			*this = *this / scalar;
			return *this;
		}
		/**
		* @brief �P��+���Z�q
		*/
		constexpr Transform<T> operator+()const
		{
			return *this;
		}
		/**
		* @brief �P��-���Z�q
		*/
		constexpr Transform<T> operator-()const
		{
			return Transform<T>(this->position * (-1), this->rotation * (-1), this->scale * (-1));
		}
	};
}

#endif //SAKI_TRANSFORM_2D_2018_12_16
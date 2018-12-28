/**
* @file transform.h
* @brief transformクラス
* @author 石山 悠
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
	* @brief transformクラス
	* @details クォータニオンは使用していません
	*/
	template<typename T>
	class Transform
	{
		//位置
		Vector3<T> position;
		//回転
		Vector3<T> rotation;
		//拡縮
		Vector3<T> scale;
	public:
		/**
		* @brief 引数なしコンストラクタ
		*/
		constexpr Transform() :
			position(vector3_zero<T>), rotation(vector3_zero<T>), scale(vector3_one<T>)
		{}
		/**
		* @brief 各値を引数にとるコンストラクタ
		* @param pos 位置
		* @param rot 回転
		* @param sca 拡縮
		*/
		constexpr Transform(const Vector3<T>& pos, const Vector3<T> rot, const Vector3<T>sca) :
			position(pos), rotation(rot), scale(sca)
		{}
		//コピームーブはデフォルトを使用
		Transform(const Transform<T>&) = default;
		Transform<T>& operator=(const Transform<T>&) = default;
		Transform(Transform<T>&&) = default;
		Transform<T>& operator=(Transform<T>&&) = default;

		/**
		* @brief 移動
		*/
		void move(const Vector3<T>& pos)
		{
			position += pos;
		}
		/**
		* @brief 回転
		*/
		void rotate(const Vector3<T>& rot)
		{
			rotation += rot;
		}
		/**
		* @brief 拡大
		*/
		void expantion(const Vector3<T>& sca)
		{
			scale += sca;
		}
		/**
		* @brief 位置のゲッタ
		*/
		auto get_pos()const
		{
			return position;
		}
		/**
		* @brief 位置のセッタ
		* @param pos 位置
		*/
		void set_pos(const Vector3<T>& pos)
		{
			position = pos;
		}
		/**
		* @brief 回転のゲッタ
		*/
		auto get_rot()const
		{
			return rotation;
		}
		/**
		* @brief 回転のセッタ
		* @param rot 回転
		*/
		void set_rot(const Vector3<T>& rot)
		{
			rotation = rot;
		}
		/**
		* @brief 拡縮のゲッタ
		*/
		auto get_scale()const
		{
			return scale;
		}
		/**
		* @brief 拡縮のセッタ
		* @param sca 拡縮
		*/
		void set_scale(const Vector3<T>& sca)
		{
			scale = sca;
		}
		/**
		* @brief +=演算子
		*/
		template<typename U = T>
		auto operator+=(const Transform<U>& other)
		{
			*this = *this + other;
			return *this;
		}
		/**
		* @brief -=演算子
		*/
		template<typename U = T>
		auto operator-=(const Transform<U>& other)
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
		* @brief /= 演算子(スカラ)
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
		constexpr Transform<T> operator+()const
		{
			return *this;
		}
		/**
		* @brief 単項-演算子
		*/
		constexpr Transform<T> operator-()const
		{
			return Transform<T>(this->position * (-1), this->rotation * (-1), this->scale * (-1));
		}
	};
}

#endif //SAKI_TRANSFORM_2D_2018_12_16
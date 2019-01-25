/**
* @file transform.h
* @brief transformクラス
* @author 石山 悠
* @date 2018/12/18
*/
#pragma once
#ifndef SAKI_TRANSFORM_2018_12_18
#define SAKI_TRANSFORM_2018_12_18
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
		saki::Vector3<T> position;
		//回転
		saki::Vector3<T> rotation;
		//拡縮
		saki::Vector3<T> scale = saki::Vector3<T>{ 1,1,1 };
	public:
		/**
		* @brief 引数なしコンストラクタ
		*/
		constexpr Transform()
		{}
		/**
		* @brief 各値を引数にとるコンストラクタ
		* @param pos 位置
		* @param rot 回転
		* @param sca 拡縮
		*/
		constexpr Transform(const saki::Vector3<T>& pos, const saki::Vector3<T> rot, const saki::Vector3<T>sca) :
			position(pos), rotation(rot), scale(sca)
		{}
		//コピームーブはデフォルトを使用
		Transform(const Transform<T>&) = default;
		Transform<T>& operator=(const Transform<T>&) = default;
		Transform(Transform<T>&&) = default;
		Transform<T>& operator=(Transform<T>&&) = default;

		/**
		* @brief 移動
		* @param pos 移動量
		*/
		constexpr void move(const saki::Vector3<T>& pos)
		{
			position += pos;
		}
		/**
		* @brief 移動
		* @param x 移動量(x)
		* @param y 移動量(y)
		* @param z 移動量(z)
		*/
		constexpr void move(const T& x, const T& y, const T& z)
		{
			position += saki::Vector3<T>(x, y, z);
		}
		/**
		* @brief 回転
		* @param rot 回転量
		*/
		constexpr void rotate(const saki::Vector3<T>& rot)
		{
			rotation += rot;
		}
		/**
		* @brief 回転
		* @param x 回転量(x)
		* @param y 回転量(y)
		* @param z 回転量(z)
		*/
		constexpr void rotate(const T& x, const T& y, const T& z)
		{
			rotation += saki::Vector3<T>(x, y, z);
		}
		/**
		* @brief 拡大
		* @param sca 拡大量
		*/
		constexpr void expantion(const saki::Vector3<T>& sca)
		{
			scale += sca;
		}
		/**
		* @brief 拡大
		* @param x 拡大量(x)
		* @param y 拡大量(y)
		* @param z 拡大量(z)
		*/
		constexpr void expantion(const T& x, const T& y, const T& z)
		{
			scale += saki::Vector3<T>(x, y, z);
		}
		/**
		* @brief 位置のゲッタ
		* @return 位置
		*/
		constexpr auto get_pos()const
		{
			return position;
		}
		/**
		* @brief 位置のセッタ
		* @param pos 位置
		*/
		constexpr void set_pos(const saki::Vector3<T>& pos)
		{
			position = pos;
		}
		/**
		* @brief 回転のゲッタ
		* @return 回転
		*/
		constexpr auto get_rot()const
		{
			return rotation;
		}
		/**
		* @brief 回転のセッタ
		* @param rot 回転
		*/
		constexpr void set_rot(const saki::Vector3<T>& rot)
		{
			rotation = rot;
		}
		/**
		* @brief 拡縮のゲッタ
		* @return 拡縮
		*/
		constexpr auto get_scale()const
		{
			return scale;
		}
		/**
		* @brief 拡縮のセッタ
		* @param sca 拡縮
		*/
		constexpr void set_scale(const saki::Vector3<T>& sca)
		{
			scale = sca;
		}
		/**
		* @brief +=演算子
		*/
		template<typename U = T>
		constexpr auto operator+=(const saki::Transform<U>& other)
		{
			*this = *this + other;
			return *this;
		}
		/**
		* @brief -=演算子
		*/
		template<typename U = T>
		constexpr auto operator-=(const saki::Transform<U>& other)
		{
			*this = *this - other;
			return *this;
		}
		/**
		* @brief *=演算子(スカラ)
		*/
		template<typename U = T>
		constexpr auto operator*=(const U& scalar)
		{
			*this = *this * scalar;
			return *this;
		}
		/**
		* @brief /= 演算子(スカラ)
		*/
		template<typename U = T>
		constexpr auto operator/=(const U& scalar)
		{
			*this = *this / scalar;
			return *this;
		}
		/**
		* @brief 単項+演算子
		*/
		constexpr saki::Transform<T> operator+()const
		{
			return *this;
		}
		/**
		* @brief 単項-演算子
		*/
		constexpr saki::Transform<T> operator-()const
		{
			return saki::Transform<T>(this->position * (-1), this->rotation * (-1), this->scale * (-1));
		}
	};
}

#endif //SAKI_TRANSFORM_2018_12_18
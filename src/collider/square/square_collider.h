/**
* @file square_collider.h
* @brief 四角形のコライダクラスの宣言
* @author 石山　悠
* @date 2018/10/12
*/
#pragma once
#include "../base/collider_base.h"
#include "../../transform/transform.h"



/**
* @brief 四角形コライダクラス
*/
class SquareCollider :public ColliderBase
{
	/**
	* @brief 四角形のコライダのステータス
	*/
	struct SquareStatus
	{
		VEC2 center_pos;		//位置
		float width, height;	//幅、高さ
		float rot;				//回転
		/**
		* @brief 初期化
		* @param pos 位置
		* @param w,h 幅、高さ
		* @param _rot 回転
		*/
		void Init(VEC2 _pos, float w, float h, float _rot)
		{
			center_pos = _pos, width = w, height = h, rot = _rot;
		}
		/**
		* @brief コピー代入演算子
		*/
		SquareStatus& operator=(const SquareStatus& other)
		{
			if (this != &other)
			{
				this->center_pos = other.center_pos;
				this->width = other.width;
				this->height = other.height;
				this->rot = other.rot;
			}
			return *this;
		}
	};
	//四角形のステータス
	SquareStatus status;
	//静的かどうか
	bool is_static;
public:
	//コンストラクタ
	SquareCollider(ObjectBase*, bool = false, bool = false);
	//ステータスをセットする
	void SetStatus(const VEC2& pos, const float w, const float h, const float rot, const float scale);
	//当たったときの押し出し
	void CollisionExtrusion(const VEC2&);
	/**
	* @brief 当たり判定のステータスを返す
	* @return const SquareStatus& ステータス
	*/
	const SquareStatus& GetStatus()const { return status; }
	//破棄
	void Destroy();

	SquareCollider& operator=(const SquareCollider& other);
};
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
		VEC2 center_pos;
		float width, height;
		float rot;
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
	};
	//四角形のステータス
	SquareStatus status;
public:
	//コンストラクタ
	SquareCollider(ObjectBase*, bool = false, bool = false);
	//ステータスをセットする
	void SetStatus(VEC2 pos, float w, float h, float rot);
	//当たったときの押し出し
	void CollisionExtrusion(const VEC2&);
	/**
	* @brief 当たり判定のステータスを返す
	* @return const SquareStatus& ステータス
	*/
	const SquareStatus& GetStatus()const { return status; }
	//破棄
	void Destroy();
};
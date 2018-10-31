/**
* @file square_collider.cpp
* @brief 四角形のコライダクラスのメンバ関数を定義
* @author 石山　悠
* @date 2018/10/12
*/
#include "square_collider.h"
#include "../manager/collider_manager.h"

/**
* @brief コンストラクタ
* @param obj オブジェクト
* @param _is_trigger 当たったときに透けるかどうか
* @param _is_static 静的かどうか
*/
SquareCollider::SquareCollider(ObjectBase* obj, bool _is_trigger, bool _is_static)
	:ColliderBase(obj, _is_trigger), is_static(_is_static)
{
	ColliderManager::GetInstance()->SetCollider(this, _is_static);
}

/**
* @brief 当たり判定のステータスをセットする
* @param pos センターの位置
* @param w,h 幅、高さ
* @param rot 回転
* @param scale 拡大・縮小
*/
void SquareCollider::SetStatus(const VEC2& pos, const float w, const float h, const float rot, const float scale)
{
	status.center_pos = pos, status.width = w * 0.5f*scale, status.height = h * 0.5f*scale, status.rot = rot;

}
/**
* @brief 当たったときの押し出し
* @param pos 移動先
* @details 加算減算にしない理由はfloatの誤差が起きてバグらないようにするため
*/
void SquareCollider::CollisionExtrusion(const VEC2& pos)
{
	status.center_pos = pos;
	object->transform.pos = pos;
}
/**
* @brief 四角形のコライダの破棄
*/
void SquareCollider::Destroy()
{
	ColliderManager::GetInstance()->DeleteCollider(this);
	enabled = false;
}

/**
* @brief コピー代入演算子
*/
SquareCollider& SquareCollider::operator=(const SquareCollider& other)
{
	if (this != &other)
	{
		this->status = other.status;
		ColliderBase::operator=(other);
		ColliderManager::GetInstance()->SetCollider(this, is_static);
	}
	return *this;
}

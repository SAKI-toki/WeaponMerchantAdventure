/**
* @file bullet.cpp
* @brief 遠距離武器から出る弾クラスのメンバ関数を定義
* @author 石山　悠
* @date 2018/10/18
*/
#include "bullet.h"
/**
* @brief 弾の初期化
* @param angle 発射角度
* @param func 当たったときに実行する関数
*/
void Bullet::BulletInit(const float angle, const std::function<void()>& func)
{
	dire = VEC2(std::cos(-angle + PI<float>*0.5f), -std::sin(-angle + PI<float>*0.5f));
	arrow_func = func;
}
/**
* @brief 初期化
*/
void Bullet::InitProcess()
{
	collider.SetStatus(transform.pos, transform.size.x, transform.size.y, transform.rot, transform.scale);
}

/**
* @brief 更新
*/
void Bullet::UpdateProcess()
{
	//寿命が来たら消える
	if (life++ > life_time)
	{
		this->Destroy();
		return;
	}
	transform.pos += dire * speed;
	collider.SetStatus(transform.pos, transform.size.x, transform.size.y, transform.rot, transform.scale);
}

/**
* @brief 破棄
*/
void Bullet::Destroy()
{
	if (collider.enabled)collider.Destroy();
	enabled = false;
}

/**
* @brief 当たったときに実行する関数
* @param obj 当たった相手のオブジェクト
*/
void Bullet::Collision(ObjectBase* obj, VEC2)
{
	if (obj == nullptr)return;
	//敵に当たったら
	if (obj->object_tag == OBJECT_TAG::ENEMY)
	{
		arrow_func();
		this->Destroy();
	}
	//マップに当たったら
	else if (obj->object_tag == OBJECT_TAG::MAP)
	{
		this->Destroy();
	}
}
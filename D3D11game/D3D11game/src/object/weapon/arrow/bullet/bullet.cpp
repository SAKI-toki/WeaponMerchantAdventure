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
	dire = Vec3(std::cos(-angle + saki::PI<float>*0.5f), -std::sin(-angle + saki::PI<float>*0.5f), 0);
	arrow_func = func;
	status.Init(1, 5, 1);
}
/**
* @brief 初期化
*/
void Bullet::InitProcess()
{
	collider.SetStatus(transform.get_pos(), size.x,
		size.y, transform.get_scale());
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
	transform.move(dire * speed);
	collider.SetStatus(transform.get_pos(), size.x,
		size.y, transform.get_scale());
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
void Bullet::Collision(ObjectBase* obj, Vec2)
{
	if (obj == nullptr)return;
	//敵に当たったら
	if (obj->object_tag == OBJECT_TAG::ENEMY)
	{
		arrow_func();
	}
	//敵か看板の場合はデストロイする
	else if (obj->object_tag == OBJECT_TAG::BOSS || obj->object_tag == OBJECT_TAG::SELECT)
	{
		arrow_func();
		this->Destroy();
	}
	//マップに当たったら
	else if (obj->object_tag == OBJECT_TAG::MAP)
	{
		this->Destroy();
	}
	else if (obj->object_tag == OBJECT_TAG::BOSS_BULLET)
	{
		arrow_func();
		this->Destroy();
	}
}
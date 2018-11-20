/**
* @file bullet.h
* @brief 遠距離武器から出る弾クラスの宣言
* @author 石山　悠
* @date 2018/10/18
*/
#pragma once
#include "../../../base/dynamic/dynamic_object.h"
#include "../../../../collider/square/square_collider.h"
#include "../arrow.h"

/**
* @brief 弾クラス
*/
class Bullet :public DynamicObject
{
	//bool is_
	//当たったときに実行する関数
	std::function<void()> arrow_func;
	//弾速
	static constexpr float speed = 20.0f;
	//弾の寿命（フレーム数）
	static constexpr int life_time = 120;
	//コライダ
	SquareCollider collider;
	//どの方向に向かって飛ぶか
	VEC2 dire;
	//生成されてからの時間
	int life = 0;
protected:
	void InitProcess()final;
	void UpdateProcess()final;
public:
	/**
	* @brief コンストラクタ
	*/
	Bullet() :collider(this, true)
	{
		object_tag = OBJECT_TAG::WEAPON;
	}
	/**
	* @brief コピーコンストラクタ
	*/
	Bullet(const Bullet& b) :collider(this, true)
	{
		this->transform = b.transform;
		this->dire = b.dire;
		this->enabled = b.enabled;
		this->object_tag = b.object_tag;
		this->sprite = b.sprite;
		this->use_gravity = b.use_gravity;
		this->life = b.life;
	}

	/**
	* @brief コピー代入演算子
	*/
	Bullet& operator=(const Bullet& other)
	{
		if (this != &other)
		{
			this->transform = other.transform;
			this->dire = other.dire;
			this->enabled = other.enabled;
			this->object_tag = other.object_tag;
			this->sprite = other.sprite;
			this->use_gravity = other.use_gravity;
			this->life = other.life;
		}
		return *this;
	}

	/**
	* @brief ムーブコンストラクタ
	*/
	Bullet(Bullet&& b) :collider(this, true)
	{
		this->transform = b.transform;
		this->dire = b.dire;
		this->enabled = b.enabled;
		this->object_tag = b.object_tag;
		this->sprite = b.sprite;
		this->use_gravity = b.use_gravity;
		this->life = b.life;
	}

	void BulletInit(const float, const std::function<void()>&);
	void Destroy()final;
	void Collision(ObjectBase*, VEC2)final;

	/**
	* @brief デストラクタ
	*/
	~Bullet()
	{
		Destroy();
	}
};
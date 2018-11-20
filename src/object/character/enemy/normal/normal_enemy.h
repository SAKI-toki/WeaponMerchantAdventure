/**
* @file normal_enemy.h
* @brief ノーマルな敵クラスの宣言
* @author 石山　悠
* @date 2018/10/18
*/
#pragma once
#include "../base/enemy_base.h"

/**
* @brief ノーマルな敵クラス
*/
class NormalEnemy :public EnemyBase
{
	//左に移動しているかどうか
	bool move_left = true;
	//当たったときに方向転換するための一時的に格納する変数
	bool prev_left = true;
	//移動速度
	static constexpr float move_speed = 0.1f;
	static constexpr float max_speed = 2.0f;
protected:
	void InitProcess()final;
	void UpdateProcess()final;
public:
	/**
	* @brief コンストラクタ
	*/
	NormalEnemy() :EnemyBase(ENEMY_TYPE::NORMAL) {}
	/**
	* @brief コピーコンストラクタ
	*/
	NormalEnemy(const NormalEnemy& ne) :EnemyBase(ENEMY_TYPE::NORMAL)
	{
		this->transform = ne.transform;
		this->enabled = ne.enabled;
		this->object_tag = ne.object_tag;
		this->sprite = ne.sprite;
		this->use_gravity = ne.use_gravity;
	}
	/**
	* @brief ムーブコンストラクタ
	*/
	NormalEnemy(NormalEnemy&& ne)noexcept :EnemyBase(ENEMY_TYPE::NORMAL)
	{
		this->transform = ne.transform;
		this->enabled = ne.enabled;
		this->object_tag = ne.object_tag;
		this->sprite = ne.sprite;
		this->use_gravity = ne.use_gravity;
	}
	/**
	* @brief コピー代入演算子
	*/
	NormalEnemy& operator=(const NormalEnemy& other) 
	{
		if (this != &other)
		{
			this->transform = other.transform;
			this->enabled = other.enabled;
			this->object_tag = other.object_tag;
			this->sprite = other.sprite;
			this->use_gravity = other.use_gravity;
			this->collider = other.collider;
			EnemyBase::operator=(other);
		}
		return *this;
	}
	
	void Collision(ObjectBase*,VEC2)final;
	void Destroy()final;

	/**
	* @brief デストラクタ
	*/
	~NormalEnemy()
	{
		Destroy();
	}
};
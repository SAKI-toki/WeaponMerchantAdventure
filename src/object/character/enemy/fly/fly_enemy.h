/**
* @file fly_enemy.h
* @brief 飛ぶエネミークラスの宣言
* @author 石山　悠
* @date 2018/10/22
*/
#pragma once
#include "../base/enemy_base.h"
/**
* @brief 飛ぶエネミークラス
*/
class FlyEnemy :public EnemyBase
{
	//スタートと終わりの間を移動する
	VEC2 start_pos, end_pos, move;
protected:
	void InitProcess()final;
	void UpdateProcess()final;
public:
	/**
	* @brief コンストラクタ
	*/
	FlyEnemy() :EnemyBase(ENEMY_TYPE::FLY) {}
	/**
	* @brief コピーコンストラクタ
	*/
	FlyEnemy(const FlyEnemy& ne) :EnemyBase(ENEMY_TYPE::FLY)
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
	FlyEnemy(FlyEnemy&& ne) :EnemyBase(ENEMY_TYPE::FLY)
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
	FlyEnemy& operator=(const FlyEnemy& other)
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
	void Collision(ObjectBase*, VEC2)final;
	void Destroy()final;

	/**
	* @brief デストラクタ
	*/
	~FlyEnemy()
	{
		Destroy();
	}

	/**
	* @brief 移動範囲を決める
	* @param range 現在の位置からどのくらい移動するか
	* @param time どのくらいの時間をかけて行き来するか
	*/
	void SetMove(const VEC2& range, float time)
	{
		VEC2 _range = range / 2;
		start_pos = VEC2(transform.pos.x - _range.x, transform.pos.y - _range.y);
		end_pos = VEC2(transform.pos.x + _range.x, transform.pos.y + _range.y);
		move = (start_pos - end_pos) / time;
	}
};
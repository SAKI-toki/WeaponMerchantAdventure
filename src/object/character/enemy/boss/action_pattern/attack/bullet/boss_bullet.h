#pragma once
#include "../../../../../../base/dynamic/dynamic_object.h"
#include "../../../../../../../rendering/sprite/sprite.h"
#include "../../../../../../../collider/square/square_collider.h"

class BossBullet :public DynamicObject
{
	SquareCollider collider;
	static constexpr int life_time = 100;
	static constexpr float speed = 15.0f;
	int time = 0;
	VEC2 vector;
protected:
	void InitProcess()final;
	void UpdateProcess()final;
public:
	void SetVector(const VEC2 vec2) { vector = vec2; }
	void Destroy()final;
	BossBullet() :collider(this, true) 
	{
		object_tag = OBJECT_TAG::BOSS;
	}
	BossBullet(const BossBullet& other) :collider(this, true)
	{
		this->time = other.time;
		this->vector = other.vector;
		object_tag = OBJECT_TAG::BOSS;
		this->transform = other.transform;
		this->enabled = other.enabled;
		this->object_tag = other.object_tag;
		this->sprite = other.sprite;
		this->use_gravity = other.use_gravity;
		//DynamicObject::operator=(other);
	}
	/**
	* @brief コピー代入演算子
	*/
	BossBullet& operator=(const BossBullet& other)
	{
		if (this != &other)
		{
			this->time = other.time;
			this->vector = other.vector;
			object_tag = OBJECT_TAG::BOSS;
			this->transform = other.transform;
			this->enabled = other.enabled;
			this->object_tag = other.object_tag;
			this->sprite = other.sprite;
			this->use_gravity = other.use_gravity;
		}
		return *this;
	}

	/**
	* @brief ムーブコンストラクタ
	*/
	BossBullet(BossBullet&& other) :collider(this, true)
	{
		this->time = other.time;
		this->vector = other.vector;
		object_tag = OBJECT_TAG::BOSS;
		this->transform = other.transform;
		this->enabled = other.enabled;
		this->object_tag = other.object_tag;
		this->sprite = other.sprite;
		this->use_gravity = other.use_gravity;
	}
	void Collision(ObjectBase*, VEC2)final;

	~BossBullet()
	{
		Destroy();
	}
};
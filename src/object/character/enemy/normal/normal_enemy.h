#pragma once
#include "../base/enemy_base.h"

class NormalEnemy :public EnemyBase
{
protected:
	void InitProcess()final;
	void UpdateProcess()final;
public:
	/**
	* @brief コンストラクタ
	*/
	NormalEnemy() :EnemyBase(ENEMY_TYPE::NORMAL) {}

	void Collision(ObjectBase*,VEC2)final;
	void Destroy()final;

};
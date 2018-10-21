/**
* @file player.h
* @brief プレイヤークラスを宣言
* @author 石山　悠
* @date 2018/10/18
*/
#pragma once
#include "../../base/dynamic/dynamic_object.h"
#include "../../../collider/square/square_collider.h"
#include "../../weapon/base/weapon_base.h"
#include "../../weapon/sword/sword.h"
#include "../../weapon/arrow/arrow.h"
/**
* @brief 向きの列挙型
*/
enum class DIRE { RIGHT, LEFT };
/**
* @brief プレイヤークラス
*/
class Player :public DynamicObject
{
	//武器
	std::unique_ptr<WeaponBase> weapon[2];
	//武器のナンバー
	int weapon_num = 0;
	//トリガーが押されていたらtrue
	bool current_trigger = false;
	//当たり判定
	SquareCollider collider;
	//移動速度
	static constexpr float speed = 4.0f;
	//ジャンプ時の上方向の加速度
	static constexpr float jump = 10.0f;
	//向き
	DIRE dire = DIRE::RIGHT;
protected:
	void InitProcess()final;
	void UpdateProcess()final;
	void RenderProcess(bool camera_affected)final;
public:
	void Destroy()final;
	/**
	* @brief コンストラクタ
	*/
	Player() :collider(this)
	{
		object_tag = OBJECT_TAG::PLAYER;
		weapon[0] = std::make_unique<Sword>();
		weapon[1] = std::make_unique<Arrow>();
	}
	void Collision(ObjectBase*,VEC2)final;

	/**
	* @brief 攻撃
	*/
	void Attack()
	{
		weapon[weapon_num]->Attack((dire == DIRE::RIGHT ? true : false), transform.pos);
	}
};
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

#include "../../../animation/animation.h"
/**
* @brief 向きの列挙型
*/
enum class DIRE { RIGHT, LEFT };
/**
* @brief プレイヤークラス
*/
class Player :public DynamicObject
{
	Animation anim;
	bool destroy_flg = false;
	//武器
	std::unique_ptr<WeaponBase> weapon[2];
	//武器のナンバー
	int weapon_num = 0;
	//トリガーが押されていたらtrue
	bool current_trigger = false;
	//当たり判定
	SquareCollider collider;
	//移動速度
	static constexpr float speed = 0.3f;
	static constexpr float max_speed = 4.0f;
	//コライダの大きさ
	static constexpr float collider_scale = 0.75f;
	//ジャンプ時の上方向の加速度
	static constexpr float jump = 10.0f;
	//向き
	DIRE dire = DIRE::RIGHT;
	//振動フラグ
	bool vib_r = false, vib_l = false;
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

	void Attack();
};
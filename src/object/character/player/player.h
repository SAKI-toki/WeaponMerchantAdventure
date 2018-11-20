/**
* @file player.h
* @brief プレイヤークラスを宣言
* @author 石山　悠
* @date 2018/11/19
*/
#pragma once
#include "../../base/dynamic/dynamic_object.h"
#include "../../../collider/square/square_collider.h"
#include "../../weapon/base/weapon_base.h"
#include "../../weapon/sword/sword.h"
#include "../../weapon/arrow/arrow.h"
#include "../../../sound/sound.h"

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
	Sprite which_weapon_ui[2];
	Sound jump_sound;
	Animation anim;
	bool destroy_flg = false;
	//武器
	std::unique_ptr<WeaponBase> weapon[2];
	//武器のナンバー
	int weapon_num = 0;
	//rightトリガーが押されていたらtrue
	bool current_trigger_right = false;
	//leftトリガーが押されていたらtrue
	bool current_trigger_left = false;
	//当たり判定
	SquareCollider collider;
	//移動速度
	static constexpr float speed = 0.5f;
	static constexpr float max_speed = 7.0f;
	//コライダの大きさ
	static constexpr float collider_scale = 0.75f;
	//ジャンプ時の上方向の加速度
	static constexpr float jump = 10.0f;
	static constexpr float ui_size = 0.3f;
	//無敵時間
	static constexpr int invincible_time = 60;
	int current_invincible_time = 0;
	bool is_invincible = false;
	//向き
	DIRE dire = DIRE::RIGHT;
	//振動フラグ
	bool vib_r = false, vib_l = false;
protected:
	void InitProcess()final;
	void UpdateProcess()final;
	void RenderProcess(bool camera_affected)final;
public:
	void UiRender()
	{
		which_weapon_ui[0].Render(Transform({ WINDOW_WIDTH - 592 * ui_size,WINDOW_HEIGHT - 592 * ui_size }, 0, ui_size), false, false);
		which_weapon_ui[1].Render(Transform({ 0,WINDOW_HEIGHT - 592 * ui_size }, 0, ui_size), false, false);
	}
	void EnabledWeapon()
	{
		weapon[0]->weapon_enabled = false;
		weapon[1]->weapon_enabled = false;
	}
	void TranslationBossScene()
	{
		weapon[weapon_num]->WeaponDestroy();
	}
	void InBossScene()
	{
		weapon[weapon_num]->WeaponStart();
	}
	void AnimationWalk(bool right)
	{
		anim.ChangeAnimation((right) ? 6 : 2, 10);
	}
	void ClearUpdate()
	{
		anim.Update();
		transform.pos += gravity.AddGravity();
		collider.SetStatus(transform.pos, transform.size.x, transform.size.y, transform.rot, transform.scale*collider_scale);
	}
	void ResetSpeed()
	{
		gravity.ResetSideGravity();
	}
	//ボスシーンに移行するかどうか
	bool boss_scene = false;
	void Destroy()final;
	void UpdateAnimation()
	{
		dire = DIRE::RIGHT;
		anim.ChangeAnimation(6, 10);
		anim.Update();
		transform.pos += gravity.AddGravity();
		if (!destroy_flg)collider.SetStatus(transform.pos, transform.size.x, transform.size.y, transform.rot, transform.scale*collider_scale);
	}
	/**
	* @brief コンストラクタ
	*/
	Player() :collider(this)
	{
		object_tag = OBJECT_TAG::PLAYER;
		weapon[0] = std::make_unique<Sword>();
		weapon[1] = std::make_unique<Arrow>();
	}
	/**
	* @brief ムーブコンストラクタ
	*/
	Player(Player&& other) noexcept :collider(this)
	{
		this->jump_sound = other.jump_sound;
		this->anim = other.anim;
		this->destroy_flg = other.destroy_flg;
		this->collider = other.collider;
		DynamicObject::operator=(other);
	}
	/**
	* @brief コピー代入演算子
	*/
	Player& operator=(const Player& other)
	{
		if (this != &other)
		{
			this->jump_sound = other.jump_sound;
			this->anim = other.anim;
			this->destroy_flg = other.destroy_flg;
			this->collider = other.collider;
			DynamicObject::operator=(other);
		}
		return *this;
	}

	void Collision(ObjectBase*, VEC2)final;

	void Attack();
};
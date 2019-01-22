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
	//やられた時の音
	Sound destroy_sound;
	//アイテムのゲット音
	Sound get_item;
	//不発音
	Sound not_fire;
	//最大弾数
	static constexpr size_t max_bullet = 10;
	//残り弾数
	size_t remaining_bullet = max_bullet;
	//弾のUIの大きさ
	static constexpr float bullet_ui_scale = 1.5f;
	//弾UI
	Sprite bullet_ui[10];
	//+1
	Sprite plus_one;
	//〇
	Sprite circle;
	static constexpr float plus_one_life_time = 30.0f;
	struct po_struct
	{
		po_struct(const Transform& t, const float lt) :transform(t), life_time(lt) {}
		Transform transform; float life_time;
	};
	std::vector<po_struct> plus_one_transform;
	//スラッシュ
	Sprite slash_ui;
	//弾UIの後ろ
	Sprite bullet_back_ui;
	//武器のUI
	Sprite which_weapon_ui[2];
	Sprite LR_ui[2];
	//ジャンプの音
	Sound jump_sound;
	//アニメーション
	Animation anim;
	//破棄フラグ
	bool destroy_flg = false;
	//武器
	std::unique_ptr<WeaponBase> weapon[2];
	//武器のナンバー
	int weapon_num = 1;
	//当たり判定
	SquareCollider collider;
	//移動速度
	static constexpr float speed = 0.5f;
	static constexpr float max_speed = 7.0f;
	//コライダの大きさ
	static constexpr float collider_scale = 0.75f;
	//ジャンプ時の上方向の加速度
	static constexpr float jump = 11.0f;
	static constexpr float ui_size = 0.3f;
	//遷移フラグ
	bool translation_flg = false;
	//向き
	DIRE dire = DIRE::RIGHT;
	//振動フラグ
	bool vib_r = false, vib_l = false;
protected:
	void InitProcess()final;
	void UpdateProcess()final;
	void RenderProcess(bool camera_affected)final;
#ifdef _DEBUG
	float DebugCollisionScale() { return collider_scale; }
#endif 
public:
	//UIの描画
	void UiRender();
	/**
	* @brief 武器の非表示
	*/
	void EnabledWeapon()
	{
		weapon[0]->weapon_enabled = false;
		weapon[1]->weapon_enabled = false;
	}
	/**
	* @brief 武器の表示
	*/
	void EenabledTrueWeapon()
	{
		weapon[0]->weapon_enabled = true;
		weapon[1]->weapon_enabled = true;
	}
	/**
	* @brief ボスシーンに移行するときの処理
	*/
	void TranslationBossScene()
	{
		weapon[weapon_num]->WeaponDestroy();
		EnabledWeapon();
		translation_flg = true;
	}
	/**
	* @brief ボスシーンに入ったときの処理
	*/
	void InBossScene()
	{
		EenabledTrueWeapon();
		weapon[weapon_num]->WeaponStart();
		translation_flg = false;
	}
	/**
	* @brief 歩くアニメーションのみ関数化
	* @param right 右かどうか
	*/
	void AnimationWalk(bool right)
	{
		anim.ChangeAnimation((right) ? 7 : 3, 10);
	}
	/**
	* @brief クリアした時の更新
	*/
	void ClearUpdate()
	{
		anim.Update();
		transform.move(gravity.AddGravity());
		collider.SetStatus(transform.get_pos(), size.x,
			size.y, transform.get_scale()*collider_scale);
	}
	/**
	* @brief 横方向の力を0にする
	*/
	void ResetSpeed()
	{
		gravity.ResetSideGravity();
	}
	//ボスシーンに移行するかどうか
	bool boss_scene = false;
	void Destroy()final;
	/**
	* @brief アニメーションの更新
	*/
	void UpdateAnimation(bool right = true)
	{
		dire = (right) ? DIRE::RIGHT : DIRE::LEFT;
		anim.ChangeAnimation((right) ? 7 : 3, 10);
		anim.Update();
		transform.move(gravity.AddGravity());
		if (!destroy_flg)collider.SetStatus(transform.get_pos(), size.x,
			size.y, transform.get_scale()*collider_scale);
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

	void Collision(ObjectBase*, Vec2)final;

	void Attack();
};
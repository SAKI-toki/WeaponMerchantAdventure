#pragma once
#include "../../../base/dynamic/dynamic_object.h"
#include "../../../../collider/square/square_collider.h"
#include "manager/action_pattern_manager.h"
#include "../../../ui/image/ui_image.h"

class Boss :public DynamicObject
{
	float MAX_HP = 0.0f;
	UiImage ui_hp;
	UiImage ui_hp_back;
	float percentage = 1.0f;
	ActionPatternManager action_pattern_manager;
	int current_time = 0;
	int delay;
	static constexpr float max_speed = 2.0f;
	bool destroy_flg = false;
	bool boss_translation_scene = false;
	bool boss_scene = false;
	float boss_scene_center_pos_x = 0.0f;
	//当たり判定
	SquareCollider collider;
	void SetCenterPosX(const float x)
	{
		boss_scene_center_pos_x = x;
	}
protected:
	void InitProcess()final;
	void UpdateProcess()final;
	void RenderProcess(bool)final;
public:
	void SetMaxHp(float max_hp)
	{
		MAX_HP = max_hp;
		status.Init(MAX_HP, 0, 0);
	}
	void ResetSpeed()
	{
		gravity.ResetSideGravity();
	}
	/**
	* @brief コンストラクタ
	*/
	Boss() :collider(this, true), action_pattern_manager(*this)
	{
		object_tag = OBJECT_TAG::BOSS;
	}
	/**
	* @brief コピーコンストラクタ
	*/
	Boss(const Boss& ne) :collider(this, true), action_pattern_manager(*this)
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
	Boss(Boss&& ne) noexcept :collider(this, true), action_pattern_manager(*this)
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
	Boss& operator=(const Boss& other)
	{
		if (this != &other)
		{
			this->transform = other.transform;
			this->enabled = other.enabled;
			this->object_tag = other.object_tag;
			this->sprite = other.sprite;
			this->use_gravity = other.use_gravity;
			this->collider = other.collider;
		}
		return *this;
	}
	void Collision(ObjectBase*, VEC2)final;
	void Destroy()final;

	void InBossScene(const float x)
	{
		boss_scene = true;
		SetCenterPosX(x);
	}
	void TranslationBossScene()
	{
		boss_translation_scene = true;
		collider.is_trigger = false;
	}
	void DestroyUi()
	{
		ui_hp_back.enabled = false;
		ui_hp.enabled = false;
	}
	/**
	* @brief デストラクタ
	*/
	~Boss()
	{
		Destroy();
	}
};
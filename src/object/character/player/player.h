/**
* @file player.h
* @brief �v���C���[�N���X��錾
* @author �ΎR�@�I
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
* @brief �����̗񋓌^
*/
enum class DIRE { RIGHT, LEFT };
/**
* @brief �v���C���[�N���X
*/
class Player :public DynamicObject
{
	Sprite which_weapon_ui[2];
	Sound jump_sound;
	Animation anim;
	bool destroy_flg = false;
	//����
	std::unique_ptr<WeaponBase> weapon[2];
	//����̃i���o�[
	int weapon_num = 0;
	//right�g���K�[��������Ă�����true
	bool current_trigger_right = false;
	//left�g���K�[��������Ă�����true
	bool current_trigger_left = false;
	//�����蔻��
	SquareCollider collider;
	//�ړ����x
	static constexpr float speed = 0.5f;
	static constexpr float max_speed = 7.0f;
	//�R���C�_�̑傫��
	static constexpr float collider_scale = 0.75f;
	//�W�����v���̏�����̉����x
	static constexpr float jump = 10.0f;
	static constexpr float ui_size = 0.3f;
	//���G����
	static constexpr int invincible_time = 60;
	int current_invincible_time = 0;
	bool is_invincible = false;
	//����
	DIRE dire = DIRE::RIGHT;
	//�U���t���O
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
	//�{�X�V�[���Ɉڍs���邩�ǂ���
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
	* @brief �R���X�g���N�^
	*/
	Player() :collider(this)
	{
		object_tag = OBJECT_TAG::PLAYER;
		weapon[0] = std::make_unique<Sword>();
		weapon[1] = std::make_unique<Arrow>();
	}
	/**
	* @brief ���[�u�R���X�g���N�^
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
	* @brief �R�s�[������Z�q
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
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
	//���ꂽ���̉�
	Sound destroy_sound;
	//�A�C�e���̃Q�b�g��
	Sound get_item;
	//�s����
	Sound not_fire;
	//�ő�e��
	static constexpr size_t max_bullet = 10;
	//�c��e��
	size_t remaining_bullet = max_bullet;
	//�e��UI�̑傫��
	static constexpr float bullet_ui_scale = 1.5f;
	//�eUI
	Sprite bullet_ui[10];
	//+1
	Sprite plus_one;
	//�Z
	Sprite circle;
	static constexpr float plus_one_life_time = 30.0f;
	struct po_struct
	{
		po_struct(const Transform& t, const float lt) :transform(t), life_time(lt) {}
		Transform transform; float life_time;
	};
	std::vector<po_struct> plus_one_transform;
	//�X���b�V��
	Sprite slash_ui;
	//�eUI�̌��
	Sprite bullet_back_ui;
	//�����UI
	Sprite which_weapon_ui[2];
	Sprite LR_ui[2];
	//�W�����v�̉�
	Sound jump_sound;
	//�A�j���[�V����
	Animation anim;
	//�j���t���O
	bool destroy_flg = false;
	//����
	std::unique_ptr<WeaponBase> weapon[2];
	//����̃i���o�[
	int weapon_num = 1;
	//�����蔻��
	SquareCollider collider;
	//�ړ����x
	static constexpr float speed = 0.5f;
	static constexpr float max_speed = 7.0f;
	//�R���C�_�̑傫��
	static constexpr float collider_scale = 0.75f;
	//�W�����v���̏�����̉����x
	static constexpr float jump = 11.0f;
	static constexpr float ui_size = 0.3f;
	//�J�ڃt���O
	bool translation_flg = false;
	//����
	DIRE dire = DIRE::RIGHT;
	//�U���t���O
	bool vib_r = false, vib_l = false;
protected:
	void InitProcess()final;
	void UpdateProcess()final;
	void RenderProcess(bool camera_affected)final;
#ifdef _DEBUG
	float DebugCollisionScale() { return collider_scale; }
#endif 
public:
	//UI�̕`��
	void UiRender();
	/**
	* @brief ����̔�\��
	*/
	void EnabledWeapon()
	{
		weapon[0]->weapon_enabled = false;
		weapon[1]->weapon_enabled = false;
	}
	/**
	* @brief ����̕\��
	*/
	void EenabledTrueWeapon()
	{
		weapon[0]->weapon_enabled = true;
		weapon[1]->weapon_enabled = true;
	}
	/**
	* @brief �{�X�V�[���Ɉڍs����Ƃ��̏���
	*/
	void TranslationBossScene()
	{
		weapon[weapon_num]->WeaponDestroy();
		EnabledWeapon();
		translation_flg = true;
	}
	/**
	* @brief �{�X�V�[���ɓ������Ƃ��̏���
	*/
	void InBossScene()
	{
		EenabledTrueWeapon();
		weapon[weapon_num]->WeaponStart();
		translation_flg = false;
	}
	/**
	* @brief �����A�j���[�V�����̂݊֐���
	* @param right �E���ǂ���
	*/
	void AnimationWalk(bool right)
	{
		anim.ChangeAnimation((right) ? 7 : 3, 10);
	}
	/**
	* @brief �N���A�������̍X�V
	*/
	void ClearUpdate()
	{
		anim.Update();
		transform.move(gravity.AddGravity());
		collider.SetStatus(transform.get_pos(), size.x,
			size.y, transform.get_scale()*collider_scale);
	}
	/**
	* @brief �������̗͂�0�ɂ���
	*/
	void ResetSpeed()
	{
		gravity.ResetSideGravity();
	}
	//�{�X�V�[���Ɉڍs���邩�ǂ���
	bool boss_scene = false;
	void Destroy()final;
	/**
	* @brief �A�j���[�V�����̍X�V
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

	void Collision(ObjectBase*, Vec2)final;

	void Attack();
};
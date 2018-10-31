/**
* @file player.h
* @brief �v���C���[�N���X��錾
* @author �ΎR�@�I
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
* @brief �����̗񋓌^
*/
enum class DIRE { RIGHT, LEFT };
/**
* @brief �v���C���[�N���X
*/
class Player :public DynamicObject
{
	Animation anim;
	bool destroy_flg = false;
	//����
	std::unique_ptr<WeaponBase> weapon[2];
	//����̃i���o�[
	int weapon_num = 0;
	//�g���K�[��������Ă�����true
	bool current_trigger = false;
	//�����蔻��
	SquareCollider collider;
	//�ړ����x
	static constexpr float speed = 0.3f;
	static constexpr float max_speed = 4.0f;
	//�R���C�_�̑傫��
	static constexpr float collider_scale = 0.75f;
	//�W�����v���̏�����̉����x
	static constexpr float jump = 10.0f;
	//����
	DIRE dire = DIRE::RIGHT;
	//�U���t���O
	bool vib_r = false, vib_l = false;
protected:
	void InitProcess()final;
	void UpdateProcess()final;
	void RenderProcess(bool camera_affected)final;
public:
	void Destroy()final;
	/**
	* @brief �R���X�g���N�^
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
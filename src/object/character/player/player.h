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
/**
* @brief �����̗񋓌^
*/
enum class DIRE { RIGHT, LEFT };
/**
* @brief �v���C���[�N���X
*/
class Player :public DynamicObject
{
	//����
	std::unique_ptr<WeaponBase> weapon[2];
	//����̃i���o�[
	int weapon_num = 0;
	//�g���K�[��������Ă�����true
	bool current_trigger = false;
	//�����蔻��
	SquareCollider collider;
	//�ړ����x
	static constexpr float speed = 4.0f;
	//�W�����v���̏�����̉����x
	static constexpr float jump = 10.0f;
	//����
	DIRE dire = DIRE::RIGHT;
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

	/**
	* @brief �U��
	*/
	void Attack()
	{
		weapon[weapon_num]->Attack((dire == DIRE::RIGHT ? true : false), transform.pos);
	}
};
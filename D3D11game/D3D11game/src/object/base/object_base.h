/**
* @file object_base.h
* @brief �I�u�W�F�N�g�̃X�[�p�[�N���X��錾
* @author �ΎR�@�I
* @date 2018/10/11
*/
#pragma once
#include "../../common/common.h"
#include <saki/transform/transform.h>
#include "../../sprite/sprite.h"
#include "../../gravity/gravity.h"
#include "../../status/status.h"

enum class OBJECT_TAG { PLAYER, ENEMY, MAP, WEAPON, BOSS, BOSS_BULLET, BOSS_ZONE, SELECT, BULLET_ITEM, NONE };
/**
* @brief �I�u�W�F�N�g�̃X�[�p�[�N���X
*/
class ObjectBase
{
protected:
	//�e�N�X�`���N���X
	Sprite sprite;
	//���[���h�ł̈ʒu�A��]�A�g��E�k��
	Transform worldTransform;
	//�q�N���X�Œ�`����
	virtual void InitProcess() = 0;
	virtual void RenderProcess(bool) = 0;
	virtual void UpdateProcess() = 0;
#ifdef _DEBUG
	virtual float DebugCollisionScale() { return 1; }
#endif
public:
	Vec2 size;
	//�X�e�[�^�X
	Status status;
	//�d��
	Gravity gravity;
	//�d�͌n�𗘗p���邩�ǂ���
	bool use_gravity;
	//�I�u�W�F�N�g�̃^�O
	OBJECT_TAG object_tag;
	//�X�V�A�`�悷�邩�ǂ���
	bool enabled = true;
	//�ʒu�A��]�A�g��E�k��(���[�J���j
	Transform transform;
	/**
	* @brief �R���X�g���N�^
	*/
	ObjectBase(bool _gravity = false) : use_gravity(_gravity) {}
	/**
	* @brief �R�s�[�R���X�g���N�^
	*/
	ObjectBase(const ObjectBase& other)
	{
		this->size = other.size;
		this->sprite = other.sprite;
		this->status = other.status;
		this->gravity = other.gravity;
		this->use_gravity = other.use_gravity;
		this->object_tag = other.object_tag;
		this->enabled = other.enabled;
		this->transform = other.transform;
	}
	/**
	* @brief �R�s�[������Z�q
	*/
	ObjectBase& operator=(const ObjectBase& other)
	{
		if (this != &other)
		{
			this->size = other.size;
			this->sprite = other.sprite;
			this->status = other.status;
			this->gravity = other.gravity;
			this->use_gravity = other.use_gravity;
			this->object_tag = other.object_tag;
			this->enabled = other.enabled;
			this->transform = other.transform;
		}
		return *this;
	}


	void Init(std::string name, WCHAR* path, const float w, const float h, Vec3 pos,
		Vec3 rot = saki::vector3_zero<float>, Vec3 scale = saki::vector3_one<float>);
	void Update();
	void Render(bool = true, const Transform& = 
		Transform(saki::vector3_zero<float>, saki::vector3_zero<float>, saki::vector3_zero<float>));

	virtual void Destroy() = 0;

	//�|�����[�t�B�Y���𗘗p����Ƃ��̓f�X�g���N�^�͉��z�֐��ɂ���
	virtual ~ObjectBase() {}

	//���������Ƃ��Ɏ��s����֐�
	virtual void Collision(ObjectBase*, Vec2) {}
};
/**
* @file object_base.h
* @brief �I�u�W�F�N�g�̃X�[�p�[�N���X��錾
* @author �ΎR�@�I
* @date 2018/10/11
*/
#pragma once
#include <Windows.h>//for HRESULT
#include "../../transform/transform.h"
#include "../../rendering/sprite/sprite.h"

enum class OBJECT_TAG { PLAYER, ENEMY, NONE };
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
public:
	//�I�u�W�F�N�g�̃^�O
	OBJECT_TAG object_tag;
	//�X�V�A�`�悷�邩�ǂ���
	bool enabled;
	/**
	* @brief �R���X�g���N�^
	*/
	ObjectBase() :enabled(true) {}

	//�ʒu�A��]�A�g��E�k��(���[�J���j
	Transform transform;

	void Init(std::string name, WCHAR* path, const LONG w, const LONG h, VEC2 pos,
		float rot = 0, float scale = 1, bool all_render = true);
	void Update();
	void Render(bool = true, const Transform& = NULL);

	virtual void Destroy() = 0;

	//�|�����[�t�B�Y���𗘗p����Ƃ��̓f�X�g���N�^�͉��z�֐��ɂ���
	virtual ~ObjectBase() {}

	//���������Ƃ��Ɏ��s����֐�
	virtual void Collision(ObjectBase*,VEC2) {}
};
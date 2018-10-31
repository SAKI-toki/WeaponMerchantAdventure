/**
* @file object_base.cpp
* @brief �I�u�W�F�N�g�N���X�̃����o�֐����`
* @author �ΎR�@�I
* @date 2018/10/11
*/
#include "object_base.h"

/**
* @brief ������
* @param name �e�N�X�`�������[�h���邽�߂̃L�[
* @param path �e�N�X�`���̃p�X
* @param w,h �e�N�X�`���̃T�C�Y
* @param pos �����ʒu
* @param rot ��]
* @param scale �g��E�k��
* @param �e�N�X�`�������ׂĕ`�悷�邩�ǂ���
*/
void ObjectBase::Init(std::string name, WCHAR* path, const LONG w, const LONG h,
	VEC2 pos, float rot, float scale)
{
	transform.Init(pos, rot, scale, VEC2(static_cast<float>(w), static_cast<float>(h)),DirectX::SpriteEffects_None);
	sprite.Init(name, path, w, h);
	InitProcess();
}

/**
* @brief �X�V���邩�ǂ������߂�
*/
void ObjectBase::Update()
{
	if (!enabled)return;
	UpdateProcess();
}

/**
* @brief �`�悷�邩�ǂ��������߂�
* @param camera_affected �J�����̈ʒu�ɂ���ĕ`��ʒu��ς��邩�ǂ���
* @param t Transform�N���X
*/
void ObjectBase::Render(bool camera_affected, const Transform& t)
{
	if (!enabled)return;
	worldTransform = t + transform;
	RenderProcess(camera_affected);
}
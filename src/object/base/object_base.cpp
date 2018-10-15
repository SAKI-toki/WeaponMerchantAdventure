/**
* @file object_base.cpp
* @brief �I�u�W�F�N�g�N���X�̃����o�֐����`
* @author �ΎR�@�I
* @date 2018/10/11
*/
#include "object_base.h"

/**
* @brief ������
* @param name map�ŊǗ����邽�߂̃L�[
* @param path �e�N�X�`���̃p�X
* @param w,h �e�N�X�`���̃T�C�Y
* @param pos �����ʒu
* @param rot ��]
* @param scale �T�C�Y
* @param all_render �e�N�X�`�����ׂĂ�`�悷�邩�ǂ���
* @param �e�N�X�`�������ׂĕ`�悷�邩�ǂ���
*/
void ObjectBase::Init(std::string name, WCHAR* path, const LONG w, const LONG h,
	VEC2 pos, float rot, float scale, bool all_render)
{
	transform.Init(pos, rot, scale);
	transform.size = VEC2(static_cast<float>(w), static_cast<float>(h));
	sprite.Init(name, path, all_render, w, h);
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
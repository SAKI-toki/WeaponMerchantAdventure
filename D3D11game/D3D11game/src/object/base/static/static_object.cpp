/**
* @file static_object.cpp
* @brief �����Ȃ��I�u�W�F�N�g�̃X�[�p�[�N���X�̃����o�֐����`
* @author �ΎR�@�I
* @date 2018/10/04
*/
#include "static_object.h"

/**
* @brief �`��
* @param camera_affected �J�����̈ʒu�ɂ���Ĉʒu��ς��邩�ǂ���
*/
void StaticObject::RenderProcess(bool camera_affected)
{
	sprite.Render(transform, camera_affected);
}

void StaticObject::SetColor(const float r, const float g, const float b, const float a)
{
	sprite.ColorChange(r, g, b, a);
}


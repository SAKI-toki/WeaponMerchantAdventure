/**
* @file dynamic_object.cpp
* @brief �����I�u�W�F�N�g�̃X�[�p�[�N���X�̃����o�֐����`
* @author �ΎR�@�I
* @date 2018/10/04
*/
#include "dynamic_object.h"

/**
* @brief �`��
* @param camera_affected �J�����̈ʒu�ɂ���Ĉʒu��ς��邩�ǂ���
*/
void DynamicObject::RenderProcess(bool camera_affected)
{
	sprite.Render(transform, camera_affected);
}
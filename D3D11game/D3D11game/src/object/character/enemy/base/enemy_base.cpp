/**
* @file enemy_base.cpp
* @brief �G�l�~�[�̃X�[�p�[�N���X�̃����o�֐����`
* @author �ΎR�@�I
* @date 2018/10/23
*/
#include "enemy_base.h"

/**
* @brief �`��
* @param camera_affected �J�����̈ʒu�ɂ���ĕ`�悷��ʒu��ς��邩�ǂ���
*/
void EnemyBase::RenderProcess(bool camera_affected)
{
	sprite.Render(transform, camera_affected);
}
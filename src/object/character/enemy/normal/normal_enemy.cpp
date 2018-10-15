#include "normal_enemy.h"

/**
* @brief ������
*/
void NormalEnemy::InitProcess()
{
	collider.SetStatus(transform.pos, transform.size.x, transform.size.y, transform.rot);
}
/**
* @brief �G�l�~�[�̍X�V
*/
void NormalEnemy::UpdateProcess()
{
	transform.pos.y += 1.0f;
	collider.SetStatus(transform.pos, transform.size.x, transform.size.y, transform.rot);
}
/**
* @brief �G�l�~�[�̔j��
*/
void NormalEnemy::Destroy()
{
	if (collider.enabled)collider.Destroy();
}

/**
* @brief �G�l�~�[�̓��������Ƃ��Ɏ��s����֐�
*/
void NormalEnemy::Collision(ObjectBase*,VEC2)
{
	//Destroy();
	//enabled = false;
}
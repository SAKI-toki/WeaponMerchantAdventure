#include "status.h"

bool Status::Damage(const float atk)
{
	//TODO:�����Ń_���[�W�̌v�Z���s��
	HP -= atk;
	return HP <= 0;
}
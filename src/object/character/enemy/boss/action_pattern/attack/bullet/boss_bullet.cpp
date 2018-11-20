#include "boss_bullet.h"

void BossBullet::InitProcess()
{
	collider.SetStatus(transform.pos, transform.size.x, transform.size.y, transform.rot, transform.scale);
}

void BossBullet::UpdateProcess()
{
	if (++time > life_time)
	{
		Destroy();
		return;
	}
	transform.Move(vector * speed);
	collider.SetStatus(transform.pos, transform.size.x, transform.size.y, transform.rot, transform.scale);

}

void BossBullet::Destroy()
{
	if (collider.enabled)collider.Destroy();
	enabled = false;
}

/**
* @brief �������Ă�Ƃ��Ɏ��s����֐�
*/
void BossBullet::Collision(ObjectBase* obj, VEC2)
{
	if (obj == nullptr)return;
	//�}�b�v�ɓ���������
	if (obj->object_tag == OBJECT_TAG::MAP || obj->object_tag == OBJECT_TAG::PLAYER)
	{
		this->Destroy();
	}
}



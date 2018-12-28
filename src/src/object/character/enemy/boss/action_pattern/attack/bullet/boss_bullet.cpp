#include "boss_bullet.h"

void BossBullet::InitProcess()
{
	collider.SetStatus(transform.get_pos(), size.x, size.y,  transform.get_scale());
}

void BossBullet::UpdateProcess()
{
	if (++time > life_time)
	{
		Destroy();
		return;
	}
	transform.move(Vec3(vector.x, vector.y, 0) * speed);
	collider.SetStatus(transform.get_pos(), size.x, size.y, transform.get_scale());

}

void BossBullet::Destroy()
{
	if (collider.enabled)collider.Destroy();
	enabled = false;
}

/**
* @brief �������Ă�Ƃ��Ɏ��s����֐�
*/
void BossBullet::Collision(ObjectBase* obj, Vec2)
{
	if (obj == nullptr)return;
	//�}�b�v�ɓ���������
	if (obj->object_tag == OBJECT_TAG::MAP || obj->object_tag == OBJECT_TAG::PLAYER || obj->object_tag == OBJECT_TAG::WEAPON)
	{
		this->Destroy();
	}
}



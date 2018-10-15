#include "map.h"



/**
* @brief ������
*/
void MapObject::InitProcess()
{
	collider.SetStatus(transform.pos, transform.size.x, transform.size.y, transform.rot);
}
/**
* @brief �}�b�v�̍X�V
*/
void MapObject::UpdateProcess()
{
	collider.SetStatus(transform.pos, transform.size.x, transform.size.y, transform.rot);
}
/**
* @brief �}�b�v�̔j��
*/
void MapObject::Destroy()
{
	if (collider.enabled)collider.Destroy();
}

/**
* @brief �}�b�v���������Ă�Ƃ��Ɏ��s����֐�
*/
void MapObject::Collision(ObjectBase* obj, VEC2 vector)
{
	if (obj->object_tag == OBJECT_TAG::ENEMY)
	{
		//Destroy();
		//enabled = false;
	}
}

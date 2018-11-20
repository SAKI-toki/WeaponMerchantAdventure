#include "select_object.h"
#include "../../input/gamepad/gamepad_input.h"

/**
* @brief ������
*/
void SelectObj::InitProcess()
{
	collider.SetStatus(transform.pos, transform.size.x, transform.size.y, transform.rot, transform.scale);
	//sprite.SetRect(RECT{ 448 + 32,32,479 + 32,63 });
}

/**
* @brief �}�b�v�̍X�V
*/
void SelectObj::UpdateProcess()
{
	collider.SetStatus(transform.pos, transform.size.x, transform.size.y, transform.rot, transform.scale);
}

/**
* @brief �}�b�v�̔j��
*/
void SelectObj::Destroy()
{
	if (collider.enabled)collider.Destroy();
	enabled = false;
}

/**
* @brief �}�b�v���������Ă�Ƃ��Ɏ��s����֐�
*/
void SelectObj::Collision(ObjectBase* obj, VEC2)
{
	if (obj == nullptr)return;
	if (!another_obj_collision&&obj->object_tag == OBJECT_TAG::WEAPON)
	{
		collision_weapon = true;
	}
}
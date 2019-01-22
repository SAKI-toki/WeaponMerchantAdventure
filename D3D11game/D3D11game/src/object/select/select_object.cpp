#include "select_object.h"
#include "../../input/gamepad/gamepad_input.h"

/**
* @brief ������
*/
void SelectObj::InitProcess()
{
	collider.SetStatus(transform.get_pos(), size.x,
		size.y, transform.get_scale());
	//sprite.SetRect(RECT{ 448 + 32,32,479 + 32,63 });
}

/**
* @brief �}�b�v�̍X�V
*/
void SelectObj::UpdateProcess()
{
	collider.SetStatus(transform.get_pos(), size.x,
		size.y, transform.get_scale());
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
void SelectObj::Collision(ObjectBase* obj, Vec2)
{
	if (obj == nullptr)return;
	if (!another_obj_collision&&obj->object_tag == OBJECT_TAG::WEAPON)
	{
		collision_weapon = true;
	}
}
/**
* @file camera.cpp
* @brief �J�����N���X�̃����o�֐����`
* @author �ΎR�@�I
* @date 2018/11/06
*/
#include "camera.h"
#include "../../common/common.h"

/**
* @brief �J�����̒l���󂯎�鏉�����R���X�g���N�^
* @param v2 ����������l
*/
Camera::Camera(const VEC2& v2):
	camera_pos(v2)
{}

/**
* @brief �J�����̈ړ�
* @param v2 �ړ���
*/
void Camera::Move(const VEC2& v2)
{
	camera_pos += v2;
}
/**
* @brief �J�����̈ʒu�ύX
* @param v2 �ʒu
*/
void Camera::SetPos(const VEC2& v2)
{
	camera_pos = v2 - VEC2(WINDOW_WIDTH / 2.0f, WINDOW_HEIGHT / 2.0f);
}

/**
* @brief �J�����̈ʒu���擾
* @return VEC2:�J�����̈ʒu
*/
VEC2 Camera::GetPos()const
{
	return camera_pos;
}

/**
* @brief �J�����̍X�V
*/
void Camera::Update()
{
	if (target != nullptr)
	{
		SetPos(target->transform.pos);
	}
	camera_pos.y = -WINDOW_HEIGHT / 2;
	if (camera_pos.x < 0)camera_pos.x = 0;
}
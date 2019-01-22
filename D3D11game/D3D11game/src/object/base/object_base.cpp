/**
* @file object_base.cpp
* @brief �I�u�W�F�N�g�N���X�̃����o�֐����`
* @author �ΎR�@�I
* @date 2018/10/11
*/
#include "object_base.h"

/**
* @brief ������
* @param name �e�N�X�`�������[�h���邽�߂̃L�[
* @param path �e�N�X�`���̃p�X
* @param w,h �e�N�X�`���̃T�C�Y
* @param pos �����ʒu
* @param rot ��]
* @param scale �g��E�k��
* @param �e�N�X�`�������ׂĕ`�悷�邩�ǂ���
*/
void ObjectBase::Init(std::string name, WCHAR* path, const float w, const float h,
	Vec3 pos, Vec3 rot, Vec3 scale)
{
	transform.set_pos(pos);
	transform.set_rot(rot);
	transform.set_scale(scale);
	size.x = w, size.y = h;
	sprite.Init(name, path, Vec2(w, h));
	InitProcess();
}

/**
* @brief �X�V���邩�ǂ������߂�
*/
void ObjectBase::Update()
{
	if (!enabled)return;
	UpdateProcess();
}
//#define COLLIDER_DEBUG
/**
* @brief �`�悷�邩�ǂ��������߂�
* @param camera_affected �J�����̈ʒu�ɂ���ĕ`��ʒu��ς��邩�ǂ���
* @param t Transform�N���X
*/
void ObjectBase::Render(bool camera_affected, const Transform& t)
{
	if (!enabled)return;
	worldTransform = t + transform;
	RenderProcess(camera_affected); 
#if defined(_DEBUG) && defined(COLLIDER_DEBUG)
	static Sprite debug_sprite;
	static bool first = true;
	if (std::exchange(first, false))
	{
		debug_sprite.Init("ColliderDebug", L"collider_debug.png", Vec2(1, 1));
	}
	debug_sprite.ColorChange(0.0f, 1.0f, 0.0f, 0.8f);
	debug_sprite.Render(Transform{
			transform.get_pos() + Vec3{0,0,-1},
			saki::vector3_zero<float>,
			transform.get_scale()*Vec3(size.x,size.y,1)*DebugCollisionScale()
		});
#endif
}
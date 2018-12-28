/**
* @file animation.cpp
* @brief �A�j���[�V�����N���X�̃����o�֐����`
* @author �ΎR�@�I
* @date 2018/10/29
*/
#include "animation.h"

/**
* @brief ������
* @param _one �������̑傫��
* @param hor ���̐�
* @param ver �c�̐�
* @param _inter ���̊Ԋu
*/
void Animation::Init(const Vec2& _one, const int hor, const int ver, const int _inter)
{
	one_size = _one;
	hor_num = hor;
	ver_num = ver;
	interval = _inter;
}

/**
* @brief �X�V
*/
void Animation::Update()
{
	//���Ԃ������玟�̃A�j���[�V����
	if (++current_time > time)
	{
		current_time = 0;
		//��ԉE�[�܂ŗ�����ŏ��ɖ߂�
		if (++current_hor_num > hor_num)
		{
			current_hor_num = 1;
		}
	}
}

/**
* @brief �A�j���[�V������ύX����
* @return RECT �e�N�X�`���ŕ`�悷�镔��
*/
Vec2 Animation::GetAnimation()const
{
	return { static_cast<float>(current_hor_num),static_cast<float>(current_ver_num)};
}
/**
* @brief �A�j���[�V������ς���
* @param vertical �ォ�牽�Ԗڂ̃A�j���[�V�����ɂ��邩(0�X�^�[�g)
* @param _time ���t���[�����ƂɕύX���邩
* @param reset �A�j���[�V�������ŏ����炷�邩�ǂ���
*/
void Animation::ChangeAnimation(const int vertical, const int _time, const bool reset)
{
	if (current_ver_num == vertical)return;
	current_ver_num = vertical;
	time = _time;
	current_time = 0;
	if (reset)
	{
		current_hor_num = 1;
	}
}
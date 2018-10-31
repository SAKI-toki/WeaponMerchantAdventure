/**
* @file animation.h
* @brief �A�j���[�V�����N���X�̐錾
* @author �ΎR�@�I
* @date 2018/10/29
*/
#pragma once
#include "../transform/transform.h"

/**
* @brief �A�j���[�V�����N���X
*/
class Animation
{
	//��̃T�C�Y
	VEC2 one_size;
	//�c�̐�
	int ver_num;
	//���̐�
	int hor_num;
	//�Ԋu
	int interval;
	//���݂̃A�j���[�V�����̈ʒu
	int current_ver_num = INT_MAX;
	int current_hor_num;
	//���̃A�j���[�V���������鎞��
	int time;
	int current_time = 0;
public:
	void Init(const VEC2&, const int, const int, const int);
	void Update();
	RECT GetAnimation()const;
	void ChangeAnimation(const int, const int, const bool = false);
};
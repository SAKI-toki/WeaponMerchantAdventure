/**
* @file ui_base.h
* @brief ui�̃X�[�p�[�N���X��錾
* @author �ΎR�@�I
* @date 2018/10/15
*/
#pragma once
#include "../../base/dynamic/dynamic_object.h"

/**
* @brief ui�̃X�[�p�[�N���X
*/
class UiBase :public DynamicObject
{
public:
	//�|�����[�t�B�Y���𗘗p����Ƃ��̓f�X�g���N�^�͉��z�֐��ɂ���
	virtual ~UiBase() {}
};
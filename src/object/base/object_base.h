/**
* @file object_base.h
* @brief �I�u�W�F�N�g�̃X�[�p�[�N���X��錾
* @author �ΎR�@�I
* @date 2018/10/05
*/
#pragma once
#include <winnt.h>//for HRESULT
#include "../../transform/transform.h"
#include "../../rendering/sprite/sprite.h"

/**
* @brief �I�u�W�F�N�g�̃X�[�p�[�N���X
*/
class ObjectBase
{
public:
	Transform transform; //�ʒu�A��]�A�g��E�k��
	virtual ~ObjectBase() {}
};
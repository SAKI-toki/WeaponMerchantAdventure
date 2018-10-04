/**
* @file object.h
* @brief �I�u�W�F�N�g�̃X�[�p�[�N���X��錾
* @author �ΎR�@�I
* @date 2018/10/04
*/
#pragma once
#include <winnt.h>//for HRESULT

/**
* @brief �I�u�W�F�N�g�̃X�[�p�[�N���X
*/
class Object
{
public:
	virtual ~Object() {}

	virtual HRESULT Init() = 0;
	virtual void Update() = 0;
	virtual void Render() = 0;
	virtual void Destroy() = 0;
};
/**
* @file character.h
* @brief Character�X�[�p�[�N���X��錾
* @author �ΎR�@�I
* @date 2018/10/07
*/
#pragma once
#include "../../base/object_base.h"

/**
* @brief �L�����N�^�[�֌W�̃X�[�p�[�N���X
*/
class CharacterBase :public ObjectBase
{
protected:
	//TODO:Add Animation,Collider
	Sprite sprite;
	bool enabled;
public:
	CharacterBase();
	virtual ~CharacterBase() {}
	virtual HRESULT Init(WCHAR* path, const LONG w, const LONG h, VEC2 pos, float rot, float scale) = 0;
	virtual void Update() = 0;
	virtual void Render() = 0;
	virtual void Destroy() = 0;
};
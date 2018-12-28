/**
* @file scene_base.h
* @brief �}�l�[�W���[���܂ރV�[���̃X�[�p�[�N���X��錾
* @author �ΎR�@�I
* @date 2018/10/02
*/
#pragma once


/**
* @brief �}�l�[�W���[���܂ރV�[���̃X�[�p�[�N���X
*/
class SceneBase
{
public:
	virtual ~SceneBase() {}

	virtual void Init() = 0;
	virtual void Render() = 0;
	virtual void Destroy() = 0;
};
/**
* @file scene_base.h
* @brief �}�l�[�W���[���܂ރV�[���̃X�[�p�[�N���X��錾
* @author �ΎR�@�I
* @date 2018/10/02
*/
#pragma once

/**
* @brief �V�[���J�ڂ��~���ɂ��邽�߂�enum class
*/
enum class SCENE { TITLE, SELECT, GAME };

/**
* @brief �}�l�[�W���[���܂ރV�[���̃X�[�p�[�N���X
*/
class SceneBase
{
protected:
	SCENE my_scene;
public:
	virtual ~SceneBase() {}

	virtual void Init() = 0;
	virtual void Render() = 0;
	virtual void Destroy() = 0;
};
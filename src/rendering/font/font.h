/**
* @file font.h
* @brief �t�H���g�N���X��錾
* @author �ΎR�@�I
* @date 2018/10/09
*/
#pragma once
#include "manager/font_manager.h"
#include "../../transform/transform.h"
/**
* @brief �t�H���g�p�̐F�\����
*/
struct FontColor
{
	float r, g, b, a;
};

/**
* @brief �t�H���g�N���X
*/
class Font
{
	WCHAR* text;
	const Transform& transform;
	FontColor color;
public:
	//�f�t�H���g�R���X�g���N�^�폜
	Font() = delete;

	Font(const Transform&);

	void Init(WCHAR* _text, float r = 1, float g = 1, float b = 1, float a = 1);
	void Render();

	/**
	* @brief ������̃Z�b�g
	* @param _text �Z�b�g���镶����
	*/
	void SetText(WCHAR* _text) { text = _text; }
	/**
	* @brief �e�L�X�g���擾����
	* @return WCHAR* �e�L�X�g
	*/
	WCHAR* GetText() { return text; }
};
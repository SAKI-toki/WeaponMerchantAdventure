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
	WCHAR text[100];
	Transform transform;
	FontColor color;
public:

	void Init(WCHAR* _text, float r = 0, float g = 0, float b = 0, float a = 1);
	void Render();

	/**
	* @brief ������̃Z�b�g
	* @param _text �Z�b�g���镶����
	*/
	void SetText(WCHAR* _text) { wcscpy_s(text, _text); }
	/**
	* @brief �e�L�X�g���擾����
	* @return WCHAR* �e�L�X�g
	*/
	WCHAR* GetText() { return text; }

	/**
	* @brief �ʒu���Z�b�g
	* @return t �ʒu���]�����܂�
	*/
	void SetTransform(const Transform& t) { transform = t; }
	/**
	* @brief �F��ς���
	* @param r,g,b,a �F
	*/
	void ColorChange(const float r, const float g, const float b, const float a)
	{
		color.r = r; color.g = g; color.b = b; color.a = a;
	}
};
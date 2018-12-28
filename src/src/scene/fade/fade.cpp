/**
* @file fade.cpp
* @brief �t�F�[�h�N���X�̃����o�֐����`
* @author �ΎR�@�I
* @date 2018/10/30
*/
#include "fade.h"
#include "../../sound/bgm/bgm.h"

void Fade::Init()
{
	//���̃e�N�X�`���̓ǂݍ���
	black.Init(std::string("black"), L"black.png", Vec2(1920, 1080));
	black.ColorChange(1.0f, 1.0f, 1.0f, 0.0f);
	transform.set_pos(Vec3(0, 0, -8000));
}

/**
* @brief �X�V
* @param fade_in �t�F�[�h�C�����ǂ���
* @return bool �t�F�[�h�C�����A�E�g���I�������true
*/
bool Fade::Update(const bool fade_in)
{
	//BGM�̃t�F�[�h�C���A�E�g
	BGM::getinstance()->Fade(fade_in);
	//�t�F�[�h�C�����A�E�g�ɂ���ĉ��Z���邩���Z���邩���߂�
	alpha += fade_in ? -FADE_SPEED : FADE_SPEED;
	//0��菬�����Ȃ�����0�ɖ߂��Atrue��Ԃ�
	if (alpha < 0.0f)
	{
		alpha = 0.0f;
		black.ColorChange(1.0f, 1.0f, 1.0f, alpha);
		return true;
	}
	//1���傫���Ȃ�����1�ɖ߂��Atrue��Ԃ�
	else if (alpha > 1.0f)
	{
		alpha = 1.0f;
		black.ColorChange(1.0f, 1.0f, 1.0f, alpha);
		return true;
	}
	//�I����ĂȂ�������false
	black.ColorChange(1.0f, 1.0f, 1.0f, alpha);
	return false;

}

/**
* @brief �`��
*/
void Fade::Render()
{
	black.Render(transform, false);
}

/**
* @brief �j��
*/
void Fade::Destroy()
{

}
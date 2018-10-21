/**
* @file sprite_manager.cpp
* @brief SpriteManager�N���X�̃����o�֐��̒�`
* @author �ΎR�@�I
* @date 2018/10/19
*/
#include "sprite_manager.h"
#include "../../font/manager/font_manager.h"
#include <WICTextureLoader.h>
#include "../../../common/common.h"
#include "../../../object/camera/camera.h"

/**
* @brief ������
*/
void SpriteManager::Init()
{
	m_pSpriteBatch = std::make_unique<DirectX::SpriteBatch>(deviceContext);
	commonState = std::make_unique<DirectX::CommonStates>(GetDevice());
	FontManager::GetInstance()->Init(device, L"resources/font/myfile.spritefont");
}

/**
* @brief �e�N�X�`����ۑ�
* @param name map�ŊǗ����邽�߂̃L�[
* @param path �e�N�X�`��������p�X
*/
void SpriteManager::SetTexture(std::string name, WCHAR* path)
{
	auto itr = textureList.find(name);
	if (itr == end(textureList))
	{
		CP<ID3D11ShaderResourceView> texture;
		WCHAR _path[256];
		wcscpy_s(_path, texture_path);
		wcscat_s(_path, path);
		//�e�N�X�`���̓ǂݍ���
		if (FAILED(DirectX::CreateWICTextureFromFile(device, _path, nullptr, texture.ReleaseAndGetAddressOf())))
		{
			Comment(L"�e�N�X�`�����ǂݍ��߂܂���ł����B", L"sprite.cpp");
		}
		//map�ɑ}��
		textureList.insert(std::make_pair(name, texture));
	}
}

/**
* @brief �`��
* @param transform �ʒu���]�A�g��E�k����
* @param affected_camera �J�����̉e�����󂯂邩�ǂ���
* @param center_axis �Z���^�[�����ɂ��邩�ǂ���
* @param name �L�[
* @param color �F
* @param rect �e�N�X�`���̂ǂ���`�悷�邩�ǂ���
*/
void SpriteManager::Render(const Transform& transform, bool affected_camera, bool center_axis, const std::string& name, const DirectX::XMVECTOR& color, const RECT& rect)
{
	try {
		//�����o�ϐ��ɂ���ƃA���C�����g���ǂ��̂����̂ƌ�����̂ł����ŕϊ�
		//DirectX::XMVECTOR _color = DirectX::XMVectorSet(color.r, color.g, color.b, color.a);
		//�`��
		if (affected_camera)
		{
			SpriteManager::GetInstance()->GetSpriteBatch()->Draw(textureList.at(name).Get(), transform.pos - Camera::GetInstance()->GetPos(), &rect, color, transform.rot, { (center_axis) ? rect.right / 2.0f : 0.0f,(center_axis) ? rect.bottom / 2.0f : 0.0f }, transform.scale);
		}
		else
		{
			SpriteManager::GetInstance()->GetSpriteBatch()->Draw(textureList.at(name).Get(), transform.pos, &rect, color, transform.rot, { (center_axis) ? rect.right / 2.0f : 0.0f,(center_axis) ? rect.bottom / 2.0f : 0.0f }, transform.scale);
		}
	}
	catch (std::exception& e)
	{
		WCHAR str[100];
		auto s = e.what();
		size_t len = 0;
		mbstowcs_s(&len, str, 50, s, _TRUNCATE);
		Comment(str, L"");
	}
}

/**
* @brief �f�X�g���N�^
*/
SpriteManager::~SpriteManager()
{
	if (m_pSpriteBatch)m_pSpriteBatch.reset();
	if (commonState)commonState.reset();
}
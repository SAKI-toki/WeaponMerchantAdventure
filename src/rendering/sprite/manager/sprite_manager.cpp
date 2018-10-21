/**
* @file sprite_manager.cpp
* @brief SpriteManagerクラスのメンバ関数の定義
* @author 石山　悠
* @date 2018/10/19
*/
#include "sprite_manager.h"
#include "../../font/manager/font_manager.h"
#include <WICTextureLoader.h>
#include "../../../common/common.h"
#include "../../../object/camera/camera.h"

/**
* @brief 初期化
*/
void SpriteManager::Init()
{
	m_pSpriteBatch = std::make_unique<DirectX::SpriteBatch>(deviceContext);
	commonState = std::make_unique<DirectX::CommonStates>(GetDevice());
	FontManager::GetInstance()->Init(device, L"resources/font/myfile.spritefont");
}

/**
* @brief テクスチャを保存
* @param name mapで管理するためのキー
* @param path テクスチャがあるパス
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
		//テクスチャの読み込み
		if (FAILED(DirectX::CreateWICTextureFromFile(device, _path, nullptr, texture.ReleaseAndGetAddressOf())))
		{
			Comment(L"テクスチャが読み込めませんでした。", L"sprite.cpp");
		}
		//mapに挿入
		textureList.insert(std::make_pair(name, texture));
	}
}

/**
* @brief 描画
* @param transform 位置や回転、拡大・縮小等
* @param affected_camera カメラの影響を受けるかどうか
* @param center_axis センターを軸にするかどうか
* @param name キー
* @param color 色
* @param rect テクスチャのどこを描画するかどうか
*/
void SpriteManager::Render(const Transform& transform, bool affected_camera, bool center_axis, const std::string& name, const DirectX::XMVECTOR& color, const RECT& rect)
{
	try {
		//メンバ変数にするとアライメントがどうのこうのと言われるのでここで変換
		//DirectX::XMVECTOR _color = DirectX::XMVectorSet(color.r, color.g, color.b, color.a);
		//描画
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
* @brief デストラクタ
*/
SpriteManager::~SpriteManager()
{
	if (m_pSpriteBatch)m_pSpriteBatch.reset();
	if (commonState)commonState.reset();
}
/**
* @file sprite_manger.h
* @brief SpriteManagerクラスの宣言
* @author 石山　悠
* @date 2018/10/04
*/
#pragma once
#include "../../../common/singleton.h"
#include <SpriteBatch.h>
#include <wrl.h>
template<typename T>
using CP = Microsoft::WRL::ComPtr<T>;

/**
* @brief Sprite関係のデバイスや描画時に経由するものを管理するクラス
*/
class SpriteManager :public Singleton<SpriteManager>
{
	//必要なもの
	std::unique_ptr<DirectX::SpriteBatch> m_pSpriteBatch;
	//1度読み込んだものは2回読み込まない
	//パスで管理
	std::unordered_map < WCHAR*, CP<ID3D11ShaderResourceView>> textureList;
	//デバイス
	ID3D11Device* device;
	ID3D11DeviceContext* deviceContext;
public:
	void Init();
	CP<ID3D11ShaderResourceView>& GetTexture(WCHAR*);
	~SpriteManager();


	/**
	* @brief SpriteBatchのゲッタ
	* @return std::unique_ptr<DirectX::SpriteBatch>&
	*/
	std::unique_ptr<DirectX::SpriteBatch>& GetSpriteBatch() { return m_pSpriteBatch; }
	/**
	* @brief ID3D11Deviceのゲッタ
	* @return ID3D11Device*&
	*/
	ID3D11Device*& GetDevice() { return device; }
	/**
	* @brief ID3D11DeviceContextのゲッタ
	* @return ID3D11DeviceContext*&
	*/
	ID3D11DeviceContext*& GetDeviceContext() { return deviceContext; }

	/**
	* @brief 描画をスタート
	*/
	void Start() { m_pSpriteBatch->Begin(); }
	/**
	* @brief 描画を終了
	*/
	void End() { m_pSpriteBatch->End(); }
};
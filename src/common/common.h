/**
* @file common.h
* @brief 定数定義やヘッダのインクルード
* @author 石山　悠
* @date 2018/10/29
*/
#pragma once
#include <Windows.h>
#include <d3d11.h>//先にd3d11.hかd3d12.hをインクルードしないとSimplemath.hがエラー出す
#include <SimpleMath.h>
using VEC2 = DirectX::SimpleMath::Vector2;

namespace
{
	//定数定義
	/*
	inline変数を使用しているためC++17以降のみ有効
	静的な定数式(static constexpr)の場合は自動でinlineがつくが、新しい規格のため、一応明示的にinline宣言する
	将来的(C++20)にはconstexprをconstevalに変更できるところは変更する
	*/
	inline constexpr bool FULL_SCREEN =
#ifdef _DEBUG
		false
#else
		true
#endif
		;
	//フルスクリーンかどうか
	inline constexpr int WINDOW_WIDTH = 1920;//ウィンドウの幅
	inline constexpr int WINDOW_HEIGHT = 1080;//ウィンドウの高さ
	inline constexpr float L_STICK_DEAD_ZONE = 0.3f;//左スティックのデッドゾーン
	inline constexpr float R_STICK_DEAD_ZONE = 0.05f;//右スティックのデッドゾーン
	inline constexpr float TRIGGER_DEAD_ZONE = 0.3f;//トリガーのデッドゾーン
	inline constexpr int MAX_CONTROLLERS = 1;//コントローラーの数
	inline constexpr float DESTROY_Y = 600.0f;//これ以上オブジェクトが下に行ったらデストロイする
	inline constexpr float FADE_SPEED = 0.01f;//フェードイン、アウトする速さ
	inline constexpr LONG BLOCK_TEXTURE_SIZE = 32;//ブロックのテクスチャのサイズ
	inline constexpr float BLOCK_SCALE = 2.0f;//ブロックのScale
	inline constexpr float BLOCK_SIZE = BLOCK_TEXTURE_SIZE * BLOCK_SCALE;//ブロックのサイズ
	//円周率の変数テンプレート
	template<typename T>
	inline constexpr auto PI = static_cast<T>(3.1415926535897932384626433832795);
	inline constexpr WCHAR* texture_path = L"resources/texture/";	//テクスチャのパス
	inline constexpr WCHAR* sound_path = L"resources/sound/";		//サウンドのパス
	inline constexpr WCHAR* csv_path = L"resources/csv/";			//csvのパス
	//メッセージボックスを使いやすくした
	template<typename T1, typename T2 = WCHAR * >
	void Comment(const T1& t1, const T2& t2 = L"")
	{
		MessageBox(NULL, t1, t2, MB_OK);
	}
	void Comment()
	{
		MessageBox(NULL, L"", L"", MB_OK);
	}
	//二点間の距離
	float distance(const VEC2& v1, const VEC2& v2)
	{
		return std::sqrt(
			std::pow(v1.x - v2.x, 2) +
			std::pow(v1.y - v2.y, 2)
		);
	}
}
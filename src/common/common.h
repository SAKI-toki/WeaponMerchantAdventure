/**
* @file common.h
* @brief 定数定義やヘッダのインクルード
* @author 石山　悠
* @date 2018/10/07
*/
#pragma once
namespace
{
	//定数定義
	/*
	inline変数を使用しているためC++17以降のみ有効
	*/
	inline constexpr bool FULL_SCREEN = false;//フルスクリーンかどうか
	inline constexpr int WINDOW_WIDTH = 1920;//ウィンドウの幅
	inline constexpr int WINDOW_HEIGHT = 1080;//ウィンドウの高さ
	inline constexpr float STICK_DEAD_ZONE = 0.3f;//スティックのデッドゾーン
	inline constexpr float TRIGGER_DEAD_ZONE = 0.3f;//トリガーのデッドゾーン
	inline constexpr int MAX_CONTROLLERS = 1;//コントローラーの数
	//円周率の変数テンプレート
	template<typename T>
	inline constexpr auto PI=static_cast<T>(3.1415926535897932384626433832795);
	inline constexpr WCHAR* texture_path = L"resources/texture/";	//テクスチャのパス
	inline constexpr WCHAR* sound_path = L"resources/sound/";		//サウンドのパス
	//メッセージボックスを使いやすくした
	template<typename T1,typename T2>
	void Comment(const T1& t1, const T2& t2)
	{
		MessageBox(NULL, t1, t2, MB_OK);
	}
}
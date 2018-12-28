#pragma once
#pragma warning(disable : 4005) 
#define NOMINMAX
#include <Windows.h>
#include <d3d11.h>
#pragma comment(lib,"d3d11.lib")
#include <d3dcompiler.h>
#pragma comment(lib,"d3dcompiler.lib")
#include <wrl.h>
//スマートポインタ
template<typename T>
using ComPtr = Microsoft::WRL::ComPtr<T>;

#include <saki/pi.h>
#include <saki/vector/vector_2d.h>
#include <saki/vector/vector_3d.h>
#include <saki/vector/vector_4d.h>
#include <saki/transform/transform.h>
#include <DirectXMath.h>
//ベクトル2D
using Vec2 = saki::Vector2<float>;
//ベクトル3D
using Vec3 = saki::Vector3<float>;
//ベクトル4D
using Vec4 = saki::Vector4<float>;
//transform
using Transform = saki::Transform<float>;
//xmfloat2
using Float2 = DirectX::XMFLOAT2;
//xmfloat3
using Float3 = DirectX::XMFLOAT3;
//xmfloat4
using Float4 = DirectX::XMFLOAT4;
//xmvector
using Vector = DirectX::XMVECTOR;
//xmmatrix
using Matrix = DirectX::XMMATRIX;
namespace
{
	//定数定義
	/*
	inline変数を使用しているためC++17以降のみ有効
	静的な定数式(static constexpr)の場合は自動でinlineがつくが、新しい規格のため、一応明示的にinline宣言する
	将来的(C++20)にはconstexprをconstevalに変更できるところは変更する
	*/
	//フルスクリーンかどうか
	inline constexpr bool FULL_SCREEN =
#ifdef _DEBUG
		false
#else
		true
#endif
		;
	inline constexpr int WINDOW_WIDTH = 1920;//ウィンドウの幅
	inline constexpr int WINDOW_HEIGHT = 1080;//ウィンドウの高さ
	inline constexpr WCHAR* APP_NAME = L"Game";//アプリ名
	inline constexpr UINT FPS = 60;//フレームレート
	inline constexpr float FOV = 60.0f;//視野角
	inline constexpr float NEAR_Z = 0.0001f;
	inline constexpr float FAR_Z = 20000.0f; 
	inline constexpr float DESTROY_Y = -600.0f;//これ以上オブジェクトが下に行ったらデストロイする
	inline constexpr float FADE_SPEED = 0.01f;//フェードイン、アウトする速さ
	inline constexpr LONG BLOCK_TEXTURE_SIZE = 32;//ブロックのテクスチャのサイズ
	inline constexpr float BLOCK_SCALE = 2.0f;//ブロックのScale
	inline constexpr float BLOCK_SIZE = BLOCK_TEXTURE_SIZE * BLOCK_SCALE;//ブロックのサイズ
	inline constexpr WCHAR* texture_path = L"resources/texture/";	//テクスチャのパス
	inline constexpr WCHAR* shader_path = L"resources/shader/";		//シェーダーのパス
	inline constexpr WCHAR* sound_path = L"resources/sound/";		//サウンドのパス
	inline constexpr WCHAR* csv_path = L"resources/csv/";			//csvのパス

	//メッセージボックスを使いやすくした
	template<typename T1, typename T2 = WCHAR*>
	void Comment(const T1& t1, const T2& t2 = L"")
	{
		MessageBox(NULL, t1, t2, MB_OK);
	}
	void Comment()
	{
		MessageBox(NULL, L"", L"", MB_OK);
	}
	//二点間の距離
	float distance(const Vec2& v1, const Vec2& v2)
	{
		return std::sqrt(
			std::pow(v1.x - v2.x, 2) +
			std::pow(v1.y - v2.y, 2)
		);
	}
}
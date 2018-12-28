#pragma once
#pragma warning(disable : 4005) 
#define NOMINMAX
#include <Windows.h>
#include <d3d11.h>
#pragma comment(lib,"d3d11.lib")
#include <d3dcompiler.h>
#pragma comment(lib,"d3dcompiler.lib")
#include <wrl.h>
//�X�}�[�g�|�C���^
template<typename T>
using ComPtr = Microsoft::WRL::ComPtr<T>;

#include <saki/pi.h>
#include <saki/vector/vector_2d.h>
#include <saki/vector/vector_3d.h>
#include <saki/vector/vector_4d.h>
#include <saki/transform/transform.h>
#include <DirectXMath.h>
//�x�N�g��2D
using Vec2 = saki::Vector2<float>;
//�x�N�g��3D
using Vec3 = saki::Vector3<float>;
//�x�N�g��4D
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
	//�萔��`
	/*
	inline�ϐ����g�p���Ă��邽��C++17�ȍ~�̂ݗL��
	�ÓI�Ȓ萔��(static constexpr)�̏ꍇ�͎�����inline�������A�V�����K�i�̂��߁A�ꉞ�����I��inline�錾����
	�����I(C++20)�ɂ�constexpr��consteval�ɕύX�ł���Ƃ���͕ύX����
	*/
	//�t���X�N���[�����ǂ���
	inline constexpr bool FULL_SCREEN =
#ifdef _DEBUG
		false
#else
		true
#endif
		;
	inline constexpr int WINDOW_WIDTH = 1920;//�E�B���h�E�̕�
	inline constexpr int WINDOW_HEIGHT = 1080;//�E�B���h�E�̍���
	inline constexpr WCHAR* APP_NAME = L"Game";//�A�v����
	inline constexpr UINT FPS = 60;//�t���[�����[�g
	inline constexpr float FOV = 60.0f;//����p
	inline constexpr float NEAR_Z = 0.0001f;
	inline constexpr float FAR_Z = 20000.0f; 
	inline constexpr float DESTROY_Y = -600.0f;//����ȏ�I�u�W�F�N�g�����ɍs������f�X�g���C����
	inline constexpr float FADE_SPEED = 0.01f;//�t�F�[�h�C���A�A�E�g���鑬��
	inline constexpr LONG BLOCK_TEXTURE_SIZE = 32;//�u���b�N�̃e�N�X�`���̃T�C�Y
	inline constexpr float BLOCK_SCALE = 2.0f;//�u���b�N��Scale
	inline constexpr float BLOCK_SIZE = BLOCK_TEXTURE_SIZE * BLOCK_SCALE;//�u���b�N�̃T�C�Y
	inline constexpr WCHAR* texture_path = L"resources/texture/";	//�e�N�X�`���̃p�X
	inline constexpr WCHAR* shader_path = L"resources/shader/";		//�V�F�[�_�[�̃p�X
	inline constexpr WCHAR* sound_path = L"resources/sound/";		//�T�E���h�̃p�X
	inline constexpr WCHAR* csv_path = L"resources/csv/";			//csv�̃p�X

	//���b�Z�[�W�{�b�N�X���g���₷������
	template<typename T1, typename T2 = WCHAR*>
	void Comment(const T1& t1, const T2& t2 = L"")
	{
		MessageBox(NULL, t1, t2, MB_OK);
	}
	void Comment()
	{
		MessageBox(NULL, L"", L"", MB_OK);
	}
	//��_�Ԃ̋���
	float distance(const Vec2& v1, const Vec2& v2)
	{
		return std::sqrt(
			std::pow(v1.x - v2.x, 2) +
			std::pow(v1.y - v2.y, 2)
		);
	}
}
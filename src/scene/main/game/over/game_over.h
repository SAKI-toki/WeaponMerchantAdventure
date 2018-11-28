/**
* @file game_over.h
* @brief �Q�[���I�[�o�[�V�[���̒�`
* @author �ΎR�@�I
* @date 2018/11/26
*/
#pragma once
#include "../../../../common/saki/singleton/singleton.h"
#include "../../../../rendering/font/font.h"
#include "../../../../rendering/sprite/sprite.h"
#include "../../../scene.h"
#include <vector>

/**
* @brief �Q�[���I�[�o�[�N���X
*/
class GameOver :public saki::singleton<GameOver>
{
	//���邳�֌W
	float brightness = (brightness_uplimit + brightness_downlimit) * 0.5f;
	static constexpr float brightness_downlimit = 0.8f;
	static constexpr float brightness_uplimit = 1.0f;
	//���邳�����݉������Ă��邩�ǂ���
	bool bright_down = false;
	//�ŏ����ǂ����̃t���O
	bool first = true;
	//�����x�̏��
	static constexpr float alpha_limit = 0.7f;
	//�����x(Fade)
	float alpha = 0.0f;
	//�f�B���C
	static constexpr int delay = 120;
	//�f�B���C���v�����邽�߂̕ϐ�
	int time = 0;
	//�e�N�X�`��
	Sprite black;
	Sprite game_over;
	Sprite next_scene[3];
	Sprite blood;
	//�������I�����Ă���g�̔ԍ�
	int current_select = 0;
	bool upflg = false;
	bool downflg = false;
	//�`�悷�邩�ǂ���
	bool rendering_flg = false;
	//���̈ʒu�Ƒ傫����\���\����
	struct blood_status
	{
		VEC2 pos;
		float scale;
	};
	//���̈ʒu�Ƒ傫�����i�[����vector
	std::vector<blood_status> blood_pos;
	//���̌���������܂ł̎���
	int blood_time = 0;
	//���݂̎���
	int current_blood_time = 0;
public:
	void Init();
	/**
	* @brief �l�����Z�b�g����
	*/
	void Reset()
	{
		alpha = 0.0f;
		current_select = 0;
		time = 0; 
		upflg = false;
		downflg = false;
		first = true;
		next_scene[0].ColorChange(1.0f, 1.0f, 1.0f, 1.0f);
		next_scene[1].ColorChange(0.4f, 0.4f, 0.4f, 1.0f);
		next_scene[2].ColorChange(0.4f, 0.4f, 0.4f, 1.0f);
		rendering_flg = false;
		blood_pos.clear();
	}
	/**
	* @brief �t�F�[�h���ɐF���Z�b�g����
	*/
	void SetColor()
	{
		black.ColorChange(1.0f, 1.0f, 1.0f, alpha);
		game_over.ColorChange(1.0f, 0.0f, 0.0f, alpha);
	}
	void Update(std::shared_ptr<Scene>&, std::shared_ptr<Scene>&&);
	void Render();
};
/**
* @file game_scene_base.h
* @brief �Q�[���V�[���̃X�[�p�[�N���X�̐錾
* @author �ΎR�@�I
* @date 2018/11/26
*/
#pragma once
#include "../../../scene.h"
#include "../../../../object/base/static/static_object.h"
#include "../../../../object/map/map.h"
#include "../../../../object/character/player/player.h"
#include "../../../../object/character/enemy/normal/normal_enemy.h"
#include "../../../../object/character/enemy/fly/fly_enemy.h"
#include "../../../../object/character/enemy/boss/boss.h"
#include "../../../../object/item/bullet/bullet_item.h"
#include <list>
#include <vector>

/**
* @brief �Q�[���V�[���̃X�[�p�[�N���X
*/
class GameSceneBase
{
private:
	float camera_prev_x = 0.0f;
public:
	//�N���A�̃W�����v���I��������ǂ���
	bool clear_jump = false;
	//�Q�[���̏�ʂ̗񋓁i�X�e�[�g�}�V���ɂ��悤�Ƃ������A���ʂ̃��\�[�X���g�p���邽��switch�Ɂj
	enum class GAME { MAIN, TRANSLATION, BOSS, CLEAR, NONE };
	//���ǂ̏�ʂ��i�[����
	GAME current_game = GAME::MAIN;
	//��΂Ȃ��G
	std::list<NormalEnemy> enemy;
	//��ԓG
	std::list<FlyEnemy> f_enemy;
	//�v���C���[
	std::unique_ptr<Player> player;
	//�{�X
	std::unique_ptr<Boss> boss;
	//�w�i
	std::vector<StaticObject> backGround;
	//�}�b�v
	std::vector<MapObject> field;
	//�A�C�e��
	std::list<BulletItem> bullet_item;
	//�{�X�Ɛ퓬����Ƃ��̒����ʒu���J�����ʒu
	float boss_center_x;
	//�Q�[���̏�����
	void GameInit();
	//�Q�[���̍X�V
	std::shared_ptr<Scene> GameUpdate(std::shared_ptr<Scene>&);
	//�Q�[���̕`��
	void GameRender();
	//�Q�[���̔j��
	void GameDestroy();
};
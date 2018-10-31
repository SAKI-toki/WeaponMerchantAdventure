/**
* @file collider_manager.h
* @brief コライダを管理するクラスを宣言
* @author 石山　悠
* @date 2018/10/15
*/
#pragma once
#include "../../common/singleton.h"
#include "../square/square_collider.h"
#include <vector>


/**
* @brief コライダを管理するクラス
*/
class ColliderManager :public Singleton<ColliderManager>
{
private:
	/**
	* @brief 四角コライダ自信と1フレーム前の位置と今の位置を格納
	*/
	struct SquarePosCol
	{
		SquareCollider* col;
		VEC2 prev_pos;
		VEC2 current_pos;
		SquarePosCol() {}
		SquarePosCol(const SquarePosCol& spc)
		{
			col = spc.col;
			prev_pos = spc.prev_pos;
			current_pos = spc.current_pos;
		}
	};
	//静的オブジェクトの四角形コライダ
	std::vector<SquarePosCol> staticSquareColliderList;

	//動的オブジェクトの四角形コライダ
	std::vector<SquarePosCol> dynamicSquareColliderList;
protected:
	//当たっているか判定する関数
	bool CompareCollision(SquarePosCol&, SquarePosCol&,bool);
public:
	//上のstd::vectorにセットする関数
	void SetCollider(SquareCollider*, bool is_static);
	//全てを走査する関数
	void CheckCollision();
	//指定した要素を削除
	void DeleteCollider(SquareCollider*);
	//シーン遷移の時にすべてのコライダを削除する
	void Reset();

};
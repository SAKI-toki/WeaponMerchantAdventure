/**
* @file collider_manager.cpp
* @brief コライダを管理するクラスのメンバ関数を定義
* @author 石山　悠
* @date 2018/10/15
*/

#include "collider_manager.h"
#include "../../common/common.h"

/**
* @brief 四角形コライダを配列に格納する
* @param obj 四角形コライダ
* @param is_static 静的か動的か
*/
void ColliderManager::SetCollider(SquareCollider* obj, bool is_static)
{
	SquarePosCol spc;
	spc.col = obj;
	//不都合が起きないように初期化として1フレーム前にも今の位置を格納する
	spc.current_pos = obj->GetStatus().center_pos;
	spc.prev_pos = spc.current_pos;
	if (is_static)
	{
		staticSquareColliderList.push_back(spc);
	}
	else
	{
		dynamicSquareColliderList.push_back(spc);
	}
}

/**
* @brief 全てのコライダを走査する
*/
void ColliderManager::CheckCollision()
{
	//全てのコライダを走査してから関数を実行するため、一時的に格納する場所
	std::vector <std::pair<std::function<void(ObjectBase*, VEC2)>, SquarePosCol>> vec;
	//前の位置を格納
	for (auto&& sc : staticSquareColliderList)
	{
		sc.prev_pos = sc.current_pos;
	}
	for (auto&& dc : dynamicSquareColliderList)
	{
		dc.prev_pos = dc.current_pos;
		dc.col->collision_is_trigger_x = false;
		dc.col->collision_is_trigger_y = false;
	}
	//静的なオブジェクトと動的なオブジェクトの当たり判定
	for (auto&& sobj : staticSquareColliderList)
	{
		if (sobj.col->enabled)
		{
			for (auto&& dobj : dynamicSquareColliderList)
			{
				if (dobj.col->enabled)
				{
					//比べる
					if (CompareCollision(sobj, dobj))
					{
						//ヒット
						//関数を格納する
						vec.push_back(std::make_pair(dobj.col->collision_func, sobj));
						vec.push_back(std::make_pair(sobj.col->collision_func, dobj));
					}
				}
			}
		}
	}
	//動的なオブジェクト同士の当たり判定
	/*
	本当はコメントアウトしているところで-1したほうが処理が少なくて済むが、
	配列の中身が0の時にエラーが発生してしまうため削除してる
	*/
	for (auto dc1 = std::begin(dynamicSquareColliderList); dc1 != std::end(dynamicSquareColliderList)/*-1*/; ++dc1)
	{
		if (dc1->col->enabled)
		{
			for (auto dc2 = dc1 + 1; dc2 != std::end(dynamicSquareColliderList); ++dc2)
			{
				if (dc2->col->enabled)
				{
					//比べる
					if (CompareCollision(*dc1, *dc2))
					{
						//ヒット
						//関数を格納する
						vec.push_back(std::make_pair(dc1->col->collision_func, *dc2));
						vec.push_back(std::make_pair(dc2->col->collision_func, *dc1));
					}
				}
			}
		}
	}

	//ぶつかったオブジェクトの関数を実行
	for (const auto& func : vec)
	{
		func.first(func.second.col->object, func.second.col->GetStatus().center_pos - func.second.prev_pos);
	}
	//現在の位置を格納
	for (auto&& sc : staticSquareColliderList)
	{
		sc.current_pos = sc.col->GetStatus().center_pos;
	}
	for (auto&& dc : dynamicSquareColliderList)
	{
		dc.current_pos = dc.col->GetStatus().center_pos;
	}
}

/**
* @brief 四角形同士が当たっているかを判定する
* @param col1,col2 比べる二つの四角形コライダ
* @return bool 当たっているかどうか
*/
bool ColliderManager::CompareCollision(SquarePosCol& col1, SquarePosCol& col2)
{
	/*
	decltype(auto)
	参照かどうかも推論してくれる（autoだと参照ではなく、コピーしてしまいパフォーマンスが落ちる）
	*/
	decltype(auto) status1 = col1.col->GetStatus();
	decltype(auto) status2 = col2.col->GetStatus();

	//これ以上離れていたら絶対に当たらない値を取得する
	//◇◇このお互いの中心から中心の距離を求める
	float maxDistance = std::sqrt(std::pow(status1.width, 2) + std::pow(status1.height, 2)) +
		std::sqrt(std::pow(status2.width, 2) + std::pow(status2.height, 2));

	//絶対に当たらない値より多い場合当たらないのでfalse
	if (std::abs(status1.center_pos.x - status2.center_pos.x) > maxDistance ||
		std::abs(status1.center_pos.y - status2.center_pos.y) > maxDistance)
	{
		return false;
	}
	//横の合計
	auto sum_width = status1.width + status2.width;
	//縦の合計
	auto sum_height = status1.height + status2.height;
	//TODO:回転を考慮する
	//当たったかどうかの判定
	if (std::abs(status1.center_pos.x - status2.center_pos.x) < sum_width&&
		std::abs(status1.center_pos.y - status2.center_pos.y) < sum_height)
	{
		//ベクトル
		auto col1vec = col1.col->GetStatus().center_pos - col1.prev_pos;
		auto col2vec = col2.col->GetStatus().center_pos - col2.prev_pos;
		//1フレーム前にx座標が当たっているかどうか
		if (std::abs(col1.prev_pos.x - col2.prev_pos.x) < sum_width)
		{
			//どちらも押し出す場合
			if (!col1.col->is_trigger && !col2.col->is_trigger && !col1.col->collision_is_trigger_y && !col2.col->collision_is_trigger_y)
			{
				//押し出す量（どちらも押し出すため半分）
				auto diff = (sum_height - std::abs(status1.center_pos.y - status2.center_pos.y)) / 2.0f;
				//半分ずつぶつかってる値を位置から引く
				col1.col->CollisionExtrusion(VEC2(
					col1.col->GetStatus().center_pos.x,
					(col1.prev_pos.y > col2.prev_pos.y) ?
					col1.col->GetStatus().center_pos.y + diff :
					col1.col->GetStatus().center_pos.y - diff));
				col2.col->CollisionExtrusion(VEC2(
					col2.col->GetStatus().center_pos.x,
					(col2.prev_pos.y > col1.prev_pos.y) ?
					col2.col->GetStatus().center_pos.y + diff :
					col2.col->GetStatus().center_pos.y - diff));
			}
			//片方が押し出す場合
			else if (!(col1.col->is_trigger&&col2.col->is_trigger))
			{
				//押し出す量
				auto diff = sum_height - std::abs(status1.center_pos.y - status2.center_pos.y);
				//is_triggerじゃないほうをターゲットにする
				decltype(auto) target_col = ((col1.col->is_trigger || col1.col->collision_is_trigger_y) ? col2 : col1);
				if (!target_col.col->collision_is_trigger_y)
				{
					//y方向をこれ以上動かさないためにする
					target_col.col->collision_is_trigger_y = true;
					//ターゲットじゃないほうも格納
					decltype(auto) not_target_col = (!(col1.col->is_trigger || col1.col->collision_is_trigger_y) ? col1 : col2);
					//ターゲットのみ押し出す処理をするため押し出す量全て受ける
					target_col.col->CollisionExtrusion(VEC2(
						target_col.col->GetStatus().center_pos.x,
						(target_col.prev_pos.y > not_target_col.prev_pos.y) ?
						target_col.col->GetStatus().center_pos.y + diff :
						target_col.col->GetStatus().center_pos.y - diff));
				}

			}
			//どちらも押し出さない場合何も処理しない
			//else {}
		}
		//1フレーム前にy座標が当たっているかどうか
		if (std::abs(col1.prev_pos.y - col2.prev_pos.y) < sum_height)
		{
			//どちらも押し出す場合
			if (!col1.col->is_trigger && !col2.col->is_trigger && !col1.col->collision_is_trigger_x && !col2.col->collision_is_trigger_x)
			{
				//押し出す量（どちらも押し出すため半分）
				auto diff = (sum_width - std::abs(status1.center_pos.x - status2.center_pos.x)) / 2.0f;
				//半分ずつぶつかってる値を位置から引く
				col1.col->CollisionExtrusion(VEC2(
					(col1.prev_pos.x > col2.prev_pos.x) ?
					col1.col->GetStatus().center_pos.x + diff :
					col1.col->GetStatus().center_pos.x - diff,
					col1.col->GetStatus().center_pos.y));
				col2.col->CollisionExtrusion(VEC2(
					(col2.prev_pos.x > col1.prev_pos.x) ?
					col2.col->GetStatus().center_pos.x + diff :
					col2.col->GetStatus().center_pos.x - diff,
					col2.col->GetStatus().center_pos.y));
			}
			//片方が押し出す場合
			else if (!(col1.col->is_trigger&&col2.col->is_trigger))
			{
				//押し出す量
				auto diff = sum_width - std::abs(status1.center_pos.x - status2.center_pos.x);
				//is_triggerじゃないほうをターゲットにする
				decltype(auto) target_col = ((col1.col->is_trigger || col1.col->collision_is_trigger_x) ? col2 : col1);
				if (!target_col.col->collision_is_trigger_x)
				{
					//x方向をこれ以上動かさないためにする
					target_col.col->collision_is_trigger_x = true;
					//ターゲットじゃないほうも格納
					decltype(auto) not_target_col = (!(col1.col->is_trigger || col1.col->collision_is_trigger_x) ? col1 : col2);
					//ターゲットのみ押し出す処理をするため押し出す量全て受ける
					target_col.col->CollisionExtrusion(VEC2(
						(target_col.prev_pos.x > not_target_col.prev_pos.x) ?
						target_col.col->GetStatus().center_pos.x + diff :
						target_col.col->GetStatus().center_pos.x - diff,
						target_col.col->GetStatus().center_pos.y));
				}

			}
			//どちらも押し出さない場合何も処理しない
			//else {}
		}
		return true;
	}

	return false;

}

/**
* @brief 四角形コライダの削除
* @param col 四角形コライダ
*/
void ColliderManager::DeleteCollider(SquareCollider* col)
{
	for (auto itr = std::begin(staticSquareColliderList); itr != std::cend(staticSquareColliderList); ++itr)
	{
		//一致したら削除
		if (itr->col == col)
		{
			staticSquareColliderList.erase(itr);
			return;
		}
	}

	for (auto itr = std::begin(dynamicSquareColliderList); itr != std::cend(dynamicSquareColliderList); ++itr)
	{
		//一致したら削除
		if (itr->col == col)
		{
			dynamicSquareColliderList.erase(itr);
			return;
		}
	}
}
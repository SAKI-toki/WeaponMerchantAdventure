/**
* @file collider_manager.cpp
* @brief コライダを管理するクラスのメンバ関数を定義
* @author 石山　悠
* @date 2018/10/15
*/

#include "collider_manager.h"
#include "../../common/common.h"
#include <queue>

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
	std::queue<std::pair<std::function<void(ObjectBase*, VEC2)>, SquarePosCol>> func_queue;

#ifdef _DEBUG
	count = 0; 
	count = staticSquareColliderList.size() + dynamicSquareColliderList.size();
#endif

	//前の位置を格納
	for (auto&& sc : staticSquareColliderList)
	{
		sc.prev_pos = sc.current_pos;
	}
	for (auto&& dc : dynamicSquareColliderList)
	{
		dc.prev_pos = dc.current_pos;
		dc.col->collision_is_static_x = false;
		dc.col->collision_is_static_y = false;
	}
	//静的なオブジェクトと動的なオブジェクトの当たり判定
	for (auto&& sobj : staticSquareColliderList)
	{
		if (sobj.col->enabled&&DistancePlayer(sobj.col->object))
		{
			for (auto&& dobj : dynamicSquareColliderList)
			{
				if (dobj.col->enabled&&DistancePlayer(dobj.col->object))
				{
					//比べる
					if (CompareCollision(sobj, dobj, true))
					{
						//ヒット
						//関数を格納する
						func_queue.push(std::make_pair(dobj.col->collision_func, sobj));
						func_queue.push(std::make_pair(sobj.col->collision_func, dobj));
					}
				}
			}
		}
	}
	//動的なオブジェクト同士の当たり判定
	for (auto dc1 = std::begin(dynamicSquareColliderList); dc1 != std::end(dynamicSquareColliderList); ++dc1)
	{
		if (dc1->col->enabled&&DistancePlayer(dc1->col->object))
		{
			for (auto dc2 = dc1 + 1; dc2 != std::end(dynamicSquareColliderList); ++dc2)
			{
				if (dc2->col->enabled&&DistancePlayer(dc2->col->object))
				{
					//比べる
					if (CompareCollision(*dc1, *dc2, false))
					{
						//ヒット
						//関数を格納する
						func_queue.push(std::make_pair(dc1->col->collision_func, *dc2));
						func_queue.push(std::make_pair(dc2->col->collision_func, *dc1));
					}
				}
			}
		}
	}


	while (!func_queue.empty())
	{
		try
		{
			//ないオブジェクトを参照しないようにする
			//volatileというには最適化させないための修飾子
			//[[maybe_unused]]属性というのは意図的に未使用の要素を定義していることをコンパイラに伝え、警告を抑制するための属性
			[[maybe_unused]]volatile auto temp = func_queue.front().second.col->object->enabled;
			if (func_queue.front().second.col->object == nullptr)
			{
				throw;
			}
			func_queue.front().first(func_queue.front().second.col->object, func_queue.front().second.col->GetStatus().center_pos - func_queue.front().second.prev_pos);
		}
		catch (...)
		{
#ifdef _DEBUG
			Comment(L"ないオブジェクトを参照", L"collider_manager.cpp");
#endif
		}
		func_queue.pop();
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
* @param col1_static スタティックかどうか
* @return bool 当たっているかどうか
*/
bool ColliderManager::CompareCollision(SquarePosCol& col1, SquarePosCol& col2, bool col1_static)
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
		//どちらもtriggerなら当たったことのみ返す
		if (col1.col->is_trigger || col2.col->is_trigger)
		{
			return true;
		}
		//どちらもENEMYなら当たったことのみ返す
		if (col1.col->object->object_tag == OBJECT_TAG::ENEMY&&
			col2.col->object->object_tag == OBJECT_TAG::ENEMY)
		{
			return true;
		}

		//ベクトル
		auto col1vec = col1.col->GetStatus().center_pos - col1.prev_pos;
		auto col2vec = col2.col->GetStatus().center_pos - col2.prev_pos;
		//1フレーム前にx座標が当たっているかどうか
		if (std::abs(col1.prev_pos.x - col2.prev_pos.x) < sum_width)
		{
			//どちらも押し出す場合
			if (!col1_static && !col1.col->collision_is_static_y && !col2.col->collision_is_static_y)
			{
				//押し出す量（どちらも押し出すため半分）
				//floatの誤差を防ぐために+0.001fしている
				auto diff = (sum_height - std::abs(status1.center_pos.y - status2.center_pos.y) + 0.001f)  *0.5f;
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
			else if (col1_static || !col1.col->collision_is_static_y || !col2.col->collision_is_static_y)
			{
				//is_triggerじゃないほうをターゲットにする
				decltype(auto) target_col = ((col1.col->collision_is_static_y || col1_static) ? col2 : col1);
				if (!target_col.col->collision_is_static_y)
				{
					//押し出す量
					//floatの誤差を防ぐために+0.001fしている
					auto diff = sum_height - std::abs(status1.center_pos.y - status2.center_pos.y) + 0.001f;
					//ターゲットじゃないほうも格納
					decltype(auto) not_target_col = (!(col1.col->collision_is_static_y || col1_static) ? col2 : col1);
					//y方向をこれ以上動かさないためにする
					target_col.col->collision_is_static_y = true;
					//ターゲットのみ押し出す処理をするため押し出す量全て受ける
					target_col.col->CollisionExtrusion(VEC2(
						target_col.col->GetStatus().center_pos.x,
						(target_col.prev_pos.y > not_target_col.prev_pos.y) ?
						target_col.col->GetStatus().center_pos.y + diff :
						target_col.col->GetStatus().center_pos.y - diff));
					//重力関係
					if (target_col.col->object->use_gravity)
					{
						//足が着いたら重力リセット
						if (target_col.prev_pos.y < not_target_col.prev_pos.y)
						{
							target_col.col->object->gravity.ResetGravity();
						}
						//頭が当たったら落下に切り替え
						else
						{
							target_col.col->object->gravity.HitHead();
						}
					}
				}
			}
			//どちらも押し出さない場合何も処理しない
			//else {}
		}
		//1フレーム前にy座標が当たっているかどうか
		if (std::abs(col1.prev_pos.y - col2.prev_pos.y) < sum_height)
		{
			//どちらも押し出す場合
			if (!col1_static && !col1.col->collision_is_static_x && !col2.col->collision_is_static_x)
			{
				//押し出す量（どちらも押し出すため半分）
				//floatの誤差を防ぐために+0.001fしている
				auto diff = (sum_width - std::abs(status1.center_pos.x - status2.center_pos.x) + 0.001f) *0.5f;
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
			else if (col1_static || !col1.col->collision_is_static_x || !col2.col->collision_is_static_x)
			{
				//is_triggerじゃないほうをターゲットにする
				decltype(auto) target_col = ((col1.col->collision_is_static_x || col1_static) ? col2 : col1);
				if (!target_col.col->collision_is_static_x)
				{
					//押し出す量
					//floatの誤差を防ぐために+0.001fしている
					auto diff = sum_width - std::abs(status1.center_pos.x - status2.center_pos.x) + 0.001f;
					//ターゲットじゃないほうも格納
					decltype(auto) not_target_col = (!(col1.col->collision_is_static_x || col1_static) ? col2 : col1);
					//x方向をこれ以上動かさないためにする
					target_col.col->collision_is_static_x = true;
					//ターゲットのみ押し出す処理をするため押し出す量全て受ける
					target_col.col->CollisionExtrusion(VEC2(
						(target_col.prev_pos.x > not_target_col.prev_pos.x) ?
						target_col.col->GetStatus().center_pos.x + diff :
						target_col.col->GetStatus().center_pos.x - diff,
						target_col.col->GetStatus().center_pos.y));
					//重力関係
					if (target_col.col->object->use_gravity)
					{
						target_col.col->object->gravity.ResetSideGravity();
					}
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
	for (auto itr = std::begin(dynamicSquareColliderList); itr != std::cend(dynamicSquareColliderList); ++itr)
	{
		//一致したら削除
		if (itr->col == col)
		{
			dynamicSquareColliderList.erase(itr);
			return;
		}
	}
	for (auto itr = std::begin(staticSquareColliderList); itr != std::cend(staticSquareColliderList); ++itr)
	{
		//一致したら削除
		if (itr->col == col)
		{
			staticSquareColliderList.erase(itr);
			return;
		}
	}

}

/**
* @brief コライダリストをクリアする
*/
void ColliderManager::Reset()
{
	dynamicSquareColliderList.clear();
	staticSquareColliderList.clear();
}

#include "status.h"

bool Status::Damage(const float atk)
{
	//TODO:ここでダメージの計算を行う
	HP -= atk;
	return HP <= 0;
}
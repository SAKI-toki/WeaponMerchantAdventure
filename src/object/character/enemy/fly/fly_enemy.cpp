#include "fly_enemy.h"

void FlyEnemy::InitProcess()
{
	collider.SetStatus(transform.pos, transform.size.x, transform.size.y, transform.rot, transform.scale);
}

void FlyEnemy::UpdateProcess()
{
	transform.pos += move;
	if (transform.pos.x > start_pos.x&&transform.pos.x > end_pos.x ||
		transform.pos.x < start_pos.x&&transform.pos.x < end_pos.x)
	{
		move *= -1;
		transform.pos += move;
	}
	collider.SetStatus(transform.pos, transform.size.x, transform.size.y, transform.rot, transform.scale);
}

void FlyEnemy::Collision(ObjectBase*, VEC2)
{

}

void FlyEnemy::Destroy()
{
	if (collider.enabled)collider.Destroy();
	enabled = false;
}


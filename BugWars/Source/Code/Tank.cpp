#include "pch.h"
#include "Tank.h"
#include "Globals.h"
#include "Game.h"
#include "Bullet.h"
#include "Bug.h"

IMPLEMENT_RTTI(Tank);

void Tank::OnUpdate(float dt)
{
}

BugBase* Tank::GetBugToShoot() const
{
	Bug* target = nullptr;
	float min_dist = std::numeric_limits<float>::max();
	for (int i = 0; i < g_Game->objects.size(); ++i)
	{
		if (g_Game->objects[i]->GetRTTI() == Bug::s_RTTI)
		{
			if (g_Game->objects[i]->disabled)
			{
				continue;
			}
			float dist = (position - g_Game->objects[i]->position).Length2();
			if (dist < min_dist)
			{
				min_dist = dist;
				target = dynamic_cast<Bug*>(g_Game->objects[i]);
			}
		}
	}
	return target;
}

Point Tank::CalcShootDirection(Point target_pos, Point target_dir, float target_vel, float bullet_vel) const
{
	float a = target_vel * target_vel - bullet_vel * bullet_vel;

	Point dir_tank_target = target_pos - position;
	float b = (target_dir.x*(dir_tank_target.x) + target_dir.y*(dir_tank_target.y)) * 2 * target_vel;

	float c = dir_tank_target.Length2();

	float D = b * b - 4 * a * c;
	if (D < 0)
	{
		return dir_tank_target;
	}

	float t1 = (-b + sqrt(D)) / (2 * a);
	float t2 = (-b - sqrt(D)) / (2 * a);

	float dt = std::max(t1, t2);
	Point goal = target_pos + target_dir * target_vel * dt;

	Point dir = goal - position;
	return dir;
}

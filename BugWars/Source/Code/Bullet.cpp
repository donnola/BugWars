#include "pch.h"
#include "Bullet.h"
#include "Game.h"
#include "Bug.h"
#include "Tank.h"

IMPLEMENT_RTTI(Bullet);

void Bullet::OnStart(Point)
{
}

void Bullet::OnUpdate(float dt)
{
	for (int i = g_Game->objects.size() - 1; i >= 0; --i)
	{
		if (!g_Game->objects[i]->disabled)
		{
			if (g_Game->objects[i]->GetRTTI() == Bug::s_RTTI)
			{
				float bag_rad = g_Game->objects[i]->GetRadius();
				if ((g_Game->objects[i]->position - position).Length2() < bag_rad * bag_rad)
				{
					g_Game->tank->score++;
					g_Game->objects[i]->disabled = true;
					g_Game->objects[i]->visible = false;
					disabled = true;
					visible = false;
					return;
				}
			}
		}
	}
}

void Bullet::OnLifeEnd()
{
	disabled = true;
	visible = false;
}

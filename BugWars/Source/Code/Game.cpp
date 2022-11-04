#include "pch.h"
#include "Game.h"
#include "GameBase/Log.h"
#include "Tank.h"
#include "Bug.h"
#include "Bullet.h"

Game* g_Game;

Game::Game(): 
	GameBase({ [] {return new Tank; },
				 [] {return new Bug; },
				 [] {return new Bullet; } }), 
	obj_grid(cells_dim, std::vector<std::vector<GameObject*>>(cells_dim))
{
	g_Game = this;
}

void Game::OnUpdate(float dt)
{
	PIXScopedEvent(PIX_COLOR_INDEX(5), __FUNCTION__);
	for (int i = objects.size() - 1; i >= 0; --i)
	{
		if (!objects[i]->disabled)
		{
			objects[i]->Update(dt);
		}
		else
		{
			delete objects[i];
			objects.erase(objects.begin() + i);
		}
	}
}

void Game::OnRender() const
{
	for (auto obj : objects)
		if (obj->visible)
			if ((tank_obj->position - obj->position).Length2() < render_rad_2)
				DoRender(obj);
}

void Game::AddObject(GameObject* object)
{
	objects.push_back(object);
	if (object->GetRTTI() == Tank::s_RTTI)
	{
		tank_obj = object;
	}
	object->disabled = false;
	object->visible = true;
	if (object->GetRTTI() == Bug::s_RTTI)
	{
		Log("I'm a bug");
	}
}

void Game::OnBugsSpawned()
{
}

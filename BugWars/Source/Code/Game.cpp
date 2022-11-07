#include "pch.h"
#include "Game.h"
#include "GameBase/Log.h"
#include "Tank.h"
#include "Bug.h"
#include "Bullet.h"
#include <algorithm>

Game* g_Game;

Game::Game(): 
	GameBase({ [] {return new Tank; },
				 [] {return new Bug; },
				 [] {return new Bullet; } }), 
	obj_grid(cells_dim, std::vector<std::set<Bug*>>(cells_dim))
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
			if (objects[i]->GetRTTI() == Bug::s_RTTI)
			{
				Bug* bug = dynamic_cast<Bug*>(objects[i]);
				obj_grid[bug->cell.second][bug->cell.first].erase(bug);
			}
			delete objects[i];
			objects.erase(objects.begin() + i);
		}
	}
}

void Game::OnRender() const
{
	for (auto obj : objects)
		if (obj->visible)
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
		auto pos = object->position;
		int x = std::min(std::max(int(floor(pos.x / cell_size)), 0), cells_dim - 1);
		int y = std::min(std::max(int(floor(pos.y / cell_size)), 0), cells_dim - 1);
		Bug* bug = dynamic_cast<Bug*>(object);
		obj_grid[y][x].insert(bug);
		bug->cell = std::pair(x, y);
	}
}

void Game::OnBugsSpawned()
{
}

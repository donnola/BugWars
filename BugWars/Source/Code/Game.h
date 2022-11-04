#pragma once
#include "GameBase/GameBase.h"
#include "Globals.h"

struct Tank;

struct Game : public GameBase
{
	Game();
	virtual ~Game() override
	{
		for (int i = 0; i < objects.size(); ++i)
		{
			delete objects[i];
		}
		objects.clear();
	}

	virtual void OnUpdate(float dt) override;
	virtual void OnRender() const override;
	virtual void AddObject(GameObject* object) override;

	virtual void OnBugsSpawned() override;

	GameObject* tank_obj;
	float render_rad_2 = 1000 * 1000;
	std::vector<GameObject*> objects;
	const float cell_size = 100;
	const float field_size = 6400;
	const int cells_dim = 64;
	std::vector<std::vector<std::vector<GameObject*>>> obj_grid;
};
#include "pch.h"
#include "Bug.h"
#include "Game.h"
#include <algorithm>

IMPLEMENT_RTTI(Bug);

void Bug::OnUpdate(float dt)
{
	auto pos = position;
	int x = std::min(std::max(int(floor(pos.x / g_Game->cell_size)), 0), g_Game->cells_dim - 1);
	int y = std::min(std::max(int(floor(pos.y / g_Game->cell_size)), 0), g_Game->cells_dim - 1);
	if (cell.first != x || cell.second != y)
	{
		g_Game->obj_grid[cell.second][cell.first].erase(this);
		g_Game->obj_grid[y][x].insert(this);
		cell = std::pair(x, y);
	}
}

BugBase* Bug::FindBugToEat() const
{
	Bug* target = nullptr;
	Bug* candidate = nullptr;
	int shift = 0;
	float min_dist = std::numeric_limits<float>::max();
	std::vector<std::vector<bool>> grid_bool = std::vector(g_Game->cells_dim, std::vector<bool>(g_Game->cells_dim, false));
	int x = cell.first;
	int y = cell.second;

	while ((!candidate || !target) && (y - shift >= 0 || x - shift >= 0 || y + shift < g_Game->cells_dim || x + shift < g_Game->cells_dim))
	{
		if (candidate)
		{
			target = candidate;
		}
		for (int i = std::max(y - shift, 0); i <= std::min(y + shift, g_Game->cells_dim - 1); ++i)
		{
			for (int j = std::max(x - shift, 0); j <= std::min(x + shift, g_Game->cells_dim - 1); ++j)
			{
				if (grid_bool[i][j])
				{
					continue;
				}
				for (Bug* b : g_Game->obj_grid[i][j])
				{
					if (b->id >= id || b->disabled)
					{
						continue;
					}
					float dist = (position - b->position).Length2();
					if (dist < min_dist)
					{
						min_dist = dist;
						candidate = b;
					}
				}
				grid_bool[i][j] = true;
			}
		}
		++shift;
	}

	if (candidate)
	{
		target = candidate;
	}

	return target;
}

void Bug::OnEat(BugBase& first, BugBase& second)
{
	if (first.id > second.id)
	{
		second.disabled = true;
		second.visible = false;
	}
	else if (first.id < second.id)
	{
		first.disabled = true;
		first.visible = false;
	}
}
#include "pch.h"
#include "Bug.h"
#include "Game.h"

IMPLEMENT_RTTI(Bug);

void Bug::OnUpdate(float dt)
{

}

BugBase* Bug::FindBugToEat() const
{
	Bug* target = nullptr;
	float min_dist = std::numeric_limits<float>::max();
	for (int i = 0; i < g_Game->objects.size(); ++i)
	{
		if (g_Game->objects[i]->GetRTTI() == Bug::s_RTTI)
		{
			if (g_Game->objects[i]->id >= id || g_Game->objects[i]->disabled)
				continue;

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

//BugBase* Bug::FindBugToEat() const
//{
//	Bug* target = nullptr;
//	float min_dist = std::numeric_limits<float>::max();
//	for (auto object : g_Game->objects)
//	{
//		if (auto bug = dynamic_cast<Bug*>(object))
//		{
//			if (bug == this)
//				continue;
//
//			if (bug->disabled)
//				continue;
//
//			if (bug->id > id)
//				continue; // Can't eat that
//
//			float dist = position.Distance(bug->position);
//			if (dist < min_dist)
//			{
//				min_dist = dist;
//				target = bug;
//			}
//		}
//	}
//
//	return target;
//}
//
//void Bug::OnEat(BugBase& first, BugBase& second)
//{
//	if (first.id > second.id)
//	{
//		second.disabled = true;
//		second.visible = false;
//	}
//	else
//	{
//		first.disabled = true;
//		first.visible = false;
//	}
//}
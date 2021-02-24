#pragma once

#include "entt/entt.hpp"

class Scene {

public:
	Scene();
	~Scene();
private:
	entt::registry m_Registry;	// contain component data and entitiy ID
};
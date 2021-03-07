#pragma once

#include "entt/entt.hpp"

namespace Phoenix {

	class Entity;
	class RenderScene;
	class SceneSerializer;

	class Scene {

	public:
		Scene();
		~Scene();

		Entity createEntity(const std::string& name = std::string());

		void OnUpdate(float timestep);
	private:
		entt::registry m_Registry;	// contain component data and entitiy ID

		friend class Entity;
		friend class RenderScene;
		friend class SceneSerializer;
	};

}

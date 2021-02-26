#pragma once

#include "entt/entt.hpp"

namespace Phoenix {

	class Scene {

	public:
		Scene();
		~Scene();

		entt::entity createEntity();

		// TEMP
		entt::registry& Reg() { return m_Registry; }

		void OnUpdate(float timestep);
	private:
		entt::registry m_Registry;	// contain component data and entitiy ID
	};

}

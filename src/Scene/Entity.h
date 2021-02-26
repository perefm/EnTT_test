#pragma once

#include "Scene.h"
#include "entt/entt.hpp"


namespace Phoenix {

	/// <summary>
	/// Entity class works like a wrapper between our engine and entt library
	/// </summary>
	class Entity {

	public:
		Entity() = default;
		Entity(entt::entity handle, Scene* scene);
		Entity(const Entity& other) = default;

		template<typename T, typename... Args>
		T& AddComponent(Args&&... args)
		{
			assert(!HasComponent<T>());	// Entity already has component!
			return m_Scene->m_Registry.emplace<T>(m_EntityHandle, std::forward<Args>(args)...); // Froward the arguments directly to entt
		}

		template<typename T>
		T& GetComponent()
		{
			assert(HasComponent<T>());	// Entity does not have component!
			return m_Scene->m_Registry.get<T>(m_EntityHandle);
		}

		template<typename T>
		bool HasComponent()
		{
			return m_Scene->m_Registry.has<T>(m_EntityHandle);
		}

		template<typename T>
		void RemoveComponent()
		{
			assert(HasComponent<T>());	// Entity does not have component!
			return m_Scene->m_Registry.remove<T>(m_EntityHandle);
		}

		operator bool() const { return m_EntityHandle != entt::null; }

	private:
		entt::entity	m_EntityHandle { entt::null };
		Scene*			m_Scene = nullptr;
	};

}

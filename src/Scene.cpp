#include <iostream>

#include "Scene.h"

#include <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp>
#include "Components.h"

namespace Phoenix {

	static void doMath(const glm::mat4& transform)
	{

	}

	// Called each time a Transform is created
	static void OnTransformConstruct(entt::registry& registry, entt::entity entity)
	{
		printf("Transform created!!!");
	}

	Scene::Scene()
	{
		//TransformMat4Component transform;
		//doMath(transform);
		/*
		entt::entity entity = m_Registry.create(); // similar to "uint32_t entity = m_Registry.create();", entity is a uint32_t

		m_Registry.on_construct<TransformMat4Component>().connect<&OnTransformConstruct>();

		// add component
		auto& transform = m_Registry.emplace<TransformMat4Component>(entity, glm::mat4(1.0f));
		transform = glm::mat4(0.0f); // We can access directly the entity



		// Get compoennet
		if (m_Registry.has<TransformMat4Component>(entity)) {
			TransformMat4Component& my_trans = m_Registry.get<TransformMat4Component>(entity);
			my_trans = glm::mat4(1.0f);
		}

		// Iterate between components
		auto view = m_Registry.view<TransformMat4Component>();
		for (auto entity : view)
		{
			//TransformMat4Component& transform = view.get<TransformMat4Component>(entity); // Probably more optimal?? to check
			TransformMat4Component& transform = m_Registry.get<TransformMat4Component>(entity);
		}

		// Group multiple components
		auto group = m_Registry.group<TransformMat4Component>(entt::get<MeshComponent>);
		for (auto entity : group)
		{
			auto& [transform, mesh] = group.get<TransformMat4Component, MeshComponent>(entity);
			transform.Transform;// and now... access the components
			mesh.Path;

			// Renderer::Submit(mesh, transform); // Example for a renderer
		}
		*/
	}

	Scene::~Scene()
	{
	}

	entt::entity Scene::createEntity()
	{
		return m_Registry.create();
	}

	void Scene::OnUpdate(float timestep) // Should be a double?
	{
		// Group multiple components
		auto group = m_Registry.group<TransformComponent>(entt::get<MeshComponent>);
		for (auto entity : group)
		{
			auto& [transform, mesh] = group.get<TransformComponent, MeshComponent>(entity);
			
			
			std::cout << "Call Render with mesh: " + mesh.Path + " at position: " + glm::to_string(transform.GetTransform()) << std::endl; // and now... access the components
			// Renderer::Submit(mesh, transform); // Example for a renderer
		}

	}
}
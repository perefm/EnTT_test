#include <iostream>

#include "Scene.h"
#include "Entity.h"

#include <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp>
#include "Components.h"
#include "Renderer/Renderer.h"

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
	
	}

	Scene::~Scene()
	{
	}

	Entity Scene::createEntity(const std::string& name)
	{
		Entity entity = { m_Registry.create(), this };
		// All our entities will have those default components
		entity.AddComponent<TransformComponent>();
		auto& tag = entity.AddComponent<TagComponent>();
		tag.Tag = name.empty() ? "No name" : name; // Set default name if tag is empty
		return entity;
	}

	void Scene::OnUpdate(float timestep) // Should be a double?
	{
		// Update scripts
		// TODO: Implement scripting

		// Render the scene
		// Find the main camera
		Camera* mainCamera = nullptr;
		glm::mat4* cameraTransform = nullptr;
		{
			auto view = m_Registry.view<TransformComponent, CameraComponent>();
			for (auto entity : view)
			{
				auto [transform, camera] = view.get<TransformComponent, CameraComponent>(entity);
				if (camera.Primary)
				{
					mainCamera = &camera.Camera;
					cameraTransform = &transform.GetTransform();
					break;
				}
			}
		}
		
		
		if (mainCamera)
		{
			Renderer::BeginScene(*mainCamera);	// Start our renderer by sending the camera projection and transform matrix

			// Group multiple components
			auto group = m_Registry.group<TransformComponent>(entt::get<MeshComponent>);
			for (auto entity : group)
			{
				auto& [transform, mesh] = group.get<TransformComponent, MeshComponent>(entity);

				std::cout << "Call Render with mesh: " + mesh.Path + " at position: " + glm::to_string(transform.GetTransform()) << std::endl; // and now... access the components
				// Renderer::Submit(mesh, transform); // Example for a renderer
			}

			Renderer::EndScene();
		}

		

	}
}
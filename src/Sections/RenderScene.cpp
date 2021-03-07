#include <iostream>
#include <string>
#include <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "RenderScene.h"
#include "Scene/Scene.h"
#include "Scene/Entity.h"
#include "Scene/Components.h"
#include "Scene/SceneSerializer.h"
#include "Sections/RenderScene.h"

namespace Phoenix {

	RenderScene::RenderScene()
	{
		s_RenderSceneData = CreateScope<RenderSceneData>();
	}

	RenderScene::~RenderScene()
	{
	}

	void RenderScene::onLoad()
	{
		m_activeScene = CreateRef<Scene>();

		// Create Model Entity
		s_RenderSceneData->someEntity = m_activeScene->createEntity("Actor mesh");
		// Add some components to entity "modelA"
		s_RenderSceneData->someEntity.AddComponent<MeshComponent>("/path_to_mesh/actor.gltf");

		// Create another model Entity
		auto car = m_activeScene->createEntity("Car mesh");
		// Add some components to entity "modelA"
		car.AddComponent<MeshComponent>("/path_to_mesh/car.gltf");

		// Create Camera Entity
		auto camera = m_activeScene->createEntity("Camera One");
		camera.AddComponent<CameraComponent>();
	}

	void RenderScene::onInit()
	{
	}

	void RenderScene::onExec(float time)
	{
		// Update Entity
		s_RenderSceneData->someEntity.GetComponent<TransformComponent>().Translation += glm::vec3(1.0f, 0.0f, 0.0f);


		std::cout << "New frame > RenderScene::onExec time: " + std::to_string(time) << std::endl;
		m_activeScene->OnUpdate(time);
	}

	void RenderScene::onEnd()
	{
	}

	void RenderScene::ShowEntities()
	{
		std::cout << "DISPLAYING ENTITIES IN SCENE:" << std::endl;
		m_activeScene->m_Registry.each([&](auto entityID)
		{
			Entity entity{ entityID , m_activeScene.get() };
			ShowComponents(entity);
		});

		std::cout << std::endl;
	}

	void RenderScene::LoadScene(std::string path)
	{
		m_activeScene = CreateRef<Scene>();
		SceneSerializer serializer(m_activeScene);
		serializer.Deserialize(path);
	}

	void RenderScene::SaveScene(std::string path)
	{
		SceneSerializer serializer(m_activeScene);
		serializer.Serialize(path);
	}
	

	template<typename T, typename UIFunction>
	static void DrawComponent(const std::string& name, Entity entity, UIFunction uiFunction)
	{
		if (entity.HasComponent<T>())
		{
			auto& component = entity.GetComponent<T>();
			uiFunction(component);
		}
	}

	void RenderScene::ShowComponents(Entity entity)
	{
		DrawComponent<TagComponent>("Tag", entity, [](auto& component)
			{
				auto& tag = component.Tag;
				std::cout << "Tag: " << tag << std::endl;
			});

		DrawComponent<TransformComponent>("Transform", entity, [](auto& component)
			{
				auto& translation = component.Translation;
				auto& rotation = component.Rotation;
				auto& scale = component.Scale;

				std::cout << "  Transform::Translation: " << glm::to_string(translation) << std::endl;
				std::cout << "  Transform::Rotation: " << glm::to_string(rotation) << std::endl;
				std::cout << "  Transform::Scale: " << glm::to_string(scale) << std::endl;
			});

		DrawComponent<CameraComponent>("Camera", entity, [](auto& component)
			{
				auto& camera = component.Camera;
				std::cout << "  Camera::Matrix: " << glm::to_string(camera.GetViewMatrix()) << std::endl;
			});
		
		DrawComponent<MeshComponent>("Mesh", entity, [](auto& component)
			{
				auto& path = component.Path;
				std::cout << "  Mesh::Path: " << path << std::endl;
			});
	}


}
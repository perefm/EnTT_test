#include "Scene.h"

#include <glm/glm.hpp>

static void doMath(const glm::mat4& transform)
{

}

Scene::Scene()
{

	struct MeshComponent
	{
		std::string Path;
		MeshComponent() = default;
		MeshComponent(const MeshComponent&) = default;
		MeshComponent(const std::string path)
			: Path(path) {};

		operator std::string () { return Path; };
		operator const std::string() const { return Path; };
	};

	struct TransformComponent
	{
		glm::mat4 Transform;
		TransformComponent() = default;
		TransformComponent(const TransformComponent&) = default;
		TransformComponent(const glm::mat4& transform)
			: Transform(transform) {};

		operator glm::mat4& () { return Transform; };
		operator const glm::mat4& () const { return Transform; };
	};


	//TransformComponent transform;
	//doMath(transform);

	entt::entity entity = m_Registry.create(); // similar to "uint32_t entity = m_Registry.create();", entity is a uint32_t

	// add component
	auto& transform = m_Registry.emplace<TransformComponent>(entity, glm::mat4(1.0f));
	transform = glm::mat4(0.0f); // We can access directly the entity

	// Get compoennet
	if (m_Registry.has<TransformComponent>(entity)) {
		TransformComponent& my_trans = m_Registry.get<TransformComponent>(entity);
		my_trans = glm::mat4(1.0f);
	}
	
	// Iterate between components
	auto view = m_Registry.view<TransformComponent>();
	for (auto entity : view)
	{
		//TransformComponent& transform = view.get<TransformComponent>(entity); // Probably more optimal?? to check
		TransformComponent& transform = m_Registry.get<TransformComponent>(entity);
	}

	// Group multiple components
	auto group = m_Registry.group<TransformComponent>(entt::get<MeshComponent>);
	for (auto entity : group)
	{
		auto&[transform, mesh] = group.get<TransformComponent, MeshComponent>(entity);
		transform.Transform;// and now... access the components
		mesh.Path;

		// Renderer::Submit(mesh, transform); // Example for a renderer
	}

}

Scene::~Scene()
{
}



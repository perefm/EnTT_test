#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/quaternion.hpp>

namespace Phoenix {

	struct TagComponent
	{
		std::string Name;
		TagComponent() = default;
		TagComponent(const TagComponent&) = default;
		TagComponent(const std::string name)
			: Name(name) {};

		operator std::string() { return Name; };
		operator const std::string() const { return Name; };
	};

	struct MeshComponent
	{
		std::string Path;
		MeshComponent() = default;
		MeshComponent(const MeshComponent&) = default;
		MeshComponent(const std::string path)
			: Path(path) {};

		operator std::string() { return Path; };
		operator const std::string() const { return Path; };
	};

	struct TransformComponent
	{
		glm::vec3 Translation = { 0.0f, 0.0f, 0.0f };
		glm::vec3 Rotation = { 0.0f, 0.0f, 0.0f };
		glm::vec3 Scale = { 1.0f, 1.0f, 1.0f };

		TransformComponent() = default;
		TransformComponent(const TransformComponent&) = default;
		TransformComponent(const glm::vec3& translation, const glm::vec3& rotation, const glm::vec3& scale)
			:
			Translation(translation),
			Rotation(rotation),
			Scale(scale) {}

		glm::mat4 GetTransform() const
		{
			return glm::translate(glm::mat4(1.0f), Translation)
				* glm::toMat4(glm::quat(Rotation))
				* glm::scale(glm::mat4(1.0f), Scale);
		}
	};

	struct TransformMat4Component
	{
		glm::mat4 Transform = glm::mat4(1.0f);

		TransformMat4Component() = default;
		TransformMat4Component(const TransformMat4Component&) = default;
		TransformMat4Component(const glm::mat4& transform)
			: Transform(transform) {};

		operator glm::mat4& () { return Transform; };
		operator const glm::mat4& () const { return Transform; };

	};
}
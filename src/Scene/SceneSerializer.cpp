#define _SILENCE_CXX17_ITERATOR_BASE_CLASS_DEPRECATION_WARNING

#include "Base.h"
#include "SceneSerializer.h"

#include "Entity.h"
#include "Components.h"

#include <fstream>

#include <yaml-cpp/yaml.h>


namespace YAML {

	template<>
	struct convert<glm::vec3>
	{
		static Node encode(const glm::vec3& rhs)
		{
			Node node;
			node.push_back(rhs.x);
			node.push_back(rhs.y);
			node.push_back(rhs.z);
			node.SetStyle(EmitterStyle::Flow);
			return node;
		}

		static bool decode(const Node& node, glm::vec3& rhs)
		{
			if (!node.IsSequence() || node.size() != 3)
				return false;

			rhs.x = node[0].as<float>();
			rhs.y = node[1].as<float>();
			rhs.z = node[2].as<float>();
			return true;
		}
	};

	template<>
	struct convert<glm::vec4>
	{
		static Node encode(const glm::vec4& rhs)
		{
			Node node;
			node.push_back(rhs.x);
			node.push_back(rhs.y);
			node.push_back(rhs.z);
			node.push_back(rhs.w);
			node.SetStyle(EmitterStyle::Flow);
			return node;
		}

		static bool decode(const Node& node, glm::vec4& rhs)
		{
			if (!node.IsSequence() || node.size() != 4)
				return false;

			rhs.x = node[0].as<float>();
			rhs.y = node[1].as<float>();
			rhs.z = node[2].as<float>();
			rhs.w = node[3].as<float>();
			return true;
		}
	};

}
namespace Phoenix {

	YAML::Emitter& operator<<(YAML::Emitter& out, const glm::vec3& v)
	{
		out << YAML::Flow;
		out << YAML::BeginSeq << v.x << v.y << v.z << YAML::EndSeq;
		return out;
	}

	YAML::Emitter& operator<<(YAML::Emitter& out, const glm::vec4& v)
	{
		out << YAML::Flow;
		out << YAML::BeginSeq << v.x << v.y << v.z << v.w << YAML::EndSeq;
		return out;
	}

	SceneSerializer::SceneSerializer(const Ref<Scene>& scene)
		: m_Scene(scene)
	{
	}

	static void SerializeEntity(YAML::Emitter& out, Entity entity)
	{
		out << YAML::BeginMap; // Entity
		out << YAML::Key << "Entity" << YAML::Value << "12837192831273"; // TODO: Entity ID goes here

		if (entity.HasComponent<TagComponent>())
		{
			out << YAML::Key << "TagComponent";
			out << YAML::BeginMap; // TagComponent

			auto& tag = entity.GetComponent<TagComponent>().Tag;
			out << YAML::Key << "Tag" << YAML::Value << tag;

			out << YAML::EndMap; // TagComponent
		}

		if (entity.HasComponent<TransformComponent>())
		{
			out << YAML::Key << "TransformComponent";
			out << YAML::BeginMap; // TransformComponent

			auto& tc = entity.GetComponent<TransformComponent>();
			out << YAML::Key << "Translation" << YAML::Value << tc.Translation;
			out << YAML::Key << "Rotation" << YAML::Value << tc.Rotation;
			out << YAML::Key << "Scale" << YAML::Value << tc.Scale;

			out << YAML::EndMap; // TransformComponent
		}

		if (entity.HasComponent<CameraComponent>())
		{
			out << YAML::Key << "CameraComponent";
			out << YAML::BeginMap; // CameraComponent

			auto& cameraComponent = entity.GetComponent<CameraComponent>();
			auto& camera = cameraComponent.Camera;

			out << YAML::Key << "Camera" << YAML::Value;
			out << YAML::BeginMap; // Camera
 
			out << YAML::Key << "Position" << YAML::Value << camera.Position;
			out << YAML::Key << "Front" << YAML::Value << camera.Front;
			out << YAML::Key << "Up" << YAML::Value << camera.Up;
			out << YAML::Key << "Right" << YAML::Value << camera.Right;
			out << YAML::Key << "Yaw" << YAML::Value << camera.Yaw;
			out << YAML::Key << "Pitch" << YAML::Value << camera.Pitch;
			out << YAML::Key << "Roll" << YAML::Value << camera.Roll;
			out << YAML::Key << "MovementSpeed" << YAML::Value << camera.MovementSpeed;
			out << YAML::Key << "RollSpeed" << YAML::Value << camera.RollSpeed;
			out << YAML::Key << "MouseSensitivity" << YAML::Value << camera.MouseSensitivity;
			out << YAML::Key << "Fov" << YAML::Value << camera.Fov;
			out << YAML::Key << "Far" << YAML::Value << camera.Far;
			out << YAML::Key << "Near" << YAML::Value << camera.Near;

			out << YAML::EndMap; // Camera

			out << YAML::Key << "Primary" << YAML::Value << cameraComponent.Primary;

			out << YAML::EndMap; // CameraComponent
		}

		if (entity.HasComponent<MeshComponent>())
		{
			out << YAML::Key << "MeshComponent";
			out << YAML::BeginMap; // MeshComponent

			auto& meshComponent = entity.GetComponent<MeshComponent>();
			out << YAML::Key << "Path" << YAML::Value << meshComponent.Path;

			out << YAML::EndMap; // MeshComponent
		}

		out << YAML::EndMap; // Entity
	}

	void SceneSerializer::Serialize(const std::string& filepath)
	{
		YAML::Emitter out;
		out << YAML::BeginMap;
		out << YAML::Key << "Scene" << YAML::Value << m_Scene->Name;
		out << YAML::Key << "Entities" << YAML::Value << YAML::BeginSeq;
		m_Scene->m_Registry.each([&](auto entityID)
		{
			Entity entity = { entityID, m_Scene.get() };
			if (!entity)
				return;

			SerializeEntity(out, entity);
		});
		out << YAML::EndSeq;
		out << YAML::EndMap;

		std::ofstream fout(filepath);
		fout << out.c_str();
	}

	void SceneSerializer::SerializeRuntime(const std::string& filepath)
	{
		// Not implemented
		assert(false);
	}

	bool SceneSerializer::Deserialize(const std::string& filepath)
	{
		YAML::Node data = YAML::LoadFile(filepath);
		if (!data["Scene"])
			return false;

		m_Scene->Name = data["Scene"].as<std::string>();
		//HZ_CORE_TRACE("Deserializing scene '{0}'", sceneName);

		auto entities = data["Entities"];
		if (entities)
		{
			for (auto entity : entities)
			{
				uint64_t uuid = entity["Entity"].as<uint64_t>(); // TODO

				std::string name;
				auto tagComponent = entity["TagComponent"];
				if (tagComponent)
					name = tagComponent["Tag"].as<std::string>();

				//HZ_CORE_TRACE("Deserialized entity with ID = {0}, name = {1}", uuid, name);

				Entity deserializedEntity = m_Scene->createEntity(name);

				auto transformComponent = entity["TransformComponent"];
				if (transformComponent)
				{
					// Entities always have transforms
					auto& tc = deserializedEntity.GetComponent<TransformComponent>();
					tc.Translation = transformComponent["Translation"].as<glm::vec3>();
					tc.Rotation = transformComponent["Rotation"].as<glm::vec3>();
					tc.Scale = transformComponent["Scale"].as<glm::vec3>();
				}

				auto cameraComponent = entity["CameraComponent"];
				if (cameraComponent)
				{
					auto& cc = deserializedEntity.AddComponent<CameraComponent>();

					//auto& cameraProps = cameraComponent["Camera"];
					auto cameraProps = cameraComponent["Camera"];

					cc.Camera.Position = cameraProps["Position"].as<glm::vec3>();
					cc.Camera.Front = cameraProps["Front"].as<glm::vec3>();
					cc.Camera.Up = cameraProps["Up"].as<glm::vec3>();
					cc.Camera.Right = cameraProps["Right"].as<glm::vec3>();
					cc.Camera.Yaw = cameraProps["Yaw"].as<float>();
					cc.Camera.Pitch = cameraProps["Pitch"].as<float>();
					cc.Camera.Roll = cameraProps["Roll"].as<float>();
					cc.Camera.MovementSpeed = cameraProps["MovementSpeed"].as<float>();
					cc.Camera.RollSpeed = cameraProps["RollSpeed"].as<float>();
					cc.Camera.MouseSensitivity = cameraProps["MouseSensitivity"].as<float>();
					cc.Camera.Fov = cameraProps["Fov"].as<float>();
					cc.Camera.Far = cameraProps["Far"].as<float>();
					cc.Camera.Near = cameraProps["Near"].as<float>();

					cc.Primary = cameraComponent["Primary"].as<bool>();
				}

				auto meshComponent = entity["MeshComponent"];
				if (meshComponent)
				{
					auto& mc = deserializedEntity.AddComponent<MeshComponent>();
					mc.Path = meshComponent["Path"].as<std::string>();
				}
			}
		}

		return true;
	}

	bool SceneSerializer::DeserializeRuntime(const std::string& filepath)
	{
		// Not implemented
		assert(false);
		return false;
	}

}

﻿// Renderer.h
// Spontz Demogroup

#pragma once

#include <iostream>
#include <string>
#include <glm/glm.hpp>
#include "Base.h"
#include "Renderer/Camera.h"

namespace Phoenix {

	class Renderer
	{
	public:
		static void Init();
		static void Shutdown();

		static void OnWindowResize(uint32_t width, uint32_t height);

		static void BeginScene(Camera& camera);
		static void EndScene();

		static void Submit(const int shader, const int vertexArray, const glm::mat4& transform = glm::mat4(1.0f));
		//static void Submit(const Ref<Shader>& shader, const Ref<VertexArray>& vertexArray, const glm::mat4& transform = glm::mat4(1.0f));

	private:
		struct SceneData
		{
			glm::mat4 ViewProjectionMatrix;
		};

		static Scope<SceneData> s_SceneData;
	};
}
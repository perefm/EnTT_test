#pragma once

#include <string>
#include <glm/glm.hpp>
#include "Base.h"
#include "Scene/Scene.h"
#include "Scene/Entity.h"

namespace Phoenix {

	class RenderScene
	{
	public:
		RenderScene();
		~RenderScene();

		void		onLoad();
		void		onInit();
		void		onExec(float time);
		void		onEnd();

		void		ShowEntities();
		void		LoadScene(std::string path);
		void		SaveScene(std::string path);

	private:
		void		ShowComponents(Entity entity);

		Ref<Scene> m_activeScene;

		struct RenderSceneData
		{
			Entity someEntity;
		};

		Scope<RenderSceneData> s_RenderSceneData;

	};
}
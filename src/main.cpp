#include <conio.h>
#include <iostream>
#include <string>
#include <fstream>

#include "Base.h"
#include "Scene/Entity.h"
#include "Scene/Scene.h"
#include "Scene/Components.h"

#include "Sections/RenderScene.h"
#include "main.h"

using namespace Phoenix;

int main() {

	float time = 0;

	char c;
	std::cout << "Press ESC to exit!" << std::endl;

	// Create the RenderScene "section"
	Ref<RenderScene> m_SectionRenderScene = CreateRef<RenderScene>();
	m_SectionRenderScene->onLoad();	// Load the section
	m_SectionRenderScene->onInit();	// Init the section

	std::string path = ".//scene.phoenix";

	while (true)
	{
		c = _getch();
		
		if (c == 27)
			break;
		else if (c == 'e') { // SHOW ENTITIES
			m_SectionRenderScene->ShowEntities();
		}
		else if (c == 'l') { // LOAD FILE
			// Load scene
			std::ifstream f(path.c_str());
			if (f.good()) {
				m_SectionRenderScene->LoadScene(path);
				std::cout << "File loaded: " << path << std::endl;
			}
			else {
				std::cout << "File not found: " << path << std::endl;
			}
		}
		else if (c == 's') { // SAVE FILE
			// Save scene
			m_SectionRenderScene->SaveScene(path);
			std::cout << "File saved: " << path << std::endl;
		}

		else if (c == 'p') { // RUN SOME MASSIVE SAVE & LOADING
			int loop = 100;
			for (int i = 0; i < loop; i++) {
				m_SectionRenderScene->SaveScene(path);
				m_SectionRenderScene->LoadScene(path);
			}
			std::cout << "File saved & loaded " << loop << " times" << std::endl;
			
		}

		else {
			m_SectionRenderScene->onExec(time);
			time += 0.1f;
		}
		
	}

	std::cout << "Exit!" << std::endl;
 
}
#include <conio.h>
#include <iostream>
#include <string>

#include "Base.h"
#include "Scene/Entity.h"
#include "Scene/Scene.h"
#include "Scene/Components.h"

#include "Sections/RenderScene.h"

using namespace Phoenix;

int main() {

	float time = 0;

	char c;
	std::cout << "Press ESC to exit!" << std::endl;

	// Create the RenderScene "section"
	Ref<RenderScene> m_SectionRenderScene = CreateRef<RenderScene>();
	m_SectionRenderScene->onLoad();	// Load the section
	m_SectionRenderScene->onInit();	// Init the section

	
	while (true)
	{
		c = _getch();
		
		if (c == 27)
			break;
		else if (c == 'e') {
			m_SectionRenderScene->ShowEntities();
		}
		else {
			m_SectionRenderScene->onExec(time);
			time += 0.1f;
		}
		
	}

	std::cout << "Exit!" << std::endl;
 
}
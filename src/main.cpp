#include <conio.h>
#include <iostream>
#include <string>

#include <entt/entt.hpp>
#include "Base.h"
#include "Scene.h"
#include "Components.h"
 

using namespace Phoenix;

int main() {

    Ref<Scene> m_ActiveScene = CreateRef<Scene>();
    float time = 0;

    char c;
    std::cout << "Press ESC to exit!" << std::endl;

    // Create Entity
    auto modelA = m_ActiveScene->createEntity();

    // Add some components to entity "modelA"
    m_ActiveScene->Reg().emplace<MeshComponent>(modelA, "my Model one");
    m_ActiveScene->Reg().emplace<TransformComponent>(modelA);
    


    while (true)
    {
        m_ActiveScene->OnUpdate(time);
        c = _getch();
        if (c == 27)
            break;

        // On each loop, we increment the X position of the translation component of ModelA
        m_ActiveScene->Reg().get<TransformComponent>(modelA).Translation += glm::vec3(1.0f, 0.0f, 0.0f);

        time += 0.1f;
        std::cout << "new frame! time:" + std::to_string(time) << std::endl;
    }

    std::cout << "Exit!" << std::endl;


}
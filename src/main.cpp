#include <conio.h>
#include <iostream>
#include <string>

#include "Base.h"
#include "Scene/Entity.h"
#include "Scene/Scene.h"
#include "Scene/Components.h"

 

using namespace Phoenix;

int main() {

    float time = 0;

    char c;
    std::cout << "Press ESC to exit!" << std::endl;

    Ref<Scene> m_ActiveScene = CreateRef<Scene>();

    // Create Entity
    auto modelA = m_ActiveScene->createEntity("Model A");
    bool should_be_true = modelA.HasComponent<TransformComponent>();
    bool should_be_false = modelA.HasComponent<MeshComponent>();

    // Add some components to entity "modelA"
    modelA.AddComponent<MeshComponent>("Path to mesh....");
    should_be_true = modelA.HasComponent<MeshComponent>();
    
    Entity& my_entity = modelA;



    while (true)
    {
        m_ActiveScene->OnUpdate(time);
        c = _getch();
        if (c == 27)
            break;

        // On each loop, we increment the X position of the translation component of ModelA
        my_entity.GetComponent<TransformComponent>().Translation +=glm::vec3(1.0f, 0.0f, 0.0f);
        //m_ActiveScene->Reg().get<TransformComponent>(modelA).Translation += glm::vec3(1.0f, 0.0f, 0.0f);

        time += 0.1f;
        std::cout << "new frame! time:" + std::to_string(time) << std::endl;
    }

    std::cout << "Exit!" << std::endl;


}
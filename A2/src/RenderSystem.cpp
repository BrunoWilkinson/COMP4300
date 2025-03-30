#include "engine/GameEngine.h"
#include "engine/Entity.h"
#include "RenderSystem.h"
#include "Components.h"

void RenderSystem::update(GameEngine* engine)
{
    for (std::shared_ptr<Entity> entity : engine->entity_manager()->get_entities())
    {
        std::shared_ptr<CShape> shape_component = entity->find_component<CShape>();
        if (shape_component)
        {
            engine->window.draw(*shape_component->shape);
        }

    }
}

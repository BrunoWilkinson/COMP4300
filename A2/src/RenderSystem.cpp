#include "engine/GameEngine.h"
#include "engine/Entity.h"
#include "RenderSystem.h"
#include "Components.h"

#include <cassert>
#include <iostream>

void RenderSystem::update(GameEngine* engine)
{
    for (std::shared_ptr<Entity> entity : engine->entity_manager()->get_entities())
    {
        assert(entity);
        if (std::shared_ptr<CShape> shape_component = entity->find_component<CShape>())
        {
            assert(shape_component);
            engine->window.draw(shape_component.get()->shape);
        }
    }
}

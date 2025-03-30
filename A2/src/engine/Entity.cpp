#include "Entity.h"

Entity::Entity(const std::string& tag, const size_t id)
    : m_tag(tag), m_id(id)
{}

void Entity::destroy()
{
    m_alive = false;
}

void Entity::add_component(std::shared_ptr<void> component)
{
    m_component_set.insert(component);
}

void Entity::remove_component(std::shared_ptr<void> component)
{
    m_component_set.erase(component);
}

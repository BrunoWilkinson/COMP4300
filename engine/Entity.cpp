#include "Entity.h"

Entity::Entity(const std::string& tag, const size_t id)
    : m_tag(tag), m_id(id)
{}

void Entity::destroy()
{
    m_alive = false;
}

#ifndef ENTITY_H
#define ENTITY_H

#include <string>

class Entity
{
    friend class EntityManager;

    const size_t m_id = 0;
    const std::string m_tag = "Default";
    bool m_alive = true;

    Entity(const std::string& tag, size_t id);

public:
    const std::string& tag() const { return m_tag; }
    const size_t id() const { return m_id; }
    bool isAlive() const { return m_alive; }

    void destroy();
};

#endif

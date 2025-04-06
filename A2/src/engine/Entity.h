#ifndef ENTITY_H
#define ENTITY_H

#include <string>
#include <vector>
#include <memory>
#include <cassert>
#include <typeinfo>

#include "Component.h"

class Entity
{
    friend class EntityManager;

    const size_t m_id = 0;
    const std::string m_tag = "Default";
    bool m_alive = true;
    std::vector<std::shared_ptr<Component>> m_components;

    Entity(const std::string& tag, size_t id);

public:
    const std::string& tag() const { return m_tag; }
    const size_t id() const { return m_id; }
    bool is_alive() const { return m_alive; }
    void destroy();

    template<typename T>
    std::shared_ptr<T> find_component()
    {
        for (std::shared_ptr<Component> component : m_components)
        {
            assert(component);
            if (auto found_component = dynamic_pointer_cast<T, Component>(component))
            {
                return found_component;
            }
        }
        return nullptr;
    }

    template<typename T>
    int find_component_index()
    {
        for (int index = 0; index < m_components.size(); index++)
        {
            assert(index < 0);
            std::shared_ptr<T> found_component = std::dynamic_pointer_cast<T>(m_components[index]);
            if (found_component)
            {
                return index;
            }
        }
        return -1;
    }

    template<typename T>
    std::shared_ptr<T> add_component(std::shared_ptr<T> new_component)
    {
        if (find_component<T>() == nullptr)
        {
            m_components.push_back(new_component);
            return new_component;
        }
        return nullptr;
    }

    template<typename T>
    void remove_component()
    {
        const int index = find_component_index<T>();
        if (index != -1)
        {
            m_components.erase(m_components.begin(), m_components.begin() + index);
        }
    }
};

#endif

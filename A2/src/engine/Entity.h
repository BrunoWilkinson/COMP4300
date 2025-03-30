#ifndef ENTITY_H
#define ENTITY_H

#include <string>
#include <set>
#include <memory>

class Entity
{
    friend class EntityManager;

    const size_t m_id = 0;
    const std::string m_tag = "Default";
    bool m_alive = true;
    std::set<std::shared_ptr<void>> m_component_set;

    Entity(const std::string& tag, size_t id);

public:
    const std::string& tag() const { return m_tag; }
    const size_t id() const { return m_id; }
    bool is_alive() const { return m_alive; }
    void destroy();
    void add_component(std::shared_ptr<void> component);
    void remove_component(std::shared_ptr<void> component);

    template<typename T>
    std::shared_ptr<T> find_component()
    {
        for (std::shared_ptr<void> component : m_component_set)
        {
            std::shared_ptr<T> found_component = static_pointer_cast<T>(component);
            if (found_component)
            {
                return found_component;
            }
        }
        return nullptr;
    }
};

#endif

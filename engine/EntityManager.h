#ifndef ENTITY_MANAGER_H
#define ENTITY_MANAGER_H

#include <vector>
#include <memory>
#include <string>
#include <map>

class Entity;

typedef std::vector<std::shared_ptr<Entity>> EntityList;
typedef std::map<std::string, EntityList> EntityMap;

class EntityManager
{
    EntityList m_entities;
    EntityList m_add_entities;
    EntityList m_remove_entities;
    EntityMap m_entity_map;
    size_t m_total_entities = 0;

public: 
    EntityManager();
    void update();
    std::shared_ptr<Entity> add_entity(const std::string& tag);
    EntityList& get_entities();
    EntityList& get_entities(const std::string& tag);
    bool find_entity(const size_t id, uint list_index, uint map_index); 
};

#endif

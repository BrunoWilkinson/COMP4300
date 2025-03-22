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
    EntityList m_addEntities;
    EntityList m_removeEntities;
    EntityMap m_entityMap;
    size_t m_totalEntities = 0;

public: 
    EntityManager();
    void update();
    std::shared_ptr<Entity> addEntity(const std::string& tag);
    EntityList& getEntities();
    EntityList& getEntities(const std::string& tag);
    bool findEntity(const size_t id, uint listIndex, uint mapIndex); 
};

#endif

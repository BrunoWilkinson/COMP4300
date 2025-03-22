#include "EntityManager.h"
#include "Entity.h"

std::shared_ptr<Entity> EntityManager::addEntity(const std::string& tag)
{
    std::shared_ptr<Entity> entity = std::shared_ptr<Entity>(new Entity (tag, m_totalEntities++));
    m_addEntities.push_back(entity);
    return entity;
}

void EntityManager::update()
{
    for (std::shared_ptr<Entity> entity : m_addEntities)
    {
	m_entities.push_back(entity);
	m_entityMap[entity->tag()].push_back(entity);
    }

    for (std::shared_ptr<Entity> entity : m_entities)
    {
	if (!entity->isAlive())
	{
	    m_removeEntities.push_back(entity);
	}
    }

    for (std::shared_ptr<Entity> entity : m_removeEntities)
    {
	uint listIndex = 0;
	uint mapIndex = 0;
	if (findEntity(entity->id(), listIndex, mapIndex))
	{
	    m_entities.erase(m_entities.begin(), m_entities.begin() + (listIndex + 1));
	    EntityList entityList = m_entityMap[entity->tag()];
	    entityList.erase(entityList.begin(), entityList.begin() + (mapIndex + 1));
	}
    }

    m_addEntities.clear();
    m_removeEntities.clear();
}

EntityList& EntityManager::getEntities() 
{
    return m_entities;
}

EntityList& EntityManager::getEntities(const std::string& tag)
{
    return m_entityMap[tag];
}

bool EntityManager::findEntity(const size_t id, uint listIndex, uint mapIndex)
{
    for (uint i = 0; i < m_entities.size(); i++)
    {
	std::shared_ptr<Entity> entity = m_entities[i];
	if (entity->id() == id)
	{
	    listIndex = i;
	    EntityList mapList = getEntities(entity->tag());
	    for (uint y = 0; y < mapList.size() ; y++)
	    {
		if (mapList[y]->id() == id)
		{
		    mapIndex = y;
		    return true;
		}
	    }
	}
    }

    return false;
}


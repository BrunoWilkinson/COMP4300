#include "EntityManager.h"
#include "Entity.h"

std::shared_ptr<Entity> EntityManager::add_entity(const std::string& tag)
{
    std::shared_ptr<Entity> entity = std::shared_ptr<Entity>(new Entity (tag, m_total_entities++));
    m_add_entities.push_back(entity);
    return entity;
}

void EntityManager::update()
{
    for (std::shared_ptr<Entity> entity : m_add_entities)
    {
	m_entities.push_back(entity);
	m_entity_map[entity->tag()].push_back(entity);
    }

    for (std::shared_ptr<Entity> entity : m_entities)
    {
	if (!entity->is_alive())
	{
	    m_remove_entities.push_back(entity);
	}
    }

    for (std::shared_ptr<Entity> entity : m_remove_entities)
    {
	uint list_index = 0;
	uint map_index = 0;
	if (find_entity(entity->id(), list_index, map_index))
	{
	    m_entities.erase(m_entities.begin(), m_entities.begin() + (list_index + 1));
	    EntityList entityList = m_entity_map[entity->tag()];
	    entityList.erase(entityList.begin(), entityList.begin() + (map_index + 1));
	}
    }

    m_add_entities.clear();
    m_remove_entities.clear();
}

EntityList& EntityManager::get_entities() 
{
    return m_entities;
}

EntityList& EntityManager::get_entities(const std::string& tag)
{
    return m_entity_map[tag];
}

bool EntityManager::find_entity(const size_t id, uint list_index, uint map_index)
{
    for (uint i = 0; i < m_entities.size(); i++)
    {
	std::shared_ptr<Entity> entity = m_entities[i];
	if (entity->id() == id)
	{
	    list_index = i;
	    EntityList map_entity_list = get_entities(entity->tag());
	    for (uint y = 0; y < map_entity_list.size() ; y++)
	    {
		if (map_entity_list[y]->id() == id)
		{
		    map_index = y;
		    return true;
		}
	    }
	}
    }

    return false;
}


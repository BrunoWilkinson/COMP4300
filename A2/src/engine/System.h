#ifndef SYSTEM_H
#define SYSTEM_H

#include <string>
#include "EntityManager.h"

class GameEngine;

class System
{
    std::string m_name = "";
    bool m_enabled = true;

public:
    System(const std::string& name);
    virtual void update(GameEngine* engine);
    void set_enabled(const bool enabled);
    bool is_enabled() const { return m_enabled; }
    const std::string& name() { return m_name; }
};

#endif

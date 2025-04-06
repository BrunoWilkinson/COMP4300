#ifndef RENDERSYSTEM_H
#define RENDERSYSTEM_H

#include "engine/System.h"

class GameEngine;

class RenderSystem : System
{
public:
    RenderSystem(const std::string& name) : System(name) {};
    virtual void update(GameEngine* engine) override;
};

#endif

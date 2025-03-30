#ifndef RENDERSYSTEM_H
#define RENDERSYSTEM_H

#include "engine/System.h"

class GameEngine;

class RenderSystem : System
{
public:
    virtual void update(GameEngine* engine) override;
};

#endif

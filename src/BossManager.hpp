
#pragma once

#include <list>
#include <vector>
#include "SDL.h"
#include "Explosion.hpp"

class Boss;

class BossManager
{
public:
    BossManager();
    ~BossManager();

    void Render();
    void Update();
    Boss* Spawn(float x, float y);

    void SpawnWave(float xOrigin, float yOrigin, int w, int h, float xDistance, float yDistance);
    void Destroy(Boss* alien);
    bool AllEnemyDead();

    void addExplosion(int x, int y);
    void updateExplosions();
    void renderExplosions();

    void Clear();

    SDL_Rect getWaveRect();

    float xOrigin, yOrigin;
    float xDistance, yDistance;

private:
    std::list<Boss*> alienList;
    std::vector<Explosion> explosions;

    SDL_Rect rect;
};


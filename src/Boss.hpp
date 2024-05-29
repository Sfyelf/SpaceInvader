#pragma once

#include <SDL.h>
#include <string>
#include "Image.hpp"
#include <list>
#include "AliensBullet.hpp"
#include <iostream>
#include "BossManager.hpp"

class Boss
{
public:

    Boss(const char* path);
    ~Boss();

    void Render();
    void Update();
    void Shoot();
    void UpdateAlienBullet();
    void Dead();
    void CheckHitBullet();

    bool CheckCollision(const SDL_Rect& otherRect);
    bool HitBullet(const SDL_Rect &anotherRect);

    double x, y, direct = 1, check = 0;

    SDL_Rect getRect();

    BossManager *manager;

    std::list<AliensBullet*> getBullets() const;

private:
    Image alienImage;



    double speed;

    std::list<AliensBullet*> alienBullet;

    float alienBulletCooldown;
    const float alienBulletCooldownTime;

};



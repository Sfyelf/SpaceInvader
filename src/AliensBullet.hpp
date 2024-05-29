
#pragma once

#include <SDL.h>
#include "Image.hpp"

class AliensBullet
{
public:
    AliensBullet(float xalien, float yalien);
    ~AliensBullet();

    void Render();
    void Move();
    void CheckHitShip();

    bool isOffScreen();
    bool HitShip(const SDL_Rect &anotherRect);

    float x, y;

    SDL_Rect getRect() const;

private:
    double speed;
    SDL_Rect rect;

    Image aliensBulletImage;
};

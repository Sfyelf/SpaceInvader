
#pragma once

#include <SDL.h>
#include "Image.hpp"

class Bullet
{
public:
    Bullet(float xship, float yship);
    ~Bullet();

    void Render();
    void Move();
    void CheckHitAlien();
    void Destroy();

    bool isOffScreen(float windowHeight);
    bool HitAlien(const SDL_Rect &anotherRect);

    SDL_Rect getRect() const;

    float x, y;

private:
    double speed;

    Image bulletImage;

};

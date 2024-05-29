#ifndef SHIP_HPP
#define SHIP_HPP

#include "Image.hpp"
#include <vector>
#include <list>
#include "Bullet.hpp"

class Ship
{
public:
    Ship();

    void Render();
    void HandleInput();
    void HandleMove();
    void Shoot();
    void UpdateBullet();
    void Dead();
    void DestroyBullet(Bullet& bullet);
    std::list<Bullet>& getBullets();

    bool CheckCollision(const SDL_Rect& otherRect);
    SDL_Rect getRect();

private:
    Image shipImage;

    float x, y;

    double speed;

    int inputDirection;

    std::list <Bullet> bullets;

    float bulletCooldown;    // Cooldown time in seconds
    const float bulletCooldownTime;
};

#endif

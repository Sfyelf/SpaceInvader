
#include "AliensBullet.hpp"
#include "Time.hpp"
#include "Game.hpp"

AliensBullet::AliensBullet(float xalien, float yalien) :
    speed(300),
    aliensBulletImage("graphics/creep_bullet.png", x, y),
    x(xalien),
    y(yalien)
{

}

AliensBullet::~AliensBullet()
{

}

void AliensBullet::Move()
{
    y += speed*Time::deltaTime();
}

void AliensBullet::Render()
{
    aliensBulletImage.xpos = x + 20;
    aliensBulletImage.ypos = y;
    aliensBulletImage.Render();
}

bool AliensBullet::isOffScreen()
{
    return y > 640;
}

SDL_Rect AliensBullet::getRect() const
{
    return aliensBulletImage.getRect();
}

bool AliensBullet::HitShip(const SDL_Rect &anotherRect)
{
    SDL_Rect shipRect = getRect();
    return SDL_HasIntersection(&shipRect, &anotherRect);
}

void AliensBullet::CheckHitShip()
{
    if (HitShip(ship->getRect()))
    {
        ship->Dead();
    }
}

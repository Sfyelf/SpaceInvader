
#include "Bullet.hpp"
#include "Time.hpp"
#include "Game.hpp"

Bullet::Bullet(float xship, float yship) :
    speed(300),
    bulletImage("graphics/bullet.png", x, y),
    x(xship),
    y(yship)

{

}

Bullet::~Bullet()
{

}

void Bullet::Move()
{
    y -= speed*Time::deltaTime();
}

void Bullet::Render()
{
    bulletImage.xpos = x + 20;
    bulletImage.ypos = y;
    bulletImage.Render();
}

bool Bullet::isOffScreen(float windowHeight)
{
    return y < 0;
}

SDL_Rect Bullet::getRect() const
{
    return bulletImage.getRect();
}

bool Bullet::HitAlien(const SDL_Rect &anotherRect)
{

}

void Bullet::CheckHitAlien()
{

}

void Bullet::Destroy()
{
    ship->DestroyBullet(*this);
    Mix_PlayChannel(-1, Game::explosionSound, 0);
}

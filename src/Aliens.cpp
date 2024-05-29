
#include "Aliens.hpp"
#include <SDL_image.h>
#include "Time.hpp"
#include "Game.hpp"

Alien::Alien(const char* path) :
    alienImage(path, 0, 0),
    x(50),
    y(50),
    speed(20),
    alienBulletCooldown(0),
    alienBulletCooldownTime(7)
{
    float lb = 0.0f * alienBulletCooldownTime;
    float up = 3.0f * alienBulletCooldownTime;
    alienBulletCooldown = lb + static_cast<float>(std::rand()) / RAND_MAX * (up - lb);
}

Alien::~Alien()
{

}

void Alien::Render()
{
    alienImage.xpos = x;
    alienImage.ypos = y;
    alienImage.Render();

    for (auto bullets : alienBullet)
    {
        bullets->Render();
    }
}

void Alien::Update()
{
    x = x + speed*direct*Time::deltaTime();
    if (check == 1)
    {
        y = y + 5;
        check = 0;
    }

    CheckHitBullet();
}

SDL_Rect Alien::getRect()
{
    return alienImage.getRect();
}

void Alien::Shoot()
{
    if (alienBulletCooldown <= 0) {
        float lb = 0.5f * alienBulletCooldownTime;
        float up = 2.0f * alienBulletCooldownTime;
        alienBulletCooldown = lb + static_cast<float>(std::rand()) / RAND_MAX * (up - lb);

        alienBullet.push_back(new AliensBullet(x, y));
    }
}

void Alien::UpdateAlienBullet()
{
    for (auto it = alienBullet.begin(); it != alienBullet.end();)
    {
        AliensBullet *bullet = *it;
        bullet->Move();
        bullet->CheckHitShip();
        if (bullet->isOffScreen()) {
            delete bullet;
            it = alienBullet.erase(it);

        } else {
            ++it;
        }
    }

    if (alienBulletCooldown > 0)
    {
        alienBulletCooldown -= Time::deltaTime(); // Decrease the cooldown timer
    }
}

std::list<AliensBullet*> Alien::getBullets() const {
    return alienBullet;
}

bool Alien::HitBullet(const SDL_Rect &anotherRect)
{
    SDL_Rect shipRect = getRect();
    return SDL_HasIntersection(&shipRect, &anotherRect);
}

void Alien::CheckHitBullet()
{
    std::list<Bullet>& bullets = ship->getBullets();

    for (auto& bullet : bullets)
    {
        if (HitBullet(bullet.getRect()))
        {
            Dead();
            bullet.Destroy();
//            score.score += 10;
        }
    }


}


bool Alien::CheckCollision(const SDL_Rect& otherRect)
{
    SDL_Rect rect = getRect();
    return SDL_HasIntersection(&rect, &otherRect);
}

void Alien::Dead()
{
    manager->Destroy(this);
    manager->addExplosion(x, y);
}

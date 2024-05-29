
#include "Ship.hpp"
#include "Input.hpp"
#include "Time.hpp"
#include <iostream>
#include "Game.hpp"

Ship::Ship() :
    shipImage("graphics/ship.png", 0, 0),
    speed(300),
    x(360),
    y(600),
    inputDirection(0),
    bulletCooldown(0),
    bulletCooldownTime(0.5)
{

}

void Ship::Render()
{
    shipImage.xpos = x;
    shipImage.ypos = y;
    shipImage.Render();

    for (auto& bullet : bullets)
    {
        bullet.Render();
    }
}

void Ship::HandleMove()
{
    x += inputDirection * speed * Time::deltaTime();
    if (x > 800) x = 0;
    if (x < 0) x = 800;
}

void Ship::HandleInput()
{
    inputDirection = 0;
    if (Input::GetKey(SDL_SCANCODE_LEFT)) inputDirection -= 1;
    if (Input::GetKey(SDL_SCANCODE_RIGHT)) inputDirection += 1;
    if (Input::GetKey(SDL_SCANCODE_SPACE)) Shoot();
}

void Ship::Shoot()
{
    if (bulletCooldown <= 0)
    {
        bullets.emplace_back(x, y);
        bulletCooldown = bulletCooldownTime;
        Mix_PlayChannel(-1, Game::shootSound, 0); // Reset the cooldown timer
    }
}

void Ship::UpdateBullet()
{

    for (auto it = bullets.begin(); it != bullets.end();) {
        it->Move();
        if (it->isOffScreen(640)) {
            it = bullets.erase(it);
        } else {
            ++it;
        }
    }

    if (bulletCooldown > 0)
    {
        bulletCooldown -= Time::deltaTime(); // Decrease the cooldown timer
    }
}

bool Ship::CheckCollision(const SDL_Rect& otherRect)
{
    SDL_Rect rect = getRect();
    return SDL_HasIntersection(&rect, &otherRect);
}

SDL_Rect Ship::getRect()
{
    return shipImage.getRect();
}

void Ship::Dead()
{
    Game::gameEnd = 1;
}

std::list<Bullet>& Ship::getBullets()
{
    return bullets;
}

void Ship::DestroyBullet(Bullet& bullet)
{
    bullets.remove_if([&bullet](const Bullet& b) {
        return &b == &bullet;
    });
}

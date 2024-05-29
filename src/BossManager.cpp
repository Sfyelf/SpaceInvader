
#include "BossManager.hpp"
#include<algorithm>
#include "Boss.hpp"

BossManager::BossManager() :
    rect()
{}

BossManager::~BossManager()
{
    for (Boss *alien : alienList)
    {
        delete alien;
    }
    alienList.clear();
}

void BossManager::Render()
{
    for (Boss *alien : alienList)
    {
        alien->Render();
    }
}

SDL_Rect BossManager::getWaveRect()
{
    if (alienList.empty()) return {};

    SDL_Rect temp = alienList.front()->getRect();

    int nx = temp.x;
    int ny = temp.y;
    int fx = temp.x + temp.w;
    int fy = temp.y + temp.h;

    for (Boss *alien : alienList)
    {
        SDL_Rect newrect = alien->getRect();
        nx = std::min(nx, newrect.x);
        ny = std::min(ny, newrect.y);
        fx = std::max(fx, newrect.x + newrect.w);
        fy = std::max(fy, newrect.y + newrect.h);
    }

    temp.x = nx;
    temp.y = ny;
    temp.w = fx-nx;
    temp.h = fy-ny;

    return temp;
}

void BossManager::Update()
{
    for (Boss *alien : alienList)
    {
        alien->Update();
        alien->UpdateAlienBullet();

        alien->Shoot();
    }

    SDL_Rect rect = getWaveRect();
    if (rect.x + rect.w >= 800)
    {
        for (Boss *alien : alienList)
        {
            alien->direct = -1;
            alien->check = 1;
        }
    }

    if (rect.x <= 0)
    {
        for (Boss *alien : alienList)
        {
            alien->direct = 1;
            alien->check = 1;
        }
    }

    //std::cout << "BossManager ran! \n";
}

Boss* BossManager::Spawn(float x, float y)
{
    Boss *alienIns = new Boss("graphics/extra.png");
    alienList.push_back(alienIns);
    alienIns->x = x;
    alienIns->y = y;

    alienIns->manager = this;

    return alienIns;
}

void BossManager::SpawnWave(float xOrigin, float yOrigin, int w, int h, float xDistance, float yDistance)
{

}

void BossManager::Destroy(Boss* alien)
{
    auto alienIterator = std::find(alienList.begin(), alienList.end(), alien);
    if (alienIterator == alienList.end()) return;

    delete alien;
    alienList.remove(alien);

    //std::cout << alienList.size() << "\n";
}

void BossManager::Clear()
{
    for (auto alien : alienList)
    {
        delete alien;
    }
    alienList.clear();
}

bool BossManager::AllEnemyDead()
{
    if (alienList.size() == 0) return 1;
    else return 0;
}

void BossManager::addExplosion(int x, int y) {
    explosions.emplace_back(x, y);
}

void BossManager::updateExplosions() {
    for (auto it = explosions.begin(); it != explosions.end();) {
        it->Update();
        if (it->isFinished()) {
            it = explosions.erase(it);
        } else {
            ++it;
        }
    }
}

void BossManager::renderExplosions() {
    for (auto& explosion : explosions) {
        explosion.Render();
    }
}


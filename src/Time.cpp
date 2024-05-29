#include "Time.hpp"

Time::Time():
    _deltaTime(0),
    _FPS(0),
    _currentTime(0),
    _stepCount(0),
    _currentTicks(SDL_GetPerformanceCounter()),
    _lastFrameTicks(SDL_GetPerformanceCounter()),
    _elapseTicks(SDL_GetPerformanceCounter())
{}

Time::~Time()
{}

double Time::deltaTime()
{
    return Instance()._deltaTime;
}
float Time::fps()
{
    return Instance()._FPS;
}
double Time::time()
{
    return Instance()._currentTime;
}
uint64_t Time::stepCount()
{
    return Instance()._stepCount;
}

void Time::Update()
{
    Instance()._currentTicks = SDL_GetPerformanceCounter();
    Instance()._elapseTicks = Instance()._currentTicks - Instance()._lastFrameTicks;
    Instance()._lastFrameTicks = Instance()._currentTicks;

    Instance()._deltaTime = static_cast<double>(Instance()._elapseTicks) / static_cast<double>(SDL_GetPerformanceFrequency());

    Instance()._currentTime += Instance()._deltaTime;

    Instance()._stepCount++;

    if (Instance()._deltaTime == 0) Instance()._FPS = 0;
    else Instance()._FPS = 1 / Instance()._deltaTime;
}

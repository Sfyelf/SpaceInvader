#pragma once

#include "SDL.h"

class Time
{
private:
    Time();
    ~Time();
    static Time& Instance()
    {
        static Time _instance;
        return _instance;
    }

private:
    double _deltaTime;
    float _FPS;
    double _currentTime;
    uint64_t _stepCount;

    uint64_t _currentTicks, _lastFrameTicks, _elapseTicks;

public:
    static void Update();

    static double deltaTime();
    static float fps();
    static double time();
    static uint64_t stepCount();
};

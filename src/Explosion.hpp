#pragma once

#include "SDL.h"
#include "Image.hpp"
#include "Time.hpp"

class Explosion {
public:
    Explosion(int x, int y);
    void Update();
    void Render();
    bool isFinished() const;

private:
    Image explosionImage;
    float frameDuration;
    float elapsedTime;
    int currentFrame;
    int totalFrames;
    bool finished;
};


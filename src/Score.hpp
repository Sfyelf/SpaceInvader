
#pragma once

#include "Game.hpp"
#include <stdio.h>

class Score
{
public:
    Score();
    ~Score();

    void NewHighscore();
    void LoadHighscore();

    double score = 0, highscore = -100;
};

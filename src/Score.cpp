
#include "Score.hpp"

Score::Score()
{

}

Score::~Score()
{

}

void Score::NewHighscore()
{
    std::freopen("Score.txt", "w", stdout);

    std::cout << highscore;

    fclose(stdout);

}

void Score::LoadHighscore()
{
    double bestscore;

    std::freopen("Score.txt", "r", stdin);
    std::cin >> bestscore;

    highscore = bestscore;
}

#include "Game.hpp"
#include "Input.hpp"
#include "Time.hpp"

Game *game = nullptr;


int main(int argc, char** argv){

    const int FPS = 60;
    const int frameDelay = 1000/FPS;

    Uint32 frameStart;
    int frameTime;

    game = new Game();

    if (!game->init("Space_Invader", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 640, 0))
    {
        throw;
    }

    game->createMenu();

    while (true)
    {
        frameStart = SDL_GetTicks();

        Input::Update();
        if (Input::IsQuit()) break;

        Time::Update();

        game->update();
        game->render();

        frameTime = SDL_GetTicks() - frameStart;

        if (frameDelay > frameTime)
        {
            SDL_Delay(frameDelay - frameTime);
        }

    }

    game->clean();

    return 0;
}

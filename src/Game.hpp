
#ifndef Game_hpp
#define Game_hpp

#include "SDL.h"
#include "SDL_image.h"
#include "SDL_mixer.h"
#include <iostream>
#include "Ship.hpp"

extern Ship *ship;
//extern Score *score;

class Game
{
    public:
        Game();
        ~Game();

        bool init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);
        void createGame();
        void createMenu();
        void gameOver();
        void gameWin();

        void handleEvents();
        void update();
        void render();
        void clean();
        void clearGame();
        void resetGame();

        static SDL_Renderer* renderer;
        bool gameStart = 0;
        bool continueGame = 0;
        bool instruc = 0;
        static bool gameEnd;
        bool win;

        static Mix_Chunk* shootSound;
        static Mix_Chunk* explosionSound;


    private:
        int cnt = 0;
        SDL_Window *window;
        //SDL_Renderer *renderer;

        SDL_Texture *backgroundTexture, *menuTexture, *tvTexture, *gameoverTexture, *gamewinTexture, *instrucTexture;

        Mix_Music *backgroundMusic;

};

#endif

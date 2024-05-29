
#include "Game.hpp"
#include "Input.hpp"
#include "TextureManager.hpp"
#include "Image.hpp"
#include "Ship.hpp"
#include "Aliens.hpp"
#include "AliensManager.hpp"
#include "Boss.hpp"
#include "BossManager.hpp"

SDL_Renderer* Game::renderer = nullptr;
Mix_Chunk* Game::shootSound = nullptr;
Mix_Chunk* Game::explosionSound = nullptr;

//Manager manager;
//auto& newShip(manager.addEntity());

bool Game::gameEnd = 0;

Game::Game()
{}
Game::~Game()
{}

Ship* ship = nullptr;
AliensManager* alienManager = nullptr;
BossManager* bossManager = nullptr;

//Score* score = nullptr;

bool Game::init(const char *title, int xpos, int ypos, int width, int height, bool fullscreen)
{
    int flags = 0;
    if (fullscreen)
    {
        flags = SDL_WINDOW_FULLSCREEN;
    }

    if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
    {
        std::cout << "Subsystem Initialised!..." << std::endl;

        window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);

        if (window)
        {
            std::cout << "Window created!" << std::endl;
        }
        else
        {
            return false;
        }

        renderer = SDL_CreateRenderer(window, -1, 0);
        if (renderer)
        {
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            std::cout << "Renderer created!" << std::endl;
        }
        else
        {
            return false;
        }

        if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
        {
            std::cerr << "SDL_mixer could not initialize! SDL_mixer Error: " << Mix_GetError() << std::endl;
            return false;
        }

        // Load background music
        backgroundMusic = Mix_LoadMUS("audio/music.wav");
        if (backgroundMusic == nullptr) {
            std::cerr << "Failed to load background music! SDL_mixer Error: " << Mix_GetError() << std::endl;
            return false;
        }

        // Play background music
        if (Mix_PlayMusic(backgroundMusic, -1) == -1) {
            std::cerr << "Failed to play background music! SDL_mixer Error: " << Mix_GetError() << std::endl;
            return false;
        }

        shootSound = Mix_LoadWAV("audio/laser.wav");  // Load the shooting sound effect
        if (shootSound == nullptr) {
            std::cout << "Failed to load shoot sound effect! SDL_mixer Error: " << Mix_GetError() << std::endl;
            return false;
        }

        explosionSound = Mix_LoadWAV("audio/explosion.wav");  // Load the explosion sound effect
        if (explosionSound == nullptr) {
            std::cout << "Failed to load explosion sound effect! SDL_mixer Error: " << Mix_GetError() << std::endl;
            return false;
        }
    }
    else
    {
        return false;
    }



//    newShip.addComponent<PositionComponent>();
    return true;
}

void Game::createMenu()
{
    tvTexture = TextureManager::LoadTexture("graphics/tv.png");
    menuTexture = TextureManager::LoadTexture("graphics/menu.png");
    instrucTexture = TextureManager::LoadTexture("graphics/instruction.png");
    std::cout << "Menu created! \n";
}

void Game::createGame()
{
    backgroundTexture = TextureManager::LoadTexture("graphics/bg.png");
    std::cout << "Background loaded! \n";

    ship = new Ship();
    alienManager = new AliensManager();
    bossManager = new BossManager();
    win = 0;
//    score = new Score();
//    alienManager->Spawn(10, 10);
    alienManager->SpawnWave(50, 50, 8, 6, 90, 50);
    bossManager->Spawn(0, 0);

    //bullet = new Bullet(5, 10);
}

void Game::update()
{
    Input::Update();

    if (gameEnd == 0)
    {
        if (gameStart == 0)
        {
            if (Input::GetKey(SDL_SCANCODE_X))
            {
                gameStart = 1;
                Game::createGame();
            }
        }
        else
        {
            if (Input::GetKey(SDL_SCANCODE_SPACE) || Input::GetKey(SDL_SCANCODE_LEFT)||Input::GetKey(SDL_SCANCODE_RIGHT)) instruc = 1;

            ship->HandleInput();
            ship->HandleMove();
            ship->UpdateBullet();
            alienManager->Update();
            alienManager->updateExplosions();
            bossManager->Update();
            bossManager->updateExplosions();

            Game::gameWin();
        }

    }
    else
    {

        if (continueGame) resetGame();
    }

    //std::cout << win << "\n";

}

void Game::render()
{
    SDL_RenderClear(renderer);

    //bg
    SDL_RenderCopy(renderer, menuTexture, NULL, NULL);
    SDL_RenderCopy(renderer, tvTexture, NULL, NULL);
    SDL_RenderCopy(renderer, backgroundTexture, NULL, NULL);
    SDL_RenderCopy(renderer, tvTexture, NULL, NULL);

    if (instruc == 0 && gameStart)
    {
        SDL_Rect srcRect = {0, 0, 91, 34};  // Assuming you want to copy the top-left 50x50 area of the texture
        SDL_Rect destRect = {300, 400, 91*2, 34*2};
        SDL_RenderCopy(renderer, instrucTexture, &srcRect, &destRect);
    }


    if (gameEnd == 0)
    {
        if (gameStart == 1)
        {
            ship->Render();
            alienManager->Render();
            alienManager->renderExplosions();
            bossManager->Render();
            bossManager->renderExplosions();

        }
    }
    else
    {
        if (win == 1)
        {
            gamewinTexture = TextureManager::LoadTexture("graphics/gamewin.png");
            SDL_RenderCopy(renderer, gamewinTexture, NULL, NULL);
        }
        else
        {
            Game::gameOver();
            SDL_RenderCopy(renderer, gameoverTexture, NULL, NULL);
        }



        if (Input::GetKey(SDL_SCANCODE_R)) continueGame = 1;

    }



    //where to add stuff
    SDL_RenderPresent(renderer);
}

void Game::clean()
{
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();

    SDL_DestroyTexture(backgroundTexture);
    SDL_DestroyTexture(menuTexture);
    SDL_DestroyTexture(tvTexture);
    SDL_DestroyTexture(gameoverTexture);

    // Free background music
    Mix_FreeMusic(backgroundMusic);
    Mix_FreeChunk(explosionSound);
    Mix_FreeChunk(shootSound);
    backgroundMusic = nullptr;

    // Quit SDL_mixer
    Mix_CloseAudio();

    //std::cout << "Game Cleaned" << std::endl;
}

void Game::clearGame() {
    // Clean up dynamically allocated objects
    delete ship;
    delete alienManager;
    delete bossManager;
    ship = nullptr;
    alienManager = nullptr;
    bossManager = nullptr;

    // Clear the screen
}

void Game::resetGame() {
    // Reinitialize game objects
    createGame();
    continueGame = 0;
    gameEnd = 0;
}

void Game::gameOver()
{
    gameoverTexture = TextureManager::LoadTexture("graphics/gameover.png");
}

void Game::gameWin()
{
    win = alienManager->AllEnemyDead();
    if (win) gameEnd = 1;
}

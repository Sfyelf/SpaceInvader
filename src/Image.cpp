
#include "Image.hpp"
#include "TextureManager.hpp"

Image::Image(const char* texturesheet, double x, double y)
{

    objTexture = TextureManager::LoadTexture(texturesheet);

    xpos = x;
    ypos = y;

}

Image::~Image()
{
    SDL_DestroyTexture(objTexture);
}

void Image::Render()
{
    int w, h;
    if (SDL_QueryTexture(objTexture, NULL, NULL, &w, &h) != 0)
    {
        printf("Error: Texture null\n");
    }

    SDL_Rect drect = {xpos, ypos, w, h};
    SDL_Rect srcrect = {0, 0, w, h};

    SDL_RenderCopy(Game::renderer, objTexture, &srcrect, &drect);
}

void Image::ChangeImage(const char* texturesheet)
{
    TextureManager::DestroyTexture(objTexture);
    objTexture = TextureManager::LoadTexture(texturesheet);
}

SDL_Rect Image::getRect() const
{
    int w, h;
    if (SDL_QueryTexture(objTexture, NULL, NULL, &w, &h) != 0)
    {
        printf("Error: Texture null\n");
    }

    SDL_Rect drect = {xpos, ypos, w, h};

    return drect;
}

SDL_Texture* Image::getTexture()
{
    return objTexture;
}

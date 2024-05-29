
#ifndef IMAGE_HPP
#define IMAGE_HPP

#include <SDL.h>

class Image{
public:
    Image(const char* texturesheet, double x, double y);
    ~Image();

    void Render();
    void ChangeImage(const char* texturesheet);

    double xpos;
    double ypos;

    SDL_Texture *getTexture();

    SDL_Rect getRect() const;


private:

    SDL_Texture* objTexture;
    SDL_Rect srcRect, destRect;

};

#endif

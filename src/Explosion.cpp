
#include "Explosion.hpp"
#include "Game.hpp"

Explosion::Explosion(int x, int y)
    : explosionImage("graphics/exp.png", x, y),  // Assuming you have an explosion sprite sheet
      frameDuration(0.1f),
      elapsedTime(0.0f),
      currentFrame(0),
      totalFrames(4),
      finished(false) {}

void Explosion::Update() {
    if (!finished) {
        elapsedTime += Time::deltaTime();
        if (elapsedTime >= frameDuration) {
            elapsedTime = 0.0f;
            currentFrame++;
            if (currentFrame >= totalFrames) {
                finished = true;
            }
        }
    }
}

void Explosion::Render() {
    if (!finished) {
        SDL_Rect srcRect = { currentFrame * explosionImage.getRect().w / totalFrames, 0, explosionImage.getRect().w / totalFrames, explosionImage.getRect().h };
        SDL_Rect dstRect = { explosionImage.xpos, explosionImage.ypos, explosionImage.getRect().w / totalFrames, explosionImage.getRect().h };
        SDL_RenderCopy(Game::renderer, explosionImage.getTexture(), &srcRect, &dstRect);
    }
}

bool Explosion::isFinished() const {
    return finished;
}


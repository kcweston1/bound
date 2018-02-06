#include <SDL2/SDL.h>
#include "renderer.h"

Renderer::Renderer()
    : renderer_(nullptr), cycles_(0)
{
    ticks_ = SDL_GetTicks();
}


Renderer::~Renderer()
{
    free();
}


bool Renderer::init(SDL_Window* window)
{
    // Sanity check.
    if (window == nullptr)
        return false;

    // Create the SDL renderer.
    renderer_ = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    // Error detection for SDL renderer.
    if (renderer_ == nullptr)
    {
        std::cout << "Could not create renderer:" << SDL_GetError() << '\n';
        return false;
    }

    return true;
}


void Renderer::free()
{
    if (renderer_ != nullptr)
    {
        SDL_DestroyRenderer(renderer_);
        renderer_ = nullptr;
    }
}


SDL_Renderer* Renderer::getSDLRenderer()
{
    return renderer_;
}


void Renderer::submit(Sprite* sprite)
{
    renderables_.push_back(sprite);
}


void Renderer::render()
{
    // Clear the screen and render the sprites.
    SDL_RenderClear(renderer_);

    for (Sprite* sprite : renderables_)
    {
        SDL_RenderCopy(renderer_,
            sprite->getSpriteSheet()->getSDLTexture(),
            &sprite->getSrcRect(),
            &sprite->getDstRect());
    }

    SDL_RenderPresent(renderer_);

    // Find the time for this frame.
    uint32_t frameTicks = SDL_GetTicks() - ticks_;

    // Force the correct FPS.
    if (frameTicks < TICKS_PER_FRAME)
        SDL_Delay(TICKS_PER_FRAME - frameTicks);

    renderables_.clear();

    ticks_ = SDL_GetTicks();
}
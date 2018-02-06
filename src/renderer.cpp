#include <SDL2/SDL.h>
#include "renderer.h"

Renderer::Renderer()
    : renderer_(nullptr), cycles_(0)
{
    timer_.start();
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

    // Force the correct FPS.
    if (timer_.time() < TICKS_PER_FRAME)
        SDL_Delay(TICKS_PER_FRAME - timer_.time());

    renderables_.clear();

    timer_.start();
}
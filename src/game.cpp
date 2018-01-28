#include "game.h"
#include "SDL2/SDL.h"

Game::Game()
{
    if (Game::init())
    {
        mainLoop();
    }
}


Game::~Game()
{
    SDL_DestroyRenderer(renderer_);
    SDL_DestroyWindow(window_);
    SDL_Quit();
}


bool Game::init()
{
    // Initialize members.
    window_ = nullptr;
    renderer_ = nullptr;

    // Initialize SDL2.
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        std::cout << "SDL_Init: " << SDL_GetError() << std::endl;
        return false;
    }

    // Create the SDL window.
    window_ = SDL_CreateWindow(
        "Bound Game",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        W,
        H,
        0);

    // Error detection for SDL window.
    if (window_ == nullptr)
    {
        std::cout << "Could not create window:" << SDL_GetError() << '\n';
        return false;
    }

    // Crate the SDL renderer.
    renderer_ = SDL_CreateRenderer(window_, -1, SDL_RENDERER_ACCELERATED);

    // Error detection for SDL renderer.
    if (renderer_ == nullptr)
    {
        std::cout << "Could not create window:" << SDL_GetError() << '\n';
        return false;
    }

    return true;
}


/*
The main game loop function.
*/
void Game::mainLoop()
{
    while (eventHandler())
    {

    }
}


/*
The main event loop function. Call the appropriate function
with the necessary data for each event type.

The return is only false when an event is found that closes
or quits the program.
*/
bool Game::eventHandler()
{
    SDL_Event event;

    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
        case SDL_KEYDOWN:
        case SDL_KEYUP:
            keyboardEvent(event.key.keysym.scancode,
                static_cast<bool>(event.key.state),
                static_cast<bool>(event.key.repeat));
            break;
        case SDL_MOUSEBUTTONDOWN:
        case SDL_MOUSEBUTTONUP:
            mouseButtonEvent(event.button.x,
                event.button.y,
                event.button.button,
                static_cast<bool>(event.button.state));
            break;
        case SDL_QUIT:
            SDL_FlushEvents(SDL_QUIT, SDL_LASTEVENT);
            return false;
        }
    }
    return true;
}


/*
Function to handle keyboard input.
key: the SDL_Scancode: https://wiki.libsdl.org/SDL_Scancode
state: true when pressed, false when released.
repeat: true if it is a repeated press.
*/
void Game::keyboardEvent(int key, bool state, bool repeat)
{

}


/*
Function to handle mouse button events.
x: the x location of the button press.
y: the y location of the button press.
button: the button  that was pressed.
SDL_BUTTON_LEFT
SDL_BUTTON_MIDDLE
SDL_BUTTON_RIGHT
SDL_BUTTON_X1
SDL_BUTTON_X2
state: true when pressed, false when released.
*/
void Game::mouseButtonEvent(int x, int y, uint8_t button, bool state)
{

}
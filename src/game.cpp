#include "game.h"
#include <SDL2/SDL_image.h>

Game::Game()
{
    if (Game::init())
    {
        mainLoop();
    }
}


Game::~Game()
{
    renderer_.free();
    SDL_DestroyWindow(window_);
    IMG_Quit();
    SDL_Quit();
}


bool Game::init()
{
    bool success = true;
    // Initialize members.
    window_ = nullptr;

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

    renderer_.init(window_);
    // Crate the SDL renderer.
    //renderer_ = SDL_CreateRenderer(window_, -1, SDL_RENDERER_ACCELERATED);

    // Error detection for SDL renderer.
    //if (renderer_ == nullptr)
    //{
        //std::cout << "Could not create window:" << SDL_GetError() << '\n';
        //return false;
    //}

    tileSheet_ = std::shared_ptr<SpriteSheet>(new SpriteSheet());
    if (!tileSheet_->init("assets/SpriteSheet.png", renderer_.getSDLRenderer(), SDL_PIXELFORMAT_RGBA8888))
        return false;

    playerSheet_ = std::shared_ptr<SpriteSheet>(new SpriteSheet());
    if (!playerSheet_->init("assets/Player.png", renderer_.getSDLRenderer(), SDL_PIXELFORMAT_RGBA8888))
        return false;

    tileSheet_->generate(0, 0, 256, 256);
    playerSheet_->generate(0, 0, 138, 138);

    //player_.setSpriteSheet(playerSheet_);
    player_.getSprite().setSpriteSheet(playerSheet_);
    

    // Populates vector "levels_" with data from levels
    initLevels();

    // Initialize the Player object;
    // Player could be an object or a polymorphic sprite.
    // player_.init(texture_, rect, rect);
    // player_ = std::make_unique(Sprite(texture_, rect, rect));
    // (above is the same as: player_ = new Sprite(texture_, rect, rect)
    // except you never have to call delete)

    return true;
}


/*
    The main game loop function.
*/
void Game::mainLoop()
{
    //Test code moved to initLevels();
    player_.getSprite().setSrcRect(playerSheet_->getSrcRect(0));
    player_.getSprite().setDstRect({500, 500, PlayerWidth, PlayerHeight});

    while (eventHandler())
    {
        // Update the game objects.
        player_.move();

        // Submit the sprites to the renderer.
        for (Sprite& tile : level_.getTiles())
            renderer_.submit(&tile);
        renderer_.submit(&player_.getSprite());

        // Render the frame.
        renderer_.render();
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
    switch (key)
    {
        case SDL_SCANCODE_SPACE:
            std::cout << player_ << std::endl;
            break;
    }
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
    switch (button)
    {
        case SDL_BUTTON_RIGHT:
            if (state) issueMoveCommand(x, y);
            break;
        default:
            break;
    }
}


void Game::initLevels()
{
    level_.generate(tileSheet_, LevelOne, 64, 64);
}


void Game::issueMoveCommand(int mouseX, int mouseY)
{
    // Update the player's direction, target coordinates, etc
    player_.updateMovement(mouseX, mouseY);

    // Update position of the target "blip" rect
    // TODO
}

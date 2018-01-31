#include <SDL2/SDL_image.h>
#include <iostream>
#include "spritesheet.h"
#include "constants.h"

SpriteSheet::SpriteSheet()
    : file_(""), texture_(nullptr), w_(0), h_(0)
{}


SpriteSheet::SpriteSheet(const std::string& file, SDL_Renderer* renderer, uint32_t pixelFormat, bool& success)
    : file_(file), texture_(nullptr), w_(0), h_(0)
{
    success = init(file, renderer, pixelFormat);
}


SpriteSheet::~SpriteSheet()
{
    SDL_DestroyTexture(texture_);
}


bool SpriteSheet::init(const std::string& file, SDL_Renderer* renderer, uint32_t pixelFormat)
{
    file_ = file;

    if (renderer == nullptr)
        return false;
    // Load the image.
    SDL_Surface* surface = IMG_Load(file.c_str());

    // Check the image loaded correctly into the surface.
    if (surface == nullptr)
    {
        std::cout << "Unable to load image " << file << " " 
                  << IMG_GetError() << std::endl;
        return false;
    }

    // Convert the surface to confirm the display format is correct.
    SDL_Surface* formatted = SDL_ConvertSurfaceFormat(surface, 
                                                      pixelFormat, 
                                                      0);

    // Confirm the conversion was successful.
    if (formatted == nullptr)
    {
        std::cout << "Cannot convert loaded surface to display format! "
                  << SDL_GetError() << std::endl;
        return false;
    }

    // Create a texture. Use the SDL_TEXTUREACCESS_STREAMING flag so that we
    // can access texture pixel data later.
    texture_ = SDL_CreateTexture(renderer, 
                                 pixelFormat, 
                                 SDL_TEXTUREACCESS_STREAMING, 
                                 formatted->w,
                                 formatted->h);

    // Confirm the texture created correctly.
    if (texture_ == nullptr)
    {
        std::cout << "Unable to create texture " << SDL_GetError() << std::endl;
        return false;
    }

    void* pixels;
    int pitch;

    // Lock the texture to access the pixel data.
    SDL_LockTexture(texture_, nullptr, &pixels, &pitch);

    // Copy the pixel data from the formatted surface to the texture.
    memcpy(pixels, formatted->pixels, formatted->pitch * formatted->h);    

    // Now that the copying is complete, unlock the texture.
    SDL_UnlockTexture(texture_);

    // Free the temporary surfaces.
    pixels = nullptr;
    SDL_FreeSurface(formatted);
    SDL_FreeSurface(surface);

    // Query the texture for basic data.
    SDL_QueryTexture(texture_, nullptr, nullptr, &w_, &h_);

    return true;
}


SDL_Texture* SpriteSheet::getSDLTexture()
{
    return texture_;
}


int SpriteSheet::getWidth() const
{
    return w_;
}


int SpriteSheet::getHeight() const
{
    return h_;
}


// Set the source rects. Not tested.
void SpriteSheet::setSrcRects(int offsetX, int offsetY, int tileW, int tileH, int n)
{
    for (int i = 0; i < n; ++i)
    {
        if (offsetY + tileH > h_)
        {
            std::cout << "Clip rect outside the bounds of the image.\n";
            break;
        }
        srcRects_.push_back({offsetX, offsetY, tileW, tileH});
        offsetX = (offsetX + tileW) % w_;
        if (offsetX == 0)
            offsetY += tileH;
    }
}


void SpriteSheet::addSrcRect(const SDL_Rect& src)
{
    srcRects_.push_back(src);
}


const SDL_Rect& SpriteSheet::operator[](std::size_t pos) const
{
    // Make sure we're not outside the bounds of the vector.
    assert(pos >= 0);
    assert(pos < srcRects_.size());

    return srcRects_[pos];
}


// TODO.
void SpriteSheet::trim()
{

}
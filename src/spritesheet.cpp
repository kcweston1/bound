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
    free();
}


bool SpriteSheet::init(const std::string& file, SDL_Renderer* renderer, uint32_t pixelFormat)
{
    file_ = file;

    if (renderer == nullptr)
        return false;

    // Create the SDL Texture.
    texture_ = IMG_LoadTexture(renderer, file_.c_str());

    // Error checking.
    if (texture_ == nullptr)
    {
        std::cout << "Could not create texture:" << IMG_GetError() << std::endl;
        return false;
    }

    // Query the texture for basic data.
    SDL_QueryTexture(texture_, &format_, nullptr, &w_, &h_);

    return true;
}


void SpriteSheet::free()
{
    if (texture_ != nullptr)
    {
        SDL_DestroyTexture(texture_);
        texture_ = nullptr;
    }

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

const SDL_Rect& SpriteSheet::getSrcRect(std::size_t pos) const
{
    // Make sure we're not outside the bounds of the vector.
    assert(pos >= 0);
    assert(pos < srcRects_.size());

    return srcRects_[pos];
}


void SpriteSheet::generate()
{
    // When the sprites are sorted, give the Y value a margin so that sprites
    // in the same row will be sorted by their X value only, as long as their
    // y value is within the y margin.
    const int YMargin = 10;

    // Create a temporary SDL surface in order to access the pixel data.
    SDL_Surface* surface = IMG_Load(file_.c_str());

    if (surface == nullptr)
    {
        std::cout << "Image " << IMG_GetError() << " could not be loaded.\n";
        return;
    }

    uint32_t* pixels = reinterpret_cast<uint32_t*>(surface->pixels);

    // Store the alpha mask for this surface.
    const int AlphaMask = surface->format->Amask;

    bool found, change, alphaFound;

    for (int y = 0; y < surface->h; ++y)
    {
        for (int x = 0; x < surface->w; ++x)
        {
            found = false;
            // Check if the pixel has an alpha value > 0.
            if ((AlphaMask & pixels[y * surface->w + x]) == 0)
                continue;

            // If the point is already contained inside a source rect, skip over
            // the rect and continue searching.
            SDL_Point pixel = {x, y};
            for (const SDL_Rect& rect : srcRects_)
            {
                if (SDL_PointInRect(&pixel, &rect))
                {
                    found = true;
                    x = rect.x + rect.w;
                    break;
                }
            }

            if (found)
                continue;

            // Create a rect of size 0.
            SDL_Rect newRect = {x, y, 0, 0};
            change = true;
            while (change)
            {
                change = false;
                // Expand the rect down (increase the height). Continue until a 
                // row of pixels is found where all alpha values are 0.
                while (newRect.y + newRect.h + 1 < surface->h)
                {
                    alphaFound = false;
                    for (int i = (newRect.y + newRect.h + 1) * surface->w + newRect.x;
                        i <= (newRect.y + newRect.h + 1) * surface->w + newRect.x + newRect.w;
                        ++i)
                    {
                        if (AlphaMask & pixels[i])
                        {
                            alphaFound = true;
                            break;
                        }
                    }
                    if (!alphaFound)
                        break;
                    newRect.h++;
                    change = true;
                }

                // Expand the rect to the left (deccrease the x value). 
                // Continue until a column of pixels is found where all alpha
                // values are 0.
                while (newRect.x - 1 >= 0)
                {
                    alphaFound = false;
                    for (int i = newRect.y * surface->w + newRect.x - 1;
                        i <= (newRect.y + newRect.h) * surface->w + newRect.x - 1;
                        i += surface->w)
                    {
                        if (AlphaMask & pixels[i])
                        {
                            alphaFound = true;
                            break;
                        }
                    }
                    if (!alphaFound)
                        break;
                    newRect.x--;
                    newRect.w++;
                    change = true;
                }

                // Expand the rect to the right (increase the width).
                // Continue until a column of pixels is found where all alpha
                // values are 0.
                while (newRect.x + newRect.w + 1 < surface->w)
                {
                    alphaFound = false;
                    for (int i = newRect.y * surface->w + newRect.x + newRect.w + 1;
                        i <= (newRect.y + newRect.h) * surface->w + newRect.x + newRect.w + 1;
                        i += surface->w)
                    {
                        if (AlphaMask & pixels[i])
                        {
                            alphaFound = true;
                            break;
                        }
                    }
                    if (!alphaFound)
                        break;
                    newRect.w++;
                    change = true;
                }
            }

            // Store the rect if it is not empty.
            if (!SDL_RectEmpty(&newRect))
                srcRects_.push_back(newRect);
        }
    }
    // First sort the source rects by the x value (left to right).
    std::stable_sort(srcRects_.begin(), srcRects_.end(),
        [](const SDL_Rect& r1, const SDL_Rect& r2) { return r1.x < r2.x; });

    // Second sort the source rects by the y value (top to bottom). Stable sort
    // is used so the order from the previous sort does not change. YMargin
    // is applied during this sort so that sprites in the same row that vary
    // in their y value by less than the YMargin are sorted is if their y
    // value was the same.
    std::stable_sort(srcRects_.begin(), srcRects_.end(),
        [](const SDL_Rect& r1, const SDL_Rect& r2) {
        return r1.y < r2.y && std::abs(r1.y - r2.y) > YMargin;
    });

    SDL_FreeSurface(surface);
}

/*
    Generate the source rects for the sprite sheet. Starting at the x and y
    offset, generate as many clip rects as possible given the w_/h_ of the
    current texture, and the clipW and clipH passed in.
*/
void SpriteSheet::generate(int offsetX, int offsetY, int clipW, int clipH)
{
    int n = (w_ / clipW) * (h_ / clipH);

    for (int i = 0; i < n; ++i)
    {
        srcRects_.push_back({offsetX, offsetY, clipW, clipH});
        offsetX = std::min(offsetX + clipW, w_) % w_;
        if (offsetX == 0)
            offsetY += clipH;
    }
}

/*
    Trim the sides of every source rect so that each edge contains at least
    one pixel where alpha > 0. This 'trims away' unused pixels and fits each
    source rect exactly to the containing sprite.
*/
void SpriteSheet::trim()
{
    SDL_PixelFormat* pixelFormat;
    uint32_t* pixels;
    uint8_t r, g, b, a;
    int pitch;
    int topLeft, topRight, bottomLeft, bottomRight;
    bool alphaFound;

    // Lock the texture. Error checking to make sure the lock didn't fail.
    if (SDL_LockTexture(texture_, nullptr, reinterpret_cast<void**>(&pixels), &pitch))
    {
        std::cout << "Texture failed to lock. " << SDL_GetError() << '\n';
        return;
    }

    pixelFormat = SDL_AllocFormat(format_);

    for (SDL_Rect& rect : srcRects_)
    {
        // Trim the Y
        while (1)
        {
            alphaFound = false;
            topLeft = rect.y * w_ + rect.x;
            for (int i = topLeft; i < topLeft + rect.w; ++i)
            {
                SDL_GetRGBA(pixels[i], pixelFormat, &r, &g, &b, &a);
                if (static_cast<int>(a) > 0)
                {
                    alphaFound = true;
                    break;
                }
            }
            if (alphaFound)
                break;
            rect.y++;
            rect.h--;
            if (rect.h == 0)
                break;
        }

        // Trim the H
        while (1)
        {
            bool alphaFound = false;
            int bottomLeft = (rect.y + rect.h) * w_ + rect.x;
            for (int i = bottomLeft; i < bottomLeft + rect.w; ++i)
            {
                SDL_GetRGBA(pixels[i], pixelFormat, &r, &g, &b, &a);
                if (static_cast<int>(a) > 0)
                {
                    alphaFound = true;
                    break;
                }
            }

            if (alphaFound)
                break;
            rect.h--;
            if (rect.h == 0)
                break;
        }

        // Trim the X
        while (1)
        {
            bool alphaFound = false;
            int topLeft = rect.y * w_ + rect.x;
            int bottomLeft = (rect.y + rect.h) * w_ + rect.x;
            for (int i = topLeft; i < bottomLeft; i += w_)
            {
                SDL_GetRGBA(pixels[i], pixelFormat, &r, &g, &b, &a);
                if (static_cast<int>(a) > 0)
                {
                    alphaFound = true;
                    break;
                }
            }
            if (alphaFound)
                break;
            rect.x++;
            rect.w--;
            if (rect.w == 0)
                break;
        }

        // Trim the W
        while (1)
        {
            bool alphaFound = false;
            int topRight = rect.y * w_ + rect.x + rect.w;
            int bottomRight = (rect.y + rect.h) * w_ + rect.x + rect.w;
            for (int i = topRight; i < bottomRight; i += w_)
            {
                SDL_GetRGBA(pixels[i], pixelFormat, &r, &g, &b, &a);
                if (static_cast<int>(a) > 0)
                {
                    alphaFound = true;
                    break;
                }
            }
            if (alphaFound)
                break;
            rect.w--;
            if (rect.w == 0)
                break;
        }
    }


    SDL_UnlockTexture(texture_);
    SDL_FreeFormat(pixelFormat);
}
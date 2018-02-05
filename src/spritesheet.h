#ifndef SPRITESHEET_H
#define SPRITESHEET_H

#include <vector>
#include <string>
#include <algorithm>
#include <SDL2/SDL.h>

/*
    Wrapper class for a SDL_Texture. The texture is formatted so that we can 
    access the pixel data directly. This class will also keep a vector of
    source rects to the spritesheet that can be accessed using an index and
    the [] operator.
*/

class SpriteSheet
{
public:
    SpriteSheet();
    SpriteSheet(const std::string& file, SDL_Renderer* renderer, uint32_t pixelFormat, bool& success);
    ~SpriteSheet();
    bool init(const std::string& file, SDL_Renderer* renderer, uint32_t pixelFormat);
    void free();
    SDL_Texture* getSDLTexture();
    int getWidth() const;
    int getHeight() const;
    void setSrcRects(int offsetX, int offsetY, int tileW, int tileH, int n);
    void addSrcRect(const SDL_Rect& src);
    const SDL_Rect& getSrcRect(std::size_t pos) const;
    void generate();
    void generate(int offsetX, int offsetY, int clipW, int clipH);
    void trim();
private:
    std::string file_;
    SDL_Texture* texture_;
    std::vector<SDL_Rect> srcRects_;
    int w_, h_;
    uint32_t format_;
};

#endif
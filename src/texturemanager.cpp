#include "Header\texturemanager.hpp"
#include "Header\game.hpp"
#include <cmath>

//Hàm này dùng để load texture từ file
//Hàm này sẽ trả về một con trỏ đến texture đã load
SDL_Texture* TextureManager::loadTexture(const char* fileName, SDL_Renderer* renderer) {
    return IMG_LoadTexture(renderer, fileName);
}

//Hàm này dùng để giải phóng texture đã load
void TextureManager::renderTexture(SDL_Texture* texture, SDL_Renderer* renderer, int x, int y, float scale) {
    SDL_Rect dest = {x, y, (int)(Game::BALL_WIDTH * scale), (int)(Game::BALL_HEIGHT * scale)};
    SDL_RenderCopy(renderer, texture, NULL, &dest);
}
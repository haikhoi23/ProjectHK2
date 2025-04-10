#include "Header/ScoreManager.hpp"
#include <iostream>
using namespace std;

ScoreManager::ScoreManager()
{
    strokes = 0;
    font = nullptr;
}

ScoreManager::~ScoreManager()
{
    if (font)
    {
        TTF_CloseFont(font);
    }
}

bool ScoreManager::init(SDL_Renderer* renderer, const string& fontPath, int fontSize) {
    font = TTF_OpenFont(fontPath.c_str(), fontSize);
    if (!font) {
        std::cerr << "Failed to load font: " << TTF_GetError() << std::endl;
        return false;
    }
    return true;
}

void ScoreManager::addStroke() {
    strokes++;
}

void ScoreManager::resetStroke() {
    strokes = 0;
}

int ScoreManager::getScore() const {
    return strokes;
}

void ScoreManager::render(SDL_Renderer* renderer, int x, int y) {
    string scoreText = "Strokes: " + to_string(strokes);
    SDL_Color color = { 255, 255, 255 }; 

    SDL_Surface* textSurface = TTF_RenderText_Solid(font, scoreText.c_str(), color);
    if (!textSurface) {
        std::cerr << "TTF_RenderText_Solid Error: " << TTF_GetError() << std::endl;
        return;
    }

    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    if (!textTexture) {
        std::cerr << "SDL_CreateTextureFromSurface Error: " << SDL_GetError() << std::endl;
        SDL_FreeSurface(textSurface);
        return;
    }

    SDL_Rect destRect = { x, y, textSurface->w, textSurface->h };
    SDL_RenderCopy(renderer, textTexture, NULL, &destRect);

    SDL_DestroyTexture(textTexture);
    SDL_FreeSurface(textSurface);
}

void ScoreManager::cleanup() {
    if (font) {
        TTF_CloseFont(font);
        font = nullptr;
    }
}

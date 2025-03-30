#include "Header/game.hpp"
#include "Header/menu.hpp"
#include "Header/renderer.hpp"
#include <SDL.h>
#include <iostream>
int main(int argc, char* argv[]) {
    
    // Initialize SDL, window and renderer
    // SDL_Window* window = SDL_CreateWindow("Mini Golf", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, Game::SCREEN_WIDTH, Game::SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    // if (!window) {
    //     std::cerr << "Failed to create window: " << SDL_GetError() << std::endl;
    //     return -1;
    // }
    // SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    // if (!renderer) {
    //     std::cerr << "Failed to create renderer: " << SDL_GetError() << std::endl;
    //     SDL_DestroyWindow(window);
    //     return -1;
    // }
    Game game;
    game.init();
    game.run();
    game.cleanup();
    return 0;
}
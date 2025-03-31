#ifndef RENDERER_HPP
#define RENDERER_HPP
#include <SDL.h>

// Hàm này dùng để khởi tạo SDL và tạo cửa sổ và renderer
class Renderer {
    public:
        static bool init(SDL_Window*& window, SDL_Renderer*& renderer, const char* title, int width, int height);
        static void cleanup(SDL_Window* window, SDL_Renderer* renderer);
    };
    
#endif
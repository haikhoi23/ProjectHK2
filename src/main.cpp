#include "Header/game.hpp"
#include "Header/menu.hpp"
#include "Header/renderer.hpp"
#include <SDL.h>
#include <iostream>

//Hàm chính của chương trình
//Khởi tạo game, chạy game và giải phóng tài nguyên
int main(int argc, char* argv[]) {
    Game game;
    game.init();
    game.run();
    game.cleanup();
    return 0;
}
#include "Header/menu.hpp"
#include "Header/texturemanager.hpp"
#include "Header/renderer.hpp"
#include <iostream>

//Hàm contructor khởi tạo các biến cần thiết cho menu
//Hàm destructor giải phóng các tài nguyên đã sử dụng trong menu
Menu::Menu()
{
    menubackgroundTexture = nullptr;
    playbuttonTexture = nullptr;
    exitbuttonTexture = nullptr;
    playbuttonPressedTexture = nullptr;
    exitbuttonPressedTexture = nullptr;
    playButtonRect = {316, 300, 168, 112};
    exitButtonRect = {316, 450, 168, 112};
    playButtonPressed = false;
    exitButtonPressed = false;
}

Menu::~Menu()
{
    cleanup();
}

//Hàm này dùng để khởi tạo menu
bool Menu::init(SDL_Renderer *renderer)
{
    menubackgroundTexture = TextureManager::loadTexture("assets/menubackground.jpg", renderer);
    if (!menubackgroundTexture)
    {
        std::cerr << "Failed to load menu background texture!" << std::endl;
        return false;
    }
    playbuttonTexture = TextureManager::loadTexture("assets/playbutton.png", renderer);
    if (!playbuttonTexture)
    {
        std::cerr << "Failed to load play button texture!" << std::endl;
        return false;
    }
    exitbuttonTexture = TextureManager::loadTexture("assets/exitbutton.png", renderer);
    if (!exitbuttonTexture)
    {
        std::cerr << "Failed to load exit button texture!" << std::endl;
        return false;
    }
    playbuttonPressedTexture = TextureManager::loadTexture("assets/playbutton_pressed.png", renderer);
    if (!playbuttonPressedTexture)
    {
        std::cerr << "Failed to load play button pressed texture!" << std::endl;
        return false;
    }
    exitbuttonPressedTexture = TextureManager::loadTexture("assets/exitbutton_pressed.png", renderer);
    if (!exitbuttonPressedTexture)
    {
        std::cerr << "Failed to load exit button pressed texture!" << std::endl;
        return false;
    }
    return true;
}

//Hàm này dùng để xử lý các sự kiện trong menu
//Nếu người dùng nhấn nút play thì trả về MenuState::PLAY
//Nếu người dùng nhấn nút exit thì trả về MenuState::EXIT
//Nếu người dùng nhấn nút khác thì trả về MenuState::MAIN_MENU
//Hàm này sẽ kiểm tra xem người dùng có nhấn nút nào không, nếu có thì sẽ trả về trạng thái tương ứng
MenuState Menu::processEvents(SDL_Event &event)
{
    if (event.type == SDL_QUIT)
    {
        return MenuState::EXIT;
    }
    else if (event.type == SDL_MOUSEBUTTONDOWN)
    {
        int mouseX = event.button.x;
        int mouseY = event.button.y;
        if (mouseX >= exitButtonRect.x && mouseX <= exitButtonRect.x + exitButtonRect.w && mouseY >= exitButtonRect.y && mouseY <= exitButtonRect.y + exitButtonRect.h)
        {
            exitButtonPressed = true;
        }
        else if (mouseX >= playButtonRect.x && mouseX <= playButtonRect.x + playButtonRect.w && mouseY >= playButtonRect.y && mouseY <= playButtonRect.y + playButtonRect.h)
        {
            playButtonPressed = true;
        }
    }
    else if (event.type == SDL_MOUSEBUTTONUP)
    {
        int mouseX = event.button.x;
        int mouseY = event.button.y;
        if (mouseX >= exitButtonRect.x && mouseX <= exitButtonRect.x + exitButtonRect.w && mouseY >= exitButtonRect.y && mouseY <= exitButtonRect.y + exitButtonRect.h)
        {
            exitButtonPressed = false;
            return MenuState::EXIT;
        }
        else if (mouseX >= playButtonRect.x && mouseX <= playButtonRect.x + playButtonRect.w && mouseY >= playButtonRect.y && mouseY <= playButtonRect.y + playButtonRect.h)
        {
            playButtonPressed = false;
            return MenuState::PLAY;
        }
        exitButtonPressed = false;
        playButtonPressed = false;
    }
    return MenuState::MAIN_MENU;
}

//Hàm này dùng để render menu
void Menu::render(SDL_Renderer *renderer)
{
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, menubackgroundTexture, NULL, NULL);
    if (playButtonPressed)
    {
        SDL_RenderCopy(renderer, playbuttonPressedTexture, NULL, &playButtonRect);
    }
    else
    {
        SDL_RenderCopy(renderer, playbuttonTexture, NULL, &playButtonRect);
    }
    if (exitButtonPressed)
    {
        SDL_RenderCopy(renderer, exitbuttonPressedTexture, NULL, &exitButtonRect);
    }
    else
    {
        SDL_RenderCopy(renderer, exitbuttonTexture, NULL, &exitButtonRect);
    }
}

//Hàm này dùng để giải phóng các tài nguyên đã sử dụng trong menu
void Menu::cleanup()
{
    if (menubackgroundTexture)
    {
        SDL_DestroyTexture(menubackgroundTexture);
        menubackgroundTexture = nullptr;
    }
    if (playbuttonTexture)
    {
        SDL_DestroyTexture(playbuttonTexture);
        playbuttonTexture = nullptr;
    }
    if (exitbuttonTexture)
    {
        SDL_DestroyTexture(exitbuttonTexture);
        exitbuttonTexture = nullptr;
    }
    if (playbuttonPressedTexture)
    {
        SDL_DestroyTexture(playbuttonPressedTexture);
        playbuttonPressedTexture = nullptr;
    }
    if (exitbuttonPressedTexture)
    {
        SDL_DestroyTexture(exitbuttonPressedTexture);
        exitbuttonPressedTexture = nullptr;
    }
}
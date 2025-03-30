#include "Header/menu.hpp"
#include "Header/texturemanager.hpp"
#include "Header/renderer.hpp"
#include <iostream>

Menu::Menu()
{
    menubackgroundTexture = nullptr;
    playbuttonTexture = nullptr;
    exitbuttonTexture = nullptr;
    playbuttonPressedTexture = nullptr;
    exitbuttonPressedTexture = nullptr;
    playButtonRect = {316, 300, 168, 88};
    exitButtonRect = {316, 450, 168, 88};
    playButtonPressed = false;
    exitButtonPressed = false;
}

Menu::~Menu()
{
    cleanup();
}

bool Menu::init(SDL_Renderer *renderer)
{
    menubackgroundTexture = TextureManager::loadTexture("assets/menubackground.png", renderer);
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
#include "Header/menu.hpp"
#include "Header/texturemanager.hpp"
#include "Header/renderer.hpp"
#include <iostream>

// Hàm constructor khởi tạo các biến cần thiết cho menu
// Hàm destructor giải phóng các tài nguyên đã sử dụng trong menu
Menu::Menu()
{
    menuState = MenuState::MAIN_MENU;
    
    menubackgroundTexture = nullptr;
    playbuttonTexture = nullptr;
    exitbuttonTexture = nullptr;
    continuebuttonTexture = nullptr;
    replaybuttonTexture = nullptr;

    playbuttonPressedTexture = nullptr;
    exitbuttonPressedTexture = nullptr;
    continuebuttonPressedTexture = nullptr;
    replaybuttonPressedTexture = nullptr;

    playButtonRect = {316, 300, 168, 112};
    exitButtonRect = {316, 450, 168, 112};
    replayButtonRect = {200, 450, 88, 88};
    continueButtonRect = {512, 450, 88, 88};

    playButtonPressed = false;
    exitButtonPressed = false;
    continueButtonPressed = false;
    replayButtonPressed = false;
    isInterLevel = false;
}

Menu::~Menu()
{
    cleanup();
}

// Hàm này dùng để khởi tạo menu
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
    continuebuttonTexture = TextureManager::loadTexture("assets/continuebutton.png", renderer);
    if (!continuebuttonTexture)
    {
        std::cerr << "Failed to load continue button texture!" << std::endl;
        return false;
    }
    replaybuttonTexture = TextureManager::loadTexture("assets/replaybutton.png", renderer);
    if (!replaybuttonTexture)
    {
        std::cerr << "Failed to load replay button texture!" << std::endl;
        return false;
    }
    continuebuttonPressedTexture = TextureManager::loadTexture("assets/continuebutton_pressed.png", renderer);
    if (!continuebuttonPressedTexture)
    {
        std::cerr << "Failed to load continue button pressed texture!" << std::endl;
        return false;
    }
    replaybuttonPressedTexture = TextureManager::loadTexture("assets/replaybutton_pressed.png", renderer);
    if (!replaybuttonPressedTexture)
    {
        std::cerr << "Failed to load replay button pressed texture!" << std::endl;
        return false;
    }
    return true;
}

// Hàm này dùng để xử lý các sự kiện trong menu
// Nếu người dùng nhấn nút play thì trả về MenuState::PLAY
// Nếu người dùng nhấn nút exit thì trả về MenuState::EXIT
// Nếu người dùng nhấn nút khác thì trả về MenuState::MAIN_MENU
// Hàm này sẽ kiểm tra xem người dùng có nhấn nút nào không, nếu có thì sẽ trả về trạng thái tương ứng
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

        if (menuState == MenuState::MAIN_MENU)
        {
            if (mouseX >= exitButtonRect.x && mouseX <= exitButtonRect.x + exitButtonRect.w &&
                mouseY >= exitButtonRect.y && mouseY <= exitButtonRect.y + exitButtonRect.h)
            {
                exitButtonPressed = true;
            }
            else if (mouseX >= playButtonRect.x && mouseX <= playButtonRect.x + playButtonRect.w &&
                     mouseY >= playButtonRect.y && mouseY <= playButtonRect.y + playButtonRect.h)
            {
                playButtonPressed = true;
            }
        }
        else if (menuState == MenuState::INTER_LEVEL)
        {
            if (mouseX >= continueButtonRect.x && mouseX <= continueButtonRect.x + continueButtonRect.w &&
                mouseY >= continueButtonRect.y && mouseY <= continueButtonRect.y + continueButtonRect.h)
            {
                continueButtonPressed = true;
            }
            else if (mouseX >= replayButtonRect.x && mouseX <= replayButtonRect.x + replayButtonRect.w &&
                     mouseY >= replayButtonRect.y && mouseY <= replayButtonRect.y + replayButtonRect.h)
            {
                replayButtonPressed = true;
            }
        }
    }
    else if (event.type == SDL_MOUSEBUTTONUP)
    {
        int mouseX = event.button.x;
        int mouseY = event.button.y;

        if (menuState == MenuState::MAIN_MENU)
        {
            if (mouseX >= exitButtonRect.x && mouseX <= exitButtonRect.x + exitButtonRect.w &&
                mouseY >= exitButtonRect.y && mouseY <= exitButtonRect.y + exitButtonRect.h)
            {
                exitButtonPressed = false;
                return MenuState::EXIT;
            }
            else if (mouseX >= playButtonRect.x && mouseX <= playButtonRect.x + playButtonRect.w &&
                     mouseY >= playButtonRect.y && mouseY <= playButtonRect.y + playButtonRect.h)
            {
                playButtonPressed = false;
                return MenuState::PLAY;
            }
        }
        else if (menuState == MenuState::INTER_LEVEL)
        {
            if (mouseX >= continueButtonRect.x && mouseX <= continueButtonRect.x + continueButtonRect.w &&
                mouseY >= continueButtonRect.y && mouseY <= continueButtonRect.y + continueButtonRect.h)
            {
                continueButtonPressed = false;
                return MenuState::CONTINUE;
            }
            else if (mouseX >= replayButtonRect.x && mouseX <= replayButtonRect.x + replayButtonRect.w &&
                     mouseY >= replayButtonRect.y && mouseY <= replayButtonRect.y + replayButtonRect.h)
            {
                replayButtonPressed = false;
                return MenuState::PLAY;
            }
        }

        exitButtonPressed = false;
        playButtonPressed = false;
        continueButtonPressed = false;
        replayButtonPressed = false;
    }

    return menuState;  // Luôn trả về trạng thái hiện tại nếu không có gì thay đổi
}

// Hàm này dùng để thiết lập trạng thái giữa các cấp độ
void Menu::setInterLevel(bool flag)
{
    isInterLevel = flag;
    if (flag)
    {
        menuState = MenuState::INTER_LEVEL;
    }
    else
    {
        menuState = MenuState::MAIN_MENU;
    }
}

// Hàm này dùng để render menu
void Menu::render(SDL_Renderer* renderer)
{
    if (!isInterLevel)
    {
        //Render menu background
        SDL_RenderCopy(renderer, menubackgroundTexture, NULL, NULL);
    }

    if (isInterLevel)
    {
        // Render trạng thái giữa các cấp độ: Continue và Replay.
        if (replayButtonPressed)
            SDL_RenderCopy(renderer, replaybuttonPressedTexture, NULL, &replayButtonRect);
        else
            SDL_RenderCopy(renderer, replaybuttonTexture, NULL, &replayButtonRect);

        if (continueButtonPressed)
            SDL_RenderCopy(renderer, continuebuttonPressedTexture, NULL, &continueButtonRect);
        else
            SDL_RenderCopy(renderer, continuebuttonTexture, NULL, &continueButtonRect);
    }
    else
    {
        // Render menu chính: Play và Exit.
        if (playButtonPressed)
            SDL_RenderCopy(renderer, playbuttonPressedTexture, NULL, &playButtonRect);
        else
            SDL_RenderCopy(renderer, playbuttonTexture, NULL, &playButtonRect);

        if (exitButtonPressed)
            SDL_RenderCopy(renderer, exitbuttonPressedTexture, NULL, &exitButtonRect);
        else
            SDL_RenderCopy(renderer, exitbuttonTexture, NULL, &exitButtonRect);
    }
}

void Menu::reset()
{
    playButtonPressed = false;
    exitButtonPressed = false;
    continueButtonPressed = false;
    replayButtonPressed = false;
    isInterLevel = false;
    menuState = MenuState::MAIN_MENU;
}

// Hàm này dùng để giải phóng các tài nguyên đã sử dụng trong menu
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
    if (continuebuttonTexture)
    {
        SDL_DestroyTexture(continuebuttonTexture);
        continuebuttonTexture = nullptr;
    }
    if (replaybuttonTexture)
    {
        SDL_DestroyTexture(replaybuttonTexture);
        replaybuttonTexture = nullptr;
    }
    if (continuebuttonPressedTexture)
    {
        SDL_DestroyTexture(continuebuttonPressedTexture);
        continuebuttonPressedTexture = nullptr;
    }
    if (replaybuttonPressedTexture)
    {
        SDL_DestroyTexture(replaybuttonPressedTexture);
        replaybuttonPressedTexture = nullptr;
    }
}
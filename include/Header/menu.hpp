#ifndef MENU_HPP
#define MENU_HPP

#include <SDL.h>


// Hàm này dùng để khởi tạo các trạng thái của menu
enum class MenuState {
    MAIN_MENU,
    PLAY,
    INTER_LEVEL,
    CONTINUE,
    EXIT
};

class Menu {
public:
    Menu();
    ~Menu();

    bool init(SDL_Renderer* renderer);

    MenuState processEvents(SDL_Event& event);

    void setInterLevel(bool flag);

    void render(SDL_Renderer* renderer);

    void cleanup();
private:
    MenuState menuState;
    
    SDL_Texture* menubackgroundTexture;

    SDL_Texture* playbuttonTexture;
    SDL_Texture* exitbuttonTexture;
    SDL_Texture* continuebuttonTexture;
    SDL_Texture* replaybuttonTexture;

    SDL_Texture* playbuttonPressedTexture;
    SDL_Texture* exitbuttonPressedTexture;
    SDL_Texture* continuebuttonPressedTexture;
    SDL_Texture* replaybuttonPressedTexture;

    SDL_Rect playButtonRect;
    SDL_Rect exitButtonRect;
    SDL_Rect continueButtonRect;
    SDL_Rect replayButtonRect;

    bool playButtonPressed;
    bool exitButtonPressed;
    bool continueButtonPressed;
    bool replayButtonPressed;
    bool isInterLevel;
};

#endif
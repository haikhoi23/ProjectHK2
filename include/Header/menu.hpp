#ifndef MENU_HPP
#define MENU_HPP

#include <SDL.h>

enum class MenuState {
    MAIN_MENU,
    PLAY,
    EXIT
};

class Menu {
public:
    Menu();
    ~Menu();

    bool init(SDL_Renderer* renderer);

    MenuState processEvents(SDL_Event& event);

    void render(SDL_Renderer* renderer);

    void cleanup();
private:
    SDL_Texture* menubackgroundTexture;
    SDL_Texture* playbuttonTexture;
    SDL_Texture* exitbuttonTexture;
    SDL_Texture* playbuttonPressedTexture;
    SDL_Texture* exitbuttonPressedTexture;
    SDL_Rect playButtonRect;
    SDL_Rect exitButtonRect;
    bool playButtonPressed;
    bool exitButtonPressed;
};

#endif
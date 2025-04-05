#ifndef SCOREMANAGER_HPP
#define SCOREMANAGER_HPP

#include <SDL.h>
#include <SDL_ttf.h>
#include <string>
using namespace std;
class ScoreManager
{
public:
    ScoreManager();
    ~ScoreManager();

    bool init(SDL_Renderer *renderer, const string& fontPath, int fontSize);
    void addStroke();
    void resetStroke();
    void render(SDL_Renderer *renderer, int x, int y);
    int getScore() const;
private:
    int strokes;
    TTF_Font *font;
};
#endif
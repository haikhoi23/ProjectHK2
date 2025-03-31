#ifndef LEVEL_HPP
#define LEVEL_HPP

#include "Header/obstacle.hpp"
#include <SDL.h>
#include <vector>
using namespace std;

//Hàm này dùng để khởi tạo đối tượng Level với vị trí bóng, danh sách chướng ngại vật và vị trí lỗ
class Level {
public:
    Level(SDL_Point ballStartPosition, vector<Obstacle> obstacles, SDL_Point holePosition);
    SDL_Point getBallStartPosition() const;
    const vector<Obstacle>& getObstacles() const;
    SDL_Point getHolePosition() const;
private:
    vector<Obstacle> obstacles;
    SDL_Point holePosition;
    SDL_Point ballStartPosition;
};

#endif 

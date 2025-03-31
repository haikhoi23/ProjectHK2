#include "Header/level.hpp"
#include "Header/obstacle.hpp"
#include <SDL.h>
using namespace std;
// Hàm khởi tạo đối tượng Level với vị trí bóng, danh sách chướng ngại vật và vị trí lỗ
Level::Level(SDL_Point _ballStartPosition, vector<Obstacle> _obstacles, SDL_Point _holePosition){
    ballStartPosition = _ballStartPosition;
    obstacles = _obstacles;
    holePosition = _holePosition;
}
const vector<Obstacle>& Level::getObstacles() const {
    return obstacles;
}

SDL_Point Level::getHolePosition() const {
    return holePosition;
}

SDL_Point Level::getBallStartPosition() const {
    return ballStartPosition;
}
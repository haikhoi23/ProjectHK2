#include "Header\game.hpp"
#include "Header\renderer.hpp"
#include "Header\texturemanager.hpp"
#include "Header\obstacle.hpp"
#include "Header\level.hpp"
#include <iostream>
#include <cmath>
#include <SDL.h>
#include <SDL_image.h>
Game::Game()
{
    ballX = 50;
    ballY = 300;
    velocityX = 0;
    velocityY = 0;
    MAX_VELOCITY = 25.0f;
    ballScale = 1.0f;
    holeX = 700;
    holeY = 300;
    dragging = false;
    startX = 0;
    startY = 0;
    currentLevel = 0;
    menuState = MenuState::MAIN_MENU;
}

Game::~Game() {}

// hàm này dùng để khởi tạo đối tượng đồ họa game cùng các level
bool Game::init()
{
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");

    if (!Renderer::init(window, renderer, "MiniGolf", SCREEN_WIDTH, SCREEN_HEIGHT))
    {
        return false;
    }

    ballTexture = TextureManager::loadTexture("assets/ball.png", renderer);
    if (!ballTexture)
    {
        std::cerr << "Failed to load ball texture!" << std::endl;
        return false;
    }
    arrowTexture = TextureManager::loadTexture("assets/arrow.png", renderer);
    if (!arrowTexture)
    {
        std::cerr << "Failed to load arrow texture!" << std::endl;
        return false;
    }
    backgroundTexture = TextureManager::loadTexture("assets/background.jpg", renderer);
    if (!backgroundTexture)
    {
        std::cerr << "Failed to load background texture!" << std::endl;
        return false;
    }
    holeTexture = TextureManager::loadTexture("assets/hole.png", renderer);
    if (!holeTexture)
    {
        std::cerr << "Failed to load hole texture!" << std::endl;
        return false;
    }
    obstacleTexture1 = TextureManager::loadTexture("assets/tile64_dark.png", renderer);
    obstacleTexture2 = TextureManager::loadTexture("assets/tile32_dark.png", renderer);
    obstacleTexture3 = TextureManager::loadTexture("assets/tile32_light.png", renderer);
    obstacleTexture4 = TextureManager::loadTexture("assets/tile64_light.png", renderer);
    if (!obstacleTexture1 || !obstacleTexture2 || !obstacleTexture3 || !obstacleTexture4)
    {
        std::cerr << "Failed to load obstacle textures!" << std::endl;
    }

    menu.init(renderer);

    loadLevels();
    initLevel();

    return true;
}

// hàm này dùng để khởi tạo game
void Game::run()
{
    bool quit = false;
    while (!quit)
    {
        processEvents();
        update();
        render();
        SDL_Delay(16);
    }
}

// hàm này dùng để giải phóng bộ nhớ và các tài nguyên đã sử dụng trong game
void Game::cleanup()
{
    SDL_DestroyTexture(ballTexture);
    SDL_DestroyTexture(backgroundTexture);
    SDL_DestroyTexture(holeTexture);
    SDL_DestroyTexture(obstacleTexture1);
    SDL_DestroyTexture(obstacleTexture2);
    SDL_DestroyTexture(obstacleTexture3);
    SDL_DestroyTexture(obstacleTexture4);
    SDL_DestroyTexture(arrowTexture);
    menu.cleanup();
    Renderer::cleanup(window, renderer);
}

// hàm này dùng để xử lý các sự kiện trong game
void Game::ingameProcessEvents(SDL_Event &event)
{
    if (event.type == SDL_QUIT)
    {
        exit(0);
    }
    else if (event.type == SDL_MOUSEBUTTONDOWN)
    {
        startX = event.button.x;
        startY = event.button.y;
        dragging = true;
    }
    else if (event.type == SDL_MOUSEMOTION && dragging)
    {
        int mouseX = event.motion.x;
        int mouseY = event.motion.y;

        float ballCenterX = ballX + (BALL_WIDTH * ballScale) / 2;
        float ballCenterY = ballY + (BALL_HEIGHT * ballScale) / 2;
        float dx = mouseX - ballCenterX;
        float dy = mouseY - ballCenterY;
        float magnitude = sqrt(dx * dx + dy * dy);

        const float MAGNITUDE_THRESHOLD = 5.0f;
        // Nếu đỘ dài của vector lớn hơn 5 thì sẽ tính toán góc của vector và gán cho góc mũi tên
        if (magnitude >= MAGNITUDE_THRESHOLD)
        {
            arrowAngle = atan2(-dy, -dx) * 180 / M_PI;
        }
    }
    else if (event.type == SDL_MOUSEBUTTONUP && dragging && velocityX == 0 && velocityY == 0)
    {
        int endX = event.button.x;
        int endY = event.button.y;
        velocityX = (startX - endX) * 0.1f;
        velocityY = (startY - endY) * 0.1f;
        dragging = false;
    }
}

// hàm này dùng để xử lý các sự kiện trong game
void Game::processEvents()
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        if (menuState == MenuState::MAIN_MENU)
        {
            menuState = menu.processEvents(event);
        }
        if (menuState == MenuState::EXIT)
        {
            exit(0);
        }
        else
        {
            ingameProcessEvents(event);
        }
    }
}

// hàm này dùng để cập nhật vị trí của bóng và xử lý va chạm giữa bóng và các đối tượng khác trong game
void Game::update()
{
    // Giới hạn tốc độ của bóng
    if (velocityX > MAX_VELOCITY)
        velocityX = MAX_VELOCITY;
    if (velocityX < -MAX_VELOCITY)
        velocityX = -MAX_VELOCITY;
    if (velocityY > MAX_VELOCITY)
        velocityY = MAX_VELOCITY;
    if (velocityY < -MAX_VELOCITY)
        velocityY = -MAX_VELOCITY;

    ballX = ballX + velocityX;
    ballY = ballY + velocityY;

    wallCollision();
    obstacleCollision();

    velocityX = velocityX * FRICTION;
    velocityY = velocityY * FRICTION;

    if (fabs(velocityX) < 0.1f)
    {
        velocityX = 0;
    }
    if (fabs(velocityY) < 0.1f)
    {
        velocityY = 0;
    }
    bool ballStopped = (fabs(velocityX) < 0.1f && fabs(velocityY) < 0.1f);
    if (ballStopped)
    {
        arrowX = ballX + Game::BALL_WIDTH / 2;
        arrowY = ballY + Game::BALL_HEIGHT / 2;
    }
    else
    {
        arrowX = -100;
        arrowY = -100;
        arrowAngle = 0;
    }

    holeCollision();

    if (ballX == 50 && ballY == 300 && velocityX == 0 && velocityY == 0)
    {
        ballScale = 1.0f;
    }
}

// hàm này dùng để render các đối tượng trong game
void Game::render()
{
    if (menuState == MenuState::MAIN_MENU)
    {
        menu.render(renderer);
        SDL_RenderPresent(renderer);
        return;
    }
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, backgroundTexture, NULL, NULL);
    if (fabs(velocityX) < 0.1f && fabs(velocityY) < 0.1f)
    {
        int arrowWidth, arrowHeight;
        SDL_QueryTexture(arrowTexture, NULL, NULL, &arrowWidth, &arrowHeight);
        SDL_Rect dest = {(int)arrowX - arrowWidth / 2, (int)arrowY - arrowHeight / 2, arrowWidth, arrowHeight};
        SDL_RenderCopyEx(renderer, arrowTexture, NULL, &dest, arrowAngle, NULL, SDL_FLIP_NONE);
        if (!arrowTexture)
        {
            std::cerr << "Arrow texture is null!" << std::endl;
        }
    }
    for (const auto &obstacle : obstacles)
    {
        if (!obstacle.texture)
        {
            std::cerr << "Obstacle texture is null!" << std::endl;
            continue;
        }
        SDL_Rect dest = {obstacle.x, obstacle.y, obstacle.width, obstacle.height};
        SDL_RenderCopy(renderer, obstacle.texture, NULL, &dest);
    }
    TextureManager::renderTexture(holeTexture, renderer, static_cast<int>(holeX), static_cast<int>(holeY), 1.0f);
    if (!holeTexture)
    {
        std::cerr << "Hole texture is null!" << std::endl;
    }
    TextureManager::renderTexture(ballTexture, renderer, static_cast<int>(ballX), static_cast<int>(ballY), ballScale);
    if (!ballTexture)
    {
        std::cerr << "Ball texture is null!" << std::endl;
    }
    SDL_RenderPresent(renderer);
}

// hàm này dùng để xử lý va chạm giữa bóng và tường
// nếu bóng va chạm với tường thì bóng sẽ dội lại theo hướng ngược lại
void Game::wallCollision()
{

    if (ballX < 0)
    {
        ballX = 0;
        velocityX = -velocityX * BOUNCE;
    }

    if (ballX + BALL_WIDTH > SCREEN_WIDTH)
    {
        ballX = SCREEN_WIDTH - BALL_WIDTH;
        velocityX = -velocityX * BOUNCE;
    }

    if (ballY < 0)
    {
        ballY = 0;
        velocityY = -velocityY * BOUNCE;
    }

    if (ballY + BALL_HEIGHT > SCREEN_HEIGHT)
    {
        ballY = SCREEN_HEIGHT - BALL_HEIGHT;
        velocityY = -velocityY * BOUNCE;
    }
}
// hàm này dùng để xử lý va chạm giữa bóng và lỗ
// nếu bóng va chạm với lỗ và tốc độ của bóng nhỏ hơn 5 thì bóng sẽ vào lỗ
void Game::holeCollision()
{
    float ballCenterX = ballX + (BALL_WIDTH * ballScale) / 2;
    float ballCenterY = ballY + (BALL_HEIGHT * ballScale) / 2;
    float holeCenterX = holeX + BALL_WIDTH / 2;
    float holeCenterY = holeY + BALL_HEIGHT / 2;
    float holeRadius = BALL_WIDTH / 2;
    float distance = sqrt(pow(ballCenterX - holeCenterX, 2) + pow(ballCenterY - holeCenterY, 2));
    float VELOCITY_THRESHOLD = 5.0f;

    if (distance < holeRadius && fabs(velocityX) < VELOCITY_THRESHOLD && fabs(velocityY) < VELOCITY_THRESHOLD)
    {
        if (ballScale > 0.3f)
        {
            ballScale *= 0.9f;
            ballX = holeCenterX - (BALL_WIDTH * ballScale) / 2;
            ballY = holeCenterY - (BALL_HEIGHT * ballScale) / 2;
        }
        else
        {
            currentLevel++;
            int size = levels.size();
            if (currentLevel < size)
            {
                initLevel();
            }
            else
            {
                currentLevel = 0;
                initLevel();
            }
            velocityX = 0;
            velocityY = 0;
            ballScale = 1.0f;
        }
    }
}
// hàm này dùng để xử lý va chạm giữa bóng và các chướng ngại vật
void Game::obstacleCollision()
{
    for (auto &obs : levels[currentLevel].getObstacles())
    {
        if (ballX + BALL_WIDTH > obs.x &&
            ballX < obs.x + obs.width &&
            ballY + BALL_HEIGHT > obs.y &&
            ballY < obs.y + obs.height)
        {

            float overlapX = (velocityX > 0) ? (ballX + BALL_WIDTH - obs.x) : (obs.x + obs.width - ballX);
            float overlapY = (velocityY > 0) ? (ballY + BALL_HEIGHT - obs.y) : (obs.y + obs.height - ballY);

            if (overlapX < overlapY)
            {
                if (velocityX > 0)
                {
                    ballX -= overlapX;
                }
                else
                {
                    ballX += overlapX;
                }
                velocityX = -velocityX * BOUNCE;
            }
            else
            {
                if (velocityY > 0)
                {
                    ballY -= overlapY;
                }
                else
                {
                    ballY += overlapY;
                }
                velocityY = -velocityY * BOUNCE;
            }
        }
    }
}
// hàm này dùng để load các level vào game
// các level được lưu trong vector levels, mỗi level là một đối tượng của class Level
void Game::loadLevels()
{
    levels.clear();
    // level 1
    std::vector<Obstacle> rectangleObstacles;

    int rectX = (SCREEN_WIDTH - 608) / 2;
    int rectY = (SCREEN_HEIGHT - 200) / 2;
    int rectWidth = 608;
    int rectHeight = 288;

    for (int x = rectX; x < rectX + rectWidth; x += 32)
    {
        rectangleObstacles.push_back({x, rectY, 32, 32, obstacleTexture2});
    }

    for (int x = rectX; x < rectX + rectWidth; x += 32)
    {
        rectangleObstacles.push_back({x, rectY + rectHeight - 32, 32, 32, obstacleTexture2});
    }

    for (int y = rectY; y < rectY + rectHeight - 32; y += 32)
    {
        rectangleObstacles.push_back({rectX, y, 32, 32, obstacleTexture2});
    }

    for (int y = rectY; y < rectY + rectHeight - 32; y += 32)
    {
        rectangleObstacles.push_back({rectX + rectWidth - 32, y, 32, 32, obstacleTexture2});
    }

    levels.push_back(Level(
        {rectX + 100, 325},
        rectangleObstacles,
        {rectX + rectWidth - 100, 325}));

    // level 2
    std::vector<Obstacle> zigzagObstacles;
    for (int i = 0; i < 10; i++)
    {
        int x = 100 + i * 64;
        int y = (i % 2 == 0) ? 200 : 300;
        zigzagObstacles.push_back({x, y, 64, 67, obstacleTexture1});
    }
    levels.push_back(Level(
        {150, 250},
        zigzagObstacles,
        {700, 275}));
    // level 3
    std::vector<Obstacle> circularObstacles;
    int centerX = SCREEN_WIDTH / 2;
    int centerY = SCREEN_HEIGHT / 2;
    int radius = 150;
    for (int angle = 0; angle < 360; angle += 45)
    {
        int x = centerX + radius * cos(angle * M_PI / 180) - 32;
        int y = centerY + radius * sin(angle * M_PI / 180) - 32;
        circularObstacles.push_back({x, y, 64, 67, obstacleTexture4});
    }
    levels.push_back(Level(
        {400, 550},
        circularObstacles,
        {400, 300}));

    // level 4
    std::vector<Obstacle> checkerboardObstacles;
    for (int x = 100; x < SCREEN_WIDTH - 100; x += 64)
    {
        for (int y = 100; y < SCREEN_HEIGHT - 100; y += 67)
        {
            if ((x / 64 + y / 67) % 2 == 0)
            {
                checkerboardObstacles.push_back({x, y, 32, 35, obstacleTexture2});
            }
        }
    }
    levels.push_back(Level(
        {150, 150},
        checkerboardObstacles,
        {SCREEN_WIDTH - 150, SCREEN_HEIGHT - 150}));

    // level 5
    levels.push_back(Level(
        {70, 300},
        {{200, 0, 64, 67, obstacleTexture1},
         {200, 70, 64, 67, obstacleTexture1},
         {200, 140, 64, 67, obstacleTexture1},
         {200, 400, 64, 67, obstacleTexture1},
         {200, 468, 64, 67, obstacleTexture1},
         {200, 530, 64, 67, obstacleTexture1},
         {270, 185, 64, 67, obstacleTexture1},
         {330, 145, 64, 67, obstacleTexture4},
         {395, 121, 64, 67, obstacleTexture1},
         {465, 100, 64, 67, obstacleTexture4},
         {260, 380, 64, 67, obstacleTexture4},
         {330, 335, 64, 67, obstacleTexture1},
         {400, 305, 64, 67, obstacleTexture4},
         {460, 270, 64, 67, obstacleTexture4},
         {300, 245, 32, 35, obstacleTexture2},
         {395, 270, 32, 35, obstacleTexture3},
         {420, 185, 32, 35, obstacleTexture2},
         {540, 75, 32, 35, obstacleTexture3},
         {540, 40, 32, 35, obstacleTexture2},
         {575, 40, 32, 35, obstacleTexture3},
         {610, 40, 32, 35, obstacleTexture2},
         {645, 40, 32, 35, obstacleTexture3},
         {645, 80, 32, 35, obstacleTexture2},
         {645, 115, 32, 35, obstacleTexture3},
         {645, 150, 32, 35, obstacleTexture2},
         {645, 185, 32, 35, obstacleTexture3},
         {610, 185, 32, 35, obstacleTexture2},
         {575, 185, 32, 35, obstacleTexture3},
         {540, 190, 32, 35, obstacleTexture2}},
        {600, 120}));

    if (!obstacleTexture1 || !obstacleTexture2 || !obstacleTexture3 || !obstacleTexture4)
    {
        std::cerr << "Failed to load obstacle textures!" << std::endl;
    }
}
// hàm này dùng để khởi tạo level đầu tiên
void Game::initLevel()
{
    int size = levels.size();
    if (currentLevel >= size)
    {
        return;
    }
    Level &level = levels[currentLevel];

    ballX = level.getBallStartPosition().x;
    ballY = level.getBallStartPosition().y;

    holeX = level.getHolePosition().x;
    holeY = level.getHolePosition().y;

    const vector<Obstacle> &levelObstacles = level.getObstacles();
    obstacles = levelObstacles;

    numObstacles = obstacles.size();

    velocityX = 0;
    velocityY = 0;
    ballScale = 1.0f;
}
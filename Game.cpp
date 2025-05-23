#include "Game.h"
#include "Utils.h"
#include <ctime>
#include <algorithm>
#define M Constants::M
#define N Constants::N


using namespace sf;
using namespace std;


Game::Game() :
    window(VideoMode(500, 800), "The Tetris!"),
    timer(0),
    delay(0.3),
    rotate(false),
    gameOver(false),
    beginGame(true),
    dx(0),


    stopButton(71, 718, 149, 46),
    newGameButton(280, 718, 149, 46)


{
    srand(time(nullptr));


    texture.loadFromFile("resources/texture/blocks.png");
    texture_backGround.loadFromFile("resources/texture/backGround.png");
    texture_frame.loadFromFile("resources/texture/gamePlace.png");
    texture_nextBlock.loadFromFile("resources/texture/nextBlock.png");

    font.loadFromFile("resources/fonts/arial.ttf");

    scoreText.setFont(font);
    linesText.setFont(font);
    levelText.setFont(font);

    scoreText.setCharacterSize(30);
    linesText.setCharacterSize(30);
    levelText.setCharacterSize(30);

    scoreText.setFillColor(Color::White);
    linesText.setFillColor(Color::White);
    levelText.setFillColor(Color::White);



    sprite.setTexture(texture);
    sprite_backGround.setTexture(texture_backGround);
    sprite_frame.setTexture(texture_frame);
    sprite_nextBlock.setTexture(texture_nextBlock);
    sprite.setTextureRect(IntRect(0, 0, 30, 30));
    sprite_frame.setPosition(26, 30);
    sprite_nextBlock.setPosition(350, 60);

}

void Game::run() {
    while (window.isOpen()) {
        float time = clock.getElapsedTime().asSeconds();
        clock.restart();

        if (!gamePaused && !gameOver) {
            timer += time;
        }

        HandleEvents();
        update();
        draw();
    }
}

void Game::HandleEvents() {
    Event event;
    while (window.pollEvent(event)) {
        if (event.type == Event::Closed) {
            window.close();
        }

        if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left) {
            Vector2i mousePos = Mouse::getPosition(window);

            if (stopButton.isInside(mousePos.x, mousePos.y)) {
                gamePaused = !gamePaused;
            }

            if (newGameButton.isInside(mousePos.x, mousePos.y)) {
                field.reset();
                scoreManager.reset();
                gameOver = false;
                beginGame = true;
                gamePaused = false;
            }
        }

        if (event.type == Event::KeyPressed) {
            if (gameOver && event.key.code == Keyboard::Space) {
                field.reset();
                scoreManager.reset();
                gameOver = false;
                beginGame = true;
            }
            else if (gamePaused && event.key.code == Keyboard::Space) {
                gamePaused = false;
            }

            if (!gameOver && !gamePaused) {
                if (event.key.code == Keyboard::Up) {
                    rotate = true;
                } else if (event.key.code == Keyboard::Left) {
                    dx = -1;
                } else if (event.key.code == Keyboard::Right) {
                    dx = 1;
                }
            }
        }
    }
}

void Game::update() {
    Utils utils;

    if (gameOver) {
        return;
    }

    if (Keyboard::isKeyPressed(Keyboard::Down)) {
        delay = 0.05;
    }

    if (beginGame) {
        beginGame = false;
        tetromino.spawn();
    }

    tetromino.move(dx);
    if (!utils.check(tetromino.getBlocks(), field)) {
        tetromino.revert();
    }

    if (rotate) {
        tetromino.rotate();
        if (!utils.check(tetromino.getBlocks(), field)) {
            tetromino.revert();
        }
    }

    if (timer > delay) {
        tetromino.drop();

        if (!utils.check(tetromino.getBlocks(), field)) {
            tetromino.revert();
            field.lockTetromino(tetromino.getBlocks(), tetromino.getColor());

            int linesCleared = field.clearLines();
            if (linesCleared > 0) {
                scoreManager.updateScore(linesCleared);

                delay = max(0.05f, 0.3f - 0.05f * (scoreManager.getLevel() - 1));
            }

            tetromino.spawn();

            if (field.isGameOver(tetromino.getBlocks())) {
                gameOver = true;
            }
        }

        timer = 0;
    }

    dx = 0;
    rotate = false;
    if (!Keyboard::isKeyPressed(Keyboard::Down)) {
        delay = max(0.05f, 0.3f - 0.02f * (scoreManager.getLevel() - 1));
    }
}

void Game::draw() {
    window.clear();

    window.draw(sprite_backGround);

    window.draw(sprite_frame);

    window.draw(sprite_nextBlock);

    for (int i = 0; i < M; ++i) {
        for (int j = 0; j < N; ++j) {
            if (field.field[i][j] == 0) {
                continue;
            }

            sprite.setTextureRect(IntRect(field.field[i][j] * 30, 0, 30, 30));
            sprite.setPosition(j * 30 + 28, i * 30 + 31);
            window.draw(sprite);
        }
    }

    if (!gameOver) {
        Point* blocks = tetromino.getBlocks();
        for (int i = 0; i < 4; ++i) {
            sprite.setTextureRect(IntRect(tetromino.getColor() * 30, 0, 30, 30));
            sprite.setPosition(blocks[i].x * 30 + 28, blocks[i].y * 30 + 31);
            window.draw(sprite);
        }

        Point* nextBlocks = tetromino.getNextFigureBlocks();
        int nextColor = tetromino.getNextFigureColor();

        float frameX = sprite_nextBlock.getPosition().x;
        float frameY = sprite_nextBlock.getPosition().y;
        float frameWidth = sprite_nextBlock.getTextureRect().width;
        float frameHeight = sprite_nextBlock.getTextureRect().height;

        int blockSize = 30;

        int minX = 4, maxX = 0, minY = 4, maxY = 0;
        for (int i = 0; i < 4; ++i) {
            minX = min(minX, nextBlocks[i].x);
            maxX = max(maxX, nextBlocks[i].x);
            minY = min(minY, nextBlocks[i].y);
            maxY = max(maxY, nextBlocks[i].y);
        }

        int figureWidth = maxX - minX + 1;
        int figureHeight = maxY - minY + 1;

        float startX = frameX + (frameWidth - figureWidth * blockSize) / 2;
        float startY = frameY + (frameHeight - figureHeight * blockSize) / 2;

        startX -= minX * blockSize;
        startY -= minY * blockSize;

        for (int i = 0; i < 4; ++i) {
            sprite.setTextureRect(IntRect(nextColor * 30, 0, 30, 30));
            float posX = startX + nextBlocks[i].x * blockSize;
            float posY = startY + nextBlocks[i].y * blockSize;
            sprite.setPosition(posX, posY);
            window.draw(sprite);
        }
    }

    string scoreStr = std::to_string(scoreManager.getScore());
    string linesStr = std::to_string(scoreManager.getLines());
    string levelStr = std::to_string(scoreManager.getLevel());

    scoreText.setString(scoreStr);
    linesText.setString(linesStr);
    levelText.setString(levelStr);


    float frameCenter = 410;

    FloatRect scoreBounds = scoreText.getGlobalBounds();
    FloatRect linesBounds = linesText.getGlobalBounds();
    FloatRect levelBounds = levelText.getGlobalBounds();

    scoreText.setOrigin(scoreBounds.width / 2, scoreBounds.height / 2);
    linesText.setOrigin(linesBounds.width / 2, linesBounds.height / 2);
    levelText.setOrigin(levelBounds.width / 2, levelBounds.height / 2);

    scoreText.setPosition(frameCenter, 480);
    linesText.setPosition(frameCenter, 370);
    levelText.setPosition(frameCenter, 260);

    window.draw(scoreText);
    window.draw(linesText);
    window.draw(levelText);

    if (gamePaused) {
        RectangleShape overlay(Vector2f(window.getSize().x, window.getSize().y));
        overlay.setFillColor(Color(0, 0, 0, 150));
        window.draw(overlay);

        Text pauseText;
        pauseText.setFont(font);
        pauseText.setString("PAUSED");
        pauseText.setCharacterSize(50);
        pauseText.setFillColor(Color::White);

        FloatRect pauseTextBounds = pauseText.getGlobalBounds();
        pauseText.setOrigin(pauseTextBounds.width / 2, pauseTextBounds.height / 2);
        pauseText.setPosition(window.getSize().x / 2, window.getSize().y / 2);

        Text restartText;
        restartText.setFont(font);
        restartText.setString("Press SPACE to restart");
        restartText.setCharacterSize(24);
        restartText.setFillColor(Color::White);

        FloatRect restartTextBounds = restartText.getGlobalBounds();
        restartText.setOrigin(restartTextBounds.width / 2, restartTextBounds.height / 2);
        restartText.setPosition(window.getSize().x / 2, window.getSize().y / 2 + 60);

        window.draw(pauseText);
        window.draw(restartText);
    }

    if (gameOver) {
        RectangleShape overlay(Vector2f(window.getSize().x, window.getSize().y));
        overlay.setFillColor(Color(0, 0, 0, 150));
        window.draw(overlay);

        Text gameOverText;
        gameOverText.setFont(font);
        gameOverText.setString("GAME OVER");
        gameOverText.setCharacterSize(50);
        gameOverText.setFillColor(Color::White);

        FloatRect gameOverTextBounds = gameOverText.getGlobalBounds();
        gameOverText.setOrigin(gameOverTextBounds.width / 2, gameOverTextBounds.height / 2);
        gameOverText.setPosition(window.getSize().x / 2, window.getSize().y / 2);

        Text restartText;
        restartText.setFont(font);
        restartText.setString("Press SPACE to restart");
        restartText.setCharacterSize(24);
        restartText.setFillColor(Color::White);

        FloatRect restartTextBounds = restartText.getGlobalBounds();
        restartText.setOrigin(restartTextBounds.width / 2, restartTextBounds.height / 2);
        restartText.setPosition(window.getSize().x / 2, window.getSize().y / 2 + 60);

        window.draw(gameOverText);
        window.draw(restartText);
    }
    window.display();
}
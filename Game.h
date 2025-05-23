#ifndef TETRIS_GAME_H
#define TETRIS_GAME_H

#include <SFML/Graphics.hpp>
#include "Tetromino.h"
#include "Field.h"
#include "ScoreManager.h"
#include "Button.h"



using namespace sf;

class Game {
private:
    RenderWindow window;
    Clock clock;
    float timer;
    float delay;
    bool rotate;
    bool gameOver;
    bool beginGame;
    bool gamePaused;
    int dx;

    Texture texture;
    Texture texture_backGround;
    Texture texture_frame;
    Texture texture_nextBlock;

    Sprite sprite;
    Sprite sprite_backGround;
    Sprite sprite_frame;
    Sprite sprite_nextBlock;

    Font font;
    Text scoreText;
    Text linesText;
    Text levelText;

    Tetromino tetromino;
    Field field;
    ScoreManager scoreManager;

    Button stopButton;
    Button newGameButton;


    void HandleEvents();
    void update();
    void draw();


public:
    Game();
    void run();
};

#endif
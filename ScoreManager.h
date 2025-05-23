#ifndef TETRIS_SCOREMANAGER_H
#define TETRIS_SCOREMANAGER_H

class ScoreManager {
private:
    int score;
    int lines;
    int level;

    const int SCORE_SINGLE = 100;
    const int SCORE_DOUBLE = 300;
    const int SCORE_TRIPLE = 500;
    const int SCORE_TETRIS = 800;

public:
    ScoreManager();

    void reset();
    void updateScore(int linesCleared);

    int getScore() const;
    int getLines() const;
    int getLevel() const;
};

#endif

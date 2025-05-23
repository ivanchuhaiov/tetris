#include "ScoreManager.h"

ScoreManager::ScoreManager() : score(0), lines(0), level(1) {
}

void ScoreManager::reset() {
    score = 0;
    lines = 0;
    level = 1;
}

void ScoreManager::updateScore(int linesCleared) {
    if (linesCleared <= 0) {
        return;
    }

    lines += linesCleared;

    switch (linesCleared) {
        case 1:
            score += SCORE_SINGLE * level;
        break;
        case 2:
            score += SCORE_DOUBLE * level;
        break;
        case 3:
            score += SCORE_TRIPLE * level;
        break;
        case 4:
            score += SCORE_TETRIS * level;
        break;
    }

    level = (lines / 10) + 1;
}

int ScoreManager::getScore() const {
    return score;
}

int ScoreManager::getLines() const {
    return lines;
}

int ScoreManager::getLevel() const {
    return level;
}

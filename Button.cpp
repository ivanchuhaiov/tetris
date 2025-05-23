#include "Button.h"

Button::Button(int x, int y, int width, int height)
    : x(x), y(y), width(width), height(height) {
}

bool Button::isInside(int mouseX, int mouseY) const {
    return mouseX >= x && mouseX <= x + width &&
           mouseY >= y && mouseY <= y + height;
}

int Button::getX() const {
    return x;
}

int Button::getY() const {
    return y;
}

int Button::getWidth() const {
    return width;
}

int Button::getHeight() const {
    return height;
}
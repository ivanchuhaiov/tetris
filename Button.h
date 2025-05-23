#ifndef BUTTON_H
#define BUTTON_H

class Button {
private:
    int x;
    int y;
    int width;
    int height;

public:
    Button(int x, int y, int width, int height);


    bool isInside(int mouseX, int mouseY) const;


    int getX() const;
    int getY() const;
    int getWidth() const;
    int getHeight() const;
};


#endif

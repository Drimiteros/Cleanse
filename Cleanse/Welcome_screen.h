#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Enums.h"
#include "File_handler.h"

using namespace std;
using namespace sf;

class Welcome_screen {
private:
    Font font;
    Font font2;

    Texture texture;

    Sprite button_sprite;

    Text title_text;
    Text title_text2;

    Clock delay_clock;

    float opacity = 0;
    float opacity2 = 0;
    float posY = 470;

public:
    Welcome_screen();
    void update(RectangleShape& cursor, Enums& enums, File_handler& file_handler);
    void draw(RenderWindow& window);
};


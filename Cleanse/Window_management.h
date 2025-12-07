#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <Windows.h>
#include "Enums.h"

using namespace std;
using namespace sf;

class Window_management {
private:
    Texture background_texture;
    Texture top_bar_texture;
    Texture buttons_texture;
    Texture logo_texture;
    Texture calendar_texture;
    Texture status_texture;
    Texture options_texture;
    Texture donate_texture;
    Texture tiles_texture;

    Font font;

public:
    Sprite top_bar;
    Sprite background_sprite;
    Sprite close_button;
    Sprite minimize_button;
    Sprite logo_sprite;
    Sprite calendar_sprite;
    Sprite status_sprite;
    Sprite options_sprite;
    Sprite donate_sprite;
    Sprite tiles;
    vector<Sprite> button_sprites;

    Text title_text;
    Text quick_clean_text;
    Text calendar_text;
    Text status_text;
    Text options_text;
    Text donate_text;

    Enums current_state;
    Enums::QUICK_CLEAN;

    Window_management();
    void update(RectangleShape& cursor, RenderWindow& window, int& width, string& version, Enums& new_state, bool& update_total_space_saved);
    void close_window(RectangleShape& cursor, RenderWindow& window);
    void minimize_window(RectangleShape& cursor, RenderWindow& window);
    void handle_window_drag(RectangleShape& cursor, RenderWindow& window, int& width);
    void change_state(Enums& new_state, RectangleShape& cursor, bool& update_total_space_saved);
    void draw(RenderWindow& window, RectangleShape& cursor, Enums& current_state);
};


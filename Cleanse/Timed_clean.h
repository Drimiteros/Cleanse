#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <dwmapi.h>
#include <atlbase.h>
#include <shlobj.h>
#include <filesystem>
#include "File_handler.h"
#include <chrono>

using namespace std;
using namespace sf;
namespace fs = std::filesystem;

class Timed_clean {

private:
    Font font;
    Font font2;
    Text title_info_text;
    Text option_text[4];
    Text option_text2[4];
    Text day_limit_text;
    Text junk_limit_text;
    Text hour_limit_text;
    Text info_text;

    Clock click_timer;

    Texture button_texture;
    Texture icon_texture;

    vector<Sprite> button_sprite;
    vector<Sprite> icon_sprite;

    bool scheduled = false;
    bool removed = false;

public:
    bool active[4] = { false, false, false, false };
    
    int day_limit = 7;
    int junk_limit = 5;
    int hour_limit = 2;

    Timed_clean();
    void update(RectangleShape& cursor, File_handler& file_handler);
    void set_shedule(File_handler& file_handler);
    void remove_shedule(File_handler& file_handler);
    void draw(RenderWindow& window);
};


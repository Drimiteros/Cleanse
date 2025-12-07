#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <cpr/cpr.h>
#include "Enums.h"
#include "File_handler.h"

using namespace std;
using namespace sf;

class Update_check {
private:
    string version_url = "https://raw.github.com/Drimiteros/cleanse-data/main/version.txt";
    string logs_url = "https://raw.github.com/Drimiteros/cleanse-data/main/logs.txt";
    string app_url = "https://raw.github.com/Drimiteros/cleanse-data/main/Cleanse%20Live%20Version%20Setup.exe";
    string date_url = "https://raw.github.com/Drimiteros/cleanse-data/main/releaseDate.txt";

    Font font;
    Font font2;

    Texture texture;
    Texture texture2;
    Texture button_texture;

    Text title_text;
    Text title_text2;
    Text whats_new_text;
    Text info_text;
    Text logs_text;

    Sprite update_sprite;
    Sprite check_sprite;
    Sprite download_button;
    Sprite ignore_button;

    float app_size = 0;

    bool get_logs = false;
    bool get_app_size = false;
    bool get_app_release_date = false;

public:
    Update_check();
    bool has_new_update(string old_version);
    void update(RectangleShape& cursor, Enums& current_state, RenderWindow& window, File_handler& file_handler);
    void draw(RenderWindow& window);
};


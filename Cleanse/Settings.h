#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Update_check.h"
#include "File_handler.h"
#include "Enums.h"

using namespace std;
using namespace sf;

class Settings {
private:
    Font font;
    Font font2;

    Texture items_texture;

    Clock click_delay_clock;

    Text cleaning_preferences_text;
    Text exclude_cleaning_categories_text;
    Text update_preferences_text;
    Text check_for_updates_text;

    Sprite reload_button_sprite;

    vector<CircleShape> exclude_circle;
    CircleShape update_check_circle;

public:

    Settings();
    void update(RectangleShape& cursor, bool exclude_categories_list[4], File_handler& file_handler, bool& check_for_updates, string& version, Update_check& update_check, Enums& enums);
    void change_pref(bool exclude_categories_list[4], RectangleShape& cursor, File_handler& file_handler, bool& check_for_updates, string& version, Update_check& update_check, Enums& enums);
    void draw(RenderWindow& window);
};


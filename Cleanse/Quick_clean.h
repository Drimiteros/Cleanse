#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <filesystem>
#include <windows.h>
#include <shlobj.h>
#include <chrono>
#include <sstream>
#include "Disk_management.h"
#include "File_handler.h"
#include "Enums.h"
#include "Report_screen.h"

using namespace std;
using namespace sf;
namespace fs = filesystem;

class Quick_clean {
private:
    Texture refresh_menu_background_texture;

    Font font;
    Font font2;

    Clock delete_clock;

    Text estimated_junk_text;
    Text categories_text;
    Text total_junk_text;
    Text recycle_junk_text;
    Text recycle_junk_category_text;
    Text temp_junk_text;
    Text temp_junk_category_text;
    Text browser_junk_category_text;
    Text browser_junk_text;
    Text log_junk_category_text;
    Text log_junk_text;
    Text status_text;
    Text status_info_text;

    Texture clean_button_texture;
    Texture refresh_button_texture;
    Texture items_texture;

    Sprite items_sprite;
    Sprite clean_button;
    Sprite refresh_button;
    Sprite refresh_menu_background;

    bool calculate_junk_size_flag = true;
    bool clean_junk_files_flag = false;
    bool is_refreshing = false;
    bool is_cleaning = false;

    float total_junk_size = 0;
    float recycle_junk_size = 0;
    float temp_junk_size = 0;
    float browser_junk_size = 0;
    float log_junk_size = 0;

    int recycle_file_count = 0;
    int temp_file_count = 0;
    int browser_file_count = 0;
    int log_file_count = 0;

public:

    Quick_clean();
    void update(RectangleShape& cursor, wstring& user_profile_path, Disk_management& disk_management, File_handler& file_handler, bool exclude_categories_list[4], Enums& current_state, Report_screen& report_screen);
    void calculate_junk_size(wstring& user_profile_path, Disk_management& disk_management, RectangleShape& cursor, vector<wstring>& temp_path, vector<wstring>& browser_path, vector<wstring>& logs_path);
    void cleanse(RectangleShape& cursor, wstring& user_profile_path, Disk_management& disk_management, File_handler& file_handler, bool exclude_categories_list[4], vector<wstring>& temp_path, vector<wstring>& browser_path, vector<wstring>& logs_path, Enums& current_state, Report_screen& report_screen);
    void draw(RenderWindow& window, RectangleShape& cursor);
};


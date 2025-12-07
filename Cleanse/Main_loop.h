#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <Windows.h>
#include <dwmapi.h>
#include "Window_management.h"
#include "Disk_management.h"
#pragma comment(lib, "dwmapi.lib")
#include "Enums.h"
#include "Quick_clean.h"
#include "File_handler.h"
#include "Settings.h"
#include "Donate.h"
#include "Report_screen.h"
#include "Update_check.h"
#include "Timed_clean.h"
#include "Welcome_screen.h"

using namespace std;
using namespace sf;

class Main_loop {
private:
    int width = 900;
    int height = 600;
    RenderWindow window;
    string version = "0.1.0";
    MARGINS margins = { -1, -1, -1, -1 };

    // Global Variables
    wstring user_profile_path;
    bool update_total_space_saved = false;
    bool exclude_categories_list[4] = { 1, 1, 1, 1 };
    bool check_for_updates = true;
    int scroll_value = 0;
    int scroll_value_report_screen = 0;

public:
    //Window UI Elements
    RectangleShape cursor;

    // Management Classes
    Window_management window_management;
    Disk_management disk_management;
    Quick_clean quick_clean;
    File_handler file_handler;
    Settings settings;
    Donate donate;
    Report_screen report_screen;
    Update_check update_check;
    Timed_clean timed_clean;
    Welcome_screen welcome_screen;

    Enums current_state;

    Main_loop();
    void events();
    void loop();
    void update();
    void draw_layer();
};


#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <locale>
#include <codecvt>
#include <cmath>
#include <sstream>
#include "File_handler.h"

using namespace std;
using namespace sf;

class Disk_management {
private:
    Clock delay_clock;
    
    Font font;
    Font font2;
    Texture drive_texture;
    Texture arrow_texture;
    Texture cosmetic_texture;

    Sprite arrow_sprite;
    Sprite arrow_sprite2;
    Sprite cosmetic_sprite;
    vector<Sprite> drive_sprites;

    Text total_drives_text;
    Text total_free_space_text;
    Text total_free_space_count_text;
    Text total_space_text;
    Text total_space_count_text;
    Text space_saved_text;
    Text space_saved_count_text;
    Text graph_drive_clean_history_text;
    Text graph_drive_free_space_history_text;
    Text current_graph_value_text;
    vector<Text> drive_texts;
    vector<Text> drive_infos;

    RectangleShape drive_view_bounds;
    RectangleShape graph_axis_X[2];
    RectangleShape graph_axis_Y[2];
    vector<RectangleShape> drive_bars;
    vector<RectangleShape> drive_progress_bars;

    CircleShape graph_drive_clean_history_point;
    CircleShape graph_drive_free_space_history_point;
    vector<CircleShape> bar_left_edges;
    vector<CircleShape> bar_right_edges;
    vector<CircleShape> graph_one_points;
    vector<CircleShape> graph_two_points;
    
    float totalFreeSpaceCount = 0;
    float totalSpaceCount = 0;
    vector<float> drive_total_size;
    vector<float> drive_free_size;
    vector<float> graph_data;

    VertexArray line;
    VertexArray fill;
    VertexArray line2;
    VertexArray fill2;

public:
    float total_free_space_percentage;
    float total_space_percentage;

    vector<wstring> drives;

    Disk_management();
    void update(int& scroll_value, RectangleShape& cursor, bool& update_total_space_saved, File_handler& file_handler);
    wstring get_user_profile_path();
    void get_system_drives();
    void calculate_total_free_space();
    void calculate_space_saved(bool& update_total_space_saved, File_handler& file_handler);
    void graph(File_handler& file_handler, RectangleShape& cursor);
    void draw(RenderWindow& window, int scroll_value);
};


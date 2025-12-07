#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <chrono>
#include <filesystem>

using namespace std;
namespace fs = std::filesystem;

class File_handler {
private:
    wstring user_profile_path;

public:
    File_handler();
    void get_user_profile_path(wstring& set_user_profile_path);
    void save_disk_data(float space_saved);
    void save_free_space_history(float current_free_space);
    void load_disk_data(float& total_space_saved);
    void save_user_settings(bool exclude_categories_list[4], bool& check_for_updates);
    void load_user_settings(bool exclude_categories_list[4], bool& check_for_updates);
    vector<float> load_disk_clean_history();
    vector<float> load_free_space_history();
    void save_scheduler_instruction(int instruction);
    int load_scheduler_instruction();
    void save_day_data(chrono::days& data);
    bool load_welcome_screen();
    void save_welcome_screen(bool play_welcome_screen);
};


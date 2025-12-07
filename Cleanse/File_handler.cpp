#include "File_handler.h"

File_handler::File_handler() {

}

void File_handler::get_user_profile_path(wstring& set_user_profile_path) {
    user_profile_path = set_user_profile_path;

    fs::path savesPath = fs::path(user_profile_path) / L"AppData" / L"Roaming" / L"Cleanse Saves";
    error_code ec;
    filesystem::create_directories(savesPath, ec);
}

void File_handler::save_disk_data(float space_saved) {
    // Get the existing total space saved
    float existing_space = 0;
    load_disk_data(existing_space);

    // Save total space saved 
    existing_space += space_saved;
    ofstream save_file(user_profile_path + L"\\AppData\\Roaming\\Cleanse Saves\\Disk_data.txt");
    if (save_file.is_open()) {
        save_file << "Total space saved: " << existing_space << endl;
        save_file.close();
    }

    ofstream save_file2(user_profile_path + L"\\AppData\\Roaming\\Cleanse Saves\\Disk_clean_history.txt", ios::app);
    if (save_file2.is_open()) {
        if (space_saved >= 0)
            save_file2 << space_saved << endl;
        else
            save_file2 << 0 << endl;
        save_file2.close();
    }
}

void File_handler::save_free_space_history(float current_free_space) {
    ofstream save_file(user_profile_path + L"\\AppData\\Roaming\\Cleanse Saves\\Disk_free_space_history.txt", ios::app);
    if (save_file.is_open()) {
        save_file << current_free_space << endl;
        save_file.close();
    }
}

void File_handler::load_disk_data(float& total_space_saved) {
    ifstream load_file(user_profile_path + L"\\AppData\\Roaming\\Cleanse Saves\\Disk_data.txt");
    if (load_file.is_open()) {
        string line;
        while (getline(load_file, line)) {
            if (line.find("Total space saved: ") != string::npos) {
                total_space_saved = stof(line.substr(line.find(": ") + 2));
            }
        }
        load_file.close();
    }
}

void File_handler::save_user_settings(bool exclude_categories_list[4], bool& check_for_updates) {
    ofstream save_file(user_profile_path + L"\\AppData\\Roaming\\Cleanse Saves\\/user_settings.txt");
    if (save_file.is_open()) {
        for (int i = 0; i < 4; ++i)
            save_file << exclude_categories_list[i] << "\n";
        save_file << check_for_updates << "\n";
        save_file.close();
    }
}

void File_handler::load_user_settings(bool exclude_categories_list[4], bool& check_for_updates) {
    ifstream load_file(user_profile_path + L"\\AppData\\Roaming\\Cleanse Saves\\user_settings.txt");
    string line;
    int count = 0;
    while (getline(load_file, line)) {
        exclude_categories_list[count] = stoi(line);
        if (count == 4)
            check_for_updates = stoi(line);
        count++;
    }
}

vector<float> File_handler::load_disk_clean_history() {
    vector<float>space_saved;
    ifstream load_file(user_profile_path + L"\\AppData\\Roaming\\Cleanse Saves\\Disk_clean_history.txt");
    if (load_file.is_open()) {
        string line;
        while (getline(load_file, line)) {
            space_saved.push_back(stof(line));
        }
        load_file.close();
    }

    if (space_saved.size() > 20)
        space_saved.erase(space_saved.cbegin(), space_saved.end() - 20);

    return space_saved;
}

vector<float> File_handler::load_free_space_history() {
    vector<float>space_saved;
    ifstream load_file(user_profile_path + L"\\AppData\\Roaming\\Cleanse Saves\\Disk_free_space_history.txt");
    if (load_file.is_open()) {
        string line;
        while (getline(load_file, line)) {
            space_saved.push_back(stof(line));
        }
        load_file.close();
    }

    if (space_saved.size() > 20)
        space_saved.erase(space_saved.cbegin(), space_saved.end() - 20);

    return space_saved;
}

void File_handler::save_scheduler_instruction(int instruction) {
    ofstream save_file(user_profile_path + L"\\AppData\\Roaming\\Cleanse Saves\\scheduler_instruction.txt");
    if (save_file.is_open()) {
        save_file << instruction;
        save_file.close();
    }
}

int File_handler::load_scheduler_instruction() {
    ifstream load_file(user_profile_path + L"\\AppData\\Roaming\\Cleanse Saves\\scheduler_instruction.txt");
    int active = -1;
    if (load_file.is_open()) {
        string line;
        while (getline(load_file, line)) {
            active = stoi(line);
        }
        load_file.close();
    }
    return active;
}

void File_handler::save_day_data(chrono::days& data) {
    ofstream file(user_profile_path + L"\\AppData\\Roaming\\Cleanse Saves\\scheduler_saves.txt");
    if (file.is_open()) {
        file << "Current day: " << data << "\n";
        file.close();
    }
}

bool File_handler::load_welcome_screen() {
    ifstream load_file(user_profile_path + L"\\AppData\\Roaming\\Cleanse Saves\\welcome_screen.txt");
    bool play_welcome_screen = true;
    if (load_file.is_open()) {
        string line;
        while (getline(load_file, line)) {
            play_welcome_screen = stoi(line);
        }
        load_file.close();
    }
    return play_welcome_screen;
}

void File_handler::save_welcome_screen(bool play_welcome_screen) {
    ofstream save_file(user_profile_path + L"\\AppData\\Roaming\\Cleanse Saves\\welcome_screen.txt");
    if (save_file.is_open()) {
        save_file << play_welcome_screen;
        save_file.close();
    }
}
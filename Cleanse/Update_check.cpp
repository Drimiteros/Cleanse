#include "Update_check.h"

Update_check::Update_check() {
    font.loadFromFile("src/Fonts/AlteHaasGroteskBold.ttf");
    font2.loadFromFile("src/Fonts/AlteHaasGroteskRegular.ttf");

    texture.loadFromFile("src/Textures/update.png");
    texture.setSmooth(true);
    texture2.loadFromFile("src/Textures/check.png");
    texture2.setSmooth(true);
    button_texture.loadFromFile("src/Textures/buttons.png");
    button_texture.setSmooth(true);

    update_sprite.setTexture(texture);
    update_sprite.setPosition(20, 65);
    update_sprite.setScale(0.15, 0.15);

    check_sprite.setTexture(texture2);
    check_sprite.setPosition(158, 158);
    check_sprite.setScale(0.05, 0.05);

    title_text.setFont(font);
    title_text.setString("Update available!");
    title_text.setPosition(85, 60);

    title_text2.setFont(font2);
    title_text2.setString("Version 2.5.0 is ready to install");
    title_text2.setPosition(85, 95);
    title_text2.setCharacterSize(15);

    info_text.setFont(font2);
    info_text.setString("Size: 127 MB | Release Date: November 21, 2025");
    info_text.setCharacterSize(15);
    info_text.setFillColor(Color(255, 255, 255, 150));

    logs_text.setFont(font2);
    logs_text.setString("FEATURES:\nNOT FOUND.\n\n============================================================================================\n\nBUG FIXES:\nNOT FOUND.");
    logs_text.setCharacterSize(15);
    logs_text.setFillColor(Color(255, 255, 255, 150));
    logs_text.setPosition(33, 200);

    whats_new_text.setFont(font);
    whats_new_text.setString("What's New");
    whats_new_text.setPosition(35, 155);
    whats_new_text.setCharacterSize(20);

    download_button.setTexture(button_texture);
    download_button.setTextureRect(IntRect(0, 65, 805, 78));
    download_button.setScale(0.8, 0.8);
    download_button.setPosition(20, 515);

    ignore_button.setTexture(button_texture);
    ignore_button.setTextureRect(IntRect(805, 65, 256, 78));
    ignore_button.setScale(0.8, 0.8);
    ignore_button.setPosition(673, 515);
}

bool Update_check::has_new_update(string old_version) {
    // Get app version
    auto response = cpr::Get(cpr::Url(version_url));
    if (response.status_code == 200) {
        string new_version = response.text.substr(0, response.text.length() - 1);
        cout << old_version << " " << new_version << endl;
        if (old_version != new_version) {
            title_text2.setString("Version " + new_version + " is ready to install");
            get_logs = true;
        }
        else
            return false;
    }
    else {
        cout << "Failed to get response..." << endl;
        return false;
    }

    // Get upfate logs
    if (get_logs) {
        response = cpr::Get(cpr::Url(logs_url));
        if (response.status_code == 200) {
            logs_text.setString(response.text.c_str());
            get_app_size = true;
        }
        else {
            cout << "Failed to get response..." << endl;
            return false;
        }
    }

    // Get update size
    if (get_app_size) {
        response = cpr::Get(cpr::Url(app_url));
        if (response.status_code == 200) {
            app_size = response.downloaded_bytes / (1024 * 1024);
            get_app_release_date = true;
        }
        else {
            cout << "Failed to get response..." << endl;
            return false;
        }
    }

    // Get update release date
    if (get_app_release_date) {
        response = cpr::Get(cpr::Url(date_url));
        if (response.status_code == 200) {
            info_text.setString("Size: " + to_string(app_size).substr(0, 4) + " MB | " + response.text.c_str());
            return true;
        }
        else {
            cout << "Failed to get response..." << endl;
            return false;
        }
    }
}

void Update_check::update(RectangleShape& cursor, Enums& current_state, RenderWindow& window, File_handler& file_handler) {
    if (cursor.getGlobalBounds().intersects(download_button.getGlobalBounds())) {
        download_button.setColor(Color(255, 255, 255, 255));
        if (Mouse::isButtonPressed(Mouse::Left)) {
            const wstring program_wstring = L"updater.exe";
            const wchar_t* program_wchar = program_wstring.c_str();

            HINSTANCE result = ShellExecuteW(NULL, L"open", program_wchar, NULL, NULL, SW_SHOWNORMAL);
            if ((INT_PTR)result <= 32)
                wcerr << L"Failed to open file. Error: " << GetLastError() << endl;
            else {
                wcerr << L"Process started successfully." << endl;
                window.close();
            }
        }
    }
    else
        download_button.setColor(Color(255, 255, 255, 150));

    if (cursor.getGlobalBounds().intersects(ignore_button.getGlobalBounds())) {
        ignore_button.setColor(Color(255, 255, 255, 255));
        if (Mouse::isButtonPressed(Mouse::Left)) {
            if (file_handler.load_welcome_screen())
                current_state = Enums::WELCOME_SCREEN;
            else
                current_state = Enums::QUICK_CLEAN;
        }
    }
    else
        ignore_button.setColor(Color(255, 255, 255, 150));

    info_text.setPosition(25, 486);
}

void Update_check::draw(RenderWindow& window) {
    window.draw(title_text);
    window.draw(title_text2);
    window.draw(update_sprite);
    window.draw(check_sprite);
    window.draw(whats_new_text);
    window.draw(download_button);
    window.draw(ignore_button);
    window.draw(info_text);
    window.draw(logs_text);
}
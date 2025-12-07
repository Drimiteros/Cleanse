#include "Timed_clean.h"

Timed_clean::Timed_clean() {
    font.loadFromFile("src/Fonts/AlteHaasGroteskBold.ttf");
    font2.loadFromFile("src/Fonts/AlteHaasGroteskRegular.ttf");

    button_texture.loadFromFile("src/Textures/buttons.png");
    icon_texture.loadFromFile("src/Textures/items2.png");
    icon_texture.setSmooth(true);

    title_info_text.setFont(font2);
    title_info_text.setString("This function performs automated cleaning based on schedule. This cleaning process is less\nagressive than a Quick Clean to prevent potential unwanted cleanups due to user absence! It will\ntry to clean System temp files, Logs, Recycled bins & Browser files. Use Quick Clean for a more\nagressive clean up.");
    title_info_text.setCharacterSize(15);
    title_info_text.setPosition(220, 72);

    for (int i = 0; i < 4; i++) {
        option_text[i].setFont(font);
        option_text[i].setCharacterSize(17);
        option_text[i].setFillColor(Color(255, 255, 255, 170));
        option_text2[i].setFont(font2);
        option_text2[i].setCharacterSize(12);
        option_text2[i].setFillColor(Color(255, 255, 255, 100));
    }
    option_text[0].setPosition(265, 195);
    option_text[0].setString("Clean on System Start");
    option_text2[0].setPosition(220, 240);
    option_text2[0].setString("Junk cleaning will run automatically every time your\nsystem starts. This happens in the background and won't\nslow down your startup or performance.");
    option_text[1].setPosition(605, 195);
    option_text[1].setString("Clean on Day Limit");
    option_text2[1].setPosition(560, 235);
    option_text2[1].setString("Schedule automatic junk cleaning at system startup\nevery:");
    option_text[2].setPosition(265, 318);
    option_text[2].setString("Clean on Junk Limit");
    option_text2[2].setPosition(220, 356);
    option_text2[2].setString("Schedule automatic junk cleaning at system startup when\nthe junk size reaches:");
    option_text[3].setPosition(605, 318);
    option_text[3].setString("Clean When Idle");
    option_text2[3].setPosition(560, 357);
    option_text2[3].setString("Schedule automatic junk cleaning when your system is\nnot in use for more than:");

    day_limit_text.setFont(font);
    day_limit_text.setCharacterSize(17);
    day_limit_text.setFillColor(Color(255, 145, 246, 170));
    day_limit_text.setPosition(560, 265);

    junk_limit_text.setFont(font);
    junk_limit_text.setCharacterSize(17);
    junk_limit_text.setFillColor(Color(255, 200, 145, 170));
    junk_limit_text.setPosition(223, 386);

    hour_limit_text.setFont(font);
    hour_limit_text.setCharacterSize(17);
    hour_limit_text.setFillColor(Color(255, 173, 145, 170));
    hour_limit_text.setPosition(560, 386);

    info_text.setFont(font2);
    info_text.setCharacterSize(17);
    info_text.setFillColor(Color(255, 188, 112, 170));
    info_text.setString("* Make sure you restart your system for the changes to take effect!");
    info_text.setPosition(900 / 2 - info_text.getLocalBounds().width / 2 + 85, 530);

    button_sprite.push_back(Sprite());
    button_sprite.back().setTexture(button_texture);
    button_sprite.back().setTextureRect(IntRect(162, 16, 48, 24));
    button_sprite.back().setPosition(475, 195);
    button_sprite.push_back(Sprite());
    button_sprite.back().setTexture(button_texture);
    button_sprite.back().setTextureRect(IntRect(162, 16, 48, 24));
    button_sprite.back().setPosition(815, 195);
    button_sprite.push_back(Sprite());
    button_sprite.back().setTexture(button_texture);
    button_sprite.back().setTextureRect(IntRect(162, 16, 48, 24));
    button_sprite.back().setPosition(475, 318);
    button_sprite.push_back(Sprite());
    button_sprite.back().setTexture(button_texture);
    button_sprite.back().setTextureRect(IntRect(162, 16, 48, 24));
    button_sprite.back().setPosition(815, 318);

    icon_sprite.push_back(Sprite());
    icon_sprite.back().setTexture(icon_texture);
    icon_sprite.back().setTextureRect(IntRect(0, 0, 50, 50));
    icon_sprite.back().setPosition(220, 195);
    icon_sprite.back().setScale(0.7, 0.7);
    icon_sprite.push_back(Sprite());
    icon_sprite.back().setTexture(icon_texture);
    icon_sprite.back().setTextureRect(IntRect(50, 0, 50, 50));
    icon_sprite.back().setPosition(560, 195);
    icon_sprite.back().setScale(0.7, 0.7);
    icon_sprite.push_back(Sprite());
    icon_sprite.back().setTexture(icon_texture);
    icon_sprite.back().setTextureRect(IntRect(100, 0, 50, 50));
    icon_sprite.back().setPosition(220, 318);
    icon_sprite.back().setScale(0.7, 0.7);
    icon_sprite.push_back(Sprite());
    icon_sprite.back().setTexture(icon_texture);
    icon_sprite.back().setTextureRect(IntRect(150, 0, 50, 50));
    icon_sprite.back().setPosition(560, 318);
    icon_sprite.back().setScale(0.7, 0.7);
}

void Timed_clean::update(RectangleShape& cursor, File_handler& file_handler) {
    int current_active = 0;
    for (int i = 0; i < button_sprite.size(); i++) {
        if (cursor.getGlobalBounds().intersects(button_sprite[i].getGlobalBounds()) && Mouse::isButtonPressed(Mouse::Left) && click_timer.getElapsedTime().asSeconds() > 0.3) {
            for (int f = 0; f < button_sprite.size(); f++) {
                if (i != f) 
                    active[f] = false;
            }
            active[i] = !active[i];
            scheduled = false;
            removed = false;
            file_handler.save_scheduler_instruction(i);
            click_timer.restart();
        }
        if (!active[i])
            button_sprite[i].setTextureRect(IntRect(162, 41, 48, 24));
        else {
            button_sprite[i].setTextureRect(IntRect(162, 16, 48, 24));
            current_active++;
        }
    }
    if (current_active >= 1)
        set_shedule(file_handler);
    else
        remove_shedule(file_handler);

    day_limit_text.setString(to_string(day_limit) + " Days");
    junk_limit_text.setString(to_string(junk_limit) + " GB");
    hour_limit_text.setString(to_string(hour_limit) + " Hours");
}

void Timed_clean::set_shedule(File_handler& file_handler) {
    if (scheduled)
        return;

    // Initialize the starting date for day limit scheduling
    if (active[1]) {
        auto now = chrono::system_clock::now();
        chrono::days current_days_since_epoch = chrono::duration_cast<chrono::days>(now.time_since_epoch());
        file_handler.save_day_data(current_days_since_epoch);
    }

    // Place shortcut of scheduler in startup folder
    // Get path of the executable
    wchar_t appPath[MAX_PATH];
    GetModuleFileNameW(NULL, appPath, MAX_PATH);

    // Extract folder from full path
    wstring appFolder = appPath;
    size_t pos = appFolder.find_last_of(L"\\/");
    if (pos != wstring::npos)
        appFolder = appFolder.substr(0, pos);

    // Define target app name
    wstring appName = L"Cleanse Scheduler.exe";
    wstring targetPath = appFolder + L"\\" + appName;

    wchar_t startupPath[MAX_PATH];
    if (SUCCEEDED(SHGetFolderPathW(NULL, CSIDL_STARTUP, NULL, 0, startupPath))) {
        wstring shortcutPath = wstring(startupPath) + L"\\Cleanse Scheduler.lnk";

        // Initialize COM
        if (SUCCEEDED(CoInitialize(NULL))) {
            CComPtr<IShellLinkW> pShellLink;
            CComPtr<IPersistFile> pPersistFile;

            if (SUCCEEDED(CoCreateInstance(CLSID_ShellLink, NULL, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&pShellLink)))) {
                pShellLink->SetPath(targetPath.c_str());
                pShellLink->SetWorkingDirectory(appFolder.c_str());
                pShellLink->SetDescription(L"Launch Cleanse scheduler");
                pShellLink->SetIconLocation(targetPath.c_str(), 0);

                if (SUCCEEDED(pShellLink.QueryInterface(&pPersistFile))) {
                    pPersistFile->Save(shortcutPath.c_str(), TRUE);
                    scheduled = true;
                }
            }
            CoUninitialize();
        }
    }
}

void Timed_clean::remove_shedule(File_handler& file_handler) {
    if (removed)
        return;

    file_handler.save_scheduler_instruction(-1);

    wchar_t startupPath[MAX_PATH];
    if (SUCCEEDED(SHGetFolderPathW(NULL, CSIDL_STARTUP, NULL, 0, startupPath))) {
        wstring shortcutPath = wstring(startupPath) + L"\\Cleanse Scheduler.lnk";
        error_code ec;
        if (fs::remove(shortcutPath, ec))
            removed = true;
    }
}

void Timed_clean::draw(RenderWindow& window) {
    window.draw(title_info_text);
    window.draw(info_text);
    for (int i = 0; i < button_sprite.size(); i++) {
        window.draw(button_sprite[i]);
        window.draw(icon_sprite[i]);
        window.draw(option_text[i]);
        window.draw(option_text2[i]);
    }
    window.draw(day_limit_text);
    window.draw(junk_limit_text);
    window.draw(hour_limit_text);
}
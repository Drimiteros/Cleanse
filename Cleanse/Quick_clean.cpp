#include "Quick_clean.h"

Quick_clean::Quick_clean() {
    font.loadFromFile("src/Fonts/AlteHaasGroteskBold.ttf");
    font2.loadFromFile("src/Fonts/AlteHaasGroteskRegular.ttf");

    estimated_junk_text.setFont(font);
    estimated_junk_text.setCharacterSize(20);
    estimated_junk_text.setPosition(225, 75);
    estimated_junk_text.setString("Estimated Junk");

    categories_text.setFont(font2);
    categories_text.setCharacterSize(16);
    categories_text.setPosition(210, 315);
    categories_text.setFillColor(Color(255, 255, 255, 150));
    categories_text.setString("Categories");

    clean_button_texture.loadFromFile("src/Textures/cleanse.png");
    clean_button_texture.setSmooth(true);
    clean_button.setTexture(clean_button_texture);
    clean_button.setPosition(543, 260);
    clean_button.setScale(0.6, 0.6);
    clean_button.setOrigin(clean_button.getLocalBounds().width / 2, clean_button.getLocalBounds().height / 2);

    refresh_button_texture.loadFromFile("src/Textures/refresh.png");
    refresh_button_texture.setSmooth(true);
    refresh_button.setTexture(refresh_button_texture);
    refresh_button.setPosition(543, 200);
    refresh_button.setScale(0.6, 0.6);
    refresh_button.setOrigin(refresh_button.getLocalBounds().width / 2, refresh_button.getLocalBounds().height / 2);

    items_texture.loadFromFile("src/Textures/items.png");
    items_texture.setSmooth(true);
    items_sprite.setTexture(items_texture);
    items_sprite.setPosition(220, 350);

    total_junk_text.setFont(font);
    total_junk_text.setCharacterSize(43);
    total_junk_text.setString("");
    total_junk_text.setFillColor(Color(255, 150, 150));
    total_junk_text.setPosition(225, 105);
    total_junk_text.setString("Calculating...");

    recycle_junk_text.setFont(font);
    recycle_junk_text.setCharacterSize(23);
    recycle_junk_text.setString("");
    recycle_junk_text.setFillColor(Color(255, 150, 150));
    recycle_junk_category_text.setFont(font2);
    recycle_junk_category_text.setCharacterSize(14);
    recycle_junk_category_text.setString("Recycled files");
    recycle_junk_category_text.setPosition(270, 353);

    temp_junk_text.setFont(font);
    temp_junk_text.setCharacterSize(23);
    temp_junk_text.setString("");
    temp_junk_text.setFillColor(Color(255, 150, 150));
    temp_junk_category_text.setFont(font2);
    temp_junk_category_text.setCharacterSize(14);
    temp_junk_category_text.setString("Temp files");
    temp_junk_category_text.setPosition(270, 413);

    browser_junk_text.setFont(font);
    browser_junk_text.setCharacterSize(23);
    browser_junk_text.setString("");
    browser_junk_text.setFillColor(Color(255, 150, 150));
    browser_junk_category_text.setFont(font2);
    browser_junk_category_text.setCharacterSize(14);
    browser_junk_category_text.setString("Browser files");
    browser_junk_category_text.setPosition(270, 473);

    log_junk_text.setFont(font);
    log_junk_text.setCharacterSize(23);
    log_junk_text.setString("");
    log_junk_text.setFillColor(Color(255, 150, 150));
    log_junk_category_text.setFont(font2);
    log_junk_category_text.setCharacterSize(14);
    log_junk_category_text.setString("System logs");
    log_junk_category_text.setPosition(270, 533);

    status_text.setFont(font);
    status_text.setCharacterSize(24);
    status_info_text.setFont(font2);
    status_info_text.setCharacterSize(18);
    status_info_text.setPosition(900 / 2 - status_info_text.getLocalBounds().width / 2, 600 / 2 + 30);
    status_info_text.setFillColor(Color(160, 160, 160));

    refresh_menu_background_texture.loadFromFile("src/Textures/tiles.png");
    refresh_menu_background.setTexture(refresh_menu_background_texture);
    refresh_menu_background.setTextureRect(IntRect(880, 590, 879, 590));
    refresh_menu_background.setColor(Color(50, 50, 50));
    refresh_menu_background.setPosition(10, 0);
}

void Quick_clean::update(RectangleShape& cursor, wstring& user_profile_path, Disk_management& disk_management, File_handler& file_handler, bool exclude_categories_list[4], Enums& current_state, Report_screen& report_screen) {
    vector<wstring> temp_path = {
        user_profile_path + L"\\AppData\\Local\\Temp",
        user_profile_path + L"\\AppData\\Local\\CrashDumps",
        user_profile_path + L"\\AppData\\Roaming\\Temp",
        L"C:\\WINDOWS\\Temp",
        L"C:\\Windows\\Prefetch",
        L"C:\\Windows\\ServiceProfiles\\LocalService\\AppData\\Local\\Temp",
        L"C:\\Windows\\ServiceProfiles\\NetworkService\\AppData\\Local\\Temp",
        L"C:\\ProgramData\\Microsoft\\Windows\\WER\\ReportArchive",
        L"C:\\ProgramData\\Microsoft\\Windows\\WER\\Temp",
        L"C:\\ProgramData\\Microsoft\\Windows\\WER\\ReportQueue",
        L"C:\\ProgramData\\Package Cache",
        L"C:\\Windows\\Installer\\$PatchCache$",
        L"C:\\Windows\\Installer\\INPROGRESS",
        L"C:\\Windows\\SoftwareDistribution\\Download",
        L"C:\\Windows\\SoftwareDistribution\\DataStore",
        L"C:\\Windows\\SoftwareDistribution\\SelfUpdate",
        user_profile_path + L"\\AppData\\Local\\Packages\\Microsoft.WindowsStore_*\\LocalCache",
        user_profile_path + L"\\AppData\\Local\\Packages\\Microsoft.Windows.Photos_*\\TempState",
        user_profile_path + L"\\AppData\\Local\\Packages\\Microsoft.ZuneMusic_*\\LocalCache",
        user_profile_path + L"\\AppData\\Local\\Microsoft\\Windows\\INetCache",
        user_profile_path + L"\\AppData\\Local\\Microsoft\\Windows\\WebCache",
        user_profile_path + L"\\AppData\\Local\\Packages\\Microsoft.MicrosoftEdge_*\\AC\\Temp",
        user_profile_path + L"\\AppData\\Local\\Packages\\Microsoft.Windows.ContentDeliveryManager_cw5n1h2txyewy\\LocalState\\Assets",
        L"C:\\Users\\Public\\AppData\\Local\\D3DSCache",
        L"C:\\Windows\\ServiceProfiles\\LocalService\\AppData\\Local\\FontCache"
    };
    vector<wstring> browser_path = {
        user_profile_path + L"\\AppData\\Local\\BraveSoftware\\Brave-Browser\\User Data\\Default\\Cache",
        user_profile_path + L"\\AppData\\Local\\BraveSoftware\\Brave-Browser\\User Data\\Default\\Code Cache",
        user_profile_path + L"\\AppData\\Local\\BraveSoftware\\Brave-Browser\\User Data\\ShaderCache",
        user_profile_path + L"\\AppData\\Local\\Google\\Chrome\\User Data\\Default\\Cache",
        user_profile_path + L"\\AppData\\Local\\Google\\Chrome\\User Data\\Default\\Code Cache",
        user_profile_path + L"\\AppData\\Local\\Google\\Chrome\\User Data\\ShaderCache",
        user_profile_path + L"\\AppData\\Local\\Google\\Chrome\\User Data\\GrShaderCache",
        user_profile_path + L"\\AppData\\Local\\Microsoft\\Edge\\User Data\\Default\\Cache",
        user_profile_path + L"\\AppData\\Local\\Microsoft\\Edge\\User Data\\Default\\Code Cache",
        user_profile_path + L"\\AppData\\Local\\Microsoft\\Edge\\User Data\\ShaderCache",
        user_profile_path + L"\\AppData\\Local\\Microsoft\\Edge\\User Data\\Default\\Service Worker\\CacheStorage",
        user_profile_path + L"\\AppData\\Local\\Opera Software\\Opera Stable\\Cache",
        user_profile_path + L"\\AppData\\Local\\Opera Software\\Opera GX Stable\\Cache",
        user_profile_path + L"\\AppData\\Local\\Vivaldi\\User Data\\Default\\Cache",
        user_profile_path + L"\\AppData\\Local\\Vivaldi\\User Data\\Default\\Code Cache",
        user_profile_path + L"\\AppData\\Local\\Vivaldi\\User Data\\ShaderCache",
        user_profile_path + L"\\AppData\\Local\\Yandex\\YandexBrowser\\User Data\\Default\\Cache",
        user_profile_path + L"\\AppData\\Local\\Chromium\\User Data\\Default\\Cache",
    };
    vector<wstring> logs_path = {
        L"C:\\Windows\\Logs",
        L"C:\\Windows\\System32\\LogFiles",
        L"C:\\Windows\\System32\\WDI\\LogFiles",
        L"C:\\Windows\\System32\\SleepStudy",
        L"C:\\Windows\\System32\\config\\systemprofile\\AppData\\Local\\Microsoft\\Windows\\Power Efficiency Diagnostics",
        L"C:\\Windows\\Performance\\WinSAT\\DataStore",
        L"C:\\Windows\\System32\\winevt\\Logs",
        L"C:\\Windows\\SoftwareDistribution\\Download",
        L"C:\\Windows\\SoftwareDistribution\\PostRebootEventCache.V2",
        L"C:\\Windows\\inf\\setupapi.dev.log",
        L"C:\\Windows\\inf\\setupapi.app.log",
        L"C:\\Windows\\Logs\\CBS",
        L"C:\\Windows\\Logs\\DISM",
        L"C:\\ProgramData\\USOPrivate\\UpdateStore",
        L"C:\\ProgramData\\Microsoft\\Diagnosis",
        L"C:\\ProgramData\\Microsoft\\Windows\\WER\\Logs"
    };

    calculate_junk_size(user_profile_path, disk_management, cursor, temp_path, browser_path, logs_path);
    cleanse(cursor, user_profile_path, disk_management, file_handler, exclude_categories_list, temp_path, browser_path, logs_path, current_state, report_screen);
}   

void Quick_clean::calculate_junk_size(wstring& user_profile_path, Disk_management& disk_management, RectangleShape& cursor, vector<wstring>& temp_path, vector<wstring>& browser_path, vector<wstring>& logs_path) {
    if (cursor.getGlobalBounds().intersects(refresh_button.getGlobalBounds())) {
        refresh_button.setColor(Color(255, 255, 255, 255));
        if (Mouse::isButtonPressed(Mouse::Left)) {
            is_refreshing = true;
            status_text.setString("Refreshing...");
            status_text.setPosition(900 / 2 - status_text.getLocalBounds().width / 2, 600 / 2 - 30);
            status_text.setFillColor(Color(50, 150, 255));
            status_info_text.setString("Please wait a couple of seconds for the refresh to finish.\n                Waiting time depends on the junk size.");
            status_info_text.setPosition(900 / 2 - status_info_text.getLocalBounds().width / 2, 600 / 2 + 30);
        }
    }
    else
        refresh_button.setColor(Color(255, 255, 255, 150));

    if (calculate_junk_size_flag) {
        calculate_junk_size_flag = false;
        recycle_junk_size = 0;
        recycle_file_count = 0;
        temp_junk_size = 0;
        temp_file_count = 0;
        browser_junk_size = 0;
        browser_file_count = 0;
        log_file_count = 0;
        log_junk_size = 0;
        total_junk_size = 0;

        // Calculate temp files size
        for (const auto& path : temp_path) {
            try {
                for (const auto& entry : fs::recursive_directory_iterator(path, fs::directory_options::skip_permission_denied)) {
                    if (fs::is_regular_file(entry)) {
                        temp_junk_size += fs::file_size(entry);
                        temp_file_count++;
                    }
                }
            }
            catch (const fs::filesystem_error&) {
                continue;
            }
        }
        total_junk_size += temp_junk_size;
        temp_junk_text.setString(to_string(temp_junk_size / (1024 * 1024 * 1024)).substr(0, 4) + " GB");
        temp_junk_text.setPosition(900 - temp_junk_text.getLocalBounds().width - 40, 415);
        temp_junk_category_text.setString("Temp files\n" + to_string(temp_file_count));

        // Calculate recycle bin size
        for (const auto& drive : disk_management.drives) {
            wcout << drive.substr(0, 1) << endl;
            wstring recycle_path = drive.substr(0, 1) + L":\\$Recycle.Bin";
            try {
                for (const auto& entry : fs::recursive_directory_iterator(recycle_path, fs::directory_options::skip_permission_denied)) {
                    if (fs::is_regular_file(entry)) {
                        recycle_junk_size += fs::file_size(entry);
                        recycle_file_count++;
                    }
                }
            }
            catch (const fs::filesystem_error&) {
                continue;
            }
        }
        recycle_junk_text.setString(to_string(recycle_junk_size / (1024 * 1024 * 1024)).substr(0, 4) + " GB");
        recycle_junk_text.setPosition(900 - recycle_junk_text.getLocalBounds().width - 40, 355);
        total_junk_size += recycle_junk_size;
        recycle_junk_category_text.setString("Recycled files\n" + to_string(recycle_file_count));

        // Calculate browser files size
        for (const auto& path : browser_path) {
            try {
                for (const auto& entry : fs::recursive_directory_iterator(path, fs::directory_options::skip_permission_denied)) {
                    if (fs::is_regular_file(entry)) {
                        browser_junk_size += fs::file_size(entry);
                        browser_file_count++;
                    }
                }
            }
            catch (const fs::filesystem_error&) {
                continue;
            }
        }
        total_junk_size += browser_junk_size;
        browser_junk_text.setString(to_string(browser_junk_size / (1024 * 1024 * 1024)).substr(0, 4) + " GB");
        browser_junk_text.setPosition(900 - browser_junk_text.getLocalBounds().width - 40, 475);
        browser_junk_category_text.setString("Browser files\n" + to_string(browser_file_count));

        // Calculate log files size
        for (const auto& path : logs_path) {
            try {
                for (const auto& entry : fs::recursive_directory_iterator(path, fs::directory_options::skip_permission_denied)) {
                    if (fs::is_regular_file(entry)) {
                        log_junk_size += fs::file_size(entry);
                        log_file_count++;
                    }
                }
            }
            catch (const fs::filesystem_error&) {
                continue;
            }
        }
        total_junk_size += log_junk_size;
        log_junk_text.setString(to_string(log_junk_size / (1024 * 1024 * 1024)).substr(0, 4) + " GB");
        log_junk_text.setPosition(900 - log_junk_text.getLocalBounds().width - 40, 538);
        log_junk_category_text.setString("Log files\n" + to_string(log_file_count));
        total_junk_text.setString(to_string(total_junk_size / (1024 * 1024 * 1024)).substr(0, 4) + " GB");

        is_refreshing = false;
    }
}

// Helper function to cleanse function
void delete_directory_contents(const wstring& dir_path, Report_screen& report_screen) {
    error_code ec;
    try {
        for (const auto& entry : fs::directory_iterator(dir_path, fs::directory_options::skip_permission_denied, ec)) {
            if (ec) {
                report_screen.log_text_title.push_back(Text());
                report_screen.log_text_title.back().setFillColor(Color(255, 150, 150, 150));
                report_screen.log_text_title.back().setString("Issue: ");
                report_screen.log_text.push_back(Text());
                report_screen.log_text.back().setFillColor(Color(255, 255, 255, 150));
                report_screen.log_text.back().setString(ec.message().c_str());
                report_screen.issue_count++;
                ec.clear();
            }
            fs::remove_all(entry.path(), ec);
            if (ec) {
                report_screen.log_text_title.push_back(Text());
                report_screen.log_text_title.back().setFillColor(Color(255, 150, 150, 150));
                report_screen.log_text_title.back().setString("Issue: ");
                report_screen.log_text.push_back(Text());
                report_screen.log_text.back().setFillColor(Color(255, 255, 255, 150));
                report_screen.log_text.back().setString(ec.message().c_str());
                report_screen.issue_count++;
                ec.clear();
            }
            else {
                report_screen.log_text_title.push_back(Text());
                report_screen.log_text_title.back().setFillColor(Color(0, 255, 150, 150));
                report_screen.log_text_title.back().setString("Cleared: ");
                report_screen.log_text.push_back(Text());
                report_screen.log_text.back().setFillColor(Color(255, 255, 255, 150));
                if (entry.path().string().length() > 75)
                    report_screen.log_text.back().setString(entry.path().string().substr(0, 72) + "...");
                else
                    report_screen.log_text.back().setString(entry.path().string());
                ec.clear();
            }
        }
    }
    catch (const fs::filesystem_error& e) {
        report_screen.log_text_title.push_back(Text());
        report_screen.log_text_title.back().setFillColor(Color(255, 150, 150));
        report_screen.log_text_title.back().setString("Issue: ");
        report_screen.log_text.push_back(Text());
        report_screen.log_text.back().setFillColor(Color(255, 255, 255, 150));
        report_screen.log_text.back().setString(e.what());
        report_screen.issue_count++;
    }
}

void Quick_clean::cleanse(RectangleShape& cursor, wstring& user_profile_path, Disk_management& disk_management, File_handler& file_handler, bool exclude_categories_list[4], vector<wstring>& temp_path, 
    vector<wstring>& browser_path, vector<wstring>& logs_path, Enums& current_state, Report_screen& report_screen) {
    if (cursor.getGlobalBounds().intersects(clean_button.getGlobalBounds())) {
        clean_button.setColor(Color(255, 255, 255, 255));
        if (Mouse::isButtonPressed(Mouse::Left) && delete_clock.getElapsedTime().asSeconds() > 0.3) {
            is_cleaning = true;
            report_screen.issue_count = 0;
            report_screen.log_text.clear();
            report_screen.log_text_title.clear();
            status_text.setString("Cleansing...");
            status_text.setPosition(900 / 2 - status_text.getLocalBounds().width / 2, 600 / 2 - 30);
            status_text.setFillColor(Color(0, 255, 150));
            status_info_text.setString("Please wait a couple of seconds for the cleanse to finish.\n                Waiting time depends on the junk size.");
            status_info_text.setPosition(900 / 2 - status_info_text.getLocalBounds().width / 2, 600 / 2 + 30);
        }
    }
    else
        clean_button.setColor(Color(255, 255, 255, 150));

    if (clean_junk_files_flag) {
        clean_junk_files_flag = false;
        auto start = chrono::high_resolution_clock::now();
        float initial_size = total_junk_size;

        // Clear recycle bin using Windows API
        if (exclude_categories_list[0]) {
            HRESULT hr = SHEmptyRecycleBinW(nullptr, nullptr, SHERB_NOCONFIRMATION | SHERB_NOPROGRESSUI | SHERB_NOSOUND);
            if (SUCCEEDED(hr))
                wcout << L"Recycle Bin cleared successfully.\n";
            else
                wcout << L"Failed to clear Recycle Bin. Error code: " << hr << L"\n";
            for (const auto& drive : disk_management.drives) {
                wstring recycle_path = drive.substr(0, 1) + L":\\$Recycle.Bin";
                delete_directory_contents(recycle_path, report_screen);
            }
        }

        // Clear temp files
        if (exclude_categories_list[1]) {
            for (const auto& path : temp_path) {
                delete_directory_contents(path, report_screen);
            }
        }

        // Clear browser cache files
        if (exclude_categories_list[2]) {
            for (const auto& path : browser_path) {
                delete_directory_contents(path, report_screen);
            }
        }

        // Clear log files
        if (exclude_categories_list[3]) {
            for (const auto& path : logs_path) {
                delete_directory_contents(path, report_screen);
            }
        }

        auto end = chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);
        int total_milliseconds = duration.count();
        int minutes = total_milliseconds / 60000;
        int seconds = (total_milliseconds % 60000) / 1000;
        int milliseconds = total_milliseconds % 1000;
        ostringstream time_oss;
        time_oss << setfill('0') << setw(2) << minutes << ":" << setfill('0') << setw(2) << seconds << ":" << setfill('0') << setw(3) << milliseconds;

        calculate_junk_size_flag = true;
        is_cleaning = false;
        is_refreshing = true;
        calculate_junk_size(user_profile_path, disk_management, cursor, temp_path, browser_path, logs_path);
        float updated_size = total_junk_size;
        float final_size = round((static_cast<float>(initial_size - updated_size) / (1024 * 1024 * 1024)) * 100) / 100;
        ostringstream oss;
        oss << defaultfloat << final_size;
        disk_management.get_system_drives();
        disk_management.calculate_total_free_space();
        report_screen.total_junk_status_count_text.setString(oss.str() + " GB");
        report_screen.total_time_status_count_text.setString(time_oss.str());
        report_screen.total_issues_count_text.setString(to_string(report_screen.issue_count));
        file_handler.save_disk_data(final_size);
        file_handler.save_free_space_history(disk_management.total_free_space_percentage);
        
        delete_clock.restart();
        current_state = Enums::REPORT_SCREEN;
    }
}

void Quick_clean::draw(RenderWindow& window, RectangleShape& cursor) {
    window.draw(refresh_button);
    window.draw(clean_button);
    window.draw(estimated_junk_text);
    window.draw(categories_text);
    window.draw(total_junk_text);
    window.draw(temp_junk_text);
    window.draw(recycle_junk_text);
    window.draw(items_sprite);
    window.draw(recycle_junk_category_text);
    window.draw(temp_junk_category_text);
    window.draw(browser_junk_category_text);
    window.draw(log_junk_category_text);
    window.draw(log_junk_text);
    window.draw(browser_junk_text);
    if (is_refreshing || is_cleaning) {
        window.draw(refresh_menu_background);
        window.draw(status_text);
        window.draw(status_info_text);
    }
    if (is_refreshing)
        calculate_junk_size_flag = true;
    if (is_cleaning)
        clean_junk_files_flag = true;
}
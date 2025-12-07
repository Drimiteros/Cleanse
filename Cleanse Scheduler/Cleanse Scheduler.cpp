#include <iostream>
#include <SFML/Graphics.hpp>
#include "File_handler.h"
#include "Cleanse_once.h"
#include <chrono>
#include <format>

using namespace std;
using namespace sf;

wstring get_user_profile_path() {
    wchar_t buffer[MAX_PATH];
    DWORD size = GetEnvironmentVariableW(L"USERPROFILE", buffer, MAX_PATH);
    return (size > 0) ? wstring(buffer, size) : wstring(L"Unable to obtain");
}

int schedule_instruction = -1;
int recycle_file_count = 0;
int temp_file_count = 0;
int browser_file_count = 0;
int log_file_count = 0;
float total_junk_size = 0;
float recycle_junk_size = 0;
float temp_junk_size = 0;
float browser_junk_size = 0;
float log_junk_size = 0;
auto now = chrono::system_clock::now();
chrono::days current_days_since_epoch = chrono::duration_cast<chrono::days>(now.time_since_epoch());
chrono::days days_since_epoch;
Clock uptime_clock;

File_handler file_handler;
Cleanse_once cleanse_once;

int main() {
    RenderWindow window(VideoMode(0, 0), "Cleanse Scheduler", Style::Titlebar | Style::Close);
    window.setPosition(Vector2i(99999, 99999));
    HWND hwnd = window.getSystemHandle();
    SetWindowLong(hwnd, GWL_EXSTYLE, GetWindowLong(hwnd, GWL_EXSTYLE) | WS_EX_TOOLWINDOW);

    wstring user_profile_path = get_user_profile_path();

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

    file_handler.load_schedule(schedule_instruction);
    schedule_instruction = 3;
    if (schedule_instruction == 0) {
        cleanse_once.cleanse(temp_path, browser_path, logs_path);
    }
    else if (schedule_instruction == 1) {
        file_handler.load_day_data(days_since_epoch);

        if (current_days_since_epoch - days_since_epoch >= chrono::days{ 7 }) {
            cleanse_once.cleanse(temp_path, browser_path, logs_path);
            file_handler.save_day_data(current_days_since_epoch);
        }
    }
    else if (schedule_instruction == 2) {
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

        // Calculate recycle bin size
        wstring recycle_path = L"C:\\$Recycle.Bin";
        try {
            for (const auto& entry : fs::recursive_directory_iterator(recycle_path, fs::directory_options::skip_permission_denied)) {
                if (fs::is_regular_file(entry)) {
                    recycle_junk_size += fs::file_size(entry);
                    recycle_file_count++;
                }
            }
        }
        catch (const fs::filesystem_error&) {}
        total_junk_size += recycle_junk_size;

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

        if (total_junk_size >= 5)
            cleanse_once.cleanse(temp_path, browser_path, logs_path);
    }
    else if (schedule_instruction == 3) {
        while (window.isOpen()) {
            if (uptime_clock.getElapsedTime().asSeconds() >= 7200) {
                cleanse_once.cleanse(temp_path, browser_path, logs_path);
                uptime_clock.restart();
            }
        }
    }

    return 0;
}
#include "Main_loop.h"

bool isRunningAsAdmin() {
    BOOL isAdmin = FALSE;
    PSID adminGroup = NULL;
    SID_IDENTIFIER_AUTHORITY ntAuth = SECURITY_NT_AUTHORITY;

    if (AllocateAndInitializeSid(&ntAuth, 2, SECURITY_BUILTIN_DOMAIN_RID, DOMAIN_ALIAS_RID_ADMINS, 0, 0, 0, 0, 0, 0, &adminGroup)) {
        CheckTokenMembership(NULL, adminGroup, &isAdmin);
        FreeSid(adminGroup);
    }

    return isAdmin;
}

void relaunchAsAdmin() {
    wchar_t exePath[MAX_PATH];
    GetModuleFileNameW(NULL, exePath, MAX_PATH);
    ShellExecuteW(NULL, L"runas", exePath, NULL, NULL, SW_SHOWNORMAL);
}

Main_loop::Main_loop() {
    // Check if the app runs with admin privileges
    if (!isRunningAsAdmin()) {
        relaunchAsAdmin();
        return;
    }

    // Remove the installer file if it exists
    try { fs::remove("Cleanse Live Version Setup.exe"); }
    catch (fs::filesystem_error err) {}

    // Define window properties
    window.create(VideoMode(width, height), "Cleanse v." + version, Style::None);
    DwmExtendFrameIntoClientArea(window.getSystemHandle(), &margins);

    // Setup UI elements
    cursor.setSize(Vector2f(1, 1));

    // Get user profile path
    user_profile_path = disk_management.get_user_profile_path();

    // Get system drives
    disk_management.get_system_drives();

    // Load user settings
    file_handler.get_user_profile_path(user_profile_path);
    file_handler.load_user_settings(exclude_categories_list, check_for_updates);
    timed_clean.active[file_handler.load_scheduler_instruction()] = true;

    // Check for updates & set current state
    if (update_check.has_new_update(version) && check_for_updates)
        current_state = Enums::UPDATE_SCREEN;
    else {
        if (file_handler.load_welcome_screen())
            current_state = Enums::WELCOME_SCREEN;
        else
            current_state = Enums::QUICK_CLEAN;
    }
}

void Main_loop::events() {
    Event event;
    while (window.pollEvent(event)) {
        if (event.type == Event::Closed)
            window.close();
        if (event.type == Event::MouseWheelScrolled) {
            if (event.mouseWheelScroll.wheel == Mouse::VerticalWheel) {
                if (current_state == Enums::DISK_STATUS) {
                    scroll_value += event.mouseWheelScroll.delta * 100;
                    if (scroll_value > 0)
                        scroll_value = 0;
                    if (scroll_value < -static_cast<int>(disk_management.drives.size() - 1) * 100)
                        scroll_value = -static_cast<int>(disk_management.drives.size() - 1) * 100;
                }
                if (current_state == Enums::REPORT_SCREEN) {
                    scroll_value_report_screen += event.mouseWheelScroll.delta * 30;
                    if (scroll_value_report_screen > 0)
                        scroll_value_report_screen = 0;
                    if (scroll_value_report_screen < -static_cast<int>(report_screen.log_text.size() - 1) * 30)
                        scroll_value_report_screen = -static_cast<int>(report_screen.log_text.size() - 1) * 30;
                }
            }
        }
    }
}

void Main_loop::loop() {
    window.setFramerateLimit(144);

    while (window.isOpen()) {
        events();

        window.clear(Color::Transparent);

        update();
        draw_layer();

        window.display();
    }
}

void Main_loop::update() {
    if (window.hasFocus() == false)
        return;

    cursor.setPosition(window.mapPixelToCoords(Mouse::getPosition(window)));
    window_management.update(cursor, window, width, version, current_state, update_total_space_saved);
    
    if (current_state == Enums::WELCOME_SCREEN)
        welcome_screen.update(cursor, current_state, file_handler);
    if (current_state == Enums::QUICK_CLEAN)
        quick_clean.update(cursor, user_profile_path, disk_management, file_handler, exclude_categories_list, current_state, report_screen);
    if (current_state == Enums::TIMED_CLEAN)
        timed_clean.update(cursor, file_handler);
    if (current_state == Enums::DISK_STATUS)
        disk_management.update(scroll_value, cursor, update_total_space_saved, file_handler);
    if (current_state == Enums::SETTINGS) 
        settings.update(cursor, exclude_categories_list, file_handler, check_for_updates, version, update_check, current_state);
    if (current_state == Enums::DONATIONS) 
        donate.update(cursor);
    if (current_state == Enums::REPORT_SCREEN) 
        report_screen.update(cursor);
    if (current_state == Enums::UPDATE_SCREEN) 
        update_check.update(cursor, current_state, window, file_handler);
}

void Main_loop::draw_layer() {
    window_management.draw(window, cursor, current_state);
    if (current_state == Enums::WELCOME_SCREEN)
        welcome_screen.draw(window);
    if (current_state == Enums::QUICK_CLEAN)
        quick_clean.draw(window, cursor);
    if (current_state == Enums::TIMED_CLEAN)
        timed_clean.draw(window);
    if (current_state == Enums::DISK_STATUS)
        disk_management.draw(window, scroll_value);
    if (current_state == Enums::SETTINGS)
        settings.draw(window);
    if (current_state == Enums::DONATIONS)
        donate.draw(window);
    if (current_state == Enums::REPORT_SCREEN)
        report_screen.draw(window, scroll_value_report_screen);
    if (current_state == Enums::UPDATE_SCREEN)
        update_check.draw(window);
    //window.draw(cursor);

}

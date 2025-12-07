#include "Disk_management.h"

Disk_management::Disk_management() {
    font.loadFromFile("src/Fonts/AlteHaasGroteskBold.ttf");
    font2.loadFromFile("src/Fonts/AlteHaasGroteskRegular.ttf");

    drive_texture.loadFromFile("src/Textures/drive.png");
    drive_texture.setSmooth(true);
    arrow_texture.loadFromFile("src/Textures/arrow.png");
    arrow_texture.setSmooth(true);
    arrow_sprite.setTexture(arrow_texture);
    arrow_sprite.setPosition(310, 490);
    arrow_sprite2.setTexture(arrow_texture);
    arrow_sprite2.setPosition(310, 520);
    arrow_sprite2.rotate(180);

    total_drives_text.setFont(font);
    total_drives_text.setCharacterSize(18);
    total_drives_text.setFillColor(Color::White);
    total_drives_text.setPosition(250, 550);

    total_space_text.setFont(font2);
    total_space_text.setCharacterSize(18);
    total_space_text.setFillColor(Color::White);
    total_space_text.setPosition(495, 155);
    total_space_text.setString("Total Space");
    total_space_count_text.setFont(font);
    total_space_count_text.setCharacterSize(35);
    total_space_count_text.setFillColor(Color(174, 195, 255));
    total_space_count_text.setPosition(455, 120);
    total_space_count_text.setString("xx GB");

    total_free_space_text.setFont(font2);
    total_free_space_text.setCharacterSize(18);
    total_free_space_text.setFillColor(Color::White);
    total_free_space_text.setPosition(675, 145);
    total_free_space_text.setString("Total Free Space");
    total_free_space_count_text.setFont(font);
    total_free_space_count_text.setCharacterSize(26);
    total_free_space_count_text.setFillColor(Color(0, 255, 150));
    total_free_space_count_text.setPosition(675, 165);
    total_free_space_count_text.setString("xx%");

    space_saved_text.setFont(font2);
    space_saved_text.setCharacterSize(18);
    space_saved_text.setPosition(675, 85);
    space_saved_text.setString("Total junk cleaned");
    space_saved_count_text.setFont(font);
    space_saved_count_text.setCharacterSize(26);
    space_saved_count_text.setPosition(675, 105);
    space_saved_count_text.setFillColor(Color(0, 255, 150));

    graph_drive_clean_history_text.setFont(font2);
    graph_drive_clean_history_text.setCharacterSize(13);
    graph_drive_clean_history_text.setPosition(469, 308);
    graph_drive_clean_history_text.setString("Freed space per clean cycle (GB)");

    graph_drive_clean_history_point.setRadius(5);
    graph_drive_clean_history_point.setOrigin(5, 5);
    graph_drive_clean_history_point.setFillColor(Color(0, 255, 150));
    graph_drive_clean_history_point.setPosition(457, 316);

    graph_drive_free_space_history_text.setFont(font2);
    graph_drive_free_space_history_text.setCharacterSize(13);
    graph_drive_free_space_history_text.setPosition(469, 420);
    graph_drive_free_space_history_text.setString("Total free space per clean cycle (%)");

    graph_drive_free_space_history_point.setRadius(5);
    graph_drive_free_space_history_point.setOrigin(5, 5);
    graph_drive_free_space_history_point.setFillColor(Color(255, 200, 0));
    graph_drive_free_space_history_point.setPosition(457, 428);

    drive_view_bounds.setSize(Vector2f(200, 396));
    drive_view_bounds.setPosition(200, 52);

    line.setPrimitiveType(LineStrip);
    fill.setPrimitiveType(TriangleStrip);
    line2.setPrimitiveType(LineStrip);
    fill2.setPrimitiveType(TriangleStrip);
    graph_axis_X[0].setSize(Vector2f(380, 1));
    graph_axis_X[0].setPosition(470, 300);
    graph_axis_X[0].setFillColor(Color(100, 100, 100));
    graph_axis_X[1].setSize(Vector2f(380, 1));
    graph_axis_X[1].setPosition(470, 410);
    graph_axis_X[1].setFillColor(Color(100, 100, 100));
    graph_axis_Y[0].setSize(Vector2f(1, 50));
    graph_axis_Y[0].setPosition(470, 250);
    graph_axis_Y[0].setFillColor(Color(100, 100, 100));
    graph_axis_Y[1].setSize(Vector2f(1, 50));
    graph_axis_Y[1].setPosition(470, 360);
    graph_axis_Y[1].setFillColor(Color(100, 100, 100));
    for (int i = 0; i < 20; i++) {
        graph_one_points.push_back(CircleShape());
        graph_one_points.back().setRadius(3);
        graph_one_points.back().setOrigin(3, 3);
        graph_one_points.back().setFillColor(Color(0, 255, 150));
        graph_one_points.back().setPosition(9999, 9999);
        graph_two_points.push_back(CircleShape());
        graph_two_points.back().setRadius(3);
        graph_two_points.back().setOrigin(3, 3);
        graph_two_points.back().setFillColor(Color(255, 200, 0));
        graph_two_points.back().setPosition(9999, 9999);
    }
    current_graph_value_text.setFont(font2);
    current_graph_value_text.setCharacterSize(10);

    cosmetic_texture.loadFromFile("src/Textures/cosmetic.png");
    cosmetic_texture.setSmooth(true);
    cosmetic_sprite.setTexture(cosmetic_texture);
    cosmetic_sprite.setPosition(655, 95);
}

void Disk_management::update(int& scroll_value, RectangleShape& cursor, bool& update_total_space_saved, File_handler& file_handler) {
    if (drives.size() > 4) {
        if (cursor.getGlobalBounds().intersects(arrow_sprite.getGlobalBounds())) {
            arrow_sprite.setColor(Color(255, 255, 255, 255));
            if (Mouse::isButtonPressed(Mouse::Left) && delay_clock.getElapsedTime().asSeconds() > 0.3 && scroll_value > -static_cast<int>(drives.size() - 1) * 100) {
                scroll_value -= 100;
                delay_clock.restart();
            }
        }
        else
            arrow_sprite.setColor(Color(255, 255, 255, 155));
        if (cursor.getGlobalBounds().intersects(arrow_sprite2.getGlobalBounds())) {
            arrow_sprite2.setColor(Color(255, 255, 255, 255));
            if (Mouse::isButtonPressed(Mouse::Left) && delay_clock.getElapsedTime().asSeconds() > 0.3 && scroll_value < 0) {
                scroll_value += 100;
                delay_clock.restart();
            }
        }
        else
            arrow_sprite2.setColor(Color(255, 255, 255, 155));
    }

    get_system_drives();
    calculate_total_free_space();
    calculate_space_saved(update_total_space_saved, file_handler);
    graph(file_handler, cursor);
}

wstring Disk_management::get_user_profile_path() {
    wchar_t buffer[MAX_PATH];
    DWORD size = GetEnvironmentVariableW(L"USERPROFILE", buffer, MAX_PATH);
    return (size > 0) ? wstring(buffer, size) : wstring(L"Unable to obtain");
}

void Disk_management::get_system_drives() {
    drives.clear();
    drive_texts.clear();
    drive_bars.clear();
    drive_progress_bars.clear();
    bar_left_edges.clear();
    bar_right_edges.clear();
    drive_total_size.clear();
    drive_free_size.clear();
    drive_sprites.clear();
    drive_infos.clear();
    totalFreeSpaceCount = 0;
    totalSpaceCount = 0;

    wchar_t buffer[256];
    DWORD size = GetLogicalDriveStringsW(256, buffer);
    if (size > 0) {
        wchar_t* drive = buffer;
        while (*drive) {
            drives.push_back(wstring(drive));
            
            drive_texts.push_back(Text());
            drive_texts.back().setFont(font);
            drive_texts.back().setCharacterSize(18);
            drive_texts.back().setFillColor(Color::White);

            wstring ws_drive(drive);
            wstring ws_label = L"Local disk (" + ws_drive + ")";
            drive_texts.back().setString(ws_label);

            drive_bars.push_back(RectangleShape(Vector2f(110.f, 10)));
            drive_bars.back().setFillColor(Color(80, 80, 80, 255));
            drive_progress_bars.push_back(RectangleShape(Vector2f(0.f, 10)));
            drive_progress_bars.back().setFillColor(Color(0, 255, 150));
            bar_left_edges.push_back(CircleShape());
            bar_left_edges.back().setRadius(5);
            bar_right_edges.push_back(CircleShape());
            bar_right_edges.back().setRadius(5);

            ULARGE_INTEGER freeBytesAvailable, totalNumberOfBytes, totalNumberOfFreeBytes;
            if (GetDiskFreeSpaceExW(drive, &freeBytesAvailable, &totalNumberOfBytes, &totalNumberOfFreeBytes)) {
                drive_total_size.push_back(static_cast<float>(totalNumberOfBytes.QuadPart));
                drive_free_size.push_back(static_cast<float>(totalNumberOfFreeBytes.QuadPart));
                
                drive_sprites.push_back(Sprite());
                drive_sprites.back().setTexture(drive_texture);
                drive_sprites.back().setScale(0.33, 0.33);

                drive_infos.push_back(Text());
                drive_infos.back().setFont(font2);
                drive_infos.back().setCharacterSize(14);
                drive_infos.back().setFillColor(Color::White);
                totalFreeSpaceCount += static_cast<float>(totalNumberOfFreeBytes.QuadPart / (1024 * 1024 * 1024));
                totalSpaceCount += static_cast<float>(totalNumberOfBytes.QuadPart / (1024 * 1024 * 1024));
                wstring ws_info = L"Total Size: " + to_wstring(totalNumberOfBytes.QuadPart / (1024 * 1024 * 1024)) + L" GB\nFree Size: " +
                    to_wstring(totalNumberOfFreeBytes.QuadPart / (1024 * 1024 * 1024)) + L" GB";
                drive_infos.back().setString(ws_info);
            }

            drive += wcslen(drive) + 1;
        }
    }

    for (int i = 0; i < drive_total_size.size(); i++) {
        wcout << L"Drive: " << drives[i] << "\nTotal size: " << drive_total_size[i] / (1024 * 1024 * 1024) << 
        L" GB\nFree size: " << drive_free_size[i] / (1024 * 1024 * 1024) << L" GB\n\n";
    }

    total_drives_text.setString(L"Total Drives: " + to_wstring(drives.size()));
    total_drives_text.setOrigin(total_drives_text.getLocalBounds().width / 2, 0);
    total_drives_text.setPosition(310, 545);
}

void Disk_management::calculate_total_free_space() {
    total_free_space_percentage = (totalFreeSpaceCount / totalSpaceCount) * 100;
    if (total_free_space_percentage >= 70)
        total_free_space_count_text.setFillColor(Color(0, 255, 150));
    else if (total_free_space_percentage >= 40)
        total_free_space_count_text.setFillColor(Color(255, 220, 150));
    else
        total_free_space_count_text.setFillColor(Color(255, 150, 150));
    total_free_space_count_text.setString(to_string(total_free_space_percentage).substr(0, 5) + "%");
    
    ostringstream oss;
    oss << defaultfloat<< totalSpaceCount;
    total_space_count_text.setString(oss.str() + " GB");
    total_space_count_text.setPosition(540 - total_space_count_text.getLocalBounds().width / 2, 110);
}

void Disk_management::calculate_space_saved(bool& update_total_space_saved, File_handler& file_handler) {
    if (!update_total_space_saved)
        return;

    float total_space_saved = 0;
    float scale = pow(10, 2);
    
    file_handler.load_disk_data(total_space_saved);
    
    total_space_saved = round(total_space_saved * scale) / scale;
    ostringstream oss;
    oss << defaultfloat << total_space_saved;

    space_saved_count_text.setString(oss.str() + " GB");
    update_total_space_saved = false;
}

void Disk_management::graph(File_handler& file_handler, RectangleShape& cursor) {
    line.clear();
    fill.clear();
    float largest_value = 0;
    for (size_t i = 0; i < file_handler.load_disk_clean_history().size(); i++)
        largest_value = max(largest_value, file_handler.load_disk_clean_history()[i]);
    for (size_t i = 0; i < file_handler.load_disk_clean_history().size(); i++) {
        float x = 470 + i * 20;
        float y = 300 - (file_handler.load_disk_clean_history()[i] / largest_value) * 55;

        graph_one_points[i].setPosition(x, y);

        line.append(Vertex(Vector2f(x, y), Color(0, 255, 200, 255)));
        fill.append(Vertex(Vector2f(x, y), Color(0, 255, 150, 80)));
        fill.append(Vertex(Vector2f(x, 300), Color(30, 30, 30, 0)));

        if (cursor.getGlobalBounds().intersects(graph_one_points[i].getGlobalBounds())) {
            current_graph_value_text.setPosition(x - current_graph_value_text.getLocalBounds().width / 2, y - 20);
            float scale = pow(10, 2);
            float display_value = file_handler.load_disk_clean_history()[i];
            display_value = round(file_handler.load_disk_clean_history()[i] * scale) / scale;
            ostringstream oss;
            oss << fixed << defaultfloat << display_value << " GB";
            current_graph_value_text.setString(oss.str());
        }
    }

    line2.clear();
    fill2.clear();
    float largest_value2 = 0;
    for (size_t i = 0; i < file_handler.load_free_space_history().size(); i++)
        largest_value2 = max(largest_value2, file_handler.load_free_space_history()[i]);
    for (size_t i = 0; i < file_handler.load_free_space_history().size(); i++) {
        float x = 470 + i * 20;
        float y = 410 - (file_handler.load_free_space_history()[i] / largest_value2) * 55;

        graph_two_points[i].setPosition(x, y);

        line2.append(Vertex(Vector2f(x, y), Color(255, 200, 0, 255)));
        fill2.append(Vertex(Vector2f(x, y), Color(255, 150, 150, 80)));
        fill2.append(Vertex(Vector2f(x, 410), Color(30, 30, 30, 0)));

        if (cursor.getGlobalBounds().intersects(graph_two_points[i].getGlobalBounds())) {
            current_graph_value_text.setPosition(x - current_graph_value_text.getLocalBounds().width / 2, y - 20);
            float scale = pow(10, 2);
            float display_value = file_handler.load_free_space_history()[i];
            display_value = round(file_handler.load_free_space_history()[i] * scale) / scale;
            ostringstream oss;
            oss << fixed << defaultfloat << display_value << " %";
            current_graph_value_text.setString(oss.str());
        }
    }
}

void Disk_management::draw(RenderWindow& window, int scroll_value) {
    //window.draw(drive_view_bounds);
    for (int i = 0; i < drive_sprites.size(); i++) {
        drive_sprites[i].setPosition(210, 65 + i * 100 + scroll_value);
        drive_texts[i].setPosition(280, 65 + i * 100 + scroll_value);
        drive_infos[i].setPosition(280, 90 + i * 100 + scroll_value);
        drive_bars[i].setPosition(285, 130 + i * 100 + scroll_value);
        drive_progress_bars[i].setPosition(285, 130 + i * 100 + scroll_value);
        drive_progress_bars[i].setSize(Vector2f(((drive_total_size[i] - drive_free_size[i]) / drive_total_size[i]) * 110, 10));

        if (drive_sprites[i].getGlobalBounds().intersects(drive_view_bounds.getGlobalBounds())) {
            window.draw(drive_sprites[i]);
            window.draw(drive_texts[i]);
            window.draw(drive_infos[i]);
            window.draw(drive_bars[i]);
            window.draw(drive_progress_bars[i]);
        }
    }
    for (int i = 0; i < bar_left_edges.size(); i++) {
        bar_left_edges[i].setFillColor(Color(0, 255, 150, 255));
        bar_left_edges[i].setPosition(280, 130 + i * 100 + scroll_value);
        bar_right_edges[i].setFillColor(Color(80, 80, 80, 255));
        bar_right_edges[i].setPosition(210 + 179, 130 + i * 100 + scroll_value);
        if (bar_left_edges[i].getGlobalBounds().intersects(drive_view_bounds.getGlobalBounds())) {
            window.draw(bar_left_edges[i]);
            window.draw(bar_right_edges[i]);
        }
    }
    if (drives.size() > 4) {
        window.draw(arrow_sprite);
        window.draw(arrow_sprite2);
    }
    window.draw(total_drives_text);
    window.draw(total_space_count_text);
    window.draw(total_space_text);
    window.draw(total_free_space_count_text);
    window.draw(total_free_space_text);
    window.draw(space_saved_text);
    window.draw(space_saved_count_text);

    window.draw(fill);
    window.draw(line);
    window.draw(fill2);
    window.draw(line2);
    window.draw(graph_drive_clean_history_text);
    window.draw(graph_drive_free_space_history_text);
    window.draw(graph_drive_clean_history_point);
    window.draw(graph_drive_free_space_history_point);
    window.draw(graph_axis_X[0]);
    window.draw(graph_axis_X[1]);
    window.draw(graph_axis_Y[0]);
    window.draw(graph_axis_Y[1]);

    for (int i = 0; i < 20; i++) {
        window.draw(graph_one_points[i]);
        window.draw(graph_two_points[i]);
    }
    window.draw(current_graph_value_text);
    window.draw(cosmetic_sprite);
}
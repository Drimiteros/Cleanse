#include "Window_management.h"

Window_management::Window_management() {
    buttons_texture.loadFromFile("src/Textures/buttons.png");
    buttons_texture.setSmooth(true);
    close_button.setTexture(buttons_texture);
    close_button.setTextureRect(IntRect(0, 0, 24, 24));
    minimize_button.setTexture(buttons_texture);
    minimize_button.setTextureRect(IntRect(24, 0, 24, 24));

    background_texture.loadFromFile("src/Textures/background.png");
    background_sprite.setTexture(background_texture);
    background_sprite.setColor(Color(50, 50, 50, 250));

    top_bar_texture.loadFromFile("src/Textures/top_bar.png");
    top_bar.setTexture(top_bar_texture);
    top_bar.setColor(Color(60, 60, 60, 255));

    logo_texture.loadFromFile("src/Textures/logo.png");
    logo_texture.setSmooth(true);
    logo_sprite.setTexture(logo_texture);
    logo_sprite.setScale(0.5, 0.5);
    logo_sprite.setPosition(25, 67);

    calendar_texture.loadFromFile("src/Textures/calendar.png");
    calendar_texture.setSmooth(true);
    calendar_sprite.setTexture(calendar_texture);
    calendar_sprite.setScale(0.5, 0.5);
    calendar_sprite.setPosition(25, 127);

    status_texture.loadFromFile("src/Textures/status.png");
    status_texture.setSmooth(true);
    status_sprite.setTexture(status_texture);
    status_sprite.setScale(0.5, 0.5);
    status_sprite.setPosition(26, 188);

    options_texture.loadFromFile("src/Textures/gear.png");
    options_texture.setSmooth(true);
    options_sprite.setTexture(options_texture);
    options_sprite.setScale(0.5, 0.5);
    options_sprite.setPosition(25, 248);

    donate_texture.loadFromFile("src/Textures/love.png");
    donate_texture.setSmooth(true);
    donate_sprite.setTexture(donate_texture);
    donate_sprite.setScale(0.5, 0.5);
    donate_sprite.setPosition(25, 308);

    font.loadFromFile("src/Fonts/AlteHaasGroteskBold.ttf");
    title_text.setFont(font);
    title_text.setCharacterSize(16);
    title_text.setFillColor(Color::White);
    
    quick_clean_text.setFont(font);
    quick_clean_text.setCharacterSize(18);
    quick_clean_text.setFillColor(Color::White);
    quick_clean_text.setString("Quick Clean");
    quick_clean_text.setPosition(62, 71);

    calendar_text.setFont(font);
    calendar_text.setCharacterSize(18);
    calendar_text.setFillColor(Color::White);
    calendar_text.setString("Scheduling");
    calendar_text.setPosition(62, 131);

    status_text.setFont(font);
    status_text.setCharacterSize(18);
    status_text.setFillColor(Color::White);
    status_text.setString("Disk Status");
    status_text.setPosition(62, 191);

    options_text.setFont(font);
    options_text.setCharacterSize(18);
    options_text.setFillColor(Color::White);
    options_text.setString("Settings");
    options_text.setPosition(62, 251);

    donate_text.setFont(font);
    donate_text.setCharacterSize(19);
    donate_text.setFillColor(Color::White);
    donate_text.setString("Donations");
    donate_text.setPosition(62, 311);

    button_sprites.push_back(Sprite());
    button_sprites.back().setTexture(buttons_texture);
    button_sprites.back().setTextureRect(IntRect(0, 24, 162, 41));
    button_sprites.back().setScale(1, 1);
    button_sprites.back().setPosition(19, 63);
    button_sprites.back().setColor(Color(90, 90, 90, 255));
    button_sprites.push_back(Sprite());
    button_sprites.back().setTexture(buttons_texture);
    button_sprites.back().setTextureRect(IntRect(0, 24, 162, 41));
    button_sprites.back().setScale(1, 1);
    button_sprites.back().setPosition(19, 123);
    button_sprites.back().setColor(Color(90, 90, 90, 255));
    button_sprites.push_back(Sprite());
    button_sprites.back().setTexture(buttons_texture);
    button_sprites.back().setTextureRect(IntRect(0, 24, 162, 41));
    button_sprites.back().setScale(1, 1);
    button_sprites.back().setPosition(19, 183);
    button_sprites.back().setColor(Color(90, 90, 90, 255));
    button_sprites.push_back(Sprite());
    button_sprites.back().setTexture(buttons_texture);
    button_sprites.back().setTextureRect(IntRect(0, 24, 162, 41));
    button_sprites.back().setScale(1, 1);
    button_sprites.back().setPosition(19, 243);
    button_sprites.back().setColor(Color(90, 90, 90, 255));
    button_sprites.push_back(Sprite());
    button_sprites.back().setTexture(buttons_texture);
    button_sprites.back().setTextureRect(IntRect(0, 24, 162, 41));
    button_sprites.back().setScale(1, 1);
    button_sprites.back().setPosition(19, 303);
    button_sprites.back().setColor(Color(90, 90, 90, 255));

    tiles_texture.loadFromFile("src/Textures/tiles.png");
    tiles.setTexture(tiles_texture);
    tiles.setColor(Color(50, 50, 50, 250));
    tiles.setPosition(10, 0);
}

void Window_management::update(RectangleShape& cursor, RenderWindow& window, int& width, string& version, Enums& new_state, bool& update_total_space_saved) {
    close_button.setPosition(width - 38, 10);
    minimize_button.setPosition(width - 78, 10);
    title_text.setString("Cleanse v." + version);
    title_text.setPosition(width / 2 - title_text.getLocalBounds().width / 2, 10);

    close_window(cursor, window);
    minimize_window(cursor, window);
    handle_window_drag(cursor, window, width);
    change_state(new_state, cursor, update_total_space_saved);
}

void Window_management::close_window(RectangleShape& cursor, RenderWindow& window) {
    if (cursor.getGlobalBounds().intersects(close_button.getGlobalBounds())) {
        close_button.setColor(Color(255, 255, 255, 255));
        if (Mouse::isButtonPressed(Mouse::Left))
            window.close();
    }
    else
        close_button.setColor(Color(255, 255, 255, 200));
}

void Window_management::minimize_window(RectangleShape& cursor, RenderWindow& window) {
    if (cursor.getGlobalBounds().intersects(minimize_button.getGlobalBounds())) {
        minimize_button.setColor(Color(255, 255, 255, 255));
        if (Mouse::isButtonPressed(Mouse::Left))
            ShowWindow(window.getSystemHandle(), SW_MINIMIZE);
    }
    else
        minimize_button.setColor(Color(255, 255, 255, 200));
}

void Window_management::handle_window_drag(RectangleShape& cursor, RenderWindow& window, int& width) {
    if (Mouse::isButtonPressed(Mouse::Left) && cursor.getGlobalBounds().intersects(top_bar.getGlobalBounds())) {
        Vector2i mouse_pos = Mouse::getPosition();
        window.setPosition(Vector2i(mouse_pos.x - width / 2, mouse_pos.y - 20));
    }
}

void Window_management::change_state(Enums& current_state, RectangleShape& cursor, bool& update_total_space_saved) {
    if (current_state == Enums::UPDATE_SCREEN) {
        tiles.setTextureRect(IntRect(881, 0, 879, 590));
        return;
    }
    if (current_state == Enums::WELCOME_SCREEN) {
        tiles.setTextureRect(IntRect(881, 591, 879, 590));
        return;
    }
    
    // Change state from the side menu buttons
    if (cursor.getGlobalBounds().intersects(button_sprites[0].getGlobalBounds()) && Mouse::isButtonPressed(Mouse::Left))
        current_state = Enums::QUICK_CLEAN;
    if (cursor.getGlobalBounds().intersects(button_sprites[1].getGlobalBounds()) && Mouse::isButtonPressed(Mouse::Left))
        current_state = Enums::TIMED_CLEAN;
    if (cursor.getGlobalBounds().intersects(button_sprites[2].getGlobalBounds()) && Mouse::isButtonPressed(Mouse::Left)) {
        current_state = Enums::DISK_STATUS;
        update_total_space_saved = true;
    }
    if (cursor.getGlobalBounds().intersects(button_sprites[3].getGlobalBounds()) && Mouse::isButtonPressed(Mouse::Left))
        current_state = Enums::SETTINGS;
    if (cursor.getGlobalBounds().intersects(button_sprites[4].getGlobalBounds()) && Mouse::isButtonPressed(Mouse::Left))
        current_state = Enums::DONATIONS;

    if (current_state == Enums::QUICK_CLEAN)
        tiles.setTextureRect(IntRect(0, 590, 879, 590));
    if (current_state == Enums::TIMED_CLEAN)
        tiles.setTextureRect(IntRect(881, 1771, 879, 590));
    if (current_state == Enums::DISK_STATUS)
        tiles.setTextureRect(IntRect(0, 0, 879, 590));
    if (current_state == Enums::SETTINGS)
        tiles.setTextureRect(IntRect(0, 1180, 879, 590));
    if (current_state == Enums::DONATIONS)
        tiles.setTextureRect(IntRect(0, 1770, 879, 590));
    if (current_state == Enums::REPORT_SCREEN)
        tiles.setTextureRect(IntRect(880, 1180, 879, 590));
}

void Window_management::draw(RenderWindow& window, RectangleShape& cursor, Enums& current_state) {
    window.draw(background_sprite);
    window.draw(tiles);
    window.draw(top_bar);
    window.draw(close_button);
    window.draw(minimize_button);
    window.draw(title_text);
    if (current_state != Enums::UPDATE_SCREEN && current_state != Enums::WELCOME_SCREEN) {
        for (int i = 0; i < button_sprites.size(); i++)
            if (cursor.getGlobalBounds().intersects(button_sprites[i].getGlobalBounds()))
                window.draw(button_sprites[i]);
        window.draw(logo_sprite);
        window.draw(calendar_sprite);
        window.draw(status_sprite);
        window.draw(quick_clean_text);
        window.draw(calendar_text);
        window.draw(status_text);
        window.draw(options_sprite);
        window.draw(options_text);
        window.draw(donate_sprite);
        window.draw(donate_text);
    }
}
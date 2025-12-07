#include "Settings.h"

Settings::Settings() {
    font.loadFromFile("src/Fonts/AlteHaasGroteskBold.ttf");
    font2.loadFromFile("src/Fonts/AlteHaasGroteskRegular.ttf");

    items_texture.loadFromFile("src/Textures/items2.png");
    items_texture.setSmooth(true);

    cleaning_preferences_text.setFont(font);
    cleaning_preferences_text.setString("Cleaning Preferences");
    cleaning_preferences_text.setCharacterSize(25);
    cleaning_preferences_text.setPosition(220, 70);

    exclude_cleaning_categories_text.setFont(font2);
    exclude_cleaning_categories_text.setString("Don't clear Recycled Files\nDon't clear Temp Files\nDon't clear Browser Files\nDon't clear Log Files");
    exclude_cleaning_categories_text.setCharacterSize(15);
    exclude_cleaning_categories_text.setPosition(225, 105);
    exclude_cleaning_categories_text.setFillColor(Color(200, 200, 200));

    for (int i = 0; i < 4; i++) {
        exclude_circle.push_back(CircleShape());
        exclude_circle.back().setRadius(8);
        exclude_circle.back().setPosition(505, 105 + (i * 19));
    }

    update_preferences_text.setFont(font);
    update_preferences_text.setString("Check for Updates");
    update_preferences_text.setCharacterSize(25);
    update_preferences_text.setPosition(560, 70);

    check_for_updates_text.setFont(font2);
    check_for_updates_text.setString("Check for updates on startup\n\n\nCheck for updates now");
    check_for_updates_text.setCharacterSize(15);
    check_for_updates_text.setPosition(560, 105);
    check_for_updates_text.setFillColor(Color(200, 200, 200));

    update_check_circle.setRadius(8);
    update_check_circle.setPosition(check_for_updates_text.getPosition().x + 285, check_for_updates_text.getPosition().y + 5);

    reload_button_sprite.setTexture(items_texture);
    reload_button_sprite.setTextureRect(IntRect(200, 0, 50, 50));
    reload_button_sprite.setPosition(check_for_updates_text.getPosition().x + 275, check_for_updates_text.getPosition().y + 45);
    reload_button_sprite.setScale(0.6, 0.6);
}

void Settings::update(RectangleShape& cursor, bool exclude_categories_list[4], File_handler& file_handler, bool& check_for_updates, string& version, Update_check& update_check, Enums& enums) {
    change_pref(exclude_categories_list, cursor, file_handler, check_for_updates, version, update_check, enums);
}

void Settings::change_pref(bool exclude_categories_list[4], RectangleShape& cursor, File_handler& file_handler, bool& check_for_updates, string& version, Update_check& update_check, Enums& enums) {
    for (int i = 0; i < 4; i++) {
        if (cursor.getGlobalBounds().intersects(exclude_circle[i].getGlobalBounds()) && Mouse::isButtonPressed(Mouse::Left) && click_delay_clock.getElapsedTime().asSeconds() > 0.3) {
            exclude_categories_list[i] = !exclude_categories_list[i];
            file_handler.save_user_settings(exclude_categories_list, check_for_updates);
            click_delay_clock.restart();
        }

        if (!exclude_categories_list[i])
            exclude_circle[i].setFillColor(Color(0, 255, 150));
        else
            exclude_circle[i].setFillColor(Color(80, 80, 80));
    }

    if (cursor.getGlobalBounds().intersects(update_check_circle.getGlobalBounds())) {
        if (Mouse::isButtonPressed(Mouse::Left) && click_delay_clock.getElapsedTime().asSeconds() > 0.3) {
            check_for_updates = !check_for_updates;
            file_handler.save_user_settings(exclude_categories_list, check_for_updates);
            click_delay_clock.restart();
        }
    }
    if (!check_for_updates)
        update_check_circle.setFillColor(Color(80, 80, 80));
    else
        update_check_circle.setFillColor(Color(0, 255, 150));

    if (cursor.getGlobalBounds().intersects(reload_button_sprite.getGlobalBounds())) {
        reload_button_sprite.setColor(Color(255, 255, 255, 255));
        if (Mouse::isButtonPressed(Mouse::Left))
            if (update_check.has_new_update(version))
                enums = Enums::UPDATE_SCREEN;
    }
    else {
        reload_button_sprite.setColor(Color(255, 255, 255, 150));
    }
}

void Settings::draw(RenderWindow& window) {
    window.draw(cleaning_preferences_text);
    window.draw(exclude_cleaning_categories_text);
    window.draw(update_preferences_text);
    window.draw(check_for_updates_text);
    for (int i = 0; i < 4; i++)
        window.draw(exclude_circle[i]);
    window.draw(update_check_circle);
    window.draw(reload_button_sprite);
}
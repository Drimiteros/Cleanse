#include "Welcome_screen.h"

Welcome_screen::Welcome_screen() {
    font.loadFromFile("src/Fonts/AlteHaasGroteskBold.ttf");
    font2.loadFromFile("src/Fonts/AlteHaasGroteskRegular.ttf");

    texture.loadFromFile("src/Textures/buttons.png");

    title_text.setFont(font);
    title_text.setString("Welcome to Cleanse!");
    title_text.setPosition(900 / 2 - title_text.getLocalBounds().width / 2, 200);

    title_text2.setFont(font2);
    title_text2.setString("\n    No bloat, no ads, no data collection.\n"
                            "Just a program made for the purpose of\n"
                            "     safely cleaning all your system junk\n"
                            "                       with one click.");
    title_text2.setCharacterSize(16);
    title_text2.setPosition(900 / 2 - title_text2.getLocalBounds().width / 2, 260);

    button_sprite.setTexture(texture);
    button_sprite.setTextureRect(IntRect(211,0, 166, 65));
    button_sprite.setPosition(900 / 2 - button_sprite.getLocalBounds().width / 2, 400);
}

void Welcome_screen::update(RectangleShape& cursor, Enums& enums, File_handler& file_handler) {
    if (delay_clock.getElapsedTime().asSeconds() > 2) {
        if (opacity < 255) opacity = opacity + 0.9;
        if (opacity > 255) opacity = 255;
        if (delay_clock.getElapsedTime().asSeconds() > 3) {
            if (opacity2 < 160) opacity2 = opacity2 + 0.5;
            if (opacity2 > 160) opacity2 = 160;
            if (posY > 400) posY = posY - 0.5;
            if (posY < 400) posY = 400;
        }
    }
    title_text.setFillColor(Color(255, 255, 255, static_cast<Uint8>(opacity)));
    title_text2.setFillColor(Color(255, 255, 255, static_cast<Uint8>(opacity2)));
    if (cursor.getGlobalBounds().intersects(button_sprite.getGlobalBounds())) {
        button_sprite.setColor(Color(255, 255, 255, 255));
        if (Mouse::isButtonPressed(Mouse::Left)) {
            enums = Enums::QUICK_CLEAN;
            file_handler.save_welcome_screen(0);
        }
    }
    else
        button_sprite.setColor(Color(255, 255, 255, static_cast<Uint8>(opacity2)));
    button_sprite.setPosition(900 / 2 - button_sprite.getLocalBounds().width / 2, posY);
}

void Welcome_screen::draw(RenderWindow& window) {
    window.draw(title_text);
    window.draw(title_text2);
    window.draw(button_sprite);
}
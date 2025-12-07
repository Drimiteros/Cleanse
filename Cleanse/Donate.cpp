#include "Donate.h"

Donate::Donate() {
    font.loadFromFile("src/Fonts/AlteHaasGroteskBold.ttf");
    font2.loadFromFile("src/Fonts/AlteHaasGroteskRegular.ttf");
    
    title_text.setFont(font);
    title_text.setString("Support!");
    title_text.setPosition(210, 60);
    title_text.setCharacterSize(25);

    title2_text.setFont(font);
    title2_text.setString("Latest Donators");
    title2_text.setPosition(210, 190);
    title2_text.setCharacterSize(25);

    thank_you_text.setFont(font2);
    thank_you_text.setString("Thank you very much for using my little software! Please consider a small donation for my work!\n"
        "To me your donation indicates your appreciation for the software and the time spend making it.\n"
        "That gives me a huge dopamine boost and allows me to keep upgrading it!");
    thank_you_text.setPosition(210, 100);
    thank_you_text.setCharacterSize(15);
    thank_you_text.setFillColor(Color(255, 255, 255, 150));

    thank2_you_text.setFont(font2);
    thank2_you_text.setString("Thank you for your support!\n~Dimitris");
    thank2_you_text.setPosition(210, 535);
    thank2_you_text.setCharacterSize(18);
    thank2_you_text.setFillColor(Color(255, 255, 255, 180));

    donate_button_texture.loadFromFile("src/Textures/Donate.png");
    donate_button_texture.setSmooth(true);
    donate_button.setTexture(donate_button_texture);
    donate_button.setPosition(722, 530);
    donate_button.setScale(0.6, 0.6);
}

void Donate::update(RectangleShape& cursor) {
    if (!donators_loaded) cachedDonators = loadDonators();
    
    if (!assign_donator_info && cachedDonators.size() > 0) {
        for (int i = cachedDonators.size() - 1; i >= 0; --i) {
            donation_date_text.push_back(Text());
            donation_date_text.back().setFont(font2);
            donation_date_text.back().setString(cachedDonators[i].date);
            donation_date_text.back().setCharacterSize(15);
            donation_date_text.back().setFillColor(Color(255, 255, 255, 150));

            donator_name_text.push_back(Text());
            donator_name_text.back().setFont(font);
            donator_name_text.back().setString(cachedDonators[i].name);
            donator_name_text.back().setCharacterSize(20);
            donator_name_text.back().setFillColor(Color(200, 250, 255, 255));

            donation_amount_text.push_back(Text());
            donation_amount_text.back().setFont(font);
            donation_amount_text.back().setString(cachedDonators[i].amount + "$");
            donation_amount_text.back().setCharacterSize(20);
            donation_amount_text.back().setFillColor(Color(0, 255, 150));

            donation_message_text.push_back(Text());
            donation_message_text.back().setFont(font2);
            donation_message_text.back().setString("| \"" + cachedDonators[i].message + "\"");
            donation_message_text.back().setCharacterSize(17);
            donation_message_text.back().setFillColor(Color(255, 255, 255, 255));

            if (i <= cachedDonators.size() - 5 && cachedDonators.size() > 5) break;
        }
        assign_donator_info = true;
    }
    open_link(cursor);
}

void Donate::open_link(RectangleShape& cursor) {
    if (cursor.getGlobalBounds().intersects(donate_button.getGlobalBounds())) {
        donate_button.setColor(Color(255, 255, 255, 255));
        if (Mouse::isButtonPressed(Mouse::Left) && !open_url) {
            ShellExecuteW(nullptr, L"open", url.c_str(), nullptr, nullptr, SW_SHOWNORMAL);
            open_url = true;
        }
    }
    else
        donate_button.setColor(Color(255, 255, 255, 150));
    if (!cursor.getGlobalBounds().intersects(donate_button.getGlobalBounds()) && !Mouse::isButtonPressed(Mouse::Left))
        open_url = false;
}

void Donate::draw(RenderWindow& window) {
    window.draw(title_text);
    window.draw(title2_text);
    window.draw(thank_you_text);
    window.draw(thank2_you_text);
    window.draw(donate_button);

    for (int i = 0; i < donator_name_text.size(); ++i) {
        donation_date_text[i].setPosition(225, 242 + (i * 55));
        window.draw(donation_date_text[i]);
        donator_name_text[i].setPosition(225, 259 + (i * 55));
        window.draw(donator_name_text[i]);
        donation_amount_text[i].setPosition(donator_name_text[i].getPosition().x + donator_name_text[i].getLocalBounds().width + 10, 259 + (i * 55));
        window.draw(donation_amount_text[i]);
        donation_message_text[i].setPosition(donation_amount_text[i].getPosition().x + donation_amount_text[i].getLocalBounds().width + 10, 259 + (i * 55));
        window.draw(donation_message_text[i]);
    }
}
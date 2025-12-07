#include "Report_screen.h"

Report_screen::Report_screen() {
    font.loadFromFile("src/Fonts/AlteHaasGroteskBold.ttf");
    font2.loadFromFile("src/Fonts/AlteHaasGroteskRegular.ttf");

    title_text.setFont(font);
    title_text.setString("System Clean Report");
    title_text.setPosition(215, 60);
    title_text.setCharacterSize(25);

    total_junk_status_text.setFont(font2);
    total_junk_status_text.setString("Total Junk Removed");
    total_junk_status_text.setPosition(230, 165);
    total_junk_status_text.setCharacterSize(18);
    total_junk_status_text.setFillColor(Color(255, 255, 255, 150));
    total_junk_status_count_text.setFont(font);
    total_junk_status_count_text.setString("2.47 GB");
    total_junk_status_count_text.setPosition(250, 120);
    total_junk_status_count_text.setCharacterSize(35);
    total_junk_status_count_text.setFillColor(Color(0, 255, 150));
    total_time_status_text.setFont(font2);
    total_time_status_text.setString("Total Time Taken");
    total_time_status_text.setPosition(475, 165);
    total_time_status_text.setCharacterSize(18);
    total_time_status_text.setFillColor(Color(255, 255, 255, 150));
    total_time_status_count_text.setFont(font);
    total_time_status_count_text.setString("00:00:00");
    total_time_status_count_text.setPosition(475, 120);
    total_time_status_count_text.setCharacterSize(35);
    total_time_status_count_text.setFillColor(Color(150, 150, 255));
    issues_title_text.setFont(font2);
    issues_title_text.setString("Issues Found");
    issues_title_text.setPosition(720, 165);
    issues_title_text.setCharacterSize(18);
    issues_title_text.setFillColor(Color(255, 255, 255, 150));
    total_issues_count_text.setFont(font);
    total_issues_count_text.setString("20");
    total_issues_count_text.setPosition(750, 120);
    total_issues_count_text.setCharacterSize(35);
    total_issues_count_text.setFillColor(Color(225, 150, 150));

    view_bounds.setFillColor(Color(255, 255, 255, 100));
    view_bounds.setSize(Vector2f(665, 303));
    view_bounds.setPosition(210, 220);
}

void Report_screen::update(RectangleShape& cursor) {
    total_junk_status_count_text.setPosition(315 - total_junk_status_count_text.getLocalBounds().width / 2, 120);
    total_time_status_count_text.setPosition(540 - total_time_status_count_text.getLocalBounds().width / 2, 120);
    total_issues_count_text.setPosition(770 - total_issues_count_text.getLocalBounds().width / 2, 120);
}

void Report_screen::draw(RenderWindow& window, int scroll_value) {
    window.draw(title_text);
    window.draw(total_junk_status_text);
    window.draw(total_time_status_text);
    window.draw(total_junk_status_count_text);
    window.draw(total_time_status_count_text);
    window.draw(total_issues_count_text);
    window.draw(issues_title_text);
    //window.draw(view_bounds);
    for (int i = 0; i < log_text.size(); ++i) {
        log_text_title[i].setFont(font2);
        log_text_title[i].setCharacterSize(15);
        log_text_title[i].setPosition(220, 223 + (i * 30 + scroll_value));
        log_text[i].setFont(font2);
        log_text[i].setCharacterSize(15);
        log_text[i].setPosition(log_text_title[i].getPosition().x + log_text_title[i].getLocalBounds().width + 10, 223 + (i * 30 + scroll_value));
        if (log_text[i].getGlobalBounds().intersects(view_bounds.getGlobalBounds())) {
            window.draw(log_text_title[i]);
            window.draw(log_text[i]);
        }
    }
}
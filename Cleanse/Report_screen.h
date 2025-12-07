#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

class Report_screen {
private:
    Font font;
    Font font2;

    Text title_text;
    Text total_junk_status_text;
    Text total_time_status_text;
    Text issues_title_text;

    RectangleShape view_bounds;

public:
    int issue_count = 0;

    Text total_junk_status_count_text;
    Text total_time_status_count_text;
    Text total_issues_count_text;
    vector<Text> log_text;
    vector<Text> log_text_title;

    Report_screen();
    void update(RectangleShape& cursor);
    void draw(RenderWindow& window, int scroll_value);
};


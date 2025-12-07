#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <Windows.h>
#include <cpr/cpr.h>
#include "json.hpp"

using namespace std;
using namespace sf;

class Donate{
private:
    Font font;
    Font font2;

    Text title_text;
    Text title2_text;
    Text thank_you_text;
    Text thank2_you_text;
    vector<Text> donation_date_text;
    vector<Text> donator_name_text;
    vector<Text> donation_amount_text;
    vector<Text> donation_message_text;

    Texture donate_button_texture;
    Sprite donate_button;

    bool open_url = false;
    bool donators_loaded = false;
    bool assign_donator_info = false;

    wstring url = L"https://cleanse.infinityfreeapp.com/donate.php";

    struct Donator {
        string name;
        string date;
        string message;
        string amount;
    };

    vector<Donator> cachedDonators;
    vector<Donator> loadDonators() {
        if (donators_loaded)
            return {};

        vector<Donator> results;

        auto response = cpr::Get(
            cpr::Url{ "https://Drimiteros.github.io/cleanse-data/donators.json" },
            cpr::VerifySsl(false),
            cpr::Header{ {"User-Agent", "Mozilla/5.0"} }
        );

        //cout << "Status: " << response.status_code << "\n";
        if (response.status_code != 200) {
            cerr << "Failed to fetch donators. Status: " << response.status_code << "\n";
            return results;
        }

        nlohmann::json json;
        try {
            json = nlohmann::json::parse(response.text);
        }
        catch (std::exception& e) {
            cerr << "JSON parse error: " << e.what() << "\n";
            return results;
        }

        if (!json.contains("success") || !json["success"].get<bool>()) {
            cerr << "API returned failure.\n";
            return results;
        }

        auto parseDonationAmount = [](const nlohmann::json& v)->double {
            if (v.is_number()) {
                return v.get<double>();
            }
            if (v.is_string()) {
                std::string s = v.get<std::string>();
                // remove common currency symbols and grouping commas
                s.erase(std::remove_if(s.begin(), s.end(),
                    [](char c) { return c == '$' || c == '€' || c == ',' || std::isspace((unsigned char)c); }),
                    s.end());
                try {
                    return std::stod(s);
                }
                catch (...) {
                    return 0.0;
                }
            }
            // null/other -> default
            return 0.0;
        };

        // usage inside loop
        for (const auto& item : json["donators"]) {
            Donator d;
            d.name = item.value("name", "");
            d.amount = item.value("donation_amount", "");
            d.date = item.value("donation_date", "");
            d.message = item.value("message", "");
            results.push_back(d);
        }

        donators_loaded = true;
        return results;
    }

public:
    Donate();
    void update(RectangleShape& cursor);
    void open_link(RectangleShape& cursor);
    void draw(RenderWindow& window);
};


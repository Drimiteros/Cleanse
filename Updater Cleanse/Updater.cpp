#include <iostream>
#include <SFML/Graphics.hpp>
#include <cpr/cpr.h>
#include <filesystem>
#include <chrono>
#include <windows.h>
#include <shlobj.h>
#include <comdef.h>
#include <thread>

using namespace std;
using namespace sf;
using namespace cpr;
namespace fs = std::filesystem;

atomic<bool>stopFlag = false;
atomic<int>app_progress = 0;
atomic<float>app_size = 0;
string app_version = "searching... ";

string version_url = "https://raw.github.com/Drimiteros/cleanse-data/main/version.txt";
string update_url = "https://raw.github.com/Drimiteros/cleanse-data/main/Cleanse%20Live%20Version%20Setup.exe";
string files_to_remove[] = {
	"src",
	"Cleanse.exe",
    "Cleanse Scheduler.exe",
    "unins000.exe"
};

void remove_old_files() {
    for (int i = 0; i < 4; i++) {
        try { fs::remove_all(files_to_remove[i]); }
        catch (fs::filesystem_error err) {}
    }
    system("cls");
}

void get_update_info() {
    // Get the version name of the updated file
    auto head_response2 = cpr::Get(cpr::Url{ version_url });
    if (head_response2.status_code == 200)
        app_version = string("v") + head_response2.text.c_str();

	// Get the size of the updated file
    auto head_response = cpr::Head(cpr::Url{ update_url });
    if (head_response.status_code == 200) {
        auto content_length = head_response.header["Content-Length"];
        app_size = stof(content_length) / (1024 * 1024);
    }
}

void start_update() {
    // Open the output file in binary mode
    string output_file = "Cleanse Live Version Setup.exe";
    ofstream out(output_file, ios::binary);
    if (!out.is_open()) {
        cerr << "Failed to open file: " << output_file << endl;
    }

    // Define the write callback
    auto write_callback = [](const string_view& data, intptr_t userdata) {
        ofstream* out_stream = reinterpret_cast<ofstream*>(userdata);
        out_stream->write(data.data(), data.size());
        return true;
    };

    // Define the progress callback
    static char download_bar[100] = {};
    auto progress_callback = [](cpr_off_t downloadTotal, cpr_off_t downloadNow, cpr_off_t, cpr_off_t, intptr_t) {
        if (downloadTotal > 0) {
            int percent = static_cast<int>((double)downloadNow / downloadTotal * 100);
            int bar_width = 50; // Width of the progress bar (adjust as needed)
            int filled = bar_width * percent / 100;

            app_progress = percent;

            download_bar[0] = '[';
            for (int i = 1; i < bar_width - 1; i++) {
                download_bar[i] = (i < filled) ? '=' : ' ';
            }
            download_bar[bar_width - 1] = ']';
            download_bar[bar_width] = '\0'; // Null-terminate the string
        }
        return true;
    };

    // Perform the download with WriteCallback and ProgressCallback
    Response response = Download(
        WriteCallback{ write_callback, reinterpret_cast<intptr_t>(&out) },  // Passing the ofstream pointer
        Url{ update_url },
        ProgressCallback{ progress_callback }
    );

    out.close();
}

void install() {
    this_thread::sleep_for(chrono::seconds(3));

    char buffer[MAX_PATH];
    GetModuleFileNameA(NULL, buffer, MAX_PATH);
    fs::path appDir = fs::path(buffer).parent_path().wstring();
    wstring parameters = L"/VERYSILENT /NORESTART /DIR=\"" + appDir.wstring() + L"\"";

    if (fs::exists("Cleanse Live Version Setup.exe")) {
        (ShellExecuteW(NULL, L"runas", L"Cleanse Live Version Setup.exe", parameters.c_str(), NULL, SW_SHOW));
        stopFlag.store(true);
    }
    else
        stopFlag.store(true);
}

void update() {
    while (!stopFlag.load()) {
        remove_old_files();
        get_update_info();
        start_update();
        install();
    }
}

void render() {
    RenderWindow window(VideoMode(500, 300), "Cleanse Updater", Style::Close);
    Event event;

    sf::Font font;
    font.loadFromFile("src_updater/Fonts/AlteHaasGroteskBold.ttf");
    sf::Font font2;
    font2.loadFromFile("src_updater/Fonts/AlteHaasGroteskRegular.ttf");
    Text title_text;
    title_text.setFont(font);
    title_text.setFillColor(Color::White);
    title_text.setCharacterSize(25);
    title_text.setString("Downloading Cleanse");
    title_text.setPosition(70, 10);
    Text app_info_text;
    app_info_text.setFont(font2);
    app_info_text.setFillColor(Color::White);
    app_info_text.setCharacterSize(16);
    app_info_text.setString("Downloading Cleanse");
    app_info_text.setPosition(70, 38);
    Text progress_text;
    progress_text.setFont(font);
    progress_text.setFillColor(Color::White);
    progress_text.setCharacterSize(20);

    RectangleShape progress_bar;
    progress_bar.setPosition(10, 270);
    RectangleShape progress_bar_back;
    progress_bar_back.setFillColor(Color(30, 30, 30));
    progress_bar_back.setPosition(10, 270);
    progress_bar_back.setSize(Vector2f(100 * 4.8, 20));

    Texture update_texture;
    update_texture.loadFromFile("src_updater/Textures/update.png");
    Sprite update_sprite;
    update_sprite.setTexture(update_texture);
    update_sprite.setPosition(5, 10);
    update_sprite.setScale(0.15, 0.15);

    RectangleShape banner;
    banner.setSize(Vector2f(500, 70));
    banner.setFillColor(Color(50, 50, 50));

    Texture logo_texture;
    logo_texture.loadFromFile("src_updater/Textures/logo.png");
    logo_texture.setSmooth(true);
    Sprite logo_sprite;
    logo_sprite.setTexture(logo_texture);
    logo_sprite.setScale(0.3, 0.3);
    logo_sprite.setPosition(500 / 2 - logo_sprite.getLocalBounds().width / 2 * logo_sprite.getScale().x, 300 / 2 - logo_sprite.getLocalBounds().height / 2 * logo_sprite.getScale().y);

    while (window.isOpen()) {
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();
                stopFlag.store(true);
            }
        }

        window.clear(Color(60, 60, 60));

        window.draw(banner);
        progress_text.setString("Downloading Update: " + to_string(app_progress) + "%");
        progress_text.setPosition(500 / 2 - progress_text.getLocalBounds().width / 2, 230);
        window.draw(progress_text);
        if (app_size > 0)
            app_info_text.setString(string(app_version).substr(0, app_version.length() - 1) + " | " + to_string(app_size).substr(0, 5) + " MB");
        else
            app_info_text.setString("Searching...");
        window.draw(app_info_text);
        window.draw(title_text);
        progress_bar.setSize(Vector2f(app_progress * 4.8, 20));
        progress_bar.setFillColor(Color(255 - app_progress, app_progress + 100, 150));
        window.draw(progress_bar_back);
        window.draw(progress_bar);
        window.draw(update_sprite);
        window.draw(logo_sprite);

        if (stopFlag.load()) {
            window.close();
        }
        cout << stopFlag.load() << endl;

        window.display();
    }
}

int main() {
    thread([] {update(); }).detach();
    render();
}
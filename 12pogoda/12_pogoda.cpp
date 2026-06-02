#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <unistd.h>
#include <curl/curl.h>

class CurlSession {
public:
    CurlSession() {
        curl_global_init(CURL_GLOBAL_ALL);
        curl_ = curl_easy_init();
        if (!curl_) {
            throw std::runtime_error("Nie udało się zainicjalizować libcurl.");
        }
    }

    ~CurlSession() {
        if (curl_) {
            curl_easy_cleanup(curl_);
        }
        curl_global_cleanup();
    }

    
    CurlSession(const CurlSession&) = delete;
    CurlSession& operator=(const CurlSession&) = delete;

    std::string fetch(const std::string& url) {
        if (!curl_) return "";

        std::string response_buffer;
        
        curl_easy_setopt(curl_, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl_, CURLOPT_SSL_VERIFYPEER, 1L); 
        curl_easy_setopt(curl_, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl_, CURLOPT_WRITEDATA, &response_buffer);

        CURLcode res = curl_easy_perform(curl_);
        if (res != CURLE_OK) {
            std::cerr << "Błąd curl_easy_perform(): " << curl_easy_strerror(res) << "\n";
            return "";
        }

        return response_buffer;
    }

private:
    CURL* curl_ = nullptr;

    static size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp) {
        size_t total_size = size * nmemb;
        std::string* buffer = static_cast<std::string*>(userp);
        buffer->append(static_cast<char*>(contents), total_size);
        return total_size;
    }
};

std::vector<std::string> splitLines(const std::string& str) {
    std::vector<std::string> lines;
    std::stringstream ss(str);
    std::string line;
    while (std::getline(ss, line)) {
        if (!line.empty() && line.back() == '\r') {
            line.pop_back();
        }
        if (!line.empty()) {
            lines.push_back(line);
        }
    }
    return lines;
}

std::vector<std::string> splitCsvRow(const std::string& row) {
    std::vector<std::string> cells;
    std::stringstream ss(row);
    std::string cell;
    while (std::getline(ss, cell, ',')) {
        cells.push_back(cell);
    }
    return cells;
}

void printStationList(const std::string& csv_data) {
    auto lines = splitLines(csv_data);
    if (lines.empty()) return;

    for (size_t i = 1; i < lines.size(); ++i) { 
        auto cells = splitCsvRow(lines[i]);
        if (cells.size() >= 2) {
            std::cout << cells[0] << "," << cells[1] << "\n";
        }
    }
}
void printSpecificParam(const std::string& csv_data, const std::string& param_name) {
    auto lines = splitLines(csv_data);
    if (lines.size() < 2) {
        std::cerr << "Brak danych lub błędny format odpowiedzi.\n";
        return;
    }

    auto headers = splitCsvRow(lines[0]);
    auto values = splitCsvRow(lines[1]);

    int target_idx = -1;
    for (size_t i = 0; i < headers.size(); ++i) {
        if (headers[i] == param_name) {
            target_idx = static_cast<int>(i);
            break;
        }
    }

    if (target_idx != -1 && target_idx < static_cast<int>(values.size())) {
        std::cout << values[target_idx] << "\n";
    } else {
        std::cerr << "Parametr '" << param_name << "' nie został znaleziony.\n";
    }
}

void printHelp() {
    std::cout << "imgw v1.0 - weather data client\n"
              << "usage: ./imgw [-t type] [-l] id\n"
              << "options:\n"
              << "  -l  list all station IDs\n"
              << "  -t  data type\n"
              << "  -h  display help\n";
}

int main(int argc, char* argv[]) {
    bool list_mode = false;
    std::string target_param = "";
    int opt;

    while ((opt = getopt(argc, argv, "lt:h")) != -1) {
        switch (opt) {
            case 'l':
                list_mode = true;
                break;
            case 't':
                target_param = optarg;
                break;
            case 'h':
            default:
                printHelp();
                return 0;
        }
    }

    try {
        CurlSession session;

        if (list_mode) {
            std::string url = "https://danepubliczne.imgw.pl/api/data/synop/format/csv";
            std::string raw_data = session.fetch(url);
            if (!raw_data.empty()) {
                printStationList(raw_data);
            }
            return 0;
        }

        if (optind >= argc) {
            std::cerr << "Błąd: Nie podano ID stacji.\n";
            printHelp();
            return 1;
        }

        std::string station_id = argv[optind];
        std::string url = "https://danepubliczne.imgw.pl/api/data/synop/id/" + station_id + "/format/csv";
        std::string raw_data = session.fetch(url);

        if (raw_data.empty()) {
            std::cerr << "Nie udało się pobrać danych dla stacji: " << station_id << "\n";
            return 1;
        }

        if (!target_param.empty()) {
            printSpecificParam(raw_data, target_param);
        } else {
            std::cout << raw_data;
        }

    } catch (const std::exception& e) {
        std::cerr << "Wystąpił krytyczny wyjątek: " << e.what() << "\n";
        return 1;
    }

    return 0;
}

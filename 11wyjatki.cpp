#include <iostream>
#include <string>
#include <stdexcept>
#include <algorithm>
#include <cctype>
#include <tuple>
#include <chrono>

std::tuple<int, int, int> getCurrentDate() {
    const auto now = std::chrono::system_clock::now();
    std::chrono::year_month_day ymd = std::chrono::floor<std::chrono::days>(now);
    return std::make_tuple(int(ymd.year()), unsigned(ymd.month()), unsigned(ymd.day()));
}

std::tuple<int, int, int> parseDate(const std::string &date) {
    int year = std::stoi(date);
    int month = std::stoi(date.substr(5, 2));
    int day = std::stoi(date.substr(8, 2));
    return std::make_tuple(year, month, day);
}

bool isLeapYear(int year) {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

int daysInMonth(int month, int year) {
    switch (month) {
        case 1: case 3: case 5: case 7: case 8: case 10: case 12: return 31;
        case 4: case 6: case 9: case 11: return 30;
        case 2: return isLeapYear(year) ? 29 : 28;
        default: return 0;
    }
}

class Company {
public:
    std::string name;
    std::string nip;
    std::string date;
    std::string mail;

    Company(const std::string &_name,
            const std::string &_nip,
            const std::string &_date,
            const std::string &_mail) {

        if (_name.length() < 3 || _name.length() > 100)
            throw std::length_error("Nazwa firmy musi miec od 3 do 100 znakow (podano: " + std::to_string(_name.length()) + ")");

        if (_nip.length() != 10)
            throw std::length_error("NIP musi skladac sie z dokladnie 10 cyfr (podano: " + std::to_string(_nip.length()) + ")");

        for (char c : _nip)
            if (!std::isdigit(c))
                throw std::invalid_argument("NIP moze zawierac tylko cyfry (niedozwolony znak: '" + std::string(1, c) + "')");

        const int weights[] = {6, 5, 7, 2, 3, 4, 5, 6, 7};
        int sum = 0;
        for (int i = 0; i < 9; ++i)
            sum += (_nip[i] - '0') * weights[i];
        int checkDigit = sum % 11;
        if (checkDigit == 10)
            throw std::domain_error("Niepoprawna cyfra kontrolna NIP (suma mod 11 = 10, brak poprawnego NIP)");
        if (checkDigit != (_nip[9] - '0'))
            throw std::domain_error("Niepoprawna cyfra kontrolna NIP (oczekiwano: " + std::to_string(checkDigit) + ", podano: " + std::string(1, _nip[9]) + ")");

        if (_date.length() != 10)
            throw std::length_error("Data musi miec dokladnie 10 znakow w formacie YYYY-MM-DD (podano: " + std::to_string(_date.length()) + ")");

        for (int i : {0,1,2,3,5,6,8,9})
            if (!std::isdigit(_date[i]))
                throw std::invalid_argument("Niepoprawny format daty: oczekiwano cyfry na pozycji " + std::to_string(i));
        if (_date[4] != '-' || _date[7] != '-')
            throw std::invalid_argument("Niepoprawny format daty: oczekiwano '-' (format: YYYY-MM-DD)");

        auto [parsedYear, parsedMonth, parsedDay] = parseDate(_date);
        auto [curYear, curMonth, curDay] = getCurrentDate();

        if (parsedYear < 1900 || parsedYear > curYear)
            throw std::domain_error("Rok musi byc z przedzialu [1900, " + std::to_string(curYear) + "] (podano: " + std::to_string(parsedYear) + ")");

        int maxMonth = (parsedYear == curYear) ? curMonth : 12;
        if (parsedMonth < 1 || parsedMonth > maxMonth)
            throw std::domain_error("Miesiac musi byc z przedzialu [1, " + std::to_string(maxMonth) + "] (podano: " + std::to_string(parsedMonth) + ")");

        int maxDay = (parsedYear == curYear && parsedMonth == curMonth) ? curDay : daysInMonth(parsedMonth, parsedYear);
        if (parsedDay < 1 || parsedDay > maxDay)
            throw std::domain_error("Dzien musi byc z przedzialu [1, " + std::to_string(maxDay) + "] (podano: " + std::to_string(parsedDay) + ")");

        if (_mail.find('@') == std::string::npos)
            throw std::invalid_argument("Adres e-mail musi zawierac znak '@' (podano: " + _mail + ")");

        name = _name;
        nip  = _nip;
        date = _date;
        mail = _mail;
    }
};

int main() {
    const std::string testName = "Januszex Sp. z.o.o";
    const std::string testNip  = "5261040828"; 
    const std::string testDate = "2024-03-15";
    const std::string testMail = "januszex@gmail.com";

    try {
        Company c(testName, testNip, testDate, testMail);
        std::cout << "Obiekt Company utworzony poprawnie:\n"
                  << "  Nazwa: " << c.name << "\n"
                  << "  NIP:   " << c.nip  << "\n"
                  << "  Data:  " << c.date << "\n"
                  << "  Mail:  " << c.mail << "\n";
    } catch (const std::exception &e) {
        std::cerr << "Blad: " << e.what() << "\n";
    }

    return 0;
}
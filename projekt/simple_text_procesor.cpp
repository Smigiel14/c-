#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <vector>
#include <regex>

std::string filename = "tekst.txt";

void menu(){
  std::cout << "\n============ MENU ============\n";
  std::cout << "(1) zliczanie znaków, słów i wierszy\n";
  std::cout << "(2) zamiana małych liter na duże\n";
  std::cout << "(3) zamiana dużych liter na małe\n";
  std::cout << "(4) kapitalizacja wszystkich wyrazów\n";
  std::cout << "(5) usuwanie wszystkich cyfr\n";
  std::cout << "(6) zamiana tabulatorów na cztery spacje\n";
  std::cout << "(7) zamiana czterech spacji na tabulatory\n";
  std::cout << "(8) zamiana podciągu na inny podciąg (w tym pusty)\n";
  std::cout << "(9) wyszukiwanie wystąpień z obsługą wyrażeń regularnych (std::regex)\n";
  std::cout << "(10) usuwanie spacji z początku i końcu wiersza\n";
  std::cout << "(11) usuwanie pustych linii.\n";
  std::cout << "(12) wyjscie z programu.\n";
  std::cout << "Twój wybór: ";
}


void zliczanie(std::string filename, int iteracja){
  std::ifstream plik(filename);
  if(!plik.is_open()){
    std::cout << "nie mozna otworzyc pliku\n";
    return;
  }

  size_t licznik_znak = 0;
  size_t licznik_slowo = 0;
  size_t licznik_wiersz = 0;
  char znak;
  char ostatni_znak = '\n';
  bool w_slowie = false;

  while(plik.get(znak)) {
    licznik_znak++;
    ostatni_znak = znak;

    if (znak == '\n'){
      licznik_wiersz++;
    }

    if (znak == 32 || (znak >= 9 && znak <= 13)){
      w_slowie = false;
    }else{
    if (!w_slowie){
      licznik_slowo++;
      w_slowie = true;
      }
    }
  }
  plik.close();

  std::string zapis = "modifier-" + std::to_string(iteracja) + ".txt";

  std::ofstream plik2(zapis);
    if(!plik2.is_open()){
    std::cout << "nie mozna zapisac pliku\n";
    return;
  }
  plik2.close();

  std::cout << "znaki: " << licznik_znak << '\n';
  std::cout << "slowa: " << licznik_slowo << '\n';
  std::cout << "wiersze: " << licznik_wiersz << '\n';
}

void male_na_duze(std::string filename, int iteracja){
  std::ifstream plik(filename);
  if(!plik.is_open()){
    std::cout << "nie mozna otworzyc pliku\n";
    return;
  }
  char znak;
  std::string zawartosc = "";

  while (plik.get(znak)){
    if (znak >= 'a' && znak <= 'z') {
            znak = znak - 32;
        }
        zawartosc += znak;
  }
  plik.close();

  std::string zapis = "modifier-" + std::to_string(iteracja) + ".txt";


  std::ofstream plik2(zapis);
    if(!plik2.is_open()){
    std::cout << "nie mozna zapisac pliku\n";
    return;
  }
  plik2 << zawartosc;
  plik2.close();
}


void duze_na_male(std::string filename, int iteracja){
    std::ifstream plik(filename);
  if(!plik.is_open()){
    std::cout << "nie mozna otworzyc pliku\n";
    return;
  }
  char znak;
  std::string zawartosc = "";

  while (plik.get(znak)){
    if (znak >= 'A' && znak <= 'Z') {
            znak = znak + 32;
        }
        zawartosc += znak;
  }
  plik.close();

  std::string zapis = "modifier-" + std::to_string(iteracja) + ".txt";


  std::ofstream plik2(zapis);
    if(!plik2.is_open()){
    std::cout << "nie mozna zapisac pliku\n";
    return;
  }
  plik2 << zawartosc;
  plik2.close();
}

void kapitalizacja(std::string filename, int iteracja) {
    std::ifstream plik(filename);
    if (!plik.is_open()) {
        std::cout << "nie mozna otworzyc pliku\n";
        return;
    }

    char znak;
    std::string zawartosc = "";
    bool w_slowie = false;

    while (plik.get(znak)) {
        if (znak == 32 || (znak >= 9 && znak <= 13)) {
            w_slowie = false;
        }else{
            if (!w_slowie) {
                if (znak >= 'a' && znak <= 'z') {
                    znak = znak - 32; 
                }
                w_slowie = true;
            }else {
                if (znak >= 'A' && znak <= 'Z') {
                    znak = znak + 32; 
                }
            }
        }
        zawartosc += znak;
    }
    plik.close();
    std::string zapis = "modifier-" + std::to_string(iteracja) + ".txt";
    std::ofstream plik2(zapis);
    if (!plik2.is_open()) {
        std::cout << "nie mozna zapisac pliku\n";
        return;
    }
    plik2 << zawartosc;
    plik2.close();
}

void usun_cyfry(std::string filename, int iteracja) {
    std::ifstream plik(filename);
    if (!plik.is_open()) {
        std::cout << "nie mozna otworzyc pliku\n";
        return;
    }

    char znak;
    std::string zawartosc = "";
    while (plik.get(znak)) {
        if (!(znak >= '0' && znak <= '9')) {
            zawartosc += znak;
        }
    }
    plik.close();

    std::string zapis = "modifier-" + std::to_string(iteracja) + ".txt";
    std::ofstream plik2(zapis);
    if (!plik2.is_open()) {
        std::cout << "nie mozna zapisac pliku\n";
        return;
    }
    plik2 << zawartosc;
    plik2.close();
}

void tabulatory_na_spacje(std::string filename, int iteracja) {
    std::ifstream plik(filename);
    if (!plik.is_open()) {
        std::cout << "nie mozna otworzyc pliku\n";
        return;
    }

    char znak;
    std::string zawartosc = "";
    while (plik.get(znak)) {
        if (znak == '\t') {
            zawartosc += "    "; 
        } else {
            zawartosc += znak;  
        }
    }
    plik.close();

    std::string zapis = "modifier-" + std::to_string(iteracja) + ".txt";
    std::ofstream plik2(zapis);
    if (!plik2.is_open()) {
        std::cout << "nie mozna zapisac pliku\n";
        return;
    }
    plik2 << zawartosc;
    plik2.close();
}


void spacje_na_tabulatory(std::string filename, int iteracja) {
    std::ifstream plik(filename);
    if (!plik.is_open()) {
        std::cout << "nie mozna otworzyc pliku\n";
        return;
    }

    char znak;
    std::string zawartosc = "";
    int licznik_spacji = 0;

    while (plik.get(znak)) {
        if (znak == ' ') {
            licznik_spacji++;
            if (licznik_spacji == 4) {
                zawartosc += '\t';   
                licznik_spacji = 0;   
            }
        } else {
            while (licznik_spacji > 0) {
                zawartosc += ' ';
                licznik_spacji--;
            }
            zawartosc += znak; 
        }
    }

    while (licznik_spacji > 0) {
        zawartosc += ' ';
        licznik_spacji--;
    }

    plik.close();

    std::string zapis = "modifier-" + std::to_string(iteracja) + ".txt";
    std::ofstream plik2(zapis);
    if (!plik2.is_open()) {
        std::cout << "nie mozna zapisac pliku\n";
        return;
    }
    plik2 << zawartosc;
    plik2.close();
}

void zamiana_podciagu(std::string filename, int iteracja) {
    std::ifstream plik(filename);
    if (!plik.is_open()) {
        std::cout << "nie mozna otworzyc pliku\n";
        return;
    }

    std::string szukany, nowy;
    std::cout << "podaj podciag do znalezienia: ";
    std::getline(std::cin, szukany);
    std::cout << "podaj nowy podciag: ";
    std::getline(std::cin, nowy);

    if (szukany.empty()) {
        std::cout << "szukany podciag nie moze byc pusty\n";
        plik.close();
        return;
    }

    std::string zawartosc = "";
    std::string linia;

    while (std::getline(plik, linia)) {
        size_t pozycja = linia.find(szukany);
        while (pozycja != std::string::npos) {
            linia.replace(pozycja, szukany.length(), nowy);
            pozycja = linia.find(szukany, pozycja + nowy.length());
        }
        
        zawartosc += linia + "\n";
    }
    plik.close();

    if (!zawartosc.empty()) {
        zawartosc.pop_back();
    }
    std::string zapis = "modifier-" + std::to_string(iteracja) + ".txt";
    std::ofstream plik2(zapis);
    if (!plik2.is_open()) {
        std::cout << "nie mozna zapisac pliku\n";
        return;
    }
    plik2 << zawartosc;
    plik2.close();
}

void wyszukiwanie_regex(std::string filename, int iteracja) {
    std::ifstream plik(filename);
    if (!plik.is_open()) {
        std::cout << "nie mozna otworzyc pliku\n";
        return;
    }

    std::string wzorzec_string;
    std::cout << "podaj wyrazenie regularne: ";
    std::getline(std::cin, wzorzec_string);

    if (wzorzec_string.empty()) {
        std::cout << "Wzorzec nie moze byc pusty!\n";
        plik.close();
        return;
    }
    std::regex wzorzec;
    try {
        wzorzec = std::regex(wzorzec_string);
    } catch (const std::regex_error) {
        std::cout << "niepoprawna skladnia wyrazenia\n";
        plik.close();
        return;
    }

    std::string zawartosc_wyjsciowa = "";
    std::string linia;
    int numer_linii = 1;
    int znaleziono_wierszy = 0;

    std::cout << "\nREGEX\n";

    while (std::getline(plik, linia)) {
        if (std::regex_search(linia, wzorzec)) {
            std::cout << "[Linia " << numer_linii << "]: " << linia << "\n";
            zawartosc_wyjsciowa += linia + "\n";
            znaleziono_wierszy++;
        }
        numer_linii++;
    }
    plik.close();

    if (znaleziono_wierszy == 0) {
        std::cout << "nie znaleziono zadnych dopasowan.\n";
    }

    if (!zawartosc_wyjsciowa.empty()) {
        zawartosc_wyjsciowa.pop_back();
    }

    std::string zapis = "modifier-" + std::to_string(iteracja) + ".txt";
    std::ofstream plik2(zapis);
    if (!plik2.is_open()) {
        std::cout << "nie mozna zapisac pliku\n";
        return;
    }
    plik2 << zawartosc_wyjsciowa;
    plik2.close();
}

void usun_spacje_krawedzi(std::string filename, int iteracja) {
    std::ifstream plik(filename);
    if (!plik.is_open()) {
        std::cout << "nie mozna otworzyc pliku\n";
        return;
    }

    std::string zawartosc = "";
    std::string linia;
    std::string biale_znaki = " \t";

    while (std::getline(plik, linia)) {
        size_t poczatek = linia.find_first_not_of(biale_znaki);
        size_t koniec = linia.find_last_not_of(biale_znaki);

        if (poczatek != std::string::npos && koniec != std::string::npos) {
            linia = linia.substr(poczatek, koniec - poczatek + 1);
            zawartosc += linia + "\n";
        } else {
            zawartosc += "\n";
        }
    }
    plik.close();

    if (!zawartosc.empty()) {
        zawartosc.pop_back();
    }

    std::string zapis = "modifier-" + std::to_string(iteracja) + ".txt";
    std::ofstream plik2(zapis);
    if (!plik2.is_open()) {
        std::cout << "nie mozna zapisac pliku\n";
        return;
    }
    plik2 << zawartosc;
    plik2.close();
}


void usun_puste_linie(std::string filename, int iteracja) {
    std::ifstream plik(filename);
    if (!plik.is_open()) {
        std::cout << "nie mozna otworzyc pliku\n";
        return;
    }

    std::string zawartosc = "";
    std::string linia;

    while (std::getline(plik, linia)) {
        if (!linia.empty()) {
            zawartosc += linia + "\n";
        }
    }
    plik.close();

    if (!zawartosc.empty()) {
        zawartosc.pop_back();
    }

    std::string zapis = "modifier-" + std::to_string(iteracja) + ".txt";
    std::ofstream plik2(zapis);
    if (!plik2.is_open()) {
        std::cout << "nie mozna zapisac pliku\n";
        return;
    }
    plik2 << zawartosc;
    plik2.close();
}


int main(){
int option;
std::string option_string;
bool running = true;
int licznik_iteracji = 1;

     while (running)
     {
        menu();
        getline(std::cin, option_string);

        try{
            option = stoi(option_string);
            if (option < 1 || option > 13){
                std::cout << " Nalezy wybrac opcje w zakresie 1-13" << std::endl;
                continue;
            }
        } catch (...){
            std::cout << " Nalezy wybrac opcje w zakresie 1-13" << std::endl;
            continue;
        }
        std::cout << option << "\n";
        switch (option){

            case 1:
                zliczanie(filename, licznik_iteracji);
                licznik_iteracji++;
                break;

            case 2:
                male_na_duze(filename, licznik_iteracji);
                licznik_iteracji++;
                break;

            case 3:
                duze_na_male(filename, licznik_iteracji);
                licznik_iteracji++;
                break;

            case 4:
                kapitalizacja(filename, licznik_iteracji);
                licznik_iteracji++;
                break;

            case 5:
                usun_cyfry(filename, licznik_iteracji);
                licznik_iteracji++;
                break;
            
            case 6:
                tabulatory_na_spacje(filename, licznik_iteracji);
                licznik_iteracji++;
                break;
            
            case 7:
                spacje_na_tabulatory(filename, licznik_iteracji);
                licznik_iteracji++;
                break;
            
            case 8:
                zamiana_podciagu(filename, licznik_iteracji);
                licznik_iteracji++;
                break;
            
            case 9:
                wyszukiwanie_regex(filename, licznik_iteracji);
                licznik_iteracji++;
                break;
            
            case 10:
                usun_spacje_krawedzi(filename, licznik_iteracji);
                licznik_iteracji++;
                break;
            
            case 11:
                usun_puste_linie(filename, licznik_iteracji);
                licznik_iteracji++;
                break;

            case 12:
                running = false;
                break;
        }
     }
return 0;
}

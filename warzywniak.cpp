#include <iostream>
#include <string>
#include <fstream>
#include <vector>

struct Product {
    std::string object;
    unsigned int price;
    unsigned int quantity; 
};

void Load(std::vector<Product> &p, const std::string &filename) {
    std::ifstream file(filename);
    Product temp;

    while (file >> temp.object >> temp.price >> temp.quantity) {
        p.push_back(temp);
    }

    file.close();
}

void Save(std::vector<Product> &p, const std::string &filename) { 
    std::ofstream file(filename);
    for (size_t i = 0; i < p.size(); i++) {
        file << p[i].object << std::endl;
        file << p[i].price << std::endl;
        file << p[i].quantity << std::endl;
    }
    file.close();

}

void Menu()
{
    std::cout << "\n============ Magazyn ============" << std::endl;
    std::cout << "(1)  Wyswietl litse produktów" << std::endl;
    std::cout << "(2)  Dodaj produkt" << std::endl;
    std::cout << "(3)  Usuń produkt" << std::endl;
    std::cout << "(4)  zmien ilosc produktu " << std::endl;
    std::cout << "(5)  Wyszukaj produkt " << std::endl;
    std::cout << "(6)  Zamknięcie programu " << std::endl;
    std::cout << "============================================" << std::endl;
    std::cout << "Twój wybór: ";
}

void const showAll(const std::vector<Product> &p) {

    std::cout << " Aktualna lista produktów " << std::endl;
    
    for (size_t i = 0; i< p.size(); i++)
    {
        std::cout << i+1 << ". " << p[i].object << ", " << p[i].price/100 << " zl " << p[i].price%100 << " gr" << ", " << "ilość " << p[i].quantity << std::endl;
        std::cout << "----------------------------------------------------------\n";
        
    }
}


void Add(std::vector<Product> &p) {
    std::string object_add;
    std::string str_price;
    std::string str_quantity;
    unsigned int price_add;
    unsigned int quantity_add;

while(true){
        std::cout << " Podaj nazwe produktu";
        std::getline(std::cin,object_add);
        if(object_add == ""|| object_add == " "){
        std::cout << "Nie podałes nazwy produktu\n ";
        }else{
            break;
        }
}

while(true){
    try{    
            std::cout << " Podaj cene produktu w groszach";
            std::getline(std::cin,str_price);
            int val = std::stoi(str_price);
            if(val <= 0){
                std::cout << "Nie podałes ceny produktu\n ";
            }else{
                price_add = val;
                break;
            }
        } catch (...){
            std::cout << "Podaj liczbe\n";
        }
        }

while(true){
    try{
        std::cout << " Podaj ilosc danego produktu";
        std::getline(std::cin,str_quantity);
        int val = std::stoi(str_quantity);
        if(val <= 0){
            std::cout << "Nie podałes ilości produktu\n ";
        }else{
            quantity_add = val;
            break;
        }
    } catch (...){
        std::cout << "Podaj liczbe\n";
    }
    }
    Product temp;
    temp.object = object_add; 
    temp.price = price_add;
    temp.quantity = quantity_add;
    p.push_back(temp);
}


void Delete(std::vector<Product> &p){
    std::string nr_del_str;
    int nr_del = 0;
    while(true){
        try{
            std::cout << "Podaj numer produktu do usuniecia";
            std::getline(std::cin,nr_del_str);
            nr_del = stoi(nr_del_str);
            if (nr_del >= 1 && nr_del <= p.size()) {
                break;
            } else {
                std::cout << "Nie znaleziono szukanego numeru w bazie\n";
            }
        } catch (...){
            std::cout << "Nie podales nawet liczby...\n";
        }
    }
    std::vector<Product>::iterator it = p.begin() + nr_del - 1;
    p.erase(it);
}


void const Search(std::vector<Product> &p){
    std::string searched;
    std::cout << "Podaj nazwe produktu, który chcesz wyszukać: \n";
    std::getline(std::cin,searched);

    bool found = false;
    for (size_t i = 0; i < p.size(); i++){
        if(p[i].object == searched){
            std::cout << "Produkt którego szukasz\n";
            std::cout << p[i].object << std::endl;
            std::cout << "Cena: " << p[i].price/100 << " zl " << p[i].price%100 << " gr" << std::endl;
            std::cout << "Ilosc: " << p[i].quantity << std::endl;
            found = true;       
        }

    }
    if (!found){
        std::cout << "Nie znaleziono szukanego produktu" << std::endl;
    }
}

void QuantityChange(std::vector<Product> &p){
    std::string searched;
    std::cout << "Podaj nazwe produktu, który chcesz wyszukać: \n";
    std::getline(std::cin,searched);
    unsigned int newquantity;

    bool found = false;
    for (size_t i = 0; i < p.size(); i++){
        if(p[i].object == searched){
            std::cout << "Produkt którego szukasz\n";
            std::cout << p[i].object << std::endl;
            std::cout << "Cena: " << p[i].price / 100 << " zl " << p[i].price % 100 << " gr" << std::endl;
            std::cout << "Ilosc: " << p[i].quantity << std::endl;

            while (true){
                std::string new_quan_str;
                std::cout << "Podaj nowa ilosc produktu: " << p[i].object << std::endl;
                std::getline(std::cin,new_quan_str);

                try{
                    int val = stoll(new_quan_str);
                    if (val <= 0){
                        std::cout << "Podaj poprawna ilosc\n";
                    } else {
                        newquantity = val;
                        p[i].quantity = newquantity;
                        found = true;
                        break;
                    }
                } catch (...){
                    std::cout << "Podaj liczbe\n";
                }
            }
        }
    }
    if (!found){
        std::cout << "Nie znaleziono szukanego produktu" << std::endl;
    }
}

int main(){
    int option;
    std::string option_string;
    std::vector<Product> p;
    const std::string filename = "magazyn.txt";

    Load(p, filename);

    bool running = true;
     while (running)
     {
        Menu();
        getline(std::cin, option_string);

        try{
            option = stoi(option_string);
            if (option < 1 || option > 6){
                std::cout << " Nalezy wybrac opcje w zakresie 1-6" << std::endl;
                continue;
            }
        } catch (...){
            std::cout << " Nalezy wybrac opcje w zakresie 1-6" << std::endl;
            continue;
        }
        std::cout << option << "\n";
        switch (option){

            case 1:
                showAll(p);
                break;

            case 2:
                Add(p);
                break;

            case 3:
                Delete(p);
                break;

            case 4:
                QuantityChange(p);
                break;

            case 5:
                Search(p);
                break;

            case 6:
                running = false;
                break;
        }
     }

     Save(p, filename);
     return 0;
}







//std::cout << price/100 << " zł" << price%100 << " gr " << std::endl;
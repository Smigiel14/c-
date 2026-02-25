#include <iostream>
int main (int argc, char *argv[] )
{
int opcja;
int wybor;

do 
{


std::cout << "MENU\n";
std::cout << "(1) wypisz ilość argumentów programu\n";
std::cout << "(2) Wypisz wybrany argument programu\n";
std::cout << "(3) Wypisz wszystkie argumenty programu\n";
std::cout << "(4) Zakończ program\n";
std::cout << "wybierz opcje";
std::cin >> opcja;
    if (opcja == 1)
    {
        std::cout << "Ilość argumentów " << argc << std::endl;
    }
    
    if (opcja == 2)
    {
        std::cout << "Jaki argument chcesz zobaczyć" << std::endl;
        std::cin >> wybor;
        if (wybor < argc){
            std::cout << argv[wybor];
         } else{
            std::cerr << "Nie ma tyle argumentów!";
        }
        
    }
    if (opcja == 3)
    {
        for (int i = 0; i < argc; i++){
            std::cout << argv[i] << std::endl;
        }
    }
    if (opcja == 4){
        std::cout << "koniec programu" << std::endl;
    }
    

    
} while (opcja!=4);
return 0;
}
#include <iostream>
#include "Ulamek.hpp"

int main() {
    Ulamek u1(2, 4);   
    Ulamek u2(1, 4);   
    Ulamek u3(5, -10); 

    
    std::cout << "u1 (2/4): " << *u1 << std::endl;
    std::cout << "u2 (1,4): " << *u2 << std::endl;
    std::cout << "u3 (5/-10): " << *u3 << std::endl;

    Ulamek suma = u1 + u2;        
    Ulamek roznica = u1 - u2;     
    Ulamek iloczyn = u1 * u2;    
    Ulamek iloraz = u1 / u2;     

    std::cout << "1/2 + 1/4 = " << *suma << std::endl;
    std::cout << "1/2 - 1/4 = " << *roznica << std::endl;
    std::cout << "1/2 * 1/4 = " << *iloczyn << std::endl;
    std::cout << "1/2 / 1/4 = " << *iloraz << std::endl;

    Ulamek u4(3, 6); 
    if (u1 == u4) {
        std::cout << "2/4 = 3/6" << std::endl;
    } else {
        std::cout << "nie sa rowne" << std::endl;
    }

    Ulamek u5(1, 2);
    std::cout << "u5:  " << *u5 << std::endl;
    
    u5 += u2; 
    std::cout << "1/2 + 1/4 = " << *u5 << std::endl;
    
    u5 *= Ulamek(2, 1); // 3/4 * 2/1 = 6/4 = 3/2
    std::cout << "3/4 * 2/1 = " << *u5 << std::endl;

    
    Ulamek u6(1, 3);
    double d = *u6; 
    std::cout << " 1/3 jako ulamek dziesiatny: " << d << std::endl;

    return 0;
}

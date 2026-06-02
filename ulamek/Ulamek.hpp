#ifndef ULAMEK_HPP
#define ULAMEK_HPP

#include <iostream>
#include <numeric>

class Ulamek {
public:
    Ulamek(int a, int b);

    Ulamek operator+(const Ulamek& other) const;
    Ulamek operator-(const Ulamek& other) const;
    Ulamek operator*(const Ulamek& other) const;
    Ulamek operator/(const Ulamek& other) const;

    Ulamek& operator+=(const Ulamek& other);
    Ulamek& operator-=(const Ulamek& other);
    Ulamek& operator*=(const Ulamek& other);
    Ulamek& operator/=(const Ulamek& other);

    bool operator==(const Ulamek& other) const;
    double operator*() const; 

    friend std::ostream& operator<<(std::ostream& os, const Ulamek& u) {
        os << u.a << "/" << u.b;
        return os;
    }

private:
    void optimize();
    int a; 
    int b; 
};

#endif
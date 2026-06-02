#include "Ulamek.hpp"
#include <stdexcept>


    Ulamek::Ulamek(int a, int b){
      this->a = a;
      this->b = b;
      this->optimize();
    }

    void Ulamek::optimize(){
      if (b < 0){
        a = -a;
        b = -b;
      }
      int gcd = std::gcd(std::abs(a), b);
    a /= gcd;
    b /= gcd;
}
    
    Ulamek Ulamek::operator+(const Ulamek& other) const{
      int new_a = (this->a * other.b) + (other.a * this->b);
      int new_b = this->b * other.b;
      return Ulamek(new_a, new_b);
    }
    Ulamek Ulamek::operator-(const Ulamek& other) const {
    int new_a = (this->a * other.b) - (other.a * this->b);
    int new_b = this->b * other.b;
    return Ulamek(new_a, new_b);
}
    Ulamek Ulamek::operator*(const Ulamek& other) const {
    return Ulamek(this->a * other.a, this->b * other.b);
}
    Ulamek Ulamek::operator/(const Ulamek& other) const {
    return Ulamek(this->a * other.b, this->b * other.a);
}

    bool Ulamek::operator==(const Ulamek& other) const {
    return this->a == other.a && this->b == other.b;
}


Ulamek& Ulamek::operator+=(const Ulamek& other) {
    *this = *this + other;
    return *this;
}

Ulamek& Ulamek::operator-=(const Ulamek& other) {
    *this = *this - other;
    return *this;
}

Ulamek& Ulamek::operator*=(const Ulamek& other) {
    *this = *this * other;
    return *this;
}

Ulamek& Ulamek::operator/=(const Ulamek& other) {
    *this = *this / other;
    return *this;
}

double Ulamek::operator*() const {
    return a / (double)b;
}



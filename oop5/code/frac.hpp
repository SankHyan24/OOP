#pragma once
#include <iostream>
/*
 * Class Fraction
 * The Range of the Fraction is from:
 * 2^31-1 to 1/2^31
 */
inline int pow10(int n) // get 10^n in integer
{
    int res = 1;
    for (int i = 0; i < n && i < 10; i++)
        res *= 10;
    return res;
}
class fraction
{
private:
    int numerator;
    int denominator;
    void reduce() // Simplification
    {
        if (denominator < 0) // Sign normalization
            numerator = -numerator, denominator = -denominator;
        int n = numerator < 0 ? -numerator : numerator;
        int d = denominator < 0 ? -denominator : denominator;
        while (d != 0)
        {
            int temp = n % d;
            n = d;
            d = temp;
        }
        numerator /= n;
        denominator /= n;
    }

public:
    // ctor dtor
    fraction() : numerator(0), denominator(1){};
    fraction(int n, int d) : numerator(n), denominator(d) { this->reduce(); };
    // copy constructor from fraction
    fraction(const fraction &f) : numerator(f.numerator), denominator(f.denominator) { this->reduce(); };
    // from double to construct a fraction, works fine on the numbers like 1.625
    fraction(double frac);

    virtual ~fraction(){};
    // arithmetical operators: + - * /
    fraction operator+(const fraction &f) const;
    fraction operator-(const fraction &f) const;
    fraction operator*(const fraction &f) const;
    fraction operator/(const fraction &f) const;
    // relational operators: < <= == != >= >
    bool operator<(const fraction &f) const;
    bool operator<=(const fraction &f) const;
    bool operator==(const fraction &f) const;
    bool operator!=(const fraction &f) const;
    bool operator>=(const fraction &f) const;
    bool operator>(const fraction &f) const;
    // assignment operators: = += -= *= /=
    fraction &operator=(const fraction &f);
    fraction &operator+=(const fraction &f);
    fraction &operator-=(const fraction &f);
    fraction &operator*=(const fraction &f);
    fraction &operator/=(const fraction &f);
    // type cast to double
    operator double() const;
    double to_double() const;
    // type cast to string
    operator std::string() const;
    std::string to_string() const;
    // inserter and extractor for streams
    friend std::ostream &operator<<(std::ostream &os, const fraction &f);
    friend std::istream &operator>>(std::istream &is, fraction &f);
    // print
    void print() const;
};
#pragma once
#include <iostream>
/**
 * File: frac.hpp
 * @author Charles Sun
 * Class fraction
 */

// Class Fraction
// This class is used to store the fraction
// It contains the numerator and denominator
// Can use the operator +, -, *, / and so on
class fraction
{
private:
    /**
     * Private members:
     *  @param numerator : the numerator of the fraction
     *  @param denominator : the denominator of the fraction
     *  @param Accuracy : the accuracy of the fraction casting from double
     */
    const double Accuracy = 0.000001;
    int numerator;
    int denominator;
    /**
     * Private functions:
     *   reduce : reduce the fraction
     * ---------------------------------------
     * This function is used to simplify the fraction
     * Like: transform 2/4 to 1/2, transform 36/4 to 9/1
     * It will be called in the constructor and operator automatically
     */
    void reduce()
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

    // Public function:
    // ctor: default
    // construct a fraction with numerator and denominator as 0 and 1
    fraction() : numerator(0), denominator(1){};
    // Public function:
    // ctor: with numerator and denominator
    // construct a fraction with numerator and denominator as n and d
    fraction(int n, int d) : numerator(n), denominator(d) { this->reduce(); };
    // Public function:
    // ctor: copy constructor from fraction
    // construct a fraction with numerator and denominator as f.numerator and f.denominator
    // f is what you give to the constructor
    fraction(const fraction &f) : numerator(f.numerator), denominator(f.denominator) { this->reduce(); };
    // Public function:
    // ctor: copy constructor from double
    // from double to construct a fraction, works fine on the numbers like 1.625
    // this function will automatically choose a better method to reduce the fraction
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
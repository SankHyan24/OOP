#include <frac.hpp>
#include <cmath>   // for pow and floor
#include <sstream> // for ostringstream
fraction::fraction(double frac)
{ // use 2 method (decimal and binary) to construct a fraction
    int len_after_point = 0, sign = frac >= 0 ? 1 : -1;
    double tmp = sign * frac; // sign modification, tmp is the fraction section without sign
    for (; fabs(tmp - floor(tmp)) > __DBL_EPSILON__ && len_after_point < 28; len_after_point++)
        tmp = (tmp - floor(tmp)) * 2; // use binary point and get the degree
    fraction tmpfrac2(int(frac * pow(2, len_after_point)), 1 << len_after_point);
    if (len_after_point > 20) // that means decimal may works better
    {
        int newlen = 0;
        double tmp = sign * frac;
        for (; fabs(tmp - floor(tmp)) > 0.1 && newlen < 9; newlen++)
            tmp = (tmp - floor(tmp)) * 10; // use decimal point and get the degree
        fraction tmpfrac10(int(frac * pow(10, newlen)) + 1, pow10(newlen));
        if (abs(tmpfrac10.denominator) + abs(tmpfrac10.numerator) <= 1e6) // because 1<<10 approx 1e3
        {
            numerator = tmpfrac10.numerator, denominator = tmpfrac10.denominator; // printf("by 10");
            return;
        } // If decimal not better, we also use binary to construct to keep the pricision
    }
    numerator = tmpfrac2.numerator, denominator = tmpfrac2.denominator; // printf("by 2");
}
fraction fraction::operator+(const fraction &f) const
{
    fraction result(0, 1);
    result.numerator = numerator * f.denominator + denominator * f.numerator;
    result.denominator = denominator * f.denominator;
    result.reduce();
    return result;
}
fraction fraction::operator-(const fraction &f) const
{
    fraction result(0, 1);
    result.numerator = numerator * f.denominator - denominator * f.numerator;
    result.denominator = denominator * f.denominator;
    result.reduce();
    return result;
}
fraction fraction::operator*(const fraction &f) const
{
    fraction result(0, 1);
    result.numerator = numerator * f.numerator;
    result.denominator = denominator * f.denominator;
    result.reduce();
    return result;
}
fraction fraction::operator/(const fraction &f) const
{
    fraction result(0, 1);
    result.numerator = numerator * f.denominator;
    result.denominator = denominator * f.numerator;
    result.reduce();
    return result;
}
bool fraction::operator<(const fraction &f) const
{
    return numerator * f.denominator < denominator * f.numerator;
}
bool fraction::operator<=(const fraction &f) const
{
    return numerator * f.denominator <= denominator * f.numerator;
}
bool fraction::operator==(const fraction &f) const
{
    return numerator * f.denominator == denominator * f.numerator;
}
bool fraction::operator!=(const fraction &f) const
{
    return !(*this == f);
}
bool fraction::operator>=(const fraction &f) const
{
    return !(*this < f);
}
bool fraction::operator>(const fraction &f) const
{
    return !(*this <= f);
}
fraction &fraction::operator=(const fraction &f)
{
    numerator = f.numerator;
    denominator = f.denominator;
    reduce();
    return *this;
}
fraction &fraction::operator+=(const fraction &f)
{
    *this = *this + f;
    return *this;
}
fraction &fraction::operator-=(const fraction &f)
{
    *this = *this - f;
    return *this;
}
fraction &fraction::operator*=(const fraction &f)
{
    *this = *this * f;
    return *this;
}
fraction &fraction::operator/=(const fraction &f)
{
    *this = *this / f;
    return *this;
}
fraction::operator double() const
{
    return (double)numerator / denominator;
}
double fraction::to_double() const
{
    return (double)(*this);
}
fraction::operator std::string() const
{
    std::stringstream ss; // use string stream to convert to string
    ss << *this;
    return ss.str();
}
std::string fraction::to_string() const
{
    return (std::string) * this;
}
std::ostream &operator<<(std::ostream &os, const fraction &f)
{
    os << f.numerator << "/" << f.denominator;
    return os;
}
std::istream &operator>>(std::istream &is, fraction &f)
{
    is >> f.numerator >> f.denominator;
    f.reduce();
    return is;
}
void fraction::print() const
{
    std::cout << numerator << "/" << denominator;
}
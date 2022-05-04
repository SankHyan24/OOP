/**
 * File: frac.cpp
 * @date:
 *  2020/04/20
 * @description:
 *  This file contains the implementation of the fraction class.
 * @warning:
 *  If you want to know more about the implementation of the fraction class,
 *  please read the frac.hpp file.
 *  All the comments are written in the frac.hpp file.
 *
 *  要想看注释去头文件看，具体实现没什么好注释的, 注释了也全都是废话
 */
#include <frac.hpp>
#include <cmath>   // for fabs
#include <sstream> // for ostringstream
fraction::fraction(double frac)
{
    int iNumerator = 0, iDenominator = 1, tle_flag = 0;
    bool positive = frac >= 0 ? true : false;
    double unsigned_frac = fabs(frac);
    double dNumerator = 0, dDenominator = 1, dFraction = 0;
    while (fabs(dFraction - unsigned_frac) > Accuracy && tle_flag < 1 << 30)
    {
        if (dFraction > unsigned_frac)
            iDenominator += 1;
        else
            iNumerator += 1;
        dFraction = (double)iNumerator / iDenominator;
        tle_flag++;
    }
    numerator = positive ? iNumerator : -iNumerator;
    denominator = iDenominator;
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
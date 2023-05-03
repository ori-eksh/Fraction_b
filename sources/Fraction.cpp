#include "Fraction.hpp"
#include <algorithm>
#include <iostream>

namespace ariel
{
    Fraction::Fraction(int _numerator, int _denominator) : numerator(_numerator), denominator(_denominator)
    {

        if (_denominator == 0)
        {
            throw std::invalid_argument("It is impossible to divide by 0");
        }
        smallestNumToDivision();
        if (denominator < 0 || ((numerator / denominator) < 0))
        {
            numerator = numerator * -1;
            denominator = denominator * -1;
        }
    };
    int lcm_loc(int a, int b)
    {

        return (a * b) / __gcd(a, b);
    }
    //+
    Fraction operator+(const Fraction &hulf1, const Fraction &hulf2) // Fraction+Fraction
    {

        Fraction::overflow_multiplication_check(hulf1.getNumerator(), hulf2.getDenominator());
        Fraction::overflow_multiplication_check(hulf2.getNumerator(), hulf1.getDenominator());
        Fraction::overflow_multiplication_check(hulf1.getDenominator(), hulf2.getDenominator());
        Fraction::overflow_addition_check((hulf1.getNumerator() * hulf2.getDenominator()), (hulf2.getNumerator() * hulf1.getDenominator()));

        Fraction newFr((hulf1.getNumerator() * hulf2.getDenominator()) + (hulf2.getNumerator() * hulf1.getDenominator()), (hulf1.getDenominator() * hulf2.getDenominator()));

        return newFr;
    }
    Fraction operator+(const Fraction &hulf1, float num) // Fraction + float
    {
        Fraction newFr(num);
        Fraction final = (newFr + hulf1);
        final.smallestNumToDivision();
        return final;
    }
    Fraction operator+(float num, const Fraction &hulf1) // float + Fraction
    {
        Fraction newFr(num);
        Fraction final = (newFr + hulf1);
        final.smallestNumToDivision();
        return final;
    }
    /**********************************************************************************************************/
    //-
    Fraction operator-(const Fraction &hulf1, const Fraction &hulf2) // Fraction - Fraction
    {
        int temp_den = lcm_loc(hulf1.getDenominator(), hulf2.getDenominator());

        int res1 = temp_den / hulf1.getDenominator();
        int res2 = temp_den / hulf2.getDenominator();

        int temp_num1 = hulf1.getNumerator() * res1;
        int temp_num2 = hulf2.getNumerator() * res2;

        if (temp_num1 == 2147483647 && temp_num2 == -1)
        {
            return Fraction(-2147483648, 1);
        }

        Fraction::overflow_division_check(temp_den, hulf1.getDenominator());
        Fraction::overflow_division_check(temp_den, hulf2.getDenominator());
        Fraction::overflow_multiplication_check(hulf1.getNumerator(), res1);
        Fraction::overflow_multiplication_check(hulf2.getNumerator(), res2);
        Fraction::overflow_subtraction_check(temp_num1, temp_num2);

        Fraction newFr((temp_num1 - temp_num2), temp_den);
        newFr.smallestNumToDivision();
        if (newFr.denominator < 0)
        {
            newFr.setDenominator(newFr.getDenominator() * -1);
            newFr.setNumerator(newFr.getNumerator() * -1);
        }
        return newFr;
    }
    Fraction operator-(const Fraction &hulf1, float num) // Fraction - float
    {
        Fraction newFr(num);
        Fraction final = (hulf1 - newFr);
        final.smallestNumToDivision();
        return final;
    }
    Fraction operator-(float num, const Fraction &hulf1) // float - Fraction
    {
        Fraction newFr(num);
        Fraction final = (newFr - hulf1);
        final.smallestNumToDivision();
        return final;
    }
    /**********************************************************************************************************/
    //*
    Fraction operator*(const Fraction &hulf1, const Fraction &hulf2) // Fraction * Fraction
    {
        Fraction::overflow_multiplication_check(hulf1.getNumerator(), hulf2.getNumerator());
        Fraction::overflow_multiplication_check(hulf1.getDenominator(), hulf2.getDenominator());

        Fraction newFr((hulf1.getNumerator() * hulf2.getNumerator()), hulf1.getDenominator() * hulf2.getDenominator());
        newFr.smallestNumToDivision();
        if (newFr.denominator < 0)
        {
            newFr.setDenominator(newFr.getDenominator() * -1);
            newFr.setNumerator(newFr.getNumerator() * -1);
        }
        return newFr;
    }
    Fraction operator*(const Fraction &hulf1, float num) // Fraction * float
    {
        Fraction newFr(num);
        Fraction final = (hulf1 * newFr);
        final.smallestNumToDivision();
        return final;
    }
    Fraction operator*(float num, const Fraction &hulf1) // float * Fraction
    {
        Fraction newFr(num);
        Fraction final = (hulf1 * newFr);
        final.smallestNumToDivision();
        return final;
    }
    /**********************************************************************************************************/
    //  /
    Fraction operator/(const Fraction &hulf1, const Fraction &hulf2) // Fraction / Fraction
    {
        if (hulf2.getNumerator() == 0)
        {
            throw runtime_error("It is impossible to divide by 0");
        }

        Fraction::overflow_multiplication_check(hulf1.getNumerator(), hulf2.getDenominator());
        Fraction::overflow_multiplication_check(hulf1.getDenominator(), hulf2.getNumerator());
        Fraction::overflow_division_check((hulf1.getNumerator() * hulf2.getDenominator()), (hulf1.getDenominator() * hulf2.getNumerator()));
        Fraction newFr((hulf1.getNumerator() * hulf2.getDenominator()), (hulf1.getDenominator() * hulf2.getNumerator()));
        newFr.smallestNumToDivision();

        if (newFr.denominator < 0)
        {
            newFr.setDenominator(newFr.getDenominator() * -1);
            newFr.setNumerator(newFr.getNumerator() * -1);
        }
        return newFr;
    }
    Fraction operator/(const Fraction &hulf1, float num) // Fraction / float
    {
        if (num == 0)
        {
            throw runtime_error("It is impossible to divide by 0");
        }
        Fraction newFr(num);
        Fraction final = (hulf1 / newFr);
        final.smallestNumToDivision();
        return final;
    }
    Fraction operator/(float num, const Fraction &hulf1) // float / Fraction
    {
        Fraction newFr(num);
        Fraction final = (newFr / hulf1);
        final.smallestNumToDivision();
        return final;
    }
    /**********************************************************************************************************/
    bool operator>=(const Fraction &hulf1, const Fraction &hulf2) // Fraction >= Fraction
    {
        int temp_den = lcm_loc(hulf1.getDenominator(), hulf2.getDenominator());
        int temp_num1 = hulf1.getNumerator() * (temp_den / hulf1.getDenominator());
        int temp_num2 = hulf2.getNumerator() * (temp_den / hulf2.getDenominator());

        if (temp_num1 >= temp_num2)
        {
            return true;
        }
        return false;
    }
    bool operator>=(const Fraction &hulf1, float num) // Fraction >= float
    {
        Fraction hulf2(num);
        int temp_den = lcm_loc(hulf1.getDenominator(), hulf2.getDenominator());
        int temp_num1 = hulf1.getNumerator() * (temp_den / hulf1.getDenominator());
        int temp_num2 = hulf2.getNumerator() * (temp_den / hulf2.getDenominator());

        if (temp_num1 >= temp_num2)
        {
            return true;
        }
        return false;
    }
    bool operator>=(float num, const Fraction &hulf1) // float >= Fraction
    {
        Fraction hulf2(num);
        int temp_den = lcm_loc(hulf1.getDenominator(), hulf2.getDenominator());
        int temp_num1 = hulf1.getNumerator() * (temp_den / hulf1.getDenominator());
        int temp_num2 = hulf2.getNumerator() * (temp_den / hulf2.getDenominator());

        if (temp_num2 >= temp_num1)
        {
            return true;
        }
        return false;
    }
    /**********************************************************************************************************/
    bool operator<=(const Fraction &hulf1, const Fraction &hulf2) // Fraction <= Fraction
    {
        int temp_den = lcm_loc(hulf1.getDenominator(), hulf2.getDenominator());
        int temp_num1 = hulf1.getNumerator() * (temp_den / hulf1.getDenominator());
        int temp_num2 = hulf2.getNumerator() * (temp_den / hulf2.getDenominator());

        if (temp_num1 <= temp_num2)
        {
            return true;
        }
        return false;
    }
    bool operator<=(const Fraction &hulf1, float num) // Fraction <= float
    {
        Fraction hulf2(num);
        int temp_den = lcm_loc(hulf1.getDenominator(), hulf2.getDenominator());
        int temp_num1 = hulf1.getNumerator() * (temp_den / hulf1.getDenominator());
        int temp_num2 = hulf2.getNumerator() * (temp_den / hulf2.getDenominator());

        if (temp_num1 <= temp_num2)
        {
            return true;
        }
        return false;
    }
    bool operator<=(float num, const Fraction &hulf1) // float <= Fraction
    {
        Fraction hulf2(num);
        int temp_den = lcm_loc(hulf1.getDenominator(), hulf2.getDenominator());
        int temp_num1 = hulf1.getNumerator() * (temp_den / hulf1.getDenominator());
        int temp_num2 = hulf2.getNumerator() * (temp_den / hulf2.getDenominator());

        if (temp_num2 <= temp_num1)
        {
            return true;
        }
        return false;
    }
    /**********************************************************************************************************/
    bool operator>(const Fraction &hulf1, const Fraction &hulf2) // Fraction > Fraction
    {
        int temp_den = lcm_loc(hulf1.getDenominator(), hulf2.getDenominator());
        int temp_num1 = hulf1.getNumerator() * (temp_den / hulf1.getDenominator());
        int temp_num2 = hulf2.getNumerator() * (temp_den / hulf2.getDenominator());

        if (temp_num1 > temp_num2)
        {
            return true;
        }
        return false;
    }
    bool operator>(const Fraction &hulf1, float num) // Fraction > float
    {
        Fraction hulf2(num);
        int temp_den = lcm_loc(hulf1.getDenominator(), hulf2.getDenominator());
        int temp_num1 = hulf1.getNumerator() * (temp_den / hulf1.getDenominator());
        int temp_num2 = hulf2.getNumerator() * (temp_den / hulf2.getDenominator());

        if (temp_num1 > temp_num2)
        {
            return true;
        }
        return false;
    }
    bool operator>(float num, const Fraction &hulf1) // float > Fraction
    {
        Fraction hulf2(num);
        int temp_den = lcm_loc(hulf1.getDenominator(), hulf2.getDenominator());
        int temp_num1 = hulf1.getNumerator() * (temp_den / hulf1.getDenominator());
        int temp_num2 = hulf2.getNumerator() * (temp_den / hulf2.getDenominator());

        if (temp_num2 > temp_num1)
        {
            return true;
        }
        return false;
    }
    /**********************************************************************************************************/
    bool operator<(const Fraction &hulf1, const Fraction &hulf2) // Fraction < Fraction
    {
        int temp_den = lcm_loc(hulf1.getDenominator(), hulf2.getDenominator());
        int temp_num1 = hulf1.getNumerator() * (temp_den / hulf1.getDenominator());
        int temp_num2 = hulf2.getNumerator() * (temp_den / hulf2.getDenominator());

        if (temp_num1 < temp_num2)
        {
            return true;
        }
        return false;
    }
    bool operator<(const Fraction &hulf1, float num) // Fraction < float
    {
        Fraction hulf2(num);
        int temp_den = lcm_loc(hulf1.getDenominator(), hulf2.getDenominator());
        int temp_num1 = hulf1.getNumerator() * (temp_den / hulf1.getDenominator());
        int temp_num2 = hulf2.getNumerator() * (temp_den / hulf2.getDenominator());

        if (temp_num1 < temp_num2)
        {
            return true;
        }
        return false;
    }
    bool operator<(float num, const Fraction &hulf1) // float < Fraction
    {
        Fraction hulf2(num);
        int temp_den = lcm_loc(hulf1.getDenominator(), hulf2.getDenominator());
        int temp_num1 = hulf1.getNumerator() * (temp_den / hulf1.getDenominator());
        int temp_num2 = hulf2.getNumerator() * (temp_den / hulf2.getDenominator());

        if (temp_num2 < temp_num1)
        {
            return true;
        }
        return false;
    }
    /**********************************************************************************************************/
    bool operator==(const Fraction &hulf1, const Fraction &hulf2) // Fraction == Fraction
    {
        const float epsilon = 1000.0;
        int opt1 = (int)(((float)hulf1.getNumerator() / (float)hulf1.getDenominator()) * epsilon);
        int opt2 = (int)(((float)hulf2.getNumerator() / (float)hulf2.getDenominator()) * epsilon);

        return (opt1 == opt2 || ((opt1 - 0.001) == opt2));
    }
    bool operator==(const Fraction &hulf1, float num) // Fraction == float
    {
        Fraction hulf2(num);

        return (hulf1 == hulf2);
    }
    bool operator==(float num, const Fraction &hulf1) // float == Fraction
    {
        Fraction hulf2(num);

        return (hulf1 == hulf2);
    }
    /**********************************************************************************************************/
    Fraction &Fraction::operator--() // Fraction--
    {
        numerator -= denominator;
        return *this;
    }

    Fraction Fraction::operator--(int) // Fraction--
    {
        Fraction temp(numerator, denominator);
        numerator -= denominator;
        return temp;
    }

    Fraction &Fraction::operator++() // Fraction++
    {
        numerator += denominator;
        return *this;
    }

    Fraction Fraction::operator++(int) // Fraction++
    {
        Fraction temp(numerator, denominator);
        numerator += denominator;
        return temp;
    }
    /**********************************************************************************************************/
    std::ostream &operator<<(std::ostream &oos, const Fraction &toprint)
    {

        oos << toprint.getNumerator() << "/" << toprint.getDenominator();
        return oos;
    }
    /**********************************************************************************************************/
    std::istream &operator>>(std::istream &iis, Fraction &tocreate)
    {
        int temp_numerator = 0, temp_denominator = 0;
        iis >> temp_numerator >> temp_denominator;

        if (iis.fail())
        {
            throw std::runtime_error("sorry faild");
        }
        if (temp_denominator == 0)
        {
            throw std::runtime_error("It is impossible to divide by 0");
        }
        tocreate.setNumerator(temp_numerator);
        tocreate.setDenominator(temp_denominator);
        tocreate.smallestNumToDivision();
        if (tocreate.getDenominator() < 0)
        {
            tocreate.setNumerator((tocreate.getNumerator() * -1));
            tocreate.setDenominator((tocreate.getDenominator() * -1));
        }
        return iis;
    }
    /**********************************************************************************************************/
}
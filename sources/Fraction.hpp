#include <string>
#include <stdexcept>
#include <limits>
using namespace std;

namespace ariel
{

    class Fraction
    {
    private:
        int numerator;
        int denominator;

        static bool overflow_addition_check(int num1, int num2)
        {
            int max_int = std::numeric_limits<int>::max();
            int min_int = std::numeric_limits<int>::min();

            if ((num2 > 0 && num1 > (max_int - num2)) || (num2 < 0 && num1 < (min_int - num2)))
            {
                throw std::overflow_error("Addition overflow");
            }

            return true;
        }

        static bool overflow_subtraction_check(int num1, int num2)
        {
            int max_int = std::numeric_limits<int>::max();
            int min_int = std::numeric_limits<int>::min();
            if ((num2 < 0 && num1 > (max_int + num2)) || (num2 > 0 && num1 < (min_int + num2)))
            {
                throw std::overflow_error("Subtraction overflow");
            }

            return true;
        }

        static bool overflow_multiplication_check(int num1, int num2)
        {
            int max_int = std::numeric_limits<int>::max();
            int min_int = std::numeric_limits<int>::min();
            if ((num2 > 0 && (num1 > (max_int / num2))) || ((num2 < 0) && (num1 < (max_int / num2))))
            {
                throw std::overflow_error("Multiplication overflow");
            }

            return true;
        }

        static bool overflow_division_check(int num1, int num2)
        {
            int max_int = std::numeric_limits<int>::max();
            int min_int = std::numeric_limits<int>::min();
            if (num2 == 0 || ((num1 == min_int) && (num2 == -1)))
            {
                throw std::overflow_error("Division overflow");
            }

            return true;
        }

    public:
        void printCardD();
        int getNumerator() const { return this->numerator; }
        int getDenominator() const { return this->denominator; }

        void setNumerator(int number) { this->numerator = number; }
        void setDenominator(int number) { this->denominator = number; }

        Fraction(int _numerator, int _denominator);

        Fraction(float floatnumber)
        {

            numerator = 1000 * floatnumber;
            denominator = 1000;

            smallestNumToDivision();
            if (denominator == 0)
            {
                throw std::invalid_argument("It is impossible to divide by 0");
            }
            if (floatnumber < 0 || denominator < 0)
            {
                numerator = numerator * -1;
                denominator = denominator * -1;
            }
        }
        Fraction() : numerator(0), denominator(1){};
        friend Fraction
        operator+(const Fraction &hulf1, const Fraction &hulf2);     // Fraction+Fraction
        friend Fraction operator+(const Fraction &hulf1, float num); // Fraction + float
        friend Fraction operator+(float num, const Fraction &hulf1); // float + Fraction

        friend Fraction operator-(const Fraction &hulf1, const Fraction &hulf2); // Fraction - Fraction
        friend Fraction operator-(const Fraction &hulf1, float num);             // Fraction - float
        friend Fraction operator-(float num, const Fraction &hulf1);             // float - Fraction

        friend Fraction operator*(const Fraction &hulf1, const Fraction &hulf2); // Fraction * Fraction
        friend Fraction operator*(const Fraction &hulf1, float num);             // Fraction * float
        friend Fraction operator*(float num, const Fraction &hulf1);             // float * Fraction

        friend Fraction operator/(const Fraction &hulf1, const Fraction &hulf2); // Fraction / Fraction
        friend Fraction operator/(const Fraction &hulf1, float num);             // Fraction / float
        friend Fraction operator/(float num, const Fraction &hulf1);             // float / Fraction

        friend bool operator>=(const Fraction &hulf1, const Fraction &hulf2); // Fraction >= Fraction
        friend bool operator>=(const Fraction &hulf1, float num);             // Fraction >= float
        friend bool operator>=(float num, const Fraction &hulf1);             // float >= Fraction

        friend bool operator<=(const Fraction &hulf1, const Fraction &hulf2); // Fraction <= Fraction
        friend bool operator<=(const Fraction &hulf1, float num);             // Fraction <= float
        friend bool operator<=(float num, const Fraction &hulf1);             // float <= Fraction

        friend bool operator>(const Fraction &hulf1, const Fraction &hulf2); // Fraction > Fraction
        friend bool operator>(const Fraction &hulf1, float num);             // Fraction > float
        friend bool operator>(float num, const Fraction &hulf1);             // float > Fraction

        friend bool operator<(const Fraction &hulf1, const Fraction &hulf2); // Fraction < Fraction
        friend bool operator<(const Fraction &hulf1, float num);             // Fraction < float
        friend bool operator<(float num, const Fraction &hulf1);             // float < Fraction

        friend bool operator==(const Fraction &hulf1, const Fraction &hulf2); // Fraction == Fraction
        friend bool operator==(const Fraction &hulf1, float num);             // Fraction == float
        friend bool operator==(float num, const Fraction &hulf1);             // float == Fraction

        Fraction &operator--();   //--Fraction
        Fraction operator--(int); // Fraction--
        Fraction &operator++();   //++Fraction
        Fraction operator++(int); // Fraction++

        friend std::ostream &operator<<(std::ostream &oos, const Fraction &print);
        friend std::istream &operator>>(std::istream &iis, Fraction &getnum);

        static int _gcd(int num1, int num2) // find the gcd -  find the greatest common divisor
        {
            while (num2 != 0)
            {
                int temp = num2;
                num2 = num1 % num2;
                num1 = temp;
            }
            return num1;
        }
        int lcm_loc(int, int);

        void smallestNumToDivision() // the redus
        {
            int divingNum = std::__gcd(this->getNumerator(), this->getDenominator());
            this->setDenominator(this->getDenominator() / divingNum);
            this->setNumerator(this->getNumerator() / divingNum);
        }
    };
}
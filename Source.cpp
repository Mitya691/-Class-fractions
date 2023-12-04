#include <iostream>
#include <numeric>
#include <conio.h>

using namespace std;

#define TYPE int
#define ENTER 13
#define BACKSPACE 8

TYPE enter() {
    TYPE maxx, minx = 1, CS_N = 0, r = 0, d;
    while (minx > 0) {
        minx *= 2;
    }
    maxx = minx - 1;
    char c, is_minus = 0;
    while ((c = _getch()) != ENTER || CS_N == 0) {
        if (c >= 48 && c <= 57) {
            d = c - 48;
            if (is_minus == 0) {
                if (CS_N > 0 && r == 0) { continue; }
                if (r <= (maxx - d) / 10) {
                    r = r * 10 + d;
                    _putch(c);
                    CS_N++;
                }
            }
            else {
                if (CS_N == 0 && d == 0) { continue; }
                if (r >= (minx + d) / 10) {
                    r = r * 10 - d;
                    _putch(c);
                    CS_N++;
                }
            }
        }
        else if (c == '-') {
            if (is_minus == 1 || CS_N > 0 || minx == 0) { continue; }
            is_minus = 1;
            _putch(c);
        }
        else if (c == BACKSPACE) {
            if (CS_N == 0 && is_minus == 0) { continue; }
            _putch(8);
            _putch(32);
            _putch(8);
            r = r / 10;
            if (is_minus == 1 && CS_N == 0) { is_minus = 0; }
            else { CS_N--; }
        }
    }
    _putch('\n');
    return r;
}

class Rational {
public:
    Rational() = default;

    Rational(double value)
        : numerator_(value)
        , denominator_(1) {
    }

    Rational(int numerator, int denominator)
        : numerator_(numerator)
        , denominator_(denominator)
    {
        Normalize();
    }

    int Numerator() const {
        return numerator_;
    }

    int Denominator() const {
        return denominator_;
    }

    Rational& operator+=(Rational right) {
        numerator_ = numerator_ * right.denominator_ + right.numerator_ * denominator_;
        denominator_ *= right.denominator_;
        //Normalize();
        return *this;
    }

    Rational& operator-=(Rational right) {
        numerator_ = numerator_ * right.denominator_ - right.numerator_ * denominator_;
        denominator_ *= right.denominator_;
       // Normalize();
        return *this;
    }

    Rational& operator*=(Rational right) {
        numerator_ *= right.numerator_;
        denominator_ *= right.denominator_;
       // Normalize();
        return *this;
    }

    Rational& operator/=(Rational right) {
        numerator_ *= right.denominator_;
        denominator_ *= right.numerator_;
        //Normalize();
        return *this;
    }

private:
   /* void Normalize() {
        if (denominator_ < 0) {
            numerator_ = -numerator_;
            denominator_ = -denominator_;
        }
        int n = gcd(numerator_, denominator_);
        numerator_ /= n;
        denominator_ /= n;
    }*/

    long long numerator_ = 0.0;
    long long denominator_ = 1.0;
};

ostream& operator<<(ostream& output, Rational rational) {
    return output << rational.Numerator() << '/' << rational.Denominator();
}

Rational input() {
    Rational rational;
    TYPE numerator, denominator;
    cout << "Please enter the numerator of the fraction: ";
    numerator = enter();
    cout << "Please enter the denominator of the fraction: ";
    denominator = enter();
    if (denominator == 0) {
        while (denominator == 0) {
            cout << "Incorrecct fraction, please try input denominator again: ";
            denominator = enter();
        }
    }
    rational = Rational{ numerator, denominator };
    return rational;
}

Rational operator+(Rational value) {
    return value;
}

Rational operator-(Rational value) {
    return { -value.Numerator(), value.Denominator()};
}

Rational operator+(Rational left, Rational right) {
    return left += right;
}

Rational operator-(Rational left, Rational right) {
    return left -= right;
}

Rational operator*(Rational left, Rational right) {
    return left *= right;
}

Rational operator/(Rational left, Rational right) {
    return left /= right;
}

bool operator==(Rational left, Rational right) {
    return left.Numerator() == right.Numerator() &&
        left.Denominator() == right.Denominator();
}

bool operator!=(Rational left, Rational right) {
    return !(left == right);
}

bool operator<(Rational left, Rational right) {
    return left.Numerator() * right.Denominator() < right.Numerator() * left.Denominator();
}

bool operator<=(Rational left, Rational right) {
    return left.Numerator() * right.Denominator() < right.Numerator() * left.Denominator() ||
        left.Numerator() * right.Denominator() == right.Numerator() * left.Denominator();
}

bool operator>(Rational left, Rational right) {
    return left.Numerator() * right.Denominator() > right.Numerator() * left.Denominator();
}

bool operator>=(Rational left, Rational right) {
    return left.Numerator() * right.Denominator() > right.Numerator() * left.Denominator() ||
        left.Numerator() * right.Denominator() == right.Numerator() * left.Denominator();
}

int main() {
    Rational f1, f2;
    cout << "Please enter the first fraction\n";
    f1 = input();
    cout << "Please enter the second fraction\n";
    f2 = input();
    int choose = 1;
    cout << "MENU\n";
    cout << "1. Add two fractions\n";
    cout << "2. Subtract two fractions\n";
    cout << "3. Survive two fractions\n";
    cout << "4. Divide two fractions\n";
    cout << "5. Compare two fractions\n";
    cout << "0. Exit\n";
    while (choose != 0) {
        choose = enter();
        while (choose < 0 || choose >5) {
            cout << "Invalid request please enter a request with a number from 0 to 5" << endl;
            choose = enter();
        }
        if (choose == 1)
            cout << f1 << " + " << f2 << " = " << f1 + f2 << endl;
        else if (choose == 2)
            cout << f1 << " - " << f2 << " = " << f1 - f2 << endl;
        else if (choose == 3)
            cout << f1 << " * " << f2 << " = " << f1 * f2 << endl;
        else if (choose == 4)
            cout << f1 << " / " << f2 << " = " << f1 / f2 << endl;
        else if (choose == 5){
            int choose_operator = 1;
            cout << "Please select an operator to compare:\n";
            cout << "  1. ==";
            cout << "  2. !=";
            cout << "  3. <";
            cout << "  4. <=";
            cout << "  5. >";
            cout << "  6. >=";
            cout << "  0. Exit";
            choose_operator = enter();
            while (choose_operator < 0 || choose_operator > 6) {
                cout << "Invalid request please enter a request with a number from 0 to 6" << endl;
                choose_operator = enter();
            }
                if (choose_operator == 1) {
                    bool res = f1 == f2;
                    if (res == 0)
                        cout << f1 << " != " << f2 << endl;
                    else cout << f1 << " = " << f2 << endl;
                }
                if (choose_operator == 2) {
                    bool res = f1 != f2;
                    if (res == 0)
                        cout << f1 << " = " << f2 << endl;
                    else cout << f1 << " != " << f2 << endl;
                }
                if (choose_operator == 3) {
                    bool res = f1 < f2;
                    if (res == 0)
                        cout << f1 << " > " << f2 << endl;
                    else cout << f1 << " < " << f2 << endl;
                }
                if (choose_operator == 4) {
                    bool res = f1 <= f2;
                    if (res == 0)
                        cout << f1 << " > " << f2 << endl;
                    else cout << f1 << " <= " << f2 << endl;
                }
                if (choose_operator == 5) {
                    bool res = f1 > f2;
                    if (res == 0)
                        cout << f1 << " < " << f2 << endl;
                    else cout << f1 << " > " << f2 << endl;
                }
                if (choose_operator == 6) {
                    bool res = f1 >= f2;
                    if (res == 0)
                        cout << f1 << " < " << f2 << endl;
                    else cout << f1 << " >= " << f2 << endl;
                }
                if (choose_operator == 7) {
                    choose_operator = 0;
                }
            }
        }
    }

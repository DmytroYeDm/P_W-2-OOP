
#include <iostream>
using namespace std;
class Proper_Fraction {
private:
    int int_part;
    int ch;
    int zn;
public:
    Proper_Fraction() {
        int_part = 0;
        ch = 0;
        zn = 1;
    }

    Proper_Fraction(int int_p, int c, int z) {
        if (z == 0) {
            abort();
        }
        if (c >= z) {
            int_part = int_p + c / z;
            ch = c - c / z * z;
            zn = z;
        }
        else {
            int_part = int_p;
            ch = c;
            zn = z;
        }
    }

    Proper_Fraction& operator=(Proper_Fraction p_f) {
        this->int_part = p_f.int_part;
        this->ch = p_f.ch;
        this->zn = p_f.zn;
        return *this;
    }

    bool operator==(Proper_Fraction& p_f) {
        return (this->int_part == p_f.int_part && this->ch == p_f.ch && this->zn == p_f.zn);
    }

    bool operator!=(Proper_Fraction& p_f) {
        return !(this->int_part == p_f.int_part && this->ch == p_f.ch && this->zn == p_f.zn);
    }

    bool operator<=(Proper_Fraction& p_f) {
        if (this->zn == p_f.zn) {
            return (this->ch + this->int_part * this->zn <= p_f.ch + p_f.int_part * p_f.zn);
        }
        else {
            return ((this->ch + this->int_part * this->zn) * p_f.zn <= (p_f.ch + p_f.int_part * p_f.zn) * this->zn);
        }
    }

    bool operator>=(Proper_Fraction& p_f) {
        if (this->int_part == p_f.int_part && this->ch == p_f.ch && this->zn == p_f.zn) {
            return true;
        }
        else {
            return !(operator<=(p_f));
        }   
    }

    operator int() {
        return int_part;
    }

    operator double() {
        return int_part + (double)ch/zn;
    }

    int operator()(string s) {
        if (s == "integer" || s == "int_part") {
            return int_part;
        }

        if (s == "ch" || s == "chiselnuk") {
            return ch;
        }

        if (s == "zn" || s == "znamennuk") {
            return zn;
        }
    }

    friend ostream& operator<<(ostream& out, Proper_Fraction p_f) {
        int cs = 0;
        if (p_f.ch != 0) {
            cs += 2;
        }
        if (p_f.int_part != 0) {
            cs++;
        }
        switch (cs)
        {
        case 0:
            out << 0 << endl;
            break;
        case 1:
            out << p_f.int_part << endl;
            break;
        case 2:
            out << p_f.ch << "/" << p_f.zn << endl;
            break;
        case 3:
            out << p_f.int_part << " " << p_f.ch << "/" << p_f.zn << endl;
            break;
        default:
            break;
        }
        return out;
    }

    friend istream& operator>>(istream& in, Proper_Fraction& p_f) {
        in >> p_f.int_part >> p_f.ch >> p_f.zn;
        if (p_f.zn == 0) {
            abort();
        }
        return in;
    }

    Proper_Fraction operator+(Proper_Fraction& p2) {
        Proper_Fraction p_f;
        p_f.int_part = this->int_part + p2.int_part;
        if (this->zn == p2.zn) {
            p_f.ch = this->ch + p2.ch;
            p_f.zn = this->zn;
        }
        else {
            p_f.ch = this->ch * p2.zn + p2.ch * this->zn;
            p_f.zn = this->zn * p2.zn;
        }
        
        if (p_f.ch > p_f.zn) {
            p_f.int_part = p_f.int_part + 1;
            p_f.ch = p_f.ch - p_f.zn;

        }
        return p_f;
    }

    Proper_Fraction operator-(const Proper_Fraction& p2) {
        Proper_Fraction p_f;
        p_f.int_part = this->int_part - p2.int_part;
        if (this->zn == p2.zn) {
            p_f.ch = this->ch - p2.ch;
            p_f.zn = this->zn;
        }
        else {
            p_f.ch = this->ch * p2.zn - p2.ch * this->zn;
            p_f.zn = this->zn * p2.zn;
        }
        return p_f;
    }

    Proper_Fraction operator*(Proper_Fraction& p2) {
        Proper_Fraction p_f;
        p_f.ch = (this->int_part * this->zn + this->ch) * (p2.int_part * p2.zn + p2.ch);
        p_f.zn = this->zn * p2.zn;
        if (p_f.ch > p_f.zn) {
            p_f.int_part = p_f.ch / p_f.zn;
            p_f.ch = p_f.ch - p_f.ch / p_f.zn * p_f.zn;
        }
        else {
            p_f.int_part = 0;
        }
        return p_f;
    }

    Proper_Fraction operator/(Proper_Fraction& p2) {
        Proper_Fraction p_f;
        p_f.ch = (this->int_part * this->zn + this->ch) * p2.zn;
        p_f.zn = this->zn * (p2.int_part * p2.zn + p2.ch);
        if (p_f.ch >= p_f.zn) {
            p_f.int_part = p_f.ch / p_f.zn;
            p_f.ch = p_f.ch - p_f.ch / p_f.zn * p_f.zn;
        }
        else {
            p_f.int_part = 0;
        }
        return p_f;
    }

    Proper_Fraction operator+(int n) {
        Proper_Fraction p_f;
        p_f.int_part = this->int_part + n;
        p_f.ch = this->ch;
        p_f.zn = this->zn;
        return p_f;
    }

    Proper_Fraction operator*(int n) {
        Proper_Fraction p_f;
        p_f.int_part = int_part * n;
        p_f.ch = ch * n;
        p_f.zn = zn;
        if (p_f.ch >= p_f.zn) {
            p_f.int_part = p_f.int_part + p_f.ch / p_f.zn;
            p_f.ch = p_f.ch - p_f.ch / p_f.zn * p_f.zn;
        }
        return p_f;
    }
};
int main()
{
    Proper_Fraction p1, p2(2, 34, 5), p3(p2), p4, p5(1, 14, 19);
    cout << p1 << p2 << p3 << p4 << p5;
    cout << p2.operator==(p3) << endl;
    cout << p2.operator!=(p5) << endl;
    cout <<p5.operator<=(p2) << endl;
    cout << p3.operator>=(p2) << endl;
    cin >> p1;
    cout << p1;
    cout << p1("integer") << ' ' << p1("ch") << ' ' << p1("zn") << endl;
    p4 = p2 = p5 + (int)p2;
    cout << (int)p2 << endl;
    cout << p2 << p4 << p5;
    p2 = p2 * 3;
    cout << p2;
    p1 = p3 - p5;
    cout << p1;
    p2 = p1 / p1;
    cout << p2;
    p1 = p5 * p3;
    cout << p1;
    cout << (double)p1 << endl;
}

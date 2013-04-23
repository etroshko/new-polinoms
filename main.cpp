#include <iostream>
#include "polinom.h"

using namespace std;

class ConP: private Polinom
{
public:
    explicit ConP(int power);
    ConP(const ConP &org);
    ConP &operator=(const ConP &org);

    ~ConP();
    ConP operator*(const ConP &org);
    ConP operator+(const ConP &org);
    ConP derivative(const ConP &org);
    ConP integral(const ConP &org);
    friend std::istream &operator >> (std::istream &in, const ConP &org);
    friend std::ostream &operator << (std::ostream &out, const ConP &org);
private:
    ConP(const Polinom &org);

};

ConP::ConP(int power):
    Polinom(power)
{

}

ConP::ConP(const ConP &org):
    Polinom(org)
{

}

ConP::ConP(const Polinom &org):
    Polinom(org)
{

}

ConP &ConP::operator=(const ConP &org)
{
    Polinom::operator=(org);
    return *this;
}

ConP ConP::operator+(const ConP &org)
{
    Polinom::operator+(org);
    return ConP(Polinom::operator+(org));
}

ConP ConP::operator*(const ConP &org)
{
    Polinom::operator*(org);
    return ConP(Polinom::operator*(org));
}


ConP::~ConP()
{

}

ConP ConP::derivative(const ConP &org)
{
    return ConP(Polinom::derivative(org));
}

ConP ConP::integral(const ConP &org)
{
    return ConP(Polinom::integral(org));
}


std::ostream &operator<<(std::ostream &out, const ConP &org)
{
    int power = org.get_power();
    double *coefficient = org.get_coef();
    for(int i=power; i>=0; --i)
    {
        switch(i)
        {
        case 0:
            out<<coefficient[i];
            break;
        case 1:
            out<<coefficient[i]<<"x"<<"+";
            break;
        default:
            out<<coefficient[i]<<"x^"<<i<<"+";
            break;
        }
    }
    out<<"\n";
    return out;
}

std::istream& operator>>(std::istream &in, const ConP &org)
{
    int power = org.get_power();
    double *coefficient = org.get_coef();
    for(int i=power; i>=0; --i)
    {
        std::cout<<"x^"<<i<<":";
        in>>coefficient[i];
    }
    return in;
}
int main()
{
    ConP a(2), b(2);
    cin>>a;
    cin>>b;
    ConP c(2);
    ConP d(4);
    c=a+b;
    d=a*b;
    cout<<"Первый полином: "<<a<<endl;
    cout<<"Второй полином: "<<b<<endl;
    cout<<"Сумма: "<<c<<endl;
    cout<<"Произведение: "<<d<<endl;
    ConP e(1);
    ConP f(3);
    e=a.derivative(a);
    f=a.integral(a);
    cout<<"Производная: "<<e<<endl;
    cout<<"Интеграл: "<<f<<endl;


    return 0;
}


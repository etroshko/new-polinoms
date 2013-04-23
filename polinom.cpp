#include "polinom.h"

class Polinom::ImP{
    private:
        int power; // степень полинома
        double *coefficient; // массив коэффициентов
    public:
        explicit ImP (int power);
        ~ImP();
        ImP(const ImP &org);
        ImP operator*(const ImP &org);
        ImP operator+(const ImP &org);
        ImP &operator=(const ImP &org);
        ImP derivative(const ImP &org);
        ImP integral(const ImP &org);
        int get_power()const;
        double *get_coef()const;

};

Polinom::Polinom(int power):
   pimpl(0)
{
   pimpl = new ImP(power);
}

Polinom::Polinom(const Polinom &org):
   pimpl(0)
{
   pimpl = new ImP(*(org.pimpl));
}

Polinom::Polinom(const ImP &org):
   pimpl(0)
{
   pimpl = new ImP(org);
}

Polinom &Polinom::operator=(const Polinom &org)
{
   *(this->pimpl) = *(org.pimpl);
   return *this;
}

Polinom Polinom::operator+(const Polinom &org)
{
    return Polinom(pimpl->operator+(*(org.pimpl)));
}

Polinom Polinom::operator*(const Polinom &org)
{

    return Polinom(pimpl->operator*(*(org.pimpl)));
}

Polinom Polinom::derivative(const Polinom &org)
{
    return Polinom(pimpl->derivative(*(org.pimpl)));
}
Polinom Polinom::integral(const Polinom &org)
{
    return Polinom(pimpl->integral(*(org.pimpl)));
}

Polinom::~Polinom()
{
   delete pimpl;
   pimpl = 0;
}

int Polinom::get_power()const
{
   return pimpl->get_power();
}

double *Polinom::get_coef()const
{
   return pimpl->get_coef();
}
/////////////////////////////////////////////////////////////

Polinom::ImP::ImP(int a):
    power(a), coefficient(0)
{
    coefficient=0;
    coefficient=new double[power+1];
};

Polinom::ImP::~ImP()
{
    delete [] coefficient;
    coefficient=0;
}

Polinom::ImP::ImP(const ImP &org):
    power(org.power),coefficient(0)
{
    coefficient=new double[power+1];
    for(int i=power; i>=0; --i)
        coefficient[i]=org.coefficient[i];
}

Polinom::ImP &Polinom::ImP::operator=(const ImP &org)
{
    if(this==&org)
        return *this;
    delete [] coefficient;
    power=org.power;
    coefficient=new double[power+1];
    for(int i=0; i<=power; ++i)
        coefficient[i]=org.coefficient[i];
    return *this;
}

Polinom::ImP Polinom::ImP::operator+(const ImP &org)
{
    int max_power;
    max_power=power>org.power?power:org.power;

    ImP temp(max_power);
    if(power==org.power)
    {
        for(int i=org.power; i>=0; --i)
            temp.coefficient[i]=coefficient[i]+org.coefficient[i];
        return temp;
    }
    if(power<org.power)
    {
        for(int i=power; i>=0; i--)
            temp.coefficient[i]=coefficient[i]+org.coefficient[i];
        for(int i=org.power; i>=power+1; --i)
            temp.coefficient[i]=org.coefficient[i];
        return temp;
    }
    if(power>org.power)
    {
        for(int i=org.power; i>=0; i--)
            temp.coefficient[i]=coefficient[i]+org.coefficient[i];
        for(int i=power; i>=org.power+1; --i)
            temp.coefficient[i]=coefficient[i];
        return temp;
    }
    return *this;
}

Polinom::ImP Polinom::ImP::operator*(const ImP &org)
{
    ImP temp(power+org.power);
    for(int i=power; i>=0; --i)
        for(int j=org.power; j>=0; --j)
            temp.coefficient[i+j]+=coefficient[i]*org.coefficient[j];
    return temp;

}

Polinom::ImP Polinom::ImP::derivative(const ImP &org)
{
    ImP temp(power-1);
    int j=power;
    for (int i=power-1; i>=0; --i)
    {
        temp.coefficient[i]=org.coefficient[j]*j;
        --j ;
    }
    return temp;
}

Polinom::ImP Polinom::ImP::integral(const ImP &org)
{
    ImP temp(power+1);
    int j=power;
    for (int i=power+1; i>0; --i)
    {
        temp.coefficient[i]=org.coefficient[j]/(j+1);
        --j ;
    }
    return temp;
}

int Polinom::ImP::get_power()const
{
   return power;
}

double *Polinom::ImP::get_coef()const
{
   return coefficient;
}




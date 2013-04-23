#ifndef POLINOM_H
#define POLINOM_H

class Polinom
{

public:
    explicit Polinom(int power);
    ~Polinom();
    Polinom(const Polinom &org);
    Polinom operator*(const Polinom &org);
    Polinom operator+(const Polinom &org);
    Polinom &operator=(const Polinom &org);
    Polinom derivative(const Polinom &org);
    Polinom integral(const Polinom &org);
protected:
    int get_power()const;
    double *get_coef()const;
private:
    class ImP;
    ImP *pimpl;
    Polinom(const ImP &org);
};

#endif // POLINOM_H_INCLUDED

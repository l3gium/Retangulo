#pragma once
class Retangulo
{
    private:
        double _base;
        double _altura;

    public:
        double getBase() const;
        void setBase(double base);
        double getAltura() const;
        void setAltura(double altura);
        double getArea() const;

        Retangulo();
        Retangulo(double val);
        Retangulo(double base, double altura);
};
#pragma once
#include "Retangulo.h"

double Retangulo::getBase() const
{
	return _base;
}

void Retangulo::setBase(double base)
{
	base > 10 ? _base = 10 : _base = base;
}

double Retangulo::getAltura() const
{
	return _altura;
}

void Retangulo::setAltura(double altura)
{
	_altura = altura;
}

double Retangulo::getArea() const
{
	return _base * _altura;
}

Retangulo::Retangulo()
{
	setBase(3); 
	setAltura(4);
}

Retangulo::Retangulo(double val)
{
	setBase(val);
	setAltura(val);
}

Retangulo::Retangulo(double base, double altura)
{
	setBase(base);
	setAltura(altura);
}
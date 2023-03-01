#pragma once
#ifndef CFLUIDO_H
#define CFLUIDO_H

#include <string>
#include <iostream>

class CFluido
{
protected:
	std::string tipoFluido;
	double viscosidade;
	double vazao;

public:
	CFluido() {};
	~CFluido() {};
	///Construtor Sobrecarregado
	CFluido(std::string _tF, double _visc, double _q);
	double gV();
	void sV(double visc);
	double gQ();
	void sQ(double q);
};
#endif

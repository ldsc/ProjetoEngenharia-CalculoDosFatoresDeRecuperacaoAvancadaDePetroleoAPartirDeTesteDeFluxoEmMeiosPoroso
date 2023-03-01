#pragma once
#ifndef CPermeabilidadeabs_h
#define CPermeabilidadeabs_h
#include <string>
#include <iostream>
#include <vector>
#include "CRocha.h"
#include "CFluido.h"
#include <armadillo> //biblioteca para regressão linear
#include "CGnuplot.h"

//arma::Col p = arma::Col<float>(std::vector<float>y); conversão STD - > ARMADILLO

class CPermeabilidadeabs
{
protected:
	std::vector<double> x; //Calculado
	std::vector<double> y; //Dados de entrada
	std::vector<double> pressao; //Dados de entrada
    double permeabilidade; //Calculado
	CRocha amostra; //Dados de entrada - amostra
	CFluido fluido; //Dados de entrada
	
public:
	//CPermeabilidadeabs() {};
	~CPermeabilidadeabs() {};
	///Construtor Sobrecarregado
	CPermeabilidadeabs(std::vector<double> _y, std::vector<double> _p, CRocha _amostra, CFluido _fl);
	std::vector<double> gX() { return x; }
	void sX(std::vector<double> _x) { x = _x; }

	std::vector<double> gY() { return y; }
	void sY(std::vector<double> _y) { y = _y; }

	std::vector<double> gP() { return pressao; }
	void sP(std::vector<double> p) { pressao = p; }

	double gK() { return permeabilidade; }
	void sK(double k) { permeabilidade = k; }

	void X();
	void Y();
	void RegressaoLinear();
};
#endif
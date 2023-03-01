#pragma once
#ifndef CROCHA_H
#define CROCHA_H
#include <string>
#define PI 3.141592654


///Representa as propriedades da rocha arenitica, Berea.
class CRocha
{
protected:
	std::string tipoRocha;
	double diametro;
	double comprimento;
	double pesoSeca;
	double pesoMolhada;
	double porosidade;

public:
	CRocha() {};
	~CRocha() {};
	///Construtor Sobrecarregado
	CRocha(std::string tR, double _d, double _c, double _ps, double _pm);

	//Alterar ou acessar os valores dos parâmetros protegidos ou privados. Declaração dos métodos.
	double gD();
	void sD(double d);

	double gC();
	void sC(double c);

	double gPS();
	void sPS(double ps);

	double gPM();
	void sPM(double pm);

	std::string gTR();
	void sTR(std::string tr);

	double Area();
	double VolumeTotal();
	double VolumePoroso();
	double Porosidade();
};
#endif
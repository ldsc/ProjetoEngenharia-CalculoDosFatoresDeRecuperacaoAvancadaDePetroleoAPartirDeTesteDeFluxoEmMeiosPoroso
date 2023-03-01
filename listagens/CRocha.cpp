#include "CRocha.h"
#include <cmath>

CRocha::CRocha(std::string tR, double _d, double _c, double _ps, double _pm) {
	tipoRocha = tR;
	diametro = _d;
	comprimento = _c;
	pesoSeca = _ps;
	pesoMolhada = _pm;
	porosidade = Porosidade();
}

std::string CRocha::gTR() { return tipoRocha; }
void CRocha::sTR(std::string tr) { tipoRocha = tr; }

double CRocha::gD() { return diametro; }
void CRocha::sD(double d) { diametro = d; }

double CRocha::gC() { return comprimento; }
void CRocha::sC(double c) { comprimento = c; }

double CRocha::gPS() { return pesoSeca; }
void CRocha::sPS(double ps) { pesoSeca = ps; }

double CRocha::gPM() { return pesoMolhada; }
void CRocha::sPM(double pm) { pesoMolhada = pm; }

double CRocha::Area() {
	return PI * (pow(diametro, 2) / 4.0) * 0.1; //0.1 Representa fator para conversão de unidades
}
double CRocha::VolumeTotal() {
	return Area()* comprimento* 0.1; //0.1 Representa fator para conversão de unidades
}
double CRocha::VolumePoroso() {
	return pesoMolhada - pesoSeca;
}
double CRocha::Porosidade() {
	return VolumePoroso() / VolumeTotal();
}
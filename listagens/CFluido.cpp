#include "CFluido.h"

CFluido::CFluido(std::string _tF, double _visc, double _q) {
	tipoFluido = _tF; 
	viscosidade = _visc;
	vazao = _q;
}
double CFluido::gV() { return viscosidade; }
void CFluido::sV(double visc) { viscosidade = visc; }
double CFluido::gQ() { return vazao; }
void CFluido::sQ(double q) { vazao = q; }
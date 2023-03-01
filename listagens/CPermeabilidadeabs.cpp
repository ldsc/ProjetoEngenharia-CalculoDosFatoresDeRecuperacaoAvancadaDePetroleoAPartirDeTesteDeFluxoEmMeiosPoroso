#include "CPermeabilidadeabs.h"

CPermeabilidadeabs::CPermeabilidadeabs(std::vector<double> _y, std::vector<double> _p, CRocha _amostra, CFluido _fl) {
	y = _y;
	pressao = _p;
	amostra = _amostra;
	fluido = _fl;
	X();
	Y();
}
void CPermeabilidadeabs::X() {
	if (y.size() != pressao.size()) { //verificando se o tamanho de y é igual da pressão.
		std::cout << "Vetores de pressao e vazao de tamanhos diferentes" << '\n';
	}
	else {
		x.resize(y.size()); //redimensionar
		for (int i = 0; i < x.size(); ++i) { //.size() - tamanho do vetor (quantidade de valores preenchidos)
			x[i] = (amostra.Area() * pressao[i]) / (fluido.gV() * amostra.gC()) * (0.06804596);
			std::cout << x[i] << " "; //Valor calculado aparece na tela
		}
	}
	std::cout << '\n';
}
void CPermeabilidadeabs::Y() {
	for (int j = 0; j < y.size(); j++) { 
		y[j] = y[j] * 16.66667; // conversão de unidade
		std::cout << y[j] << "\n";
	}
}
void CPermeabilidadeabs::RegressaoLinear() {
	arma::Col<double> x1 = arma::Col<double>(x); //Conversão dos parâmetros x para Armadillo
	arma::Col<double> y1 = arma::Col<double>(y); //Conversão dos parâmetros y para Armadillo
	auto d = arma::polyfit(x1, y1, 1); //f = ax+b; d é o polinômio de ajuste
	permeabilidade = d.eval()(0); // retirando o coeficiente A do pol. de ajuste
	std::cout << "Permeabilidade absoluta do plug: " << permeabilidade << " mD\n";
	//float b = d.eval()(1); //retirando o coeficiente B do pol. de ajuste
	//std::cout << permeabilidade << " " << d.eval()(1);

	std::vector<double> x2; //criando 
	std::vector<double> y2; //criando
	for (int i = 0; i < x.size(); i++) {
		x2.push_back(x[i]);
		y2.push_back(y[i]);
	}
	//Aparecer a equação da reta no gráfico - PlotVector não rodou.
	std::string eqreta = "y = " + std::to_string(permeabilidade) + "x +" + std::to_string(d.eval()(1));
	CGnuplot plot;
	std::ofstream tmpfile("myfile4.txt");
	for (int i = 0; i < x2.size(); i++) {
		tmpfile << x2[i] << "	" << y2[i] << '\n';
	}
	tmpfile.close();
	plot << "set title \"Permeabilidade Absoluta - BEREA6\"";
	plot << "set xlabel \"X\"";
	plot << "set ylabel \"Vazão\"";
	plot << "plot 'myfile4.txt' title \"" + eqreta + "\" with lines";
	//plot << "set legend \"Series1\"";
	std::cout << "Pressione uma tecla para continuar"; std::cin.get(); std::cout << '\n';
	system("erase myfile4.txt");
}



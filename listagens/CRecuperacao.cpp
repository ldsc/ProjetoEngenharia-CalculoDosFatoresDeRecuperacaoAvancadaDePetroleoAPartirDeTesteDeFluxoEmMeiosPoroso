#include "CRecuperacao.h"

CRecuperacao::CRecuperacao(CRocha _rocha) {
	rocha = _rocha;
}

double CRecuperacao::gVwi() { return VolumeAguaInicial; }
void CRecuperacao::sVwi(double Vwi) { VolumeAguaInicial = Vwi; }

double CRecuperacao::gVwf() { return VolumeAguaProduzida; }
void CRecuperacao::sVwf(double Vwf) { VolumeAguaProduzida = Vwf; }

double CRecuperacao::gVof() { return VolumeOleoProduzido1; }
void CRecuperacao::sVof(double Vof1) { VolumeOleoProduzido1 = Vof1; }

double CRecuperacao::gVor() { return VolumeOleoProduzido2; }
void CRecuperacao::sVor(double Vof2) { VolumeOleoProduzido2 = Vof2; }

std::string CRecuperacao::gTF() { return tipoFluido; }
void CRecuperacao::sTF(std::string tF) { tipoFluido = tF; }

double CRecuperacao::VolumeOleoInicial() {
	return VolumeAguaProduzida;
}
double CRecuperacao::SaturacaoAguaInicial() {
	return (VolumeAguaInicial / rocha.VolumePoroso())*100.0;
}
double CRecuperacao::SaturacaoOleoInicial() {
	return (VolumeOleoInicial() / rocha.VolumePoroso())*100.0;
}
double CRecuperacao::SaturacaoAguaIrredutivel() {
    return ((VolumeAguaInicial - VolumeAguaProduzida) / rocha.VolumePoroso())*100.0;
}
double CRecuperacao::VolumeOleoResidual() {
	return VolumeOleoInicial() - VolumeOleoProduzido1;
}
double CRecuperacao::SaturacaoOleoResidual() {
	return (VolumeOleoResidual() / rocha.VolumePoroso())*100.0;
}
double CRecuperacao::FatorRecuperacaoSecundadria() {
	return (VolumeOleoProduzido1 / VolumeOleoInicial())*100.0;
}
double CRecuperacao::FatorRecuperacaoAvancada() {
	return (VolumeOleoProduzido2 / VolumeOleoInicial())*100.0;
}
double CRecuperacao::VolumeTotalProduzido() {
	return VolumeOleoProduzido1 + VolumeOleoProduzido2;
}
double CRecuperacao::FatorRecuperacaoTotal() {
	return (VolumeTotalProduzido() / VolumeOleoInicial())*100.0;
}
///Leitura do arquivo de texto: "experimento.recuperacao.txt".
void CRecuperacao::Read(std::string arq) {
	std::ifstream fin(arq);
	if (!fin.good()) {
		std::cerr << "Erro na leitura do arquivo";
	}
	double d;
	fin.ignore(5000, '\n'); //Ignorando as primeiras linhas do arquivo .txt que contem cabecario
	fin.ignore(5000, '\n');
	while (!fin.eof()) {
		fin >> d; //eu quero esse
		t_volume_agua_produzida.push_back(d);
		fin >> d;
		fin >> d; 
		fin >> d;
		volume_oleo_produzido_rsecundaria.push_back(d);
		fin >> d;
		fin >> d; 
		t_volume_oleo_produzido_rsecundaria.push_back(d);
		fin >> d;
		fin >> d;
		volume_agua_produzida.push_back(d);
		fin >> d; 
		fin >> d;
		fin >> d; 
		t_volume_oleo_produzido_ravancada.push_back(d);
		fin >> d;
		fin >> d;
		fin >> d; 
		volume_oleo_produzido_ravancada.push_back(d);
		fin >> d;
		fin.ignore(5000, '\n');
	}
	t_volume_agua_produzida.pop_back();
	t_volume_oleo_produzido_rsecundaria.pop_back();
	t_volume_oleo_produzido_ravancada.pop_back();
	volume_agua_produzida.pop_back();
	volume_oleo_produzido_rsecundaria.pop_back();
	volume_oleo_produzido_ravancada.pop_back();
	//fiz isso para tirar o 20.3
}
void CRecuperacao::VwProduzida() {
	CGnuplot plot;
	std::ofstream tmpfile("myfile1.txt");
	for (int i = 0; i < t_volume_agua_produzida.size(); i++) {
			tmpfile << t_volume_agua_produzida[i] << "	" << volume_agua_produzida[i] << '\n';
	}
	tmpfile.close();
	plot << "set title \"Vol. Água Produzida Acumulada - BEREA\"";
	plot << "set xlabel \"Tempo (min)\"";
	plot << "set ylabel \"Volume de Água (ml)\"";
	plot << "plot 'myfile1.txt' with lines";
	std::cout << "Pressione uma tecla para continuar"; std::cin.get(); std::cout << '\n';
	system("erase myfile1.txt");
}
void CRecuperacao::VoProduzido1() {
	CGnuplot plot;
	std::ofstream tmpfile("myfile2.txt");
	for (int i = 0; i < t_volume_oleo_produzido_rsecundaria.size(); i++) {
		tmpfile << t_volume_oleo_produzido_rsecundaria[i] << "	" << volume_oleo_produzido_rsecundaria[i] << '\n';
	}
	tmpfile.close();
	plot << "set title \"Vol. Óleo Produzido por Recuperação Secundária\"";
	plot << "set xlabel \"Tempo (min)\"";
	plot << "set ylabel \"Volume de Óleo (ml)\"";
	plot << "plot 'myfile2.txt' with lines";
	std::cout << "Pressione uma tecla para continuar"; std::cin.get(); std::cout << '\n';
	system("erase myfile2.txt");
}
void CRecuperacao::VoProduzido2() {
	CGnuplot plot;
	std::ofstream tmpfile("myfile3.txt");
	for (int i = 0; i < t_volume_oleo_produzido_ravancada.size(); i++) {
		//std::cout << t_volume_oleo_produzido_ravancada[i] << "	" << volume_oleo_produzido_ravancada[i] << '\n';
		tmpfile << t_volume_oleo_produzido_ravancada[i] << "	" << volume_oleo_produzido_ravancada[i] << '\n';
	}
	tmpfile.close();
	plot << "set title \"Vol. Óleo Produzido por Recuperação Avançada\"";
	plot << "set xlabel \"Tempo (min)\"";
	plot << "set ylabel \"Volume de Óleo (ml)\"";
	plot << "plot 'myfile3.txt' with lines";
	std::cout << "Pressione uma tecla para continuar"; std::cin.get(); std::cout << '\n';
	system("erase myfile3.txt");
}
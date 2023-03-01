#pragma once
#ifndef CRecuperacao_h
#define CRecuperacao_h
#include <string>
#include <iostream>
#include "CRocha.h"
#include <fstream>
#include <vector>
#include "CGnuplot.h"

class CRecuperacao
{
protected:
	//typedef std::vector<double> vetor - apelido para o vetor.
	std::vector<double> t_volume_agua_produzida;
	std::vector<double> t_volume_oleo_produzido_rsecundaria;
	std::vector<double> t_volume_oleo_produzido_ravancada;

	std::vector<double> volume_agua_produzida;
	std::vector<double> volume_oleo_produzido_rsecundaria;
	std::vector<double> volume_oleo_produzido_ravancada;

	std::string tipoFluido;
	double VolumeAguaInicial;
	double VolumeAguaProduzida;
	double VolumeOleoProduzido1;
	double VolumeOleoProduzido2;
	CRocha rocha;

public:
	CRecuperacao() {};
	~CRecuperacao() {};
	///Construtor Sobrecarregado
	CRecuperacao(CRocha _rocha);

	double gVwi();
	void sVwi(double Vwi);

	double gVwf();
	void sVwf(double Vwf);

	double gVof();
	void sVof(double Vof1);

	double gVor();
	void sVor(double Vof2);
	
	std::string gTF();
	void sTF(std::string tF);

	double VolumeOleoInicial();
	double SaturacaoAguaInicial();
	double SaturacaoOleoInicial();
	double SaturacaoAguaIrredutivel();
	double VolumeOleoResidual();
	double SaturacaoOleoResidual();
	double FatorRecuperacaoSecundadria();
	double FatorRecuperacaoAvancada();
	double VolumeTotalProduzido();
	double FatorRecuperacaoTotal();
	void Read(std::string arq); //método para ler o arquivo
	void VwProduzida();
	void VoProduzido1();
	void VoProduzido2();
};
#endif


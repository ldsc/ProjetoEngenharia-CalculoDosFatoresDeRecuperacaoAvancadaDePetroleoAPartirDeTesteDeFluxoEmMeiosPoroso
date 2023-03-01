// ProjetoBuenoLaisa.cpp : Este arquivo contem a funcao 'main'. 

#include <iostream>
#include <fstream>
#include "CFluido.h"
#include "CRocha.h"
#include "CPermeabilidadeabs.h"
#include "CGnuplot.h"
#include "CRecuperacao.h"
#include <string>

using namespace std;
int main()
{	
	std::cout << "###########################################################\n";
	std::cout << "###########################################################\n";
	std::cout << "LENEP/UENF - Programacao Pratica\n";
	std::cout << "Calculo dos Fatores de Recuperacao de Oleo para Metodos EOR\n";
	std::cout << "Teste de Fluxo em Meio Poroso - Recuperacao Avancada\n";
	std::cout << "Nome: Laisa Rigueti Brasil \n";
	std::cout << "###########################################################\n";
	std::cout << "###########################################################\n";
	std::cout << "\n";
	double d1; double d2; double d3;
	std::cout << "Entre com os dados da Rocha:\n";
	std::cout << "Entre com tres medidas de diametro em mm:\n";
	std::cout << "Diametro (1/3): "; cin >> d1; cin.get(); std::cout << "\n";
	std::cout << "Diametro (2/3): "; cin >> d2; cin.get(); std::cout << "\n";
	std::cout << "Diametro (3/3): "; cin >> d3; cin.get(); std::cout << "\n";
	double d_medio = (d1 + d2 + d3) / 3;
	double c1; double c2; double c3;
	std::cout << "Entre com tres medidas de comprimento em mm:\n";
	std::cout << "Comprimento (1/3): "; cin >> c1; cin.get(); std::cout << "\n";
	std::cout << "Comprimento (2/3): "; cin >> c2; cin.get(); std::cout << "\n";
	std::cout << "Comprimento (3/3): "; cin >> c3; cin.get(); std::cout << "\n";
	double c_medio = (c1 + c2 + c3) / 3;
	double p_mo;
	std::cout << "\n";
	std::cout << "Entre com o peso da amostra saturada com o fluido em g:\n";
	std::cout << "Peso molhada: "; cin >> p_mo; cin.get(); std::cout << "\n";
	double p_se;
	std::cout << "Entre com o peso da amostra seca em g:\n";
	std::cout << "Peso seca: "; cin >> p_se; cin.get(); std::cout << "\n";
	std::cout << "\n";
	std::cout << "##########################################################\n";
	std::cout << "Resumo dos dados de entrada da amostra (plug):\n";
	std::cout << "Diametro medio: " << d_medio << " mm" << '\n';
	std::cout << "Comprimento medio: " << c_medio << " mm" << '\n';
	std::cout << "Peso molhada: " << p_mo << " g" << '\n';
	std::cout << "Peso seca " << p_se << " g" << '\n';
	CRocha berea6("Arenito", d_medio, c_medio, p_se, p_mo); 	//Construtor Sobrecarregado
	std::cout << "Area: " << berea6.Area() << " mm^2" << '\n';
	std::cout << "Volume Total: " << berea6.VolumeTotal() << " mm^3" << '\n';
	std::cout << "Volume Poroso: " << berea6.VolumePoroso() << " mL" << '\n';
	std::cout << "Porosidade: " << berea6.Porosidade() << '\n';
	std::cout << "##########################################################\n";
	std::cout << "\n";

	std::cout << "Calcularemos agora da Permeabilidade absoluta do meio poroso:\n";
	double visc; double q_inj;
	std::cout << "Entre com os dados do Fluido.\n";
	std::cout << "Entre com a vazao de injecao em mL/min\n";
	std::cout << "Vazao de injecao: "; cin >> q_inj; cin.get(); std::cout << '\n';
	std::cout << "Entre com a viscosidade do fluido em cP\n";
	std::cout << "Viscosidade: "; cin >> visc; cin.get(); std::cout << '\n';

	std::cout << "##########################################################\n";
	std::cout << "Resumo do dados de entrada do fluido\n";
	std::cout << "Vazao de injecao: " << q_inj << '\n';
	std::cout << "Viscosidade: " << visc << '\n';
	std::cout << "##########################################################\n";
	CFluido brine("Brine", visc, q_inj);

	std::cout << "Entre com as vazoes utilizadas no experimento de Perm.Absoluta para criacao do grafico\n";
	double q1; double q2; double q3;
	std::cout << "Entre com tres medidas de vazao em mL/min\n";
	std::cout << "Vazao (1/3): "; cin >> q1; cin.get(); std::cout << '\n';
	std::cout << "Vazao (2/3): "; cin >> q2; cin.get(); std::cout << '\n';
	std::cout << "Vazao (3/3): "; cin >> q3; cin.get(); std::cout << '\n';
	std::cout << "\n";
	std::cout << "Entre com as pressoes utilizadas no experimento de Perm.Absoluta para criacao do grafico\n";
	double p1; double p2; double p3;
	std::cout << "Entre com tres medidas de pressao em psia\n";
	std::cout << "Pressao (1/3): "; cin >> p1; cin.get(); std::cout << '\n';
	std::cout << "Pressao (2/3): "; cin >> p2; cin.get(); std::cout << '\n';
	std::cout << "Pressao (3/3): "; cin >> p3; cin.get(); std::cout << '\n';
	std::vector<double> vaz = { q1,q2,q3 };
	std::vector<double> pre = { p1,p2,p3 };
	std::cout << "##########################################################\n";
	CPermeabilidadeabs exp1(vaz, pre, berea6, brine);
	exp1.RegressaoLinear();
	std::cout << "##########################################################\n";
	std::cout << "\n";

	std::cout << "Calcularemos agora os Fatores de Recuperacao de Oleo:\n";
	CRecuperacao r1 (berea6);
	std::string arq;
	std::cout << "Entre com o nome do arquivo contendo os dados do experimento de Recuperacao (.txt): "; cin >> arq; cin.get(); std::cout << '\n';
	r1.Read(arq);
	while (true) {
		int resp;
		std::cout << "Escolha o grafico de volume produzido a ser gerado: \n";
		std::cout << "1 - Volume de Agua Produzida Acumulada\n";
		std::cout << "2 - Volume de Oleo Recuperado com metodo secundario\n";
		std::cout << "3 - Volume Adicional de Oleo Recuperado com metodo EOR\n";
		std::cout << "4 - Sair da selecao do grafico\n";
		cin >> resp; cin.get();
		if (resp == 1) {
			r1.VwProduzida();
		}
		else if (resp == 2) {
			r1.VoProduzido1();
		}
		else if (resp == 3) {
			r1.VoProduzido2();
		}
		else if (resp == 4) break;
		else std::cout << "Entrada invalida\n";
	}
	double aux;
	std::cout << "Entre com os dados da Recuperacao:\n";
	std::cout << "Volume de Agua Inicial (Recuperacao Secundaria): "; cin >> aux; cin.get(); r1.sVwi(aux); std::cout << '\n';
	std::cout << "Volume de Agua Produzida (Recuperacao Secundaria): "; cin >> aux; cin.get(); r1.sVwf(aux); std::cout << '\n';
	std::cout << "Volume de Oleo Produzido (Recuperacao Secundaria): "; cin >> aux; cin.get(); r1.sVof(aux); std::cout << '\n';
	std::cout << "Volume de Oleo Produzido (Recuperacao Avancada): "; cin >> aux; cin.get(); r1.sVor(aux); std::cout << '\n';
	
	std::cout << "Dados da Recuperacao\n";
	std::cout << "Volume de Oleo Inicial: " << r1.VolumeOleoInicial() << " mL" << '\n';
	std::cout << "Saturacao de Oleo Inicial: " << r1.SaturacaoOleoInicial() << " %" << '\n';
	std::cout << "Saturacao de Agua Irredutivel: " << r1.SaturacaoAguaIrredutivel() << " %" << '\n';
	std::cout << "Fator Recuperacao Secundaria: " << r1.FatorRecuperacaoSecundadria() << " %" << '\n';

	std::cout << "Saturacao de Oleo Residual: " << r1.SaturacaoOleoResidual() << " %" << '\n';
	std::cout << "Volume de Oleo Residual: " << r1.VolumeOleoResidual() << " mL" << '\n';
	std::cout << "Fator Recuperacao Avancada: " << r1.FatorRecuperacaoAvancada() << " %" << '\n';

	std::cout << "Fator Recuperacao Total: " << r1.FatorRecuperacaoTotal() << " %" << '\n';

	std::ofstream out; // 
	std::ofstream fout("Resultados.txt");
	fout << "Resultados do Software:\n";
	fout << "\n";
	fout << "#############################################################################\n";
	fout << "Resumo dos dados de entrada da amostra (plug):\n";
	fout << "Diametro medio: " << d_medio << " mm" << '\n';
	fout << "Comprimento medio: " << c_medio << " mm" << '\n';
	fout << "Peso molhada: " << p_mo << " g" << '\n';
	fout << "Peso seca " << p_se << " g" << '\n';
	fout << "#############################################################################\n";
	fout << "Resumo das propriedades do meio poroso (plug):\n";
	fout << "Area: " << berea6.Area() << " mm^2" << '\n';
	fout << "Volume Total: " << berea6.VolumeTotal() << " mm^3" << '\n';
	fout << "Volume Poroso: " << berea6.VolumePoroso() << " mL" << '\n';
	fout << "Porosidade: " << berea6.Porosidade() << '\n';
	fout << "#############################################################################\n";
	fout << "Resultado dos Fatores de Recuperacao à partir de Testes de Fluxo em Meio Poroso:\n";
	fout << "Volume de Oleo Inicial: " << r1.VolumeOleoInicial() << " mL" << '\n';
	fout << "Saturacao de Oleo Inicial: " << r1.SaturacaoOleoInicial() << " %" << '\n';
	fout << "Saturacao de Agua Irredutivel: " << r1.SaturacaoAguaIrredutivel() << " %" << '\n';
	fout << "Fator Recuperacao Secundaria: " << r1.FatorRecuperacaoSecundadria() << " %" << '\n';
	fout << "Saturacao de Oleo Residual: " << r1.SaturacaoOleoResidual() << " %" << '\n';
	fout << "Volume de Oleo Residual: " << r1.VolumeOleoResidual() << " mL" << '\n';
	fout << "Fator Recuperacao Avancada: " << r1.FatorRecuperacaoAvancada() << " %" << '\n';
	fout << "\n";
	fout << "Fator Recuperacao Total: " << r1.FatorRecuperacaoTotal() << " %" << '\n';
	out.close();

	std::cout << "Pressione uma tecla para continuar"; std::cin.get(); std::cout << '\n';

}

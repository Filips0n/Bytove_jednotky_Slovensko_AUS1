#pragma once
#include <string>
#include <iostream>
#include "heap_monitor.h"
#include <iomanip>
using namespace std;

class ObecData {
private:
	string nazov;
	int predProdObyv;
	int prodObyv;
	int poProdObyv;
	double vymera;
	double zastPlocha;
public:
	ObecData(string nazov, int predProdObyv, int prodObyv, int poProdObyv, double vymera, double zastPlocha)
	{
		this->nazov = nazov;
		this->predProdObyv = predProdObyv;
		this->prodObyv = prodObyv;
		this->poProdObyv = poProdObyv;
		this->vymera = vymera;
		this->zastPlocha = zastPlocha;
	}

	string getNazov() { return nazov; };
	int getPredProdObyv() { return predProdObyv; };
	int getProdObyv() { return prodObyv; };
	int getPoProdObyv() { return poProdObyv; };
	int getPocetObyv() {return predProdObyv + prodObyv + poProdObyv; };
	double getVymera() { return vymera; };
	double getZastPlocha() { return zastPlocha; };
};
#pragma once
#include "KriteriumUJ.h"
#include "KUJZastavanaPlocha.h"
#include "KUJCelkovaVymera.h"
class KUJZastavanost : public KriteriumUJ<double>
{
public:
	double operator()(UzemnaJednotka* uzemnaJednotka) { 
		KUJZastavanaPlocha kzp;
		KUJCelkovaVymera kcv;
		return 100*(kzp.operator()(uzemnaJednotka)/kcv.operator()(uzemnaJednotka));
	};
};

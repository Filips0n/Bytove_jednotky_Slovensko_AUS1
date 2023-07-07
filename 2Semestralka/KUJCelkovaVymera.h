#pragma once
#include "KriteriumUJ.h"
class KUJCelkovaVymera : public KriteriumUJ<double>
{
public:
	double operator()(UzemnaJednotka* uzemnaJednotka) {
		double vymera = 0;
		if (TypUzemnejJednotky::OBEC == uzemnaJednotka->getTyp())
		{
			vymera = uzemnaJednotka->getObecData()->getVymera();
		}
		else {
			for (auto* x : *(uzemnaJednotka->getNizsieUzeJedn()))
			{
				if (TypUzemnejJednotky::OKRES == uzemnaJednotka->getTyp()) {
					vymera += x->accessData()->getObecData()->getVymera();
					continue;
				}
				for (auto* y : *(x->accessData()->getNizsieUzeJedn()))
				{
					if (TypUzemnejJednotky::KRAJ == uzemnaJednotka->getTyp()) {
						vymera += y->accessData()->getObecData()->getVymera();
						continue;
					}
					for (auto* z : *(y->accessData()->getNizsieUzeJedn()))
					{
						if (TypUzemnejJednotky::STAT == uzemnaJednotka->getTyp()) {
							vymera += z->accessData()->getObecData()->getVymera();
							continue;
						}
					}
				}
			}
		}
		return vymera;
	};
};

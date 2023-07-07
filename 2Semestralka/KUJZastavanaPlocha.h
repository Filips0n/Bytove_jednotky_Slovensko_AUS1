#pragma once
#include "KriteriumUJ.h"
class KUJZastavanaPlocha : public KriteriumUJ<double>
{
public:
	double operator()(UzemnaJednotka* uzemnaJednotka) {
		double zastPlocha = 0;
		if (TypUzemnejJednotky::OBEC == uzemnaJednotka->getTyp())
		{
			zastPlocha = uzemnaJednotka->getObecData()->getZastPlocha();
		}
		else {
			for (auto* x : *(uzemnaJednotka->getNizsieUzeJedn()))
			{
				if (TypUzemnejJednotky::OKRES == uzemnaJednotka->getTyp()) {
					zastPlocha += x->accessData()->getObecData()->getZastPlocha();
					continue;
				}
				for (auto* y : *(x->accessData()->getNizsieUzeJedn()))
				{
					if (TypUzemnejJednotky::KRAJ == uzemnaJednotka->getTyp()) {
						zastPlocha += y->accessData()->getObecData()->getZastPlocha();
						continue;
					}
					for (auto* z : *(y->accessData()->getNizsieUzeJedn()))
					{
						if (TypUzemnejJednotky::STAT == uzemnaJednotka->getTyp()) {
							zastPlocha += z->accessData()->getObecData()->getZastPlocha();
							continue;
						}
					}
				}
			}
		}
		return zastPlocha;
	};
};

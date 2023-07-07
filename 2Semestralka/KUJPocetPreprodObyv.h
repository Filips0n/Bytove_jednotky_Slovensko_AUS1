#pragma once
#include "KriteriumUJ.h"
class KUJPocetPredprodObyv : public KriteriumUJ<int>
{
public:
	int operator()(UzemnaJednotka* uzemnaJednotka) {
		int pocetObyv = 0;
		if (TypUzemnejJednotky::OBEC == uzemnaJednotka->getTyp())
		{
			pocetObyv = uzemnaJednotka->getObecData()->getPredProdObyv();
		}
		else {
			for (auto* x : *(uzemnaJednotka->getNizsieUzeJedn()))
			{
				if (TypUzemnejJednotky::OKRES == uzemnaJednotka->getTyp()) {
					pocetObyv += x->accessData()->getObecData()->getPredProdObyv();
					continue;
				}
				for (auto* y : *(x->accessData()->getNizsieUzeJedn()))
				{
					if (TypUzemnejJednotky::KRAJ == uzemnaJednotka->getTyp()) {
						pocetObyv += y->accessData()->getObecData()->getPredProdObyv();
						continue;
					}
					for (auto* z : *(y->accessData()->getNizsieUzeJedn()))
					{
						if (TypUzemnejJednotky::STAT == uzemnaJednotka->getTyp()) {
							pocetObyv += z->accessData()->getObecData()->getPredProdObyv();
							continue;
						}
					}
				}
			}
		}
		return pocetObyv;
	};
};

#pragma once
#include "KriteriumUJ.h"
class KUJPrislusnost : public KriteriumUJ<bool>
{
private:
	UzemnaJednotka* vyssiaUJ;
public:
	KUJPrislusnost(UzemnaJednotka* vyssiaUJ) {
		this->vyssiaUJ = vyssiaUJ;
	}
	bool operator()(UzemnaJednotka* uzemnaJednotka) { 
		if (uzemnaJednotka->getVyssiaUzemJedn() == nullptr)
		{
			return true;
		}
		for (UzemnaJednotka* vyssia = uzemnaJednotka->getVyssiaUzemJedn(); vyssia != nullptr; vyssia = vyssia->getVyssiaUzemJedn()) {
			if (vyssia->getNazov() == vyssiaUJ->getNazov()) { return true; };
		}
		return false;
	};
};

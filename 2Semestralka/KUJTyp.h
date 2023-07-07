#pragma once
#include "KriteriumUJ.h"
class KUJTyp : public KriteriumUJ<TypUzemnejJednotky>
{
public:
	TypUzemnejJednotky operator()(UzemnaJednotka* uzemnaJednotka) { return uzemnaJednotka->getTyp(); };
};

#pragma once
#include "KriteriumUJ.h"
class KUJNazov: public KriteriumUJ<std::string>
{
public:
	std::string operator()(UzemnaJednotka* uzemnaJednotka) { return uzemnaJednotka->getNazov(); };
};

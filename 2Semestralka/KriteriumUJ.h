#pragma once
#include "Kriterium.h"
#include "UzemnaJednotka.h"

template<typename T>
class KriteriumUJ : public Kriterium<T, UzemnaJednotka>
{
public:
	virtual T operator()(UzemnaJednotka* uzemnaJednotka) = 0;
};

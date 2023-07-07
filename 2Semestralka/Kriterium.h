#pragma once
#include "heap_monitor.h"
template<typename T, typename O>
class Kriterium {
public:
	virtual T operator()(O* objekt) = 0;
};
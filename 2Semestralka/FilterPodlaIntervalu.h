#pragma once
#include "KriteriumUJ.h"
#include "Kriterium.h"
template<typename K, typename T, typename V>
class FilterPodlaIntervalu : public Filter<K, T, V>
{
private:
	V min;
	V max;
public:
	FilterPodlaIntervalu(Kriterium<V, T>* kriterium, V min, V max);
	bool splnaFilter(T* uzemnaJednotka);
};

template<typename K, typename T, typename V>
inline FilterPodlaIntervalu<K, T, V>::FilterPodlaIntervalu(Kriterium<V, T>* kriterium, V min, V max):
	Filter<K, T, V>(kriterium)
{
	this->min = min;
	this->max = max;
}

template<typename K, typename T, typename V>
inline bool FilterPodlaIntervalu<K, T, V>::splnaFilter(T* uzemnaJednotka)
{
	return this->kriterium->operator()(uzemnaJednotka) >= min && this->kriterium->operator()(uzemnaJednotka) <= max;
}

#pragma once
#include "KriteriumUJ.h"
#include "Kriterium.h"
template<typename K, typename T, typename V>
class FilterPodlaHodnoty : public Filter<K, T, V>
{
private:
	V hodnota;
public:
	FilterPodlaHodnoty(Kriterium<V, T> *kriterium, V hodnota);
	FilterPodlaHodnoty();
	bool splnaFilter(T *uzemnaJednotka);
};

template<typename K, typename T, typename V>
inline FilterPodlaHodnoty<K, T, V>::FilterPodlaHodnoty(Kriterium<V, T> *kriterium, V hodnota):
	Filter<K, T, V>(kriterium)
{	
	this->hodnota = hodnota;
}

template<typename K, typename T, typename V>
inline FilterPodlaHodnoty<K, T, V>::FilterPodlaHodnoty() {}

template<typename K, typename T, typename V>
inline bool FilterPodlaHodnoty<K, T, V>::splnaFilter(T *uzemnaJednotka)
{
	return this->kriterium->operator()(uzemnaJednotka) == hodnota;
}
